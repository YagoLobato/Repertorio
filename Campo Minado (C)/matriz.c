#include "matriz.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//No arquivo "matriz.h" pode ser encontrado informações mais detalhadas sobre cada função presente neste arquivo 

// A funçao checaPonto analisa se as coordenadas passadas são repetidas, retornando 0 caso sejam e 1 caso n sejam.
int checaPonto(int tamanho, int x, int y, char **campU)
{
	int pontoValido = 0;
	if ((x >= 0 && x < tamanho) && (y >= 0 && y < tamanho) && (campU[x][y] == 'x'))
	{
		pontoValido = 1;
	}

	return pontoValido;
}

// A funçao inicializaCampoDefault inicializa os elementos do campo minado com valores inteiros
void inicializaCampoDefault(int tamanho, int minas, int **mD)
{
	// o laço a seguir inicializa as minas no campo com coordenadas geradas aleatoriamente.
	srand(time(NULL));
	int  coordX, coordY, cont, loop;

	for (int cont = 0; cont < minas; cont++)
	{
		coordX = rand() % tamanho;
		coordY = rand() % tamanho;

		if (mD[coordX][coordY] != -1)//checa se o elemento das coordenadas ja nao foi incializado com uma mina.
		{
			mD[coordX][coordY] = -1;
		}

		else
		{
			cont--;
		}
	}

	// o laço a seguir inicializa os elementos com suas respectivas quantidades de minas ao seu redor.
	//A ideia é que esse laco inicial percorra toda a matriz buscando o endereco das minas.
	for (int linha = 0; linha < tamanho; linha++)
	{
		for (int coluna = 0; coluna < tamanho; coluna++)
		{
			
			if (mD[linha][coluna] == -1)//caso ache uma mina, icrementara +1 nas 8 casas vizinhas a ela.
			{
				cont = loop = 0;
				int linha2 = linha - 1;
				int coluna2 = coluna - 1;

				while (loop < 9)//laco responsavel por percorrer as 8 casas vizinhas da mina
				{
					if (coluna2 == (coluna + 2))// esse if checa se ja foi percorrido o necessario na linha desejada
					{
						linha2++;
						coluna2 = coluna - 1;
					}

					//esse if checa se as coordenadas (linha2,coluna2) existem dentro da matriz e, se nao forem uma mina, as incrementa com +1.
					if ((linha2 >= 0 && linha2 < tamanho) && (coluna2 >= 0 && coluna2 < tamanho))
					{
						if (mD[linha2][coluna2] != -1)
						{
							mD[linha2][coluna2] = mD[linha2][coluna2] + 1;
							coluna2++;
						}
						else
						{
							coluna2++;
						}
					}
					else
					{
						coluna2++;
					}
					loop++;
				}
			}
		}
	}
}

// A funçao alocaMatrizChar aloca dinamicamente memoria para o campo que o usuario irá interagir
char **alocaMatrizChar(int tamanho)
{
	char **campoUser = (char **)malloc(tamanho * sizeof(char *));
	if (campoUser == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}
	for (int cont = 0; cont < tamanho; cont++)
	{
		campoUser[cont] = (char *)malloc(tamanho * sizeof(char));

		if (campoUser[cont] == NULL)
		{
			printf("ERRO\n");
			exit(1);
		}
	}

	// o laço a seguir inicializa todos os elementos do campo que sera impresso ao usuario com 'x'.
	for (int linha = 0; linha < tamanho; linha++)
	{
		for (int coluna = 0; coluna < tamanho; coluna++)
		{
			campoUser[linha][coluna] = 'x';
		}
	}

	return campoUser;
}

// A funçao alocaMatrizInt aloca dinamicamente memoria para o campo que guardará os valores originais dos elementos
int **alocaMatrizInt(int tamanho)
{
	int **campoDefault = (int **)calloc(tamanho, sizeof(int *));
	if (campoDefault == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}
	for (int cont = 0; cont < tamanho; cont++)
	{
		campoDefault[cont] = (int *)calloc(tamanho, sizeof(int));

		if (campoDefault[cont] == NULL)
		{
			printf("ERRO\n");
			exit(1);
		}
	}

	return campoDefault;
}

// A funçao liberaMatriz libera a memoria das linhas das matrizes
void liberaMatriz(int tamanho, int **campD, char **campU)
{
	for (int cont = 0; cont < tamanho; cont++)
	{
		free(campD[cont]);
	}

	for (int cont = 0; cont < tamanho; cont++)
	{
		free(campU[cont]);
	}
}

