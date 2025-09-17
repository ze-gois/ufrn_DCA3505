Tarefa 2: Modo usuário e chamadas de sistema 	de 06/05/2025 às 00h00 a 22/06/2025 às 23h59 	Não 	28

Utilizando a linguagem C, escreva um programa simples que utilize a função write() da biblioteca padrão para imprimir uma mensagem na tela. Compile e execute o programa normalmente e, em seguida, utilize o comando strace para observar as chamadas de sistema realizadas durante a execução. Identifique no strace a chamada que realiza a escrita no terminal e observe qual mecanismo é utilizado para a transição entre o modo usuário e o modo kernel.


A seguir, reescreva o mesmo programa utilizando linguagem de montagem, implementando a chamada de sistema correspondente de forma manual (por exemplo, usando a instrução syscall). Compile e execute o código e, novamente, utilize strace para observar a diferença no fluxo de execução.

Responda:

    Qual é o papel da instrução syscall no programa em Assembly?
    O que muda na forma de execução entre o programa em C e o em Assembly?
    Por que é necessário utilizar chamadas de sistema para realizar tarefas simples como imprimir na tela?
    O que garante a transição segura entre os modos de execução? O que aconteceria se o modo usuário tivesse acesso direto aos dispositivos?

 Enviar relatório em PDF com no máximo 4 páginas ou 2000 palavras.
