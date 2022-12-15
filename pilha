#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

typedef struct elem {
    int dado;
    struct elem *pseguinte;
}tElem;

typedef struct {
    tElem *inicio;
    tElem *fim;
    int tam;
}tPilha;

//protótipos de funções

void mostrarMenu ();
void criarPilha (tPilha *);
void inserirElemento (tPilha *, int);
int removerElemento (tPilha *);
int vaziaPilha (tPilha);
void mostrarPilha (tPilha); 
void mostrarTopo (tPilha);
void apagarPilha (tPilha *);

int main()
{

    tPilha minhaPilha;
    int x, i, y, opcao, tam;


    printf ("Bem-vindo!\nSelecione uma das opções abaixo:\n");

    mostrarMenu();
    scanf ("%d", &opcao);

    while (opcao!=7){
    
        switch (opcao){

            case 1: 

                criarPilha (&minhaPilha);
                printf ("Sua pilha foi criada com sucesso!\n");
                printf ("Digite o tamanho inicial da sua pilha:");
                scanf ("%d", &tam);
                printf ("Agora, digite os valores que deseja inserir:");
                for (i=0; i<tam; i++){
                    scanf ("%d", &x);
                    inserirElemento (&minhaPilha, x);
                }

                break;

            case 2: 

                printf ("Digite o elemento que deseja inserir:");
                scanf ("%d", &x);
                inserirElemento (&minhaPilha, x);
            
                break;

            case 3: 

                y = removerElemento (&minhaPilha);
                if (y!=false) printf ("Elemento removido: %d\n", y); 
                else printf ("A pilha está vazia");
            
                break;

            case 4:

                printf ("Minha pilha:\n");
                mostrarPilha (minhaPilha);

                break;

            case 5:

                printf ("Elemento do topo:");
                mostrarTopo (minhaPilha);

                break;

            case 6:
                 
                apagarPilha (&minhaPilha);
                printf ("A pilha foi apagada com sucesso\n");

                break;

            default:

                printf ("Opção inválida\n");

                break;   
            
        }

        printf ("\n");
        
        printf ("Digite outra opção:");
        scanf ("%d", &opcao);

    }

    return 0;
}

// funções

void mostrarMenu (){

    printf ("1.Criar uma pilha\n");
    printf ("2.Inserir novo elemento\n");
    printf ("3.Remover elemento\n");
    printf ("4.Visualizar pilha completa\n");
    printf ("5.Mostrar elemento do topo\n");
    printf ("6.Apagar pilha\n");
    printf ("7.Sair do programa\n");

}

void criarPilha (tPilha *pilha){

    pilha->inicio = NULL; // acesso à informação início da pilha 
    pilha->tam = 0;
    
}

void inserirElemento (tPilha *pilha, int dado_inserido){
    tElem *x;
    x = (struct elem*)malloc((unsigned)(sizeof(int)));
    x->dado = dado_inserido;
    x->pseguinte = pilha->inicio; // pseguinte recebe o valor de inicio apontado por pilha 
    pilha->inicio = x;
    pilha->tam++;
}


int removerElemento (tPilha *pilha){

    if (vaziaPilha(*pilha))
        return false;
    
    
    else {
        tElem *x; // precisa ser ponteiro? sim, para apagar o espaço da memória
        int Aux;

        Aux = pilha->inicio->dado;
        x = pilha->inicio;
        pilha->inicio = pilha->inicio->pseguinte;
        pilha->tam--;

        free (x);
        return Aux;
    }
    
}     

int vaziaPilha (tPilha pilha){
    
    if (pilha.inicio==NULL)

        return 1;

    else 
    
       return 0;
}

void mostrarPilha (tPilha pilha){ // não pode ser ponteiro para não mudar a ordem da pilha
    
    int i;
    
    if (pilha.inicio!=NULL) {
        
      for (i=0;i<pilha.tam;i++){
          
            printf ("%d\n", pilha.inicio->dado);
            pilha.inicio = pilha.inicio->pseguinte;
            
        }
    }
    
}

void mostrarTopo(tPilha pilha){

   int x;
   
   if (vaziaPilha(pilha)==0){
    x = removerElemento (&pilha); 
    inserirElemento (&pilha, x);
    printf ("%d", x);
   }

   else printf ("A pilha está vazia");

}

void apagarPilha (tPilha *pilha){

    while (pilha->inicio!=NULL){
       removerElemento(pilha);
    }

}
