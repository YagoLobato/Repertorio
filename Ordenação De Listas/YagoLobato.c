#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/*
Para compilar e executar o codigo, contanto que os arquivos fila.c, fila.h, YagoLobato.c e clientes.txt estejam na mesma pasta,
basta navegar no terminal ate o diretorio da pasta e executar os comandos:

>> $ gcc YagoLobato.c fila.c -o main
>> $ ./main

e o codigo sera executado!!


>>>Caso queira relizar testes com outros valores, basta alterar os inteiros presentes em clientes.txt, obviamente seguindo a mesma formatacao,
salvar as alteracoes e entao executar o codigo novamente.
*/


/*
Recebe como argumentos o endereco de uma lista duplamente encadeada (Fila* f).

A funcao ler_FilaDeEspera() inicializa a lista passada como argumento com os inteiros(idade dos clientes) presentes no arquivo "clientes.txt".
A funcao termina com um erro se o arquivo "clientes.txt" nao puder ser aberto, caso possa, o arquivo eh fechado corretamente após a leitura dos dados.

Eh importante ressaltar que a funcao considera que o arquivo "clientes.txt" ja exista no mesmo diretorio que os outros programas.
*/ 
void ler_FilaDeEspera(Fila *f){
    int num;

    FILE* fila = fopen("clientes.txt", "r");
    if(fila == NULL){
        exit(1);
    }

    while(fscanf(fila, "%d", &num) != EOF){
        insere_Pessoa(f, num);
    }

    fclose(fila);
}

/*
Recebe como argumentos o endereco de uma lista duplamente encadeada (Fila* f).

Seguindo o principio de organizar uma fila com prioridade em pessoas mais velhas:
A funcao ordenaFila_maiorIdade implementa o algoritmo de ordenacao Bubble Sort para ordenar uma fila (lista duplamente encadeada) de pessoas pela idade, em ordem decrescente. 
O algoritmo percorre a fila, comparando cada pessoa com a proxima e trocando suas posicoes quando necessario. O processo eh repetido ate que a lista esteja ordenada.

Antes de comecar a ordenacao, a funcao verifica se a fila tem mais de um elemento. Se a fila estiver vazia ou contiver apenas um elemento, nao ha necessidade de ordenacao, e a funcao termina imediatamente.

sobre a ordenacao com Bubble Sort:
A ordenacao eh realizada em um loop do-while. O loop interno percorre a fila comparando cada pessoa com a proxima na "Fila".
Uma variavel sinalizadora eh usada para monitorar se houve alguma troca e o processo continua enquanto houver trocas a serem feitas.
Apos cada iteracao completa do loop interno, a variável eh verificada. Se ao menos uma troca foi realizada, o processo eh repetido, garantindo que a fila continue sendo organizada ate que nao haja mais trocas necessarias.

Exemplo de entrada e saida de uma fila apos ser ordenada pela funcao ordenaFila_maiorIdade():
>>> os inteiros representam a idade das pessoas na fila.

Entrada:
90
99
100
68
62
70
73
62
9

saida:
100
99
90
73
70
68
62
62
9
*/

void ordenaFila_maiorIdade(Fila *f)
{
    int trocou;
    Pessoa *atual, *proxPessoa;

    if (f->prim != NULL && f->prim->prox != NULL) // Caso a lista esteja vazia ou com apenas um No, nao ha necessidade de ordenar.
    {
        do
        {
            trocou = 0;
            atual = f->prim;

            // Percorre a lista inteira comparando cada No com seu No sucessor(prox) e realiza trocas, se necessario.
            while (atual->prox != NULL)
            {
                if (atual->idade < atual->prox->idade)
                {
                    // Troca e ajusta os ponteiros dos Nos
                    proxPessoa = atual->prox;
                    atual->prox = proxPessoa->prox;

                    if (proxPessoa->prox != NULL) // checa se proxPessoa nao eh o ultimo No
                    {
                        proxPessoa->prox->ant = atual;
                    }
                    else
                    {
                        f->ult = atual;
                    }

                    proxPessoa->ant = atual->ant;

                    if (atual->ant != NULL) // checa se nao eh o primeiro No
                    {
                        atual->ant->prox = proxPessoa;
                    }
                    else
                    {
                        f->prim = proxPessoa;
                    }

                    proxPessoa->prox = atual;
                    atual->ant = proxPessoa;

                    trocou = 1;
                }
                else
                {
                    atual = atual->prox;
                }
            }

        } while (trocou); 
        // repete o processo de comparacao e troca de elementos ate que nao seja mais necessario.
        //De maneira que, apos percorrer a lista inteira, a variavel "trocou" permaneceu == 0.
    }
}


int main(void){
   Fila *fila = cria_fila();

   ler_FilaDeEspera(fila); 

   ordenaFila_maiorIdade(fila);

   atende_fila(fila);
}