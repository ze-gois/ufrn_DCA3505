#define FUSE_USE_VERSION 31
#include <fuse.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct super {
    uint32_t assinatura;
    uint32_t tamanho_bloco;
    uint64_t nr_arquivos;
} __attribute__((packed));

struct arquivo {
    char nome[20];
    uint32_t bloco_inicial;
    uint64_t tamanho;
} __attribute__((packed));

static int mifs_getattr(const char *path, struct stat *stbuf,
                        struct fuse_file_info *fi)
{
    if (strcmp(path, "/teste.txt") != 0) {
        return -ENOENT;
    }

    *stbuf = (struct stat) {
        .st_mode = S_IFREG | 0444,
        .st_nlink = 1,
        .st_size = 10,
    };

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <imagem> <diretorio>\n", argv[0]);
        exit(1);
    }

    uint32_t fd = open(argv[1],O_RDONLY);
    struct stat st;
    fstat(fd,&st);
    size_t img_size = st.st_size;
    void *map = mmap(NULL,img_size, PROT_READ, MAP_PRIVATE, fd, 0);

    struct super *sb = (struct super *) map;

    // if (sb->assinatura != 0x5346494D)
    printf("\tsuper {\n");
    printf("\t\tassinatura: 0x%x\n",sb->assinatura);
    printf("\t\ttamanho do bloco: %d\n",sb->tamanho_bloco);
    printf("\t\tnumero de arquivos: %u\n",sb->nr_arquivos);
    printf("\t} super;\n");

    uint32_t block_size = sb->tamanho_bloco;

    struct arquivo *tabela = (struct arquivo *)((uint8_t *)map + block_size);

    static const struct fuse_operations mifs_ops = {
        .getattr = mifs_getattr,
    };

    struct fuse_args args = FUSE_ARGS_INIT(0, NULL);

    fuse_opt_add_arg(&args, argv[0]);
    fuse_opt_add_arg(&args, argv[2]);

    int fm = fuse_main(argc, argv, NULL, NULL);

    // Create mount directory if it doesn't exist
    struct stat st_mount;

    if (stat(argv[2], &st_mount) == -1) {
        if (errno == ENOENT) {
            if (mkdir(argv[2], 0755) != 0) {
                perror("Failed to create mount directory");
                munmap(map, img_size);
                close(fd);
                return 1;
            }
        } else {
            perror("Failed to check mount directory");
            munmap(map, img_size);
            close(fd);
            return 1;
        }
    }

    return fm;
    printf("\nMounting files...\n");
    for (uint64_t a = 0; a < sb->nr_arquivos; a++) {
        // Extract the filename (remove trailing spaces)
        char filename[21]; // +1 for null terminator
        memcpy(filename, tabela[a].nome, 20);
        filename[20] = '\0';

        // Find actual length of filename (remove trailing spaces)
        int name_len = 20;
        while (name_len > 0 && filename[name_len-1] == ' ') {
            name_len--;
        }
        filename[name_len] = '\0';

        // Calculate source data position
        uint8_t *src_data = (uint8_t *)map + (tabela[a].bloco_inicial * block_size);
        uint64_t file_size = tabela[a].tamanho;

        printf("[%d] Extracting '%s' (%lu bytes) from block %d\n",
               a, filename, file_size, tabela[a].bloco_inicial);

        // Create output filepath
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s",argv[2], filename);

        // Create and write to the output file
        int out_fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (out_fd == -1) {
            perror("Failed to create output file");
            continue;
        }

        // Write data to the file
        ssize_t written = write(out_fd, src_data, file_size);
        if (written == -1 || (uint64_t)written != file_size) {
            perror("Failed to write file data");
        } else {
            printf("  Successfully mounted: %s\n", filepath);
        }

        close(out_fd);
    }

    // Cleanup
    munmap(map, img_size);
    close(fd);
    printf("\nFile mounting complete!\n");
    return fm;
}
