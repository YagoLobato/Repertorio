#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/*
    Para melhor compreensao do codigo, é importante citar que, apesar de trabalhar com listas duplamente encadeadas no programa, 
    os nomes das funcoes e das variaveis criadas foram pensados de acordo com a ideia de que esta sendo implementado um sistema que controla uma FILA de PESSOAS.
    Vi a necessidade de ressaltar isso apenas para evitar a confusao na leitura, ja que fila tambem é uma estrutura de dados.
*/

Fila *cria_fila(void)
{
    Fila *f = malloc(sizeof(Fila));
    if (f == NULL)
    {
        exit(1);
    }

    f->prim = NULL;
    f->ult = NULL;

    return f;
}

void insere_Pessoa(Fila *f, int num)
{
    Pessoa *p = malloc(sizeof(Pessoa));
    if (p == NULL)
    {
        exit(1);
    }

    p->idade = num;
    p->prox = f->prim;
    p->ant = NULL;

    if (f->prim != NULL)
    {
        f->prim->ant = p;
    }
    else
    {
        f->ult = p;
    }

    f->prim = p;
}

void atende_fila(Fila *f)
{
    Pessoa *p = f->prim;
    Pessoa *atendido;

    while (p != NULL)
    {
        printf("%d\n", p->idade);

        atendido = p;
        p = p->prox;

        if (f->prim == NULL)

            if (atendido == f->prim)
            {
                f->prim = atendido->prox;
            }
            else
            {
                atendido->ant->prox = atendido->prox;
            }

        if (atendido == f->ult)
        {
            f->ult = atendido->ant;
        }
        else
        {
            atendido->prox->ant = atendido->ant;
        }

        free(atendido);
    }

    
    free(f);
}
