
/*
Recebe como argumento: o tamanho da matriz, as coordenadas x e y escolhidas pelo usuario, o endereco da matriz de char que eh impressa para o usuario.

A funçao checaPonto analisa se as coordenadas passadas são repetidas ou inválidas.

Retornando 0 caso sejam e 1 caso nao sejam. 
*/
int checaPonto(int tamanho, int x, int y, char **campU);



/*
A funçao inicializaCampoDefault() tem como objetivo inicializar uma matriz inteira de campo minado, onde o campo é representado por uma matriz bidimensional de inteiros (mD), com minas e números que indicam a quantidade de minas ao redor de cada célula.

A função recebe três parâmetros:

tamanho (int): Tamanho da matriz quadrada (campo minado), ou seja, a matriz terá tamanho x tamanho células.
minas (int): Quantidade de minas a serem colocadas aleatoriamente no campo.
mD (int**): Um ponteiro para a matriz que representa o campo minado. A função modificará esse campo para adicionar as minas e os números que indicam a quantidade de minas adjacentes.

Passo a Passo da Função:
1. Inicialização das Minas
A função usa srand(time(NULL)) para garantir que a aleatoriedade das minas seja diferente a cada execução.
Em seguida, o laço for (que se repete minas vezes) coloca minas aleatoriamente no campo. Cada mina é representada por um valor -1 dentro da matriz mD.
A cada iteração:
Coordenadas aleatórias (coordX e coordY) são geradas para as minas, utilizando rand() % tamanho.
Antes de colocar uma mina, a função verifica se o local já contém uma mina (ou seja, se mD[coordX][coordY] != -1). Se já houver uma mina, a iteração é repetida (decrementando cont para tentar novamente).
Caso contrário, o valor -1 é atribuído à célula para marcar a presença de uma mina.

2. Inicialização dos Números Adjuntos
Após colocar todas as minas, a função entra em um segundo laço duplo que percorre toda a matriz (mD), célula por célula.
Para cada célula que contém uma mina (mD[linha][coluna] == -1), a função incrementa as células vizinhas com a quantidade de minas ao redor delas. O incremento é feito nas células que não são minas.
A lógica de verificação das células vizinhas usa um laço while que percorre as 8 células ao redor da mina (na direção das 8 vizinhanças possíveis: cima, baixo, esquerda, direita e as 4 diagonais).
As coordenadas vizinhas são ajustadas por linha2 e coluna2 (variáveis que percorrem as células vizinhas).
A cada célula vizinha, a função verifica se as coordenadas são válidas (se estão dentro dos limites da matriz) e se a célula não contém uma mina.
Se a célula não tiver mina, ela é incrementada em 1, o que indica que há uma mina adjacente.

3. Controle de Limites
Dentro do laço de vizinhos, há uma série de verificações de limites para garantir que o acesso às células vizinhas não ultrapasse os limites da matriz. Caso uma célula vizinha esteja fora dos limites, ela é ignorada.
A função também faz um controle para percorrer corretamente as 8 vizinhanças de cada mina.
Resumo da Lógica:
Primeiro, o campo é preenchido com minas aleatórias.
Depois, as células do campo são analisadas e as células vizinhas das minas recebem um número que indica quantas minas estão ao seu redor.
Exemplo:
Considerando uma matriz de tamanho 5x5 e 3 minas, a matriz final pode ficar parecida com isso (onde -1 representa minas e os números representam o número de minas vizinhas):


[ 1,  1, -1,  1,  0]
[ 1,  2,  2,  2,  1]
[-1,  2, -1,  2,  1]
[ 1,  2,  2,  3,  2]
[ 0,  1,  1,  2, -1]

*/
void inicializaCampoDefault(int tamanho, int minas, int **mD);



/*
Recebe como argumentos: o tamanho da matriz.
A funçao alocaMatrizChar(), usando a função malloc(), aloca dinamicamente memoria para o campo (matriz de char) que o usuário irá interagir.
Após isso a função inicializará todos os elementos da matriz com 'x'.
*/
char **alocaMatrizChar(int tamanho);



