Tarefa 6: Escalonamento de processos 	de 06/05/2025 às 00h00 a 22/06/2025 às 23h59 	Não 	26

Descubra o número de núcleos de CPU disponíveis no seu sistema utilizando o comando nproc. Com base nesse valor N, crie N processos idênticos que executem laços infinitos para consumir CPU continuamente. Utilize ferramentas como top, htop ou ps para observar como o sistema operacional distribui o uso da CPU entre esses processos. Registre o tempo de CPU consumido, o estado dos processos e verifique se todos recebem tratamento justo.

Em seguida, repita o experimento com N+1 processos. Observe como o sistema lida com a sobrecarga. Todos os processos continuam recebendo tempo de CPU de forma igualitária? Justifique com base nas observações.
Na etapa seguinte, altere a prioridade de um dos processos com o comando renice, atribuindo-lhe uma prioridade significativamente mais alta (menor valor de nice). Observe se o uso da CPU por esse processo muda e como isso afeta os demais.

Agora, reinicie o experimento com N processos de carga e adicione um processo adicional que apenas aguarde por entrada do teclado (bloqueado em read). Observe o comportamento desse processo em repouso e após uma entrada ser fornecida. Modifique sua prioridade e verifique se há impacto no uso da CPU.

Por fim, reflita sobre o comportamento observado e responda:

    O sistema distribuiu o tempo de CPU de forma justa nos diferentes cenários? Como isso está relacionado ao funcionamento do CFS?
    O que aconteceu quando a prioridade de um processo foi alterada? Por que isso ocorreu?
    Por que o processo bloqueado por entrada não utilizou CPU até receber dados?
    A mudança de prioridade afeta processos bloqueados? Por quê?
    Compare esse comportamento com o que seria esperado em algoritmos como FIFO, Round Robin e Shortest Job First (SJF).
    Qual é a vantagem do modelo do Linux em relação aos algoritmos tradicionais?

 Enviar relatório em PDF com no máximo 4 páginas ou 2000 palavras.