// a funçao imprimeCampo imprime tanto o campo que o usuario interage, quanto o campo com os valores originais
//se o achouMina for diferente de 0, imprimira a matriz de char. Se for igual a 0 entao imprimira a matriz de inteiros.
void imprimeCampo(int achouMina, int tamanho, char **campU, int **campD)
{
	if (achouMina)
	{	
		putchar('\n');
		for (int indc = 1; indc <= tamanho; indc++)
		{
			if (indc == 1)
			{
				printf("   %d  ", indc);
			}
			else if (indc > 9)
			{
				printf("%d ", indc);
			}
			else
			{
				printf("%d  ", indc);
			}
		}
		putchar('\n');

		for (int linha = 0; linha < tamanho; linha++)
		{
			if (linha < 9)
			{
				printf("%d  ", linha + 1);
			}
			else
			{
				printf("%d ", linha + 1);
			}

			for (int coluna = 0; coluna < tamanho; coluna++)
			{
				printf("%c  ", campU[linha][coluna]);
			}
			putchar('\n');
		}
	}
	else
	{	
		putchar('\n');
		for (int indc = 1; indc <= tamanho; indc++)
		{
			if (indc == 1)
			{
				printf("    %d  ", indc);
			}
			else if (indc > 9)
			{
				printf("%d ", indc);
			}
			else
			{
				printf("%d  ", indc);
			}
		}
		putchar('\n');

		for (int linha = 0; linha < tamanho; linha++)
		{
			if (linha < 9)
			{
				printf(" %d ", linha + 1);
			}
			else
			{
				printf("%d ", linha + 1);
			}

			for (int coluna = 0; coluna < tamanho; coluna++)
			{
				if(campD[linha][coluna] == -1){
					printf("%d ", campD[linha][coluna]);		
				}
				else{ 
					printf(" %d ", campD[linha][coluna]);
				}
			}
			putchar('\n');
		}
	}
}

// a funçao defineDificuldade consultará o jogador e, a partir disso, definirá o tamanho e a quantidade de minas no campo
void defineDificuldade(int *tamanho, int *minas)
{
	char nivel[5];

	printf("Escolha a dificuldade do jogo!!\nDigite: \n[1] -> Facil || [2] -> Medio || [3] -> Dificil\n");
	scanf("%s", nivel);

	if (strcmp(nivel, "1") == 0)
	{
		*tamanho = 10;
		*minas = 15;
	}
	else if (strcmp(nivel, "2") == 0)
	{
		*tamanho = 20;
		*minas = 60;
	}
	else if (strcmp(nivel, "3") == 0)
	{
		*tamanho = 30;
		*minas = 135;
	}
	else
	{
		defineDificuldade(tamanho, minas);
	}
}

// executa a parte interativa do código, o jogo em si
void executa_partida()
{
	int tamanho, minas, pontos_Seguros, achouMina, x, y;
	defineDificuldade(&tamanho, &minas);

	int **campoDefault = alocaMatrizInt(tamanho);
	char **campoUsuario = alocaMatrizChar(tamanho);

	inicializaCampoDefault(tamanho, minas, campoDefault);
	pontos_Seguros = (tamanho * tamanho) - minas;
	achouMina = 1;

	while ((pontos_Seguros > 0) && achouMina)
	{
		imprimeCampo(achouMina, tamanho, campoUsuario, campoDefault);

		printf("\n>>>Insira as coordenadas do ponto(x,y): ");
		scanf("%d,%d", &x, &y);

		x--;
		y--;

		if (checaPonto(tamanho, x, y, campoUsuario))
		{
			if (campoDefault[x][y] == -1)
			{
				achouMina = 0;
			}
			else
			{
				campoUsuario[x][y] = campoDefault[x][y] + 48;
			}
		}
		else
		{
			printf("\nPonto (%d,%d) repetido ou invalido!! insira novas coordenadas.\n", x + 1, y + 1);
			pontos_Seguros++;
		}

		pontos_Seguros--;
	}

	if (achouMina)
	{
		printf("\nPARABENS, VOCE EH FERA\n");
		imprimeCampo(achouMina, tamanho, campoUsuario, campoDefault);
	}
	else
	{
		printf("\nGAME OVER\n");
		printf("As coordenadas (%d,%d) eram o endereco de uma mina!!\n", x + 1, y + 1);
		imprimeCampo(achouMina, tamanho, campoUsuario, campoDefault);
	}

	liberaMatriz(tamanho, campoDefault, campoUsuario);
	free(campoDefault);
	free(campoUsuario);
}
