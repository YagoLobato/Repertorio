// Tipos de dados exportados

typedef struct listaDupla Fila;  // Pessoa* prim; Pessoa* ult;
typedef struct No Pessoa;  // int idade; Pessoa *prox; Pessoa *ant;


struct listaDupla
{
    Pessoa *prim;
    Pessoa *ult;
};

struct No
{
    int idade;
    Pessoa *prox;
    Pessoa *ant;
};


/*
Nao necessita de argumentos para a sua execucao.
A funcao cria_fila cria e inicializa uma lista duplamente encadeada, alocando memoria dinamicamente para tal.
Ela inicializa os ponteiros prim e ult como NULL e retorna um ponteiro para a lista criada.
Caso a alocacao de memoria falhe, o programa eh encerrado com exit(1).
*/
Fila *cria_fila(void);


/*
Recebe como argumentos o endereco de uma lista duplamente encadeada (Fila*) e um inteiro n.
A funcao insere_Pessoa insere um novo No na lista, com a idade da pesssoa que o No representa definida pelo parametro num.
Se a alocação de memoria falhar, o programa eh encerrado com exit(1).
*/
void insere_Pessoa(Fila *f, int num);


/*
Recebe como argumentos o endereco de uma lista duplamente encadeada (Fila* f).
é responsavel por esvaziar e processar uma fila implementada como uma lista duplamente encadeada, liberando todos os Nos da memoria e imprimindo a idade de cada pessoa atendida.

Um ponteiro p eh usado para percorrer os Nos da lista, começando pelo primeiro No (f->prim).
Enquanto p nao for NULL, a funcao processa o No atual:
Imprime a idade do elemento atual.
Armazena o No atual em uma variavel auxiliar (atendido) para posterior liberacao de memoria.
Atualiza o ponteiro p para o proximo No da lista (p->prox).
Remove o No atual da lista:
Se o No atual eh o primeiro No da lista, atualiza f->prim para o proximo elemento.
Se nao for o primeiro, ajusta o ponteiro prox do No anterior para pular o No atual.
Se o No atual eh o ultimo, atualiza f->ult para o No anterior.
Se nao for o ultimo, ajusta o ponteiro ant do proximo No para pular o No atual.
Libera a memoria do No atual usando free(atendido).
O loop continua ate que todos os Nos tenham sido processados e a lista esteja vazia.

Após processar todos os Nos, a memoria alocada para a estrutura da fila (f) eh liberada com free(f).

Exemplo de entrada e saida de uma fila ao ser passada para a funcao atende_fila():
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
9
62
73
70
62
68
100
99
90
*/

void atende_fila(Fila *f);

