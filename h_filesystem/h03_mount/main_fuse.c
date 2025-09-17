#define FUSE_USE_VERSION 31
#include <fuse.h>
#include <stddef.h>
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

typedef struct cursor {
    int* file_descriptor;
    size_t* offset;
    void** map;
} cursor;

struct cursor* a(char* filepath) {
    struct cursor *c = malloc(sizeof(cursor));

    c->file_descriptor = malloc(sizeof(int));
    c->offset = malloc(sizeof(size_t));
    c->map = malloc(sizeof(void*));

    *c->file_descriptor = open(filepath, O_RDONLY);
    *c->offset = 0;

    struct stat st;

    fstat(*c->file_descriptor,&st);
    size_t img_size = st.st_size;
    *c->map = mmap(NULL,img_size, PROT_READ, MAP_PRIVATE, *c->file_descriptor, 0);

    return c;
}

void i(struct cursor* c){
    printf("{{%d, %zu, %lu }}\n",*c->file_descriptor, *c->offset, (uint64_t)(*c->map));
}

int s(int offset, struct cursor* c){
    struct stat st;

    fstat(*c->file_descriptor,&st);
    size_t img_size = st.st_size;

    int offset_surrogate = ((int) *c->offset) + offset;

    return (offset_surrogate < 0) ? -1 : (offset_surrogate > img_size ? -2 : (*c->offset = offset_surrogate));
    return 0;
}

void* j(struct cursor* c){
    return (void *)((uint8_t *) *c->map + *c->offset);
}

struct cursor* b(struct cursor* c){
    struct cursor *b = malloc(sizeof(cursor));

    b->file_descriptor = malloc(sizeof(int));
    b->offset = malloc(sizeof(size_t));
    b->map = malloc(sizeof(void*));

    *b->file_descriptor = *c->file_descriptor;
    *b->offset = *c->offset;
    *b->map = *c->map;

    return b;
}

int teardown(struct cursor* c){
    struct stat st;
    fstat(*c->file_descriptor,&st);
    size_t img_size = st.st_size;
    munmap(*c->map, img_size);
    free(c->map);

    free(c->offset);

    close(*c->file_descriptor);
    free(c->file_descriptor);

    free(c);

    return 0;
}

int read_super(void *map_pointer) {

    return 0;
}

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

    struct stat st_mount;
    if (stat(argv[2], &st_mount) == -1) {
        if (errno == ENOENT) {
            if (mkdir(argv[2], 0755) != 0) {
                perror("Failed to create mount directory");
                return 1;
            }
        } else {
            perror("Failed to check mount directory");
            return 1;
        }
    }

    static const struct fuse_operations mifs_ops = {
        .getattr = mifs_getattr,
    };

    struct fuse_args args = FUSE_ARGS_INIT(0, NULL);

    fuse_opt_add_arg(&args, argv[0]);
    fuse_opt_add_arg(&args, argv[2]);

    int fm = fuse_main(argc, argv, NULL, NULL);

    return fm;

    char * filepaths[4] = {
        "./data/out1024.img",
        "./data/out2048.img",
        "./data/out4096.img",
        "./data/out512.img"
    };

    for (size_t f = 0 ; f < 4; f++){
        struct cursor* cursor = a(filepaths[f]);
        struct super* sb = (struct super*) j(cursor);
        printf("\t%d (0x%x)",sb->assinatura,sb->assinatura);
        printf(" %d",sb->tamanho_bloco);
        printf(" %lu",sb->nr_arquivos);
        printf("\n");
        s(sb->tamanho_bloco, cursor);
        struct arquivo* tabela = (struct arquivo*) j(cursor);
        for(size_t f = 0; f < sb->nr_arquivos; f++) {
            struct cursor* below = b(cursor);
            *below->offset &= ~*below->offset;

            // struct arquivo* arquivo = (struct arquivo*) j(cursor);
            printf("\n");
            printf("\t%ld",sizeof(struct arquivo));
            printf(" 0x%lx",(uint64_t)(tabela+f));
            // printf(" 0x%lx",(uint64_t)(arquivo+f));
            printf(" %s",tabela[f].nome);
            printf(" %d",tabela[f].bloco_inicial);
            printf(" %lu",tabela[f].tamanho);
            printf("\n");

            s(tabela[f].bloco_inicial*sb->tamanho_bloco,below);

            char* content = malloc(sizeof(char)*tabela[f].tamanho);
            memcpy(content, (char *) j(below), tabela[f].tamanho);

            size_t number_of_nl = 0;
            size_t g = 0;
            while (*(content + g) != '\0') {
                if (*(content + g) == '\n') number_of_nl++;
                g++;
            }

            size_t* nl_index = malloc(sizeof(size_t)*number_of_nl*2);

            g = 0;
            size_t i = 0;
            *nl_index = 0;
            while (*(content + g) != '\0') {
                if (*(content + g) == '\n') {
                    *(nl_index+1+i*2) = g;
                    printf("[%zu, %zu]",*(nl_index+i*2),*(nl_index+1+i*2));
                    i = i+1;
                    *(nl_index+i*2) = g+1;
                }
                g++;
            }

            char** lines = malloc(sizeof(char*)*number_of_nl);

            printf("\n");
            for (i = 0; i < number_of_nl; i++){
                char* line = *(lines+i);
                size_t l0 = *(nl_index+0+i*2);
                size_t lf = *(nl_index+1+i*2);
                size_t line_length = lf-l0;

                line = malloc(sizeof(char) * line_length+1);

                memcpy(line,content+l0,line_length);

                *(line+line_length) = '\0';

                printf("\t^%s\n",line);
            }

            printf(">%s",*(lines+1));

            // for(i = 0; i< number_of_nl; i++){
            //     free(*(lines+i));
            // }

            free(lines);
            free(nl_index);
            free(content);
            // teardown(below);
        }
        teardown(cursor);
    }

    printf("\nFile mounting complete!\n");
    return 0;
}
