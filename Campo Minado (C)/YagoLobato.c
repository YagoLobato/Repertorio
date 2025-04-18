
#include "matriz.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

/*
>>>> ATENÇÃO <<<<

Para compilar e executar o código, contanto que os arquivos log.c, log.h, matriz.c, matriz.h e YagoLobato.c estejam na mesma pasta,
basta navegar no terminal até o diretório da pasta e executar os comandos:

>> $ gcc YagoLobato.c matriz.c log.c -o main
>> $ ./main

Assim a partida será iniciada!!
*/






/*
Recebe como argumentos: o tamanho das matrizes, coordenadas x e y e os endereços da matriz de inteiros e da matriz de char, respectivamente.

Dadas coordenadas de um elemento, enquanto o elemento for igual a 0, a função floodfill() irá revelar todos os elementos nas casas vizinhas do mesmo. 
Aplicando a mesma funcionalidade nas casas vizinhas das coordenadas passadas, no caso de também serem iguais a 0.
Assim, recursivamente, revela todos os elementos enquanto não encontrar um ponto igual a 0 em que todas as casas vizinhas sejam diferentes de 0. 
*/
void floodfill(int tamanho, int x, int y, int **campD, char **campU){

//A ideia é que essa função seja acionada somente quando o usuário escolhe um ponto no campo que é igual a 0.
//para evitar processamento desnecessário, a primeira coisa que a função faz é inicializar o elemento da matriz de char com o seu respectivo elemento da matriz de inteiros
    
    campU[x][y] = campD[x][y] + 48;


//os próximos 3 laços são responsáveis por "revelar" as 8 casas vizinhas das coordenadas x,y passadas como argumento.

/*
Esse primeiro laço checa os elementos das casas acima do ponto x,y.
Sendo x - 1 = a linha acima do ponto, y - 1 = a coluna anterior ao ponto, o laço incrementa a coluna de uma maneira 
que percorre todos os 3 elementos acima do ponto x,y.

exemplo: x = 2 e y = 4

o laço irá checar os elementos nas coordenadas (1,3), (1,4) e (1,5). Que são as casas vizinhas superiores ao ponto x,y.

*/
    for(int coluna = y -1; coluna < y + 2; coluna++){
        if(checaPonto(tamanho, x - 1, coluna, campU)){
            if(campD[x - 1][coluna] == 0){

                /* 
                se o elemento na casa vizinha for igual a 0, a função floodfill também será chamada, com as coordenadas desse 
                novo ponto sendo passadas como argumento. Dessa maneira, garantindo que os elementos serão revelados enquanto não
                achar um ponto igual a 0 que tenha todas as casas vizinhas diferente de 0.
                */

               floodfill(tamanho, x - 1, coluna, campD, campU);
            }
            else{

                //caso não seja igual a 0, então o elemento da matriz de char será inicializado com o seu respectivo elemento das mesmas coordenadas na matriz de inteiros
                campU[x - 1][coluna] = campD[x - 1][coluna] + 48;
            }
        }
    }


/*
Esse segundo laço checa os elementos das casas na mesma linha do ponto x,y.
Sendo x = a linha do ponto, y - 1 = a coluna anterior ao ponto, o laço incrementa a coluna de uma maneira 
que percorre os elementos a direita e a esquerda do ponto x,y.

exemplo: x = 2 e y = 4

o laço irá checar os elementos nas coordenadas (2,3) e (2,5). Que são as casas vizinhas a direita e a esquerda do ponto x,y.

*/
     for(int coluna = y -1; coluna < y + 2; coluna = coluna + 2){
        if(checaPonto(tamanho, x, coluna, campU)){

            // esse if else tem a mesma funcionalidade descrita no primeiro laço.
            if(campD[x][coluna] == 0){
                floodfill(tamanho, x, coluna, campD, campU);
            }
            else{
                campU[x][coluna] = campD[x][coluna] + 48;
            }
        }
    }


/*
Esse terceiro laço checa os elementos das casas abaixo do ponto x,y.
Sendo x + 1 = a linha abaixo do ponto, y - 1 a coluna anterior ao ponto, o laço incrementa a coluna de uma maneira 
que percorre todos os 3 elementos abaixo do ponto x,y.

exemplo: x = 2 e y = 4

o laço irá checar os elementos nas coordenadas (3,3), (3,4) e (3,5). Que são as casas vizinhas inferiores ao ponto x,y.

*/
     for(int coluna = y -1; coluna < y + 2; coluna++){
        if(checaPonto(tamanho, x + 1, coluna, campU)){

            // esse if else tem a mesma funcionalidade descrita no primeiro laço.
            if(campD[x + 1][coluna] == 0){
                floodfill(tamanho, x + 1, coluna, campD, campU);
            }
            else{
                campU[x + 1][coluna] = campD[x + 1][coluna] + 48;
            }
        }
    }

}


/*
Recebendo o tamanho e o endereço da matriz que o usuário interage(matriz de caracteres), a função Pontos_Abertos() conta quantos pontos já foram revelados na partida.
Retorna esse valor como um número inteiro
*/
int Pontos_Abertos(int tamanho, char **campU){

    int pontosAbertos = 0;
    for(int linha = 0; linha < tamanho; linha++){
        for(int coluna = 0; coluna < tamanho; coluna++){

            // checando os valores diferentes de 'x', tem se a quantidade de elementos já modificados. Ou seja, já descobertos.
            if(campU[linha][coluna] != 'x'){
                pontosAbertos++;
            }
        }
    }

    return pontosAbertos;
}


/*
A função executa_partidaV2() possui, de certa forma, a mesma lógica da função executa_partida() descrita no arquivo "matriz.h".
Entretanto, foram implementadas novas linhas de código de maneira a utilizar as funcionalidades da função floodfill() e ainda a
utilizar as funções descritas no arquivo "log.h" para registrar as interações com o usuário da partida mais recente que foi executada. 
*/
void executa_partidaV2(){

    FILE* log = criar_log();// criando e registrando o horário da partida no arquivo "log.txt"
    registra_horario();

    int tamanho, minas, pontos_Seguros, pontos_descobertos, achouMina, x, y;
	defineDificuldade(&tamanho, &minas);
    printf("\nQuantidade total de minas: %d\n", minas);

    //aqui é feito o registro no log.txt do que costuma ser impresso na funcao defineDificuldade()
    log = abrir_log();
    fprintf(log,"Escolha a dificuldade do jogo!!\nDigite: \n[1] -> Facil || [2] -> Medio || [3] -> Dificil\n");
    fprintf(log, "\n%d\nQuantidade total de minas: %d\n\n", tamanho / 10, minas);
	fclose(log);

    //inicializando as principais variaveis que serão utilizadas na lógica do jogo
	int **campoDefault = alocaMatrizInt(tamanho);
	char **campoUsuario = alocaMatrizChar(tamanho);
	inicializaCampoDefault(tamanho, minas, campoDefault);
	pontos_Seguros = (tamanho * tamanho) - minas;
    pontos_descobertos = Pontos_Abertos(tamanho, campoUsuario);
	achouMina = 1;
    


	while (((pontos_Seguros - pontos_descobertos) > 0) && achouMina)
	{
		imprimeCampo(achouMina, tamanho, campoUsuario, campoDefault);
        

		printf("\n>>>Insira as coordenadas do ponto(x,y):\n");
		scanf("%d,%d", &x, &y);

        registra_interacao_com_usuario(tamanho, x, y, campoUsuario);
        
		x--;
		y--;

		if (checaPonto(tamanho, x, y, campoUsuario))
		{
			if (campoDefault[x][y] == -1)
			{
				achouMina = 0;
			}
            else if(campoDefault[x][y] == 0){
                //implementando floodfill
                floodfill(tamanho, x, y, campoDefault, campoUsuario);
            }
			else
			{
				campoUsuario[x][y] = campoDefault[x][y] + 48;
			}
		}
		else
		{   
            log = abrir_log();
			printf("\nPonto (%d,%d) repetido ou invalido!! Lembre-se, as coordenadas devem estar dentro do campo minado.\nInsira novas coordenadas.", x + 1, y + 1);
            fprintf(log, "\nPonto (%d,%d) repetido ou invalido!! Lembre-se, as coordenadas devem estar dentro do campo minado.\nInsira novas coordenadas.\n", x + 1, y +1);
            fclose(log);
		}

		pontos_descobertos = Pontos_Abertos(tamanho, campoUsuario);
	}

	if (achouMina)
	{   
		printf("\nPARABENS, VOCE EH FERA\n");
		imprimeCampo(achouMina, tamanho, campoUsuario, campoDefault);
        registra_Resultado_da_Partida(achouMina, tamanho, x + 1, y + 1, campoUsuario, campoDefault);
	}
	else
	{   
		printf("\nGAME OVER\n");
		printf("As coordenadas (%d,%d) eram o endereco de uma mina!!\n", x + 1, y + 1);
        imprimeCampo(achouMina, tamanho, campoUsuario, campoDefault);
		registra_Resultado_da_Partida(achouMina, tamanho, x + 1, y + 1, campoUsuario, campoDefault); 
	}

	liberaMatriz(tamanho, campoDefault, campoUsuario);
	free(campoDefault);
	free(campoUsuario);
}

int main(void){
    
    executa_partidaV2();

    //caso queira jogar a versão sem a feature floodfill e o registro de interação, adicione "//" antes da função executa_partidaV2() e retire as barras "//" anteriores a seguinte função:
    
    //executa_partida();

    return 0;
}