/*
Recebe como argumentos: o tamanho da matriz.
A funçao alocaMatrizInt(), usando a função calloc(), aloca dinamicamente memoria para a matriz que guardará os valores originais dos elementos no campo minado.
*/
int **alocaMatrizInt(int tamanho);



/*
Recebe como argumentos: o tamanho das matrizes(que é o mesmo para ambas) e os endereços da matriz de inteiros e da matriz de char, respectivamente.
A funçao liberaMatriz() libera a memoria das linhas das matrizes, tanto da matriz inteira quanto da matriz de char.
*/
void liberaMatriz(int tamanho, int **campD, char **campU);



/*
Recebe como argumentos: um inteiro que indica como a partida terminou, o tamanho da matriz e os endereços da matriz de char e da matriz de inteiros, respectivamente.
A função imprimeCampo() imprime tanto o campo que o usuario interage, quanto o campo com os valores originais.
Se o valor inteiro passado como primeiro argumento for diferente de 0, imprimirá a matriz de char, e for igual a 0, entao imprimirá a matriz de inteiros.
*/
void imprimeCampo(int achouMina, int tamanho, char **campU, int **campD);



/* 
Recebe como argumentos:  o endereço da variavel que guardará o valor do tamanho das matrizes e o endereço da variavel que guardará o valor da quantidade de minas no jogo.
A funçao defineDificuldade() consultará o jogador e, a partir disso, definirá o tamanho e a quantidade de minas no campo

Descrição:
Entrada do Nível de Dificuldade:

A função começa com um prompt que solicita ao jogador escolher um nível de dificuldade para o jogo. A escolha pode ser:
[1] para fácil
[2] para médio
[3] para difícil
O jogador deve inserir o número correspondente ao nível de dificuldade.
A função usa scanf() para capturar a entrada do jogador e armazená-la na variável nivel (um array de caracteres com espaço para até 4 caracteres, o que é suficiente para armazenar a opção do jogador como uma string, como "1", "2", ou "3").

Comparação da Entrada com as Opções:
A função utiliza strcmp() para comparar a entrada do jogador (nivel) com as opções válidas ("1", "2" ou "3"). O strcmp() retorna 0 se as duas strings forem idênticas.

Dependendo da escolha do jogador:

Se o jogador escolher "1", o campo será de 10x10 (tamanho de 10) e haverá 15 minas.
Se o jogador escolher "2", o campo será de 20x20 (tamanho de 20) e haverá 60 minas.
Se o jogador escolher "3", o campo será de 30x30 (tamanho de 30) e haverá 135 minas.
A função então atribui os valores apropriados de tamanho e minas por meio de ponteiros (passagem por referência).

Tratamento de Entrada Inválida:

Se o jogador digitar uma entrada que não seja "1", "2" ou "3", a função entra no bloco else, onde chama a própria função defineDificuldade() recursivamente. Isso força o jogador a inserir uma opção válida, pois a função irá perguntar novamente até uma entrada válida ser fornecida.
Passo a Passo:
O jogador é solicitado a escolher a dificuldade do jogo.
A entrada do jogador é lida e comparada com as opções válidas.
Com base na entrada válida:
O tamanho do campo e o número de minas são definidos.
Se a entrada for inválida, o processo é repetido até uma entrada válida ser fornecida.
Exemplos de Definições de Dificuldade:

Se o jogador escolher 1, o campo será de 10x10 e terá 15 minas.
Se o jogador escolher 2, o campo será de 20x20 e terá 60 minas.
Se o jogador escolher 3, o campo será de 30x30 e terá 135 minas.

Caso o jogador insira algo diferente de 1, 2 ou 3, a função será chamada novamente, pedindo a escolha do nível.
*/
void defineDificuldade(int *tamanho, int *minas);



