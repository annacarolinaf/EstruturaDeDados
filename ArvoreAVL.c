// Criador por: Anna Carolinas Farias

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int tipochave;

 typedef struct ArvAVL{
     tipochave valor;
     struct ArvAVL *esq, *dir;
     tipochave altura;
 }ArvAVL;

typedef struct ArvAVL ArvAVL;

ArvAVL* novoNo(tipochave x);
int maiorAltura(int a, int b);
int alturaDoNo (ArvAVL *r);
int fatorDeBalanceamento(ArvAVL *r);
ArvAVL* rotacaoEsquerda(ArvAVL *r);
ArvAVL* rotacaoDireita(ArvAVL *r);
ArvAVL* rotacaoEsquerdaDireita(ArvAVL *r);
ArvAVL* rotacaoEsquerdaDireita(ArvAVL *r);
ArvAVL* rotacaoDireitaEsquerda(ArvAVL *r);
ArvAVL* inserir(ArvAVL *raiz, tipochave x);
ArvAVL* balancear(ArvAVL *raiz);
ArvAVL* remover(ArvAVL *raiz, tipochave chave);
void imprimir(ArvAVL *raiz, int nivel);

//cria novo nó
ArvAVL* novoNo(tipochave x){
    ArvAVL *novo = malloc(sizeof(ArvAVL));

    if(novo){
        novo->valor = x;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

//função para comparar duas alturas
int maiorAltura(int a, int b){
    if (a>b)
     return a;
    else return b;
}
//função para saber a altura do nó
int alturaDoNo(ArvAVL *ArvAVL){
     if (ArvAVL==NULL)
        return -1;
     else 
       return ArvAVL->altura;   
}

int fatorDeBalanceamento(ArvAVL *ArvAVL){
    return (alturaDoNo(ArvAVL->esq) - alturaDoNo(ArvAVL->dir));
}

//função para a rotação à esquerda
ArvAVL* rotacaoEsquerda(ArvAVL *r){
    ArvAVL *novaRaiz, *f;

    novaRaiz = r->dir; // novaRaiz aponta para a subárvore direita da raiz r
    f = novaRaiz->esq; // f aponta para o filho esq de novaRaiz

    novaRaiz->esq = r; // o filho esq de novaRaiz passa a ser a raiz r
    r->dir = f; // o filho dir de r passa a ser f

    // recalcula a altura dos nós que foram movimentados
    r->altura = maiorAltura(alturaDoNo(r->esq), alturaDoNo(r->dir)) + 1;
    novaRaiz->altura = maiorAltura(alturaDoNo(novaRaiz->esq), alturaDoNo(novaRaiz->dir)) + 1;

    return novaRaiz;
}

//função para a rotação à direita
ArvAVL* rotacaoDireita(ArvAVL *r){
    ArvAVL *novaRaiz, *f;

    novaRaiz = r->esq;
    f = novaRaiz->dir;

    novaRaiz->dir = r;
    r->esq = f;

    r->altura = maiorAltura(alturaDoNo(r->esq), alturaDoNo(r->dir)) + 1;
    novaRaiz->altura = maiorAltura(alturaDoNo(novaRaiz->esq), alturaDoNo(novaRaiz->dir)) + 1;

    return novaRaiz;
}

//funções para as rotações duplas

ArvAVL* rotacaoEsquerdaDireita(ArvAVL *r){ 
    r->esq = rotacaoEsquerda(r->esq);
    return rotacaoDireita(r);
}

ArvAVL* rotacaoDireitaEsquerda(ArvAVL *r){
    r->dir = rotacaoDireita(r->dir);
    return rotacaoEsquerda(r);
}
//função para inserir um nó na Árvore AVL
ArvAVL* inserir(ArvAVL *raiz, tipochave x){

    if(raiz == NULL) // árvore vazia
        return novoNo(x);
    else{ // inserção será à esquerda ou à direita
        if(x < raiz->valor)
            raiz->esq = inserir(raiz->esq, x);
        else if(x > raiz->valor)
            raiz->dir = inserir(raiz->dir, x);
        else
            printf("\nInsercao nao realizada!\nO elemento %d já existe!\n", x);
        
    }
    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maiorAltura(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
    
}    

//função para remover um nó da Árvore AVL
ArvAVL* remover(ArvAVL *raiz, tipochave chave) {
    if(raiz == NULL){
        printf("Valor não encontrado!\n");
        return NULL;
    } 
    else { // procura o nó a remover
        if(raiz->valor == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                return NULL;
            }

            else{
                // remover nós que possuem 2 filhos
                if(raiz->esq != NULL && raiz->dir != NULL){
                    ArvAVL *aux = raiz->esq;
                    while(aux->dir != NULL)
                        aux = aux->dir;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    raiz->esq = remover(raiz->esq, chave);
                    return raiz;
                }
                else {
                    // remover nós que possuem apenas 1 filho
                    ArvAVL *aux;
                    if(raiz->esq != NULL)
                        aux = raiz->esq;
                    else
                        aux = raiz->dir;
                    free(raiz);
                    return aux;
                }
            }
        } 

        else {
            if(chave < raiz->valor)
                raiz->esq = remover(raiz->esq, chave);
            else
                raiz->dir = remover(raiz->dir, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maiorAltura(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

//função para realizar o balanceamento da árvore após uma inserção ou remoção
ArvAVL* balancear(ArvAVL *raiz){
    tipochave fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->dir) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esq) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esq) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->dir) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

//função que pesquisa se o elemento chave está na árvore
int pesquisaElemento (ArvAVL *raiz, tipochave chave){
    if (raiz==NULL)
        return 0;
    else {
        if (raiz->valor==chave)
            return 1;
        else{
            if (chave>raiz->valor)
                pesquisaElemento(raiz->dir, chave);
            else 
                pesquisaElemento(raiz->esq, chave);
        }
    }

}

//função para imprimir uma Árvore AVL
void imprimir(ArvAVL* raiz, int espaco) {
    if (raiz){
        // Espaçamento para criar uma representação visual de níveis diferentes na árvore
        int espaco_aux = 4;

        // Aumenta o espaçamento para níveis inferiores
        espaco += espaco_aux;

        // Chamada recursiva para o nó da direita
        imprimir(raiz->dir, espaco);

        // Imprime o nó atual com espaçamento
        printf("\n");
        for (int i = espaco_aux; i < espaco; i++) {
            printf(" ");
        }
        printf("%d\n", raiz->valor);

        // Chamada recursiva para o nó da esquerda
        imprimir(raiz->esq, espaco);
    }
}

/*//função para imprimir uma Árvore AVL
void imprimir_horizontal(ArvAVL *raiz, int nivel){
tipochave i;
if(raiz){
imprimir_horizontal(raiz->dir, nivel + 1);
printf("\n\n");


for(i = 0; i < nivel; i++)
printf("\t");


printf("%d", raiz->valor);
imprimir_horizontal(raiz->esq, nivel + 1);
}
}
*/

void menu();

int main(){
    ArvAVL *ArvAvl=NULL;
    int opcao = 0, x, result;
    printf ("Olá! Esse programa mostra o funcionamenteo de uma Árvore Binária AVL\n");
    printf ("Qual opção deseja escolher?\n");
    menu();
    scanf ("%d", &opcao);

    while (1){

        switch (opcao){
            case 1:
                printf ("Digite o número que deseja inserir:\n");
                scanf ("%d", &x);
                ArvAvl = inserir(ArvAvl, x);
                break;
            case 2:
                printf ("Digite o número que deseja remover:\n");
                scanf ("%d", &x);
                if (pesquisaElemento(ArvAvl, x)==0)
                    printf ("O número não está na Árvore para ser removido\n");
                else
                    ArvAvl = remover(ArvAvl, x);
                    printf("Número removido\n");
                break;
            case 3:
                printf ("Imprimindo a Árvore...\n");
                imprimir(ArvAvl, 1);
                printf ("\n");
                break;
            case 4:
                printf("Digite o número que deseja pesquisar:\n");
                scanf ("%d", &x);
                result = pesquisaElemento(ArvAvl, x);
                if (result==0)
                    printf ("O número não está na Árvore\n");
                else 
                    printf ("O número está na Árvore\n");
                break;
            case 5:
                printf ("O programa será encerrado\n");
                return 0;

            default:
			    printf("Opção inválida\n");
			    break;
        }

        printf("\nDigite outra opção do menu:\n\n");
        menu();
        scanf ("%d", &opcao);

    }
    
    return 0;
}

void menu(){
    printf ("1. Inserir número\n");
    printf ("2. Remover número\n");
    printf ("3. Imprimir a Árvore AVL\n");
    printf ("4. Pesquisar número\n");
    printf ("5. Sair do programa\n");
}
