#include <stdio.h>

/*
Sem necessitar de argumentos para a sua execução, a função criar_log() cria um ponteiro FILE que aponta para
o arquivo "log.txt", criando um novo arquivo ou apenas apagando oque já estiver escrito no caso de já existir.
Após a tentativa de abrir o arquivo, a função verifica se o ponteiro arqv é NULL. 
Isso indica que houve um erro na abertura do arquivo (por exemplo, problemas de permissão de escrita, ou o diretório não existir).
Se o arquivo não puder ser aberto, a função executa exit(1), o que termina imediatamente a execução do programa. O valor 1 passado para exit() indica um código de erro.

Ao final de tudo, retornará esse ponteiro que aponta para o aquivo "log.txt".
*/
FILE* criar_log();
 


/* 
Sem necessitar de argumentos para a sua execução, a função abrir_log() tem como objetivo abrir um arquivo de log chamado log.txt em modo de acréscimo ("a"). 
Esse modo permite adicionar dados ao final do arquivo sem sobrescrever o conteúdo existente. Caso o arquivo não possa ser aberto (por exemplo, se houver problemas de permissão ou o diretório não existir), a função termina o programa com um código de erro. 
Caso contrário, ela retorna o ponteiro para o arquivo aberto, permitindo que o usuário realize operações de escrita ou leitura no arquivo de log.
*/
FILE* abrir_log();



/*
Sem necessitar de argumentos para a sua execução, utilizando da biblioteca <time.h>, a função registra_horario() registra 
no arquivo "log.txt" a data e o horário exatos do momento em que a funcao foi executada. 
É registrado, em inglês, na seguinte ordem: dia da semana, mês, dia do mês, horário(horas:minutos,segundos) e o ano.

Exemplo de registro:
    "Data e horario do inicio da partida: Fri Nov 15 14:11:01 2024"
*/
void registra_horario();



/*
Argumentos: o tamanho da matriz, as coordenadas x e y escolhidas pelo usuaário, o endereco da matriz de char que é
impressa para o usuario.

A funcao registra_interacao_com_usuario() registra no arquivo "log.txt" as mudancas na matriz de char ao decorrer da partida
juntamente das coordenadas escolhidas pelo usuário.

Exemplo de registro:

Escolha a dificuldade do jogo!!
Digite: 
[1] -> Facil || [2] -> Medio || [3] -> Dificil

1

   1  2  3  4  5  6  7  8  9  10 
1  x  x  x  x  x  x  x  x  x  x  
2  x  x  x  x  x  x  x  x  x  x  
3  x  x  x  x  x  x  x  x  x  x  
4  x  x  x  x  x  x  x  x  x  x  
5  x  x  x  x  x  x  x  x  x  x  
6  x  x  x  x  x  x  x  x  x  x  
7  x  x  x  x  x  x  x  x  x  x  
8  x  x  x  x  x  x  x  x  x  x  
9  x  x  x  x  x  x  x  x  x  x  
10 x  x  x  x  x  x  x  x  x  x  

>>>Insira as coordenadas do ponto(x,y): (1,1)
   1  2  3  4  5  6  7  8  9  10 
1  0  0  0  2  x  x  x  x  x  x  
2  0  0  0  2  x  x  x  x  x  x  
3  0  0  0  2  x  x  x  x  x  x  
4  0  1  1  2  x  x  x  x  x  x  
5  0  2  x  x  x  x  x  x  x  x  
6  0  2  x  x  x  x  x  x  x  x  
7  0  1  1  x  x  x  x  x  x  x  
8  0  0  1  x  x  x  x  x  x  x  
9  1  1  1  x  x  x  x  x  x  x  
10 x  x  x  x  x  x  x  x  x  x 
[...]

*/ 
void registra_interacao_com_usuario(int tamanho, int x, int y, char **campU);



/*
Argumentos: um inteiro que representa como a partida terminou, o tamanho da matriz, as ultimas coordenadas x e y escolhidas pelo usuário, o endereco da matriz de char que é impressa para o usuário, o endereco da matriz original com os valores inteiros do campo minado.

A funcao registra_Resultado_da_Partida() registra no arquivo "log.txt" o resultado da partida juntamente das ultimas coordenadas escolhidas pelo usuario.

Caso o inteiro passado como primeiro argumento seja diferente de 0, será impresso no "log.txt" uma menssagem de parabenização pela vitoria seguida da matriz de char. 
Agora, se for igual a 0, será impresso uma menssagem sinalizando o fim do jogo seguida da matriz de
inteiros e das últimas coordenadas x e y que o usuario escolheu.

Exemplos de registro:

1) Caso o "achou mina" seja igual a 0, o tamanho igual a 10 e as últimas coordenadas escolhidas tenham sido x = 1 e y = 5: 
GAME OVER
As coordenadas (1,5) eram o endereco de uma mina!!
    1  2  3  4  5  6  7  8  9  10 
 1  0  0  0  2 -1  2  1  2 -1  1 
 2  0  0  0  2 -1  2  1 -1  2  1 
 3  0  0  0  2  2  2  1  1  1  0 
 4  0  1  1  2 -1  2  1  2  1  1 
 5  0  2 -1  3  1  2 -1  2 -1  2 
 6  0  2 -1  2  0  2  2  3  2 -1 
 7  0  1  1  1  0  2 -1  3  2  1 
 8  0  0  1  1  1  2 -1 -1  1  0 
 9  1  1  1 -1  1  1  2  2  1  0 
10 -1  1  1  1  1  0  0  0  0  0 


2) Caso o "achou mina" seja diferente de 0 e o tamanho igual a 10: 
PARABENS, VOCE EH FERA
    1  2  3  4  5  6  7  8  9  10 
 1  0  0  0  2  x  2  1  2  x  1 
 2  0  0  0  2  x  2  1  x  2  1 
 3  0  0  0  2  2  2  1  1  1  0 
 4  0  1  1  2  x  2  1  2  1  1 
 5  0  2  x  3  1  2  x  2  x  2 
 6  0  2  x  2  0  2  2  3  2  x 
 7  0  1  1  1  0  2  x  3  2  1 
 8  0  0  1  1  1  2  x  x  1  0 
 9  1  1  1  x  1  1  2  2  1  0 
10  x  1  1  1  1  0  0  0  0  0 
*/
void registra_Resultado_da_Partida(int achouMina, int tamanho, int x, int y, char **campU, int **campD);