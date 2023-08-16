#Criado por: Anna Carolina Farias 

global total_bits #variável global para o número total de bits da árvore
total_bits = 4

class No: #classe para construção do nó

    def __init__(self, chave): #construtor

        self.chave = chave 

        self.esq = None

        self.dir = None

class ArvoreDigital: #classe para a árvore digital 

    def __init__ (self): #construtor

        self.raiz = None
    
    def insere(self, raiz, nivel, chave): #função de inserção

        novoNo = No(chave) #cria novo nó

        if (raiz==None): #se a raíz for nula, o novo nó será a raíz
            return novoNo
        
        else:
            if (raiz.chave==chave): #se o valor já estiver na árvore, ele não será inserido
                print ("Valor já está presente na árvore")
                return raiz
            
            else:
                bit = (novoNo.chave >> (total_bits - 1 - nivel)) & 1 #extrai o bit que será comparado

                if (bit==0): #se o bit for 0, o valor será inserido do lado esquerdo
                    raiz.esq = self.insere(raiz.esq, nivel + 1, chave)
                else: #caso contrário (o bit é 1), o valor será inserido do lado direito
                    raiz.dir =  self.insere(raiz.dir, nivel + 1, chave)

            return raiz

    def insereGlobal (self, chave): #função de inserção para a main

        self.raiz = self.insere(self.raiz, 0, chave) #chama a outra função de insere com todos os parâmetros necessários

    def busca(self, raiz, nivel, chave): #função para buscar um valor na árvore

        if (raiz==None): #se a árvore estiver vazia, retorna falso para a busca do valor
            return False
        
        else:
            if (raiz.chave==chave): #se o valor foi encontrado, retorna verdadeiro
                return True
            
            else:
                bit = (chave >> (total_bits - 1 - nivel)) & 1 #extrai o bit que será comparado

                if (bit==0): #se o bit for 0, procura do lado esquerdo da árvore
                    return self.busca(raiz.esq, nivel + 1, chave)
                
                else: #caso contrário, procura do lado direito
                     return self.busca(raiz.dir, nivel + 1, chave)
                
                
    def buscaGlobal (self, chave): #função de busca para a main
        return self.busca(self.raiz, 0, chave) #chama a a função busca com todos os parâmetros necessários
    
    def remove(self, raiz, chave, nivel): #função para remover um valor da árvore
        if not self.buscaGlobal(chave): #chama a função busca para saber se o elemento está na árvore
            return False
        
        pai = None #auxiliar para saber qual é o pai do nó folha que vamos remover

        while (raiz.chave!=chave): #procura o nó com o valor que queremos
            pai = raiz

            bit = (chave >> (total_bits - 1 - nivel)) & 1 
            
            if (bit==0):
                raiz = raiz.esq
            else:
                raiz = raiz.dir

            nivel+=1
        

        if (raiz.esq==None and raiz.dir==None): #se o nó que queremos remover é nó folha, ele pode ser removido sem problemas

            if (pai==None): #se o pai não recebeu nenhuma outra atribuição, então a árvore só possui o elemento da raíz
                self.raiz = None #raíz recebe null

            else: 
                if (bit==1): #se o nó folha está do lado direito, o pai recebe null do lado direito
                    pai.dir = None
                else:
                    pai.esq = None #caso contrário, recebe null do lado esquerdo


        else: #se o nó que queremos excluir não é nó folha, temos que procurar algum descendente que seja nó folha
            pai_esq = raiz
            pai_dir = raiz
            aux_esq = raiz.esq
            aux_dir = raiz.dir

            if (aux_esq!=None and aux_dir!=None):

                while ((aux_esq.esq!=None and aux_esq.dir!=None) and (aux_dir.esq!=None and aux_esq.dir!=None)): #procura dos dois lados por um descendente nó folha
                    pai_esq = aux_esq
                    pai_dir = aux_dir
                    aux_esq = aux_esq.esq
                    aux_dir = aux_dir.dir

                if (aux_esq.esq==None and aux_esq.dir==None): #se o primeiro nó folha que encontrou for do lado esquerdo, substitui o valor que queremos remover por ele e aponta seu antigo pai para null
                    raiz.chave = aux_esq.chave
                    pai_esq.esq = None

                else:  #caso contrário, substitui o valor que queremos remover por ele e aponta seu antigo pai para null
                    raiz.chave = aux_dir.chave
                    pai_dir.dir = None

            elif (aux_esq==None): #caso um lado seja null, procurar o nó folha somente do outro lado
                while (aux_dir.esq!=None and aux_esq.dir!=None):
                    pai_dir = aux_dir
                    aux_dir = aux_dir.dir
                raiz.chave = aux_dir.chave
                pai_dir.dir = None 

            else:
                while(aux_esq.esq!=None and aux_esq.dir!=None):
                    pai_esq = aux_esq
                    aux_esq = aux_esq.esq

                raiz.chave = aux_esq.chave
                pai_esq.esq = None

        return True #retorna verdadeiro se a remoção foi bem sucedida

    def removeGlobal(self, chave): #função para de remoção para ser chamada na main
        result = self.remove(self.raiz, chave, 0)
        return result
    
    def imprime(self, raiz, nivel): #função para percorrer a árvore e imprimi-la 

        if(raiz!=None):
            self.imprime(raiz.dir, nivel + 1)
            print("  " * nivel + str(raiz.chave))
            self.imprime(raiz.esq, nivel + 1)

#### fim da classe ####

ArvDigital = ArvoreDigital()

print(f'Programa Árvore de Busca Digital (Trie) de {total_bits} bits')

opcao = 0

while opcao != 5:
    
    print("\n")
    print("Entre com a opção desejada:")
    print(" --- 1: Inserir")
    print(" --- 2: Remover")
    print(" --- 3: Buscar")
    print(" --- 4: Imprimir")
    print(" --- 5: Sair do programa")
    print("\n")

    opcao = int(input("Digite a opção desejada:"))
    
    if opcao == 1:
        x = int(input("Informe o valor -> "))
        ArvDigital.insereGlobal(x)

    elif opcao == 2:
        x = int(input("Informe o valor -> "))

        if ArvDigital.removeGlobal(x) == False:
            print("Valor não encontrado!")
        else:
            print(f'Valor {x} removido com sucesso')

    elif opcao == 3:
        x = int(input("Informe o valor -> "))
        if ArvDigital.buscaGlobal(x) == False:
            print("Valor não encontrado")
        else:
            print("Valor encontrado!")	 

    elif opcao == 4:
        print("\n")
        ArvDigital.imprime(ArvDigital.raiz, 0)

    elif opcao == 5:
        print("O programa será encerrado")
        break
        
