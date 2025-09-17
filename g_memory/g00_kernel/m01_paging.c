// /*
//  1. Prática: habilitar paginação
//  ● Declarar a raiz, alinhada com 4096
//  ○ __attribute__((aligned(4096)))
//  ● Inicializar os primeiros 4MB com identidade, valor:
//  ○ (1 << 7) | (1 << 1) | (1 << 0)
//  ○ Página de 4MB, leitura/escrita,presente
//  ● Inicializar cr3 para apontar para a raiz
//  ○ set_cr3()
//  ● Habilitar páginas de 4MB
//  ○ Ligar bit 4 de cr4
//  ○ set_cr4(), get_cr4()
//  ● Habilitar paginação
//  ○ Ligar bit 31 de cr0
//  ○ set_cr0(), get_cr0()
//  ● Escrever "Paginação habilitada"
//  */
// #include "helper.h"
// #include <stdarg.h>
// #include <stdint.h>

// __attribute__((aligned(4096))) uint32_t raiz[1024];

// uint32_t b(int count, ...) {
//     uint32_t x = 0;
//     va_list args;
//     va_start(args, count);

//     for (int i = 0; i < count; i++) {
//         int v = va_arg(args, int);
//         x |= (1 << v);
//     }

//     va_end(args);
//     return x;
// }

// int main()
// {
//     puts("\n=====================================================\n");
//     puts("1. Prática: habilitar paginação\n");
//     // puts("● Declarar a raiz, alinhada com 4096\n");
//     // puts("○ __attribute__((aligned(4096)))\n");
//     // puts("● Inicializar os primeiros 4MB com identidade, valor:\n");
//     // puts("○ (1 << 7) | (1 << 1) | (1 << 0)\n");
//     puts("○ Página de 4MB, leitura/escrita,presente\n");
//     puts("● Inicializar cr3 para apontar para a raiz\n");
//     puts("○ set_cr3()\n");
//     puts("● Habilitar páginas de 4MB\n");
//     puts("○ Ligar bit 4 de cr4\n");
//     puts("○ set_cr4(), get_cr4()\n");
//     puts("● Habilitar paginação\n");
//     puts("○ Ligar bit 31 de cr0\n");
//     puts("○ set_cr0(), get_cr0()\n");
//     puts("● Escrever \"Paginação habilitada\"\n");

//     uint32_t heading = 4*1024*1024;
//     do {
//         raiz[heading] = (1 << 7) | (1 << 1) | (1 << 0);
//     } while (heading-- > 0);

// 	puts("\nOlá mundo!\n");
// 	// for(;;);
// }

#include "helper.h"
#include <stdarg.h>
#include <stdint.h>

__attribute__((aligned(4096))) uint32_t raiz[1024];

uint32_t b(int count, ...) {
    uint32_t x = 0;
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        int v = va_arg(args, int);
        x |= (1 << v);
    }

    va_end(args);
    return x;
}

int main()
{
    puts("\n=====================================================\n");
    puts("1. Prática: habilitar paginação\n");

    puts("● Inicializar os primeiros 4MB com identidade, valor:\n");
    puts("○ Página de 4MB, leitura/escrita, presente\n");

    raiz[0] = 0x00000000 | b(3, 7, 1, 0); // Identity mapping, PS|RW|P
    // Se quiser mapear todo espaço de 4GB:
    // for (uint32_t i = 0; i < 1024; i++) {
    //     raiz[i] = (i * 0x400000) | b(3, 7, 1, 0);
    // }

    puts("● Inicializar cr3 para apontar para a raiz\n");
    set_cr3((uint32_t)raiz);

    puts("● Habilitar páginas de 4MB\n");
    uint32_t cr4 = get_cr4();
    cr4 |= (1 << 4); // Set PSE (bit 4)
    set_cr4(cr4);

    puts("● Habilitar paginação\n");
    uint32_t cr0 = get_cr0();
    cr0 |= (1 << 31); // Set PG (bit 31)
    set_cr0(cr0);

    puts("● Escrever \"Paginação habilitada\"\n");
    puts("\nPaginação habilitada\n");

    for (;;) {}
}
