Tarefa 3: Criação e identificação de processos 	de 06/05/2025 às 00h00 a 22/06/2025 às 23h59 	Não 	28

Escreva um programa em linguagem C que imprima na tela o identificador do processo atual (PID) e o identificador do processo pai (PPID), utilizando as funções getpid() e getppid(). Compile e execute o programa, e observe os valores exibidos. Em seguida, execute o programa múltiplas vezes e registre se os valores de PID e PPID permanecem os mesmos ou variam entre execuções. O que isso nos diz sobre a natureza dos processos?


A seguir, modifique o programa para que ele crie um novo processo utilizando a função fork(). O processo pai e o processo filho devem imprimir suas respectivas identificações, informando claramente quem é quem. Compile e execute o programa várias vezes, e analise os resultados.


Agora, utilize os comandos ps, top ou htop durante a execução do programa para observar os processos ativos. Tente identificar o processo pai e o filho em tempo real.


Responda:

    Qual é a diferença entre getpid() e getppid()? O que eles representam?
    O que acontece com o PID do processo filho após o fork()?
    Como o sistema operacional identifica e organiza os processos em execução?
    É possível prever quantas vezes o programa imprimirá mensagens após o fork()? Justifique.
    Por que o mesmo programa pode ter múltiplos processos com identidades distintas?

 Enviar relatório em PDF com no máximo 4 páginas ou 2000 palavras.
