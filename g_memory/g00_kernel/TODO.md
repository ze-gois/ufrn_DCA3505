1. Prática: rodar diretamente em uma máquina virtual
● Clonar repositório https://github.com/wedsonaf/metal_c.git
○ Por exemplo, git clone https://github.com/wedsonaf/metal_c.git
● Rodar
○ Por exemplo, make run
○ Expectativa: "Olá mundo"
○ Para sair: ctrl+a x

1. Prática: habilitar paginação
● Declarar a raiz, alinhada com 4096
○ __attribute__((aligned(4096)))
● Inicializar os primeiros 4MB com identidade, valor:
○ (1 << 7) | (1 << 1) | (1 << 0)
○ Página de 4MB, leitura/escrita,presente
● Inicializar cr3 para apontar para a raiz
○ set_cr3()
● Habilitar páginas de 4MB
○ Ligar bit 4 de cr4
○ set_cr4(), get_cr4()
● Habilitar paginação
○ Ligar bit 31 de cr0
○ set_cr0(), get_cr0()
● Escrever "Paginação habilitada"

1. Prática: testar que paginação está ativa
● Acessar uma página que não está mapeada
● Declarar uma variável global
● Criar um ponteiro apontando para a variável mais 4MB
○ Certamente não está mapeado, já que só mapeamos os primeiros 4MB
● Tentar ler desse ponteiro
● Qual é o resultado?
● Qual é o resultado se paginação estiver desabilitada?

1. Prática: mapear os 4MB seguintes aos primeiros
● Atualizar exemplo anterior
● Modificar raiz tal que
○ O segundo elemento (índice 1), aponte para o endereço físico 0
○ Ou seja, os endereços virtuais 0 - 4MB e 4MB - 8MB apontam para o mesmo endereço físico
● Mostrar o conteúdo dos dois ponteiros
● Modificar o valor
● Mostrar o conteúdo dos dois ponteiros

1. Prática: efeito na tabela de paginação ao ler
● Modificar o exemplo anterior
● Somente ler o conteúdo de ptr2
● Mostrar o valor de raiz[1] antes e depois da leitura
● Qual é o resultado?

1. Prática: efeito na tabela de paginação ao escrever
● Modificar o exemplo anterior
● Somente alterar o conteúdo de ptr2
● Mostrar o valor de raiz[1] antes e depois da escrita
● Qual é o resultado?

1. Prática: remover mapeamento
● Modificar prática anterior
● Ler o conteúdo de ptr2
● Remover o mapeamento
● Ler o conteúdo de ptr2 de novo
● Qual é o resultado esperado?
● Qual é o resultado real?

1. Prática: invalidar o buffer de mapeamento
● Modificar exemplo anterior
● Após remover o mapeamento, invalidar o TLB
○ Função invlpg()
● Qual é o resultado?

1. Prática: fazer a página ser somente leitura
● Modificar o exemplo anterior
● Ligar bit 16 em cr0
○ Para habilitar proteção em modo kernel também
● Mudar mapeamento para somente leitura
● Tentar modificar o conteúdo de ptr2

1. Prática: instalar tratador de exceção
● Baixar a última versão do repositório
○ Incluindo a função init_idt()
● Chamar a função init_idt()
○ Instala um tratador de exceção para falhas de paginação
● Qual é o resultado?

1. Prática: personalizar o tratador de exceção
● Implementar uma função com o seguinte nome e protótipo:
void page_fault_handler(struct state *s)
● Colocar um corpo que imprime "Falha de paginação"
● Qual é o resultado?

1. Desafio
● Recuperar a execução sem modificar raiz
● Solução específica para este programa

1. Prática: mostrar detalhes sobre as falhas
● Registrador cr2 (função get_cr2()) contém o endereço que falhou
● Campo eip da estrutura state é o endereço da instrução que falhou
● Campo error da estrutura state contém detalhes sobre a falha

1. Prática: paginação em 2 níveis
● Inicializar raiz[2] para apontar para um nó filho
○ Ou seja, usando páginas de 4KB
● Nó filho é todo zerado para começar
● Criar um ponteiro ptr3, 4MB à frente de ptr2
● Tentar ler o conteúdo de ptr3
● Qual é o resultado?

1. Prática: atualizar nó filho para dar acesso a ptr3
● Modificar o tratador de exceções
● Para mapear o endereço de ptr3
○ Apontar para a mesma página física que ptr1 e ptr2
● Outras entradas precisam continuar ausentes
● Mostrar o conteúdo de ptr1, ptr2 e ptr3

1. Prática: duas tabelas de paginação
● Criar uma segunda tabela de paginação
● Fazer ptr3 ser diferente em cada uma:
○ Um aponta para o primeiro bloco de 4MB, outro aponta para o segundo bloco
● Mostrar o conteúdo de ptr3 com cada tabela de paginação
