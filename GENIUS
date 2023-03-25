#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define VERMELHO     "\x1b[31m"
#define VERDE   "\x1b[32m"
#define AZUL    "\x1b[34m"
#define AMARELO    "\x1b[33m"
#define RESET   "\x1b[0m"

struct elem{
    int dado;
    struct elem *seguinte;
};

typedef struct elem tElem;

typedef struct {
    tElem *inicio;
    tElem *fim;
} tFila;


//protótipos de funções

void criarFila (tFila *);
void inserirElemento (tFila *, int);
int removerElemento (tFila *);
int filaVazia (tFila *);
void mostrarFila (tFila); 
int compararFilas (tFila, tFila);
void deleteFila (tFila *);
void printarCores (tFila);
int corParaNumero(char *);

// funções

void criarFila (tFila *fila){
    
    fila->inicio = NULL;
    fila->fim = NULL; // acesso à informação início da pilha 
    
}

void inserirElemento (tFila *fila, int dado_inserido){
    
    tElem *x;
    x = (struct elem*)malloc((unsigned)(sizeof(int)));
    x->dado=dado_inserido;
    
    if (filaVazia(fila)){ 
        
        fila->inicio=x;
        fila->fim=x;
        x->seguinte=NULL;
    }
    
    else {

        fila->fim->seguinte = x;
        fila->fim = x;
        x->seguinte = NULL;
    }
    
}


int removerElemento (tFila *fila){
    
    if (filaVazia(fila))
      
      return 0;
      
    else {
        
        tElem *x;
        
          x = fila->inicio;
          
          fila->inicio = fila->inicio->seguinte;
          
          return x->dado;
   }   
}

int filaVazia (tFila *fila){
    
    if (fila->inicio==NULL)
    
       return 1;
       
    else
    
       return 0;
}

void mostrarFila (tFila fila){ // não pode ser ponteiro para não mudar a ordem da pilha
    
    while (filaVazia(&fila)==0){
      
        printf ("%d\n", fila.inicio->dado);
        fila.inicio = fila.inicio->seguinte;
            
    }
    
}

int compararFilas (tFila fila, tFila fila2){
    
   int x, y, certo = 1;
   tFila filaAux;
   criarFila(&filaAux);
   
   while (filaVazia(&fila)==0 && certo == 1){
       
       x = removerElemento(&fila);
       inserirElemento(&filaAux, x);
       y = removerElemento(&fila2);
       
       if (x!=y)
           certo = 0;
           
   }
   
   while (filaVazia(&filaAux)==0){ // 0 = falso
       
       x = removerElemento(&filaAux);
       inserirElemento(&fila, x);
       
   }
   
   return certo;
}

void deleteFila (tFila *fila){
    
    while (filaVazia(fila)==0)
      removerElemento(fila);
    
}

void printarCores (tFila fila){
    
   int x, y;
   tFila filaAux;
   criarFila(&filaAux);
    
    while (filaVazia(&fila)==0){
        
        y = removerElemento(&fila);
        inserirElemento(&filaAux, y);
        
        if (y==0)
            printf (AMARELO "AMARELO" RESET "\n");
        else if (y==1)
            printf (AZUL "AZUL"  RESET "\n");
        else if (y==2)
            printf (VERMELHO "VERMELHO" RESET "\n");
        else 
           printf (VERDE "VERDE" RESET "\n");
    }
    
    while (filaVazia(&filaAux)==0){
       x = removerElemento(&filaAux);
       inserirElemento(&fila, x);
    }
    
}

int corParaNumero (char *vet) {
    
    int x;
    
    if ((vet[1]=='M') || (vet[1]=='m'))
    x = 0;
    if ((vet[1]=='Z') || (vet[1]=='z'))
    x = 1;
    if ((vet[3]=='M') || (vet[3]=='m'))
    x = 2;
    if ((vet[3]=='D') || (vet[3]=='d'))
    x = 3;
    
    return x;
    
}

int main(){

    tFila minhaFila, minhaFila2;
    criarFila (&minhaFila);
    criarFila (&minhaFila2);
    int certo, tam, opcao=0;
    char vet[10];
    
    printf ("BEM-VINDO AO JOGO GENIUS!\n");
    printf ("1- INICIAR JOGO\n");
    printf ("2- COMO SE JOGA\n");
    printf ("3- SAIR\n");

    scanf ("%d", &opcao);
    
    while (opcao!=3){

        switch (opcao){

        case 1:
            certo = 1;
            tam = 0;
            printf ("MEMORIZE AS SEGUINTES CORES:\n");
            
            while (certo == 1){
                
                srand (time(NULL)); // função para resetar a função random
                int x = rand()%4; // gerador de números random
                inserirElemento(&minhaFila, x);
                
                //mostrarFila(minhaFila);
            
                printarCores(minhaFila);
                
                usleep(10000000/4);
                system("clear");
                
                tam++;
                
                printf ("AGORA É SUA VEZ DE JOGAR, ESCREVA O(S) NOME(S) DA(S) COR(ES):\n");
                            
                for (int i=0; i<tam; i++){
                    
                    scanf ("%s", vet);
                    int y = corParaNumero(vet);
                    inserirElemento (&minhaFila2, y);
                }    
                
                certo = compararFilas(minhaFila, minhaFila2);
                
                if (certo==1){ 
                    printf ("A RESPOSTA ESTÁ CORRETA!\n");
                    printf ("PRÓXIMO NÍVEL:\n");
                }
                
                else{
                    printf ("ERRADO :( TENTATIVA FINALIZADA!\n");
                    //printf ("A SEQUÊNCIA CORRETA ERA:\n");
                    //printarCores(minhaFila);
                }
                
                deleteFila(&minhaFila2);      
            }
        break;
        
        case 2:
           printf ("Simples jogo de memória, cujo objetivo é desafiar os participantes a acertarem\n");
           printf ("as diversas sequências de cores propostas no jogo!\n");
        break;

        case 3:
           printf ("O jogo será encerrado\n");
        break;
       }

      printf ("\n");
      printf ("BEM-VINDO AO JOGO GENIUS!\n");
      printf ("1- INICIAR JOGO\n");
      printf ("2- COMO SE JOGA\n");
      printf ("3- SAIR\n");
 
      scanf ("%d", &opcao);
      deleteFila(&minhaFila);   
    } 

    printf ("O jogo será encerrado\n");
    
    return 0;

}
