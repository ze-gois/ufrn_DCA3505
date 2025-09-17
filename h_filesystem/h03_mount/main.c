#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

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

int main() {

    uint32_t fd = open("./data/out1024.img",O_RDONLY);
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

    for (uint64_t a = 0; a < sb->nr_arquivos; a++){
        printf("%d > %.*s with %d bytes in block %d\n",a, 20,tabela[a].nome,tabela[a].tamanho,tabela[a].bloco_inicial);

        char filepath[222];
        snprintf(filepath, 222,"./mount/%s",tabela[a].nome);
        printf("%s\n",filepath);
    }

    close(fd);
    return 0;
}