/*
Sem a necessidade de argumentos, a função executa_partida() é a implementação central da lógica de execução do jogo Campo Minado. Ela controla o fluxo do jogo, desde a definição da dificuldade até o momento final, onde o jogador ganha ou perde. A função interage com o jogador, permitindo que ele escolha coordenadas no campo para tentar evitar as minas, enquanto o estado do campo é atualizado de acordo com suas escolhas.

Descrição Detalhada da Função:
Definindo a Dificuldade:

A função começa chamando a função defineDificuldade(&tamanho, &minas), que consulta o jogador sobre a dificuldade e define o tamanho do campo (matriz) e o número de minas de acordo com a escolha. O número de pontos seguros (a quantidade de células que não possuem minas) também é calculado com base no tamanho e no número de minas.
Alocação das Matrizes:

Duas matrizes são alocadas dinamicamente:
campoDefault (matriz de inteiros): Onde são armazenadas as minas (-1) e a quantidade de minas ao redor de cada célula.
campoUsuario (matriz de caracteres): Onde o jogador irá ver o progresso da partida. Inicialmente, todas as células são marcadas com um valor 'x' que indica que ainda não foram reveladas.
Ambas as matrizes têm o tamanho definido pela variável tamanho.

Inicialização do Campo:
A função inicializaCampoDefault(tamanho, minas, campoDefault) é chamada para preencher o campo com as minas e as quantidades de minas ao redor das células.

Cálculo dos Pontos Seguros:
O número de pontos seguros (pontos_Seguros) é calculado como o total de células no campo (tamanho * tamanho) menos o número de minas.
A variável achouMina é inicialmente definida como 1 (indicando que o jogo continua e nenhuma mina foi encontrada ainda).

Loop de Execução do Jogo:
A função entra em um laço while que continua até que todos os pontos seguros sejam revelados (pontos_Seguros > 0) ou até que uma mina seja encontrada (achouMina).
Dentro do laço:

>>Impressão do Campo: A função imprimeCampo(achouMina, tamanho, campoUsuario, campoDefault) é chamada para mostrar o estado atual do campo ao jogador, com as células reveladas e as que ainda não foram reveladas.
>>Entrada das Coordenadas: O jogador é solicitado a inserir as coordenadas de uma célula no formato (x, y). Essas coordenadas são lidas com scanf() e ajustadas para índices de array (subtraindo 1 de x e y).
>>Verificação de Ponto Válido: A função checaPonto(tamanho, x, y, campoUsuario) verifica se o ponto inserido pelo jogador já foi escolhido ou se é uma coordenada inválida.

>>Se o ponto for válido:
Se o valor da célula no campo (campoDefault[x][y]) for -1, significa que o jogador encontrou uma mina, e o jogo termina (a variável achouMina é setada para 0).
Caso contrário, a célula é atualizada no campo do jogador (campoUsuario[x][y]) com o número de minas ao redor (a partir de campoDefault[x][y], convertido para caractere com + 48 para representar um número em ASCII).
>>Se o ponto for inválido (já foi jogado ou fora dos limites):
O jogador é avisado e o número de pontos seguros é ajustado (aumentando de novo o número de pontos seguros, pois ele tentou uma coordenada inválida).
Decremento de Pontos Seguros: A cada jogada, o número de pontos seguros é decrementado.


Fim do Jogo:
Após o laço, se o jogador encontrou uma mina, o jogo termina com a mensagem "GAME OVER", mostrando as coordenadas da mina encontrada e o estado final do campo.
Se o jogador venceu, ou seja, revelou todos os pontos seguros sem encontrar minas, a função parabeniza o jogador com a mensagem "PARABÉNS, VOCÊ É FERA" e mostra o estado final do campo.

Liberação de Memória:
Após o término do jogo, a memória alocada para as matrizes campoDefault e campoUsuario é liberada usando a função liberaMatriz().
Em seguida, as matrizes são desalocadas com free() para evitar vazamentos de memória.
*/
void executa_partida();


