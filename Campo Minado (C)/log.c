#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//No arquivo "log.h" pode ser encontrado informações mais detalhadas sobre cada função presente neste arquivo 


FILE *criar_log()
{
	FILE *arqv = fopen("log.txt", "w");
	if (arqv == NULL)
	{
		exit(1);
	}

	fclose(arqv);
	return arqv;
}

FILE *abrir_log()
{
	FILE *log = fopen("log.txt", "a");
	if (log == NULL)
	{
		exit(1);
	}

	return log;
}

void registra_horario()
{
	FILE *log = abrir_log();
	time_t horarioAtual;
	time(&horarioAtual);

	fprintf(log, "Data e horario do inicio da partida: ");
	fprintf(log, "%s\n", ctime(&horarioAtual));
	fclose(log);
}

//registra no log o progresso da matriz de char juntamente das  coordenadas escolhidas pelo usuario.
void registra_interacao_com_usuario(int tamanho, int x, int y, char **campU)
{
	FILE *log = abrir_log();

	for (int indc = 1; indc <= tamanho; indc++)
	{
		if (indc == 1)
		{
			fprintf(log, "   %d  ", indc);
		}
		else if (indc > 9)
		{
			fprintf(log, "%d ", indc);
		}
		else
		{
			fprintf(log, "%d  ", indc);
		}
	}
	fprintf(log, "\n");

	for (int linha = 0; linha < tamanho; linha++)
	{
		if (linha < 9)
		{
			fprintf(log, "%d  ", linha + 1);
		}
		else
		{
			fprintf(log, "%d ", linha + 1);
		}

		for (int coluna = 0; coluna < tamanho; coluna++)
		{
			fprintf(log, "%c  ", campU[linha][coluna]);
		}
		fprintf(log, "\n");
	}

	fprintf(log, "\n>>>Insira as coordenadas do ponto(x,y): ");
	fprintf(log, "(%d,%d)\n", x, y);
	fclose(log);
}

//registra no log o resultado da partida.
void registra_Resultado_da_Partida(int achouMina, int tamanho, int x, int y, char **campU, int **campD)
{
	FILE *log = abrir_log();

	if (achouMina)
	{
		fprintf(log, "\nPARABENS, VOCE EH FERA\n");
		for (int indc = 1; indc <= tamanho; indc++)
		{
			if (indc == 1)
			{
				fprintf(log, "   %d  ", indc);
			}
			else if (indc > 9)
			{
				fprintf(log, "%d ", indc);
			}
			else
			{
				fprintf(log, "%d  ", indc);
			}
		}
		fprintf(log, "\n");

		for (int linha = 0; linha < tamanho; linha++)
		{
			if (linha < 9)
			{
				fprintf(log, "%d  ", linha + 1);
			}
			else
			{
				fprintf(log, "%d ", linha + 1);
			}

			for (int coluna = 0; coluna < tamanho; coluna++)
			{
				fprintf(log, "%c  ", campU[linha][coluna]);
			}
			fprintf(log, "\n");
		}
	}
	else
	{
		fprintf(log, "\nGAME OVER\n");
		fprintf(log, "As coordenadas (%d,%d) eram o endereco de uma mina!!\n", x, y);

		for (int indc = 1; indc <= tamanho; indc++)
		{
			if (indc == 1)
			{
				fprintf(log, "    %d  ", indc);
			}
			else if (indc > 9)
			{
				fprintf(log, "%d ", indc);
			}
			else
			{
				fprintf(log, "%d  ", indc);
			}
		}
		fprintf(log, "\n");

		for (int linha = 0; linha < tamanho; linha++)
		{
			if (linha < 9)
			{
				fprintf(log, " %d ", linha + 1);
			}
			else
			{
				fprintf(log, "%d ", linha + 1);
			}

			for (int coluna = 0; coluna < tamanho; coluna++)
			{
				if (campD[linha][coluna] == -1)
				{
					fprintf(log, "%d ", campD[linha][coluna]);
				}
				else
				{
					fprintf(log, " %d ", campD[linha][coluna]);
				}
			}
			fprintf(log, "\n");
		}
	}

	fclose(log);
}
