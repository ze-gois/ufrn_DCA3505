/*
    1. Prática: testar que paginação está ativa
    ● Acessar uma página que não está mapeada
    ● Declarar uma variável global
    ● Criar um ponteiro apontando para a variável mais 4MB
    ○ Certamente não está mapeado, já que só mapeamos os primeiros 4MB
    ● Tentar ler desse ponteiro
    ● Qual é o resultado?
    ● Qual é o resultado se paginação estiver desabilitada?
*/
#include "helper.h"

int main()
{
	puts("\nOlá mundo!\n");
	// for(;;);
}
