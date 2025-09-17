#include <stdint.h>
#include <stdio.h>

struct Super {
    char assinatura[4];
    uint64_t n_arquivos;
    uint64_t tamanho_bloco;
} __attribute__((packed));

struct Arquivo {
    char nome[20];
    uint32_t bloco_inicial;
    uint64_t tamanho;
} __attribute__((packed));

int main () {
    printf("Size of struct SuperBloco: %zu bytes\n", sizeof(struct Super));
    printf("Size of struct Arquivo: %zu bytes\n", sizeof(struct Arquivo));

    return 0;
}
