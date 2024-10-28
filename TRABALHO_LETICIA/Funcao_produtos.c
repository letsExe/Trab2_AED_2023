#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Prototipo_auxiliares.h"
#include "Prototipo_comandos.h"
#include "Prototipo_interface.h"
#include "Prototipo_produtos.h"

// Realiza a modificação do cabecalho
// Entrada: Arquivo binário e cabeçalho auxiliar
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário modificado
void escreve_cabecalho(FILE* arq, Cabecalho* Cab){
    fseek(arq, 0, SEEK_SET); // Posiciona no arquivo
    fwrite(Cab, sizeof(Cabecalho), 1, arq); // Escreve informação
}

// Realiza a incialização do cabeçalho do arquivo
// Entrada: Arquivo binário
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo binário incializado
void cria_lista_vazia(FILE* arq){
    Cabecalho * cab = (Cabecalho*) malloc(sizeof(Cabecalho)); //Aloca cabeçalho temporario
    cab->cabeca = -1; //Inicializa fatores
    cab->livre = -1;
    cab->topo = 0;
    escreve_cabecalho(arq,cab); //Escreve arquivo
    free(cab); //Libera temporário
}

// Realiza uma cópia das informações que estão no cabeçalho
// Entrada: Arquivo binário
// Retorno: Cabeçalho cópia alocado
// Pré-condição: arquivo binário tem que estar incializado
// Pós-condição: arquivo binário incializado
Cabecalho* le_cabecalho(FILE * arq){
    Cabecalho* cab = (Cabecalho *) malloc(sizeof(Cabecalho)); //Aloca cabeçalho
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(Cabecalho), 1, arq);
    
    return cab;
}

// Realiza a leitura do arquivo binário para copiar um nó da árvore
// Entrada: Arquivo binário e posição do elemento
// Retorno: Nó alocado da árvore
// Pré-condição: nenhuma
// Pós-condição: nenhuma
No_Arvore* le_Arvore(FILE* arquivo, int posi){
    No_Arvore* aux = (No_Arvore*) malloc(sizeof(No_Arvore));

    fseek(arquivo, sizeof(Cabecalho)+posi*sizeof(No_Arvore), SEEK_SET);
    fread(aux, sizeof(No_Arvore), 1, arquivo);

    return aux;
}

// Realiza a inserção e modificação do arquivo binário
// Entrada: arquivo binário, nó que será inserido e indice do arquivo que ocorrerá a inserção
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
void escreve_Arvore(FILE* arq, No_Arvore* aux, int posi){
    fseek(arq, sizeof(Cabecalho) + posi*sizeof(No_Arvore), SEEK_SET);
    fwrite(aux, sizeof(No_Arvore), 1, arq);
}

// Procura a posição ocupada pelo elemento com a chave desejada
// Entrada: arquivo binário e chave do código
// Retorno: posição se encontrado e -1 se não estiver na lista
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: nenhuma
int procura_codigo(FILE* arquivo, int key){
    Cabecalho* cab = le_cabecalho(arquivo);
    if(cab->cabeca != - 1){
        No_Arvore* verifica = le_Arvore(arquivo, 0);
        int posi = 0; //Sempre começa pela cabeça

        while(1){
            if(verifica->codigo == key) return posi;
            if(verifica->codigo > key){ //Se a chave for menor
                if(verifica->noEsquerdo == - 1) break; //Achou a posição em que vai inserir
                posi = verifica->noEsquerdo; //Guarda o nó que será verificado
            }
            else{ //Se não a chave é menor, já que igual não pode
                if(verifica->noDireito == - 1) break; //Achou a posição em que vai inserir
                posi = verifica->noDireito; //Guarda o nó que será verificado
            }
            
            free(verifica); //Libera o ponteiro alocado antes de fazer a transição
            verifica = le_Arvore(arquivo, posi); //Realiza transição
        }

        free(verifica); //Libera o ponteiro alocado antes de retornar a posição
    }
    return -1;
}

// Configura e inicializa um nó para inserir na árvore
// Entrada: struct do produto preenchida
// Retorno: Nó alocado da árvore
// Pré-condição: struct do produto tem que apresentar o código
// Pós-condição: nenhuma
No_Arvore* inicializa_No_arvore(Produtos* produto){
    No_Arvore* aux = (No_Arvore*) malloc(sizeof(No_Arvore));

    aux->codigo = produto->codigo; //Define a chave de procura no Nó
    aux->produto = *produto; //Salva as informações do produto
    aux->noDireito = -1; //Define como nulo o nó direito
    aux->noEsquerdo = -1; //Define como nulo o nó esquedo

    return aux;
}

// Realiza uma busca de uma posição livre da árvore, ou não, e retorna o nó pai deste
// Entrada: arquivo binário e chave de busca
// Retorno: Nó alocado da árvore
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int procura_Posi_Anterior(FILE* arquivo, int key){
    No_Arvore* verifica = le_Arvore(arquivo, 0);
    int posi = 0; //Sempre começa pela cabeça

    while(1){
        if(verifica->codigo > key){ //Se a chave for menor
            if(verifica->noEsquerdo == - 1) break; //Achou a posição em que vai inserir
            posi = verifica->noEsquerdo; //Guarda o nó que será verificado
        }
        else{ //Se não a chave é menor, já que igual não pode
            if(verifica->noDireito == - 1) break; //Achou a posição em que vai inserir
            posi = verifica->noDireito; //Guarda o nó que será verificado
        }
        
        free(verifica); //Libera o ponteiro alocado antes de fazer a transição
        verifica = le_Arvore(arquivo, posi); //Realiza transição
    }

    free(verifica); //Libera o ponteiro alocado antes de retornar a posição
    return posi;
}

// Encadeia com o nó pai o novo nó inserido
// Entrada: arquivo binário, chave do código e posição do arquivo
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
void encadeia_No(FILE* arquivo, int codigo, int posi){
    No_Arvore* aux; //Nó para cópia
    int posi_Anterior;

    posi_Anterior = procura_Posi_Anterior(arquivo, codigo); //Deixa salvo a posição do nó da árvore
    aux = le_Arvore(arquivo, posi_Anterior); //Realiza uma cópia do nó para modificar
    
    if(aux->codigo > codigo) aux->noEsquerdo = posi; // codigo for menor que o do nó vai na esquerda
    else aux->noDireito = posi; //Se não vai na direita

    escreve_Arvore(arquivo, aux, posi_Anterior); //Reescreve o nó da arvore com o novo filho
}

// Encadeia com o nó pai o novo nó inserido
// Entrada: arquivo binário, chave do código e posição do arquivo
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
void inserir_Produto_Arquivo(Produtos* produto, FILE* arquivo){
    Cabecalho* cab = le_cabecalho(arquivo);
    No_Arvore* novo; //Nó que será inserido na arvore
    novo = inicializa_No_arvore(produto);

    if(cab->cabeca == -1 && cab->livre == -1){ //Caso de inserção caso a árvore não tenha sido inicializada
        if(cab->topo == 0) cab->topo++; //Caso já tenha sido inserido elmentos, mas todos foram removidos reiniciando a árvore
        cab->cabeca = 0; //Pelo padrão da árvore proposta, sempre será '0' a posição da cabeça
        escreve_Arvore(arquivo, novo, cab->cabeca); //Função que escreve o novo elemnto na árvore
    }
    else{ 
        if(cab->livre == -1){ // Caso não haja posição livre (nó livre)
            escreve_Arvore(arquivo, novo, cab->topo); //Função que escreve o novo elemnto na árvore
            encadeia_No(arquivo, novo->codigo, cab->topo); //Procura e encadeia o nó de maneira ordenada
            cab->topo++;
        }
        else{ //Para caso haja nó livre
            No_Arvore* aux = le_Arvore(arquivo, cab->livre); //Cópia para pegar o encadeamento de nós livres
            escreve_Arvore(arquivo, novo, cab->livre);
            if(cab->livre == 0) cab->cabeca = cab->livre; //Se a cabeça foi removida
            else encadeia_No(arquivo, novo->codigo, cab->livre);
            cab->livre = aux->noDireito;

            free(aux);
        }
    }

    escreve_cabecalho(arquivo, cab); //Modificando o cabeçalho com a nova inserção
    free(cab);
    free(novo);
}

// Realiza leitura das informações do produto e insere ele na árvore
// Entrada: arquivo binário e inputs do teclado
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
void cadastra_Produto_Individual(FILE* ArvoreBinaria){
    Produtos* aux = (Produtos*) malloc(sizeof(Produtos));

    printf("Insira o codigo do produto:\n>");
    scanf("%d%*c", &aux->codigo);

    printf("Insira o nome do produto (max. 50 caracteres):\n>");
    scanf("%[^\n]%*c", aux->nome);

    printf("Insira a marca do produto (max. 30 caracteres):\n>");
    scanf("%[^\n]%*c", aux->marca);

    printf("Insira a categoria do produto (max. 50 caracteres):\n>");
    scanf("%[^\n]%*c", aux->categoria);

    printf("Insira o estoque do produto:\n>");
    scanf("%d%*c", &aux->estoque);

    printf("Insira o preço do produto (R$ XX,XX):\n> R$ ");
    aux->valor = ler_Preco();

    if(procura_codigo(ArvoreBinaria, aux->codigo) != -1){ //Código repetido é ignorado
        printf("Codigo repetido, a operação sera cancelada...");
    }
    else{ //Se não, é inserido
        inserir_Produto_Arquivo(aux, ArvoreBinaria);
    }
    free(aux);
}

// Realiza a leitura de um arquivo e insere em uma struct
// Entrada: arquivo binário e inputs do teclado
// Retorno: se leitura for um sucesso 1, se não tiver leitura 0
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
int Le_Produto_Arquivo(FILE* ArvoreBinaria, FILE* finput){  
    Produtos* aux = (Produtos*) malloc(sizeof(Produtos));

    if(fscanf(finput, "%d;", &aux->codigo) == EOF) //Realiza a leitura do código e acaba se for Fim Do Arquivo
        return 0;

    fscanf(finput, "%[^;]%*c", aux->nome);

    fscanf(finput, "%[^;]%*c", aux->marca);

    fscanf(finput, "%[^;]%*c", aux->categoria);

    fscanf(finput, "%d;", &aux->estoque);

    aux->valor = le_Preco_Arquivo(finput); //Leitura para mascara a virgula

    if(procura_codigo(ArvoreBinaria, aux->codigo) != -1) printf("Insercao do produto com codigo [%d] cancelada (codigo repetido).\n", aux->codigo); //Se o código já foi inserido, vai ignorar a operação
    else{
        inserir_Produto_Arquivo(aux, ArvoreBinaria);
        printf("Insercao do produto com codigo [%d] realizada.\n", aux->codigo);
    }
    free(aux);
    return 1;
}

// Realiza leitura de um arquivo que contem as informações do produtos e insere ele na árvore
// Entrada: arquivo binário e arquivo de texto
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado e arquivo de texto no formato adequado
// Pós-condição: Arquivo binário modificado
void cadastra_Produto_Lote(FILE* ArvoreBinaria){
    FILE* finput;
    char nome[20];

    printf("Insira o nome do arquivo (com .txt):\n>");
    scanf("%[^\n]%*c", nome);

    finput = fopen(nome, "r");

    if(finput == NULL) printf("Diretorio invalido!\n");
    else{
        while(Le_Produto_Arquivo(ArvoreBinaria, finput)); //Vai inserir até encontrar o final do arquivo (EOF)
        printf("Leitura realizada com sucesso!\n");
    }
}

// Realiza a impressão dos códigos em ordem crescente de forma recursiva
// Entrada: arquivo binário e posição que sera imprimida
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: nenhuma
void Imprimir_In_Ordem(FILE* ArvoreBinaria, int pose){
    if(pose != -1){
        No_Arvore* aux = le_Arvore(ArvoreBinaria, pose);
        
        Imprimir_In_Ordem(ArvoreBinaria, aux->noEsquerdo); //Esquerda
        printf("Codigo: %03d - Nome: %s\n", aux->codigo, aux->produto.nome); //Meio
        Imprimir_In_Ordem(ArvoreBinaria, aux->noDireito); //Direita
        
        free(aux);
    }
}

// Realiza a impressão dos códigos em ordem crescente de forma recursiva
// Entrada: arquivo binário e posição que sera imprimida
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: nenhuma
void imprimir_Lista_Livre(FILE* ArvoreBinaria){
    Cabecalho *cab = le_cabecalho(ArvoreBinaria);

    if(cab->livre == -1) printf("Não ha nos livres\n"); //Verificação se há nós para imprimr
    else imprimir_No_Livre(ArvoreBinaria, cab->livre); //se há imprime
 
    free(cab);
}

// Opção slecianada do menu que verifica a lista de nós livres contém algo, se estiver imprime
// Entrada: arquivo binário
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: nenhuma
void imprimir_No_Livre(FILE* ArvoreBinaria, int posi){
    if(posi != -1){ //Se for igual a -1 já nem realiza nenhuma operação recursiva
        No_Arvore* aux = le_Arvore(ArvoreBinaria, posi);
        
        if(aux->noDireito == -1) printf("%d\n", posi); //Se o proximo elemento for o último
        else printf("%d -> ", posi); //Se não continuar imprimindo a lista encadead
        
        imprimir_No_Livre(ArvoreBinaria, aux->noDireito); //Chamada recursiva
        free(aux);
    }
}

// Opção selecionado do menu que verifica a arvore está inicializada, se estiver imprime
// Entrada: arquivo binário
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: nenhuma
void imprimir_Lista_Produtos(FILE* ArvoreBinaria){
    Cabecalho* cabecalho;
    cabecalho = le_cabecalho(ArvoreBinaria);

    if(cabecalho->cabeca == -1) printf("Arvore vazia...\n"); //Caso não há elementos
    else{
        Imprimir_In_Ordem(ArvoreBinaria, 0);
    }
    free(cabecalho);
}

// Função que realiza a leitura do teclado e inicializa a remoção de determinado produto, se presente no arquivo
// Entrada: arquivo binário
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
void remove_Produto_Individual(FILE* ArquivoBinario){
    int codigo;

    imprimir_Lista_Produtos(ArquivoBinario);
    printf("Insira o codigo desejado:\n>");
    scanf("%d%*c", &codigo);

    if(procura_codigo(ArquivoBinario, codigo) == -1) //Verifica se não há o elemento
        printf("Codigo não encontrado.\n");
    else{
        remove_Produto(ArquivoBinario, codigo, 0);
        printf("Produto removido!\n");
    }
}

// Procura o elemnto com menor codigo na árvore, ou sub-árvore
// Entrada: arquivo binário e posição inicial da árvore
// Retorno: posição do menor elemento, ou -1 se não for nada
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: nenhuma
int posi_codigo_Minimo(FILE* ArvoreBinaria, int posi){
    No_Arvore *aux = le_Arvore(ArvoreBinaria, posi);
    int posi_min;

    if(aux->noEsquerdo == -1) posi_min = posi; //Caso base
    else posi_min = posi_codigo_Minimo(ArvoreBinaria, aux->noEsquerdo); //Chamada recursiva a procura do menor código
    free(aux);

    return posi_min;
}

// Procura o elemnto com mair codigo na árvore, ou sub-árvore
// Entrada: arquivo binário e posição inicial da árvore
// Retorno: posição do maior elemento, ou -1 se não for nada
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: nenhuma
int posi_codigo_Maximo(FILE* ArvoreBinaria, int posi){
    No_Arvore *aux = le_Arvore(ArvoreBinaria, posi);
    int posi_max;

    if(aux->noDireito == -1) posi_max = posi; //Caso base
    else posi_max = posi_codigo_Maximo(ArvoreBinaria, aux->noDireito); //Chamada recursivo que procura o maior código
    free(aux);

    return posi_max;
}

// Função que troca informações de nós, mantendo o código do segundo
// Entrada: arquivo binário, posição do nó 1 e 2
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
void troca_No(FILE* ArvoreBinaria, int posi1, int posi2){
    No_Arvore *Elemento1 = le_Arvore(ArvoreBinaria, posi1);
    No_Arvore *Elemento2 = le_Arvore(ArvoreBinaria, posi2);
    No_Arvore *aux = (No_Arvore*) malloc(sizeof(No_Arvore));

    aux->produto = Elemento1->produto; //Guarda nó de informações do produto para troca

    Elemento1->produto = Elemento2->produto;
    Elemento1->codigo = Elemento2->produto.codigo;

    Elemento2->produto = aux->produto;

    escreve_Arvore(ArvoreBinaria, Elemento1, posi1); //Modifica as informações
    escreve_Arvore(ArvoreBinaria, Elemento2, posi2); //Modifica as informações

    free(aux);
    free(Elemento1);
    free(Elemento2);
}

// Função que realiza a leitura do arquivo e inicializa a remoção de determinado produto se presente no arquivo
// Entrada: arquivo binário
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
void remove_Produto_Lote(FILE* ArquivoBinario){
    FILE* finput;
    char nome[20];
    int codigo;

    printf("Insira o nome do arquivo (com .txt):\n>");
    scanf("%[^\n]%*c", nome);

    finput = fopen(nome, "r");

    if(finput == NULL) printf("Diretorio invalido!\n");
    else{
        while(fscanf(finput, "%d\n", &codigo) != EOF){ //Vai realizar a leitura dos produtos que precisam ser removidos até EOF
            if(procura_codigo(ArquivoBinario, codigo) == -1); //Se não há o codigo, não faz nada
            else remove_Produto(ArquivoBinario, codigo, 0); //Se há remove normalmente
        } 
        printf("Leitura realizada com sucesso, produtos removidos!\n");
    }
}

// Função recursiva de remoção do produto
// Entrada: arquivo binário, chave de procura e posição inicial da árvore/sub-árvore
// Retorno: retorna a posição do nó removido ou subsequente
// Pré-condição: Arquivo binário tem que estar inicializado
// Pós-condição: Arquivo binário modificado
int remove_Produto(FILE* ArvoreBinaria, int key, int posi){
    if(posi == -1) return -1; //Caso base
    No_Arvore* aux = le_Arvore(ArvoreBinaria, posi); // Nó de cópia para consultarmos as informações

    if(key < aux->codigo){ //Se a chave de pesquisa for menor
        aux->noEsquerdo = remove_Produto(ArvoreBinaria, key, aux->noEsquerdo);
        escreve_Arvore(ArvoreBinaria, aux, posi); //Caso haja uma alteração irá sobrescrever 
    }
    else if(key > aux->codigo){ //Se a chave de pesquisa for maior
        aux->noDireito = remove_Produto(ArvoreBinaria, key, aux->noDireito);
        escreve_Arvore(ArvoreBinaria, aux, posi); //Caso haja uma alteração irá sobrescrever 
    }
    else{ //Caso em que key == codigo
        if(aux->noEsquerdo == -1 && aux->noDireito == -1){ //Nó folha
            Cabecalho* cab = le_cabecalho(ArvoreBinaria);

            if(posi == cab->cabeca) cab->cabeca = -1;
            aux->noEsquerdo = -1; // Deixa nulo o nó esquerdo
            aux->noDireito = cab->livre; // Encadeia nós livres a direita
            cab->livre = posi; //Adiciona o nó na lista de livres

            escreve_Arvore(ArvoreBinaria, aux, posi);
            escreve_cabecalho(ArvoreBinaria, cab);

            posi = -1;
            free(cab);
        }
        else if(aux->noEsquerdo == -1){
            int posi_Min = posi_codigo_Minimo(ArvoreBinaria, aux->noDireito);
            No_Arvore *minimo = le_Arvore(ArvoreBinaria, posi_Min); //Nó auxiloar para consultar informação

            troca_No(ArvoreBinaria, posi, posi_Min); //Realiza a troca de posição no Arquivo
            free(aux); //libera o antigo ponteiro
            aux = le_Arvore(ArvoreBinaria, posi); //Lê novamente o posição trocada

            aux->noDireito = remove_Produto(ArvoreBinaria, minimo->codigo, aux->noDireito);
            escreve_Arvore(ArvoreBinaria, aux, posi);
            free(minimo); //Libera o auxiliar criado
        }
        else{
            int posi_Max = posi_codigo_Maximo(ArvoreBinaria, aux->noEsquerdo);
            No_Arvore *maximo = le_Arvore(ArvoreBinaria, posi_Max); //Nó auxiloar para consultar informação

            troca_No(ArvoreBinaria, posi, posi_Max); //Realiza a troca de posição no Arquivo
            free(aux); //libera o antigo ponteiro
            aux = le_Arvore(ArvoreBinaria, posi); //Lê novamente o posição trocada

            aux->noEsquerdo = remove_Produto(ArvoreBinaria, maximo->codigo, aux->noEsquerdo);
            escreve_Arvore(ArvoreBinaria, aux, posi);
            free(maximo); //Libera o auxiliar criado
        }
    }

    free(aux);
    return posi;
}

// Função que apresenta as opções e tipos de atualizações de valores
// Entrada: arquivo binário com a árvore
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void atualiza_Produto(FILE* ArvoreBinaria){
    
    quebra_Pagina();
    
    printf("1 - Atualizar valor\n");
    printf("2 - Atualizar estoque\n");
    printf("3 - Atualizar em lote\n>");
    
    int escolha;
    
    scanf("%d%*c", &escolha);
    
    switch (escolha){
                case 1 :
                    atualiza_Produto_valor(ArvoreBinaria);
                    break;
                case 2 :
                    atualiza_Produto_estoque(ArvoreBinaria);
                    break;
                case 3 :
                    atualiza_Produto_Lote(ArvoreBinaria);
                    break;
                default:
                    printf("Comando invalido!\n");
                    break;
            }
}

// Atualiza individualmente o valor do produto desejado a partir de seu código
// Entrada: arquivo binário com a árvore e input do teclado
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
void atualiza_Produto_valor(FILE* ArvoreBinaria){
    
    int codigo, posi;
    
    imprimir_Lista_Produtos(ArvoreBinaria);
    
    printf("Digite o codigo do produto cujo valor deve ser alterado:\n>");
    
    scanf("%d%*c", &codigo);
    
    if( (posi = procura_codigo(ArvoreBinaria, codigo)) == -1){ //Caso não exist o produto
        printf("Produto nao existe\n");
    }
    else{ // Se não
        No_Arvore* aux = le_Arvore(ArvoreBinaria, posi); //Copia o produto para modificar só a informção desejada
        
        printf("Digite o novo preço do produto R$ XX,XX:\n>R$ ");
        aux->produto.valor = ler_Preco(); //Troca de valor
        
        escreve_Arvore(ArvoreBinaria, aux, posi); //Sobreescreve informação com ela alterada
        
        printf("Valor do produto alterado!\n");
        free(aux);
    }    
}

// Atualiza individualmente o estoque do produto desejado a partir de seu código
// Entrada: arquivo binário com a árvore e input do teclado
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
void atualiza_Produto_estoque(FILE* ArvoreBinaria){
    
    int codigo, posi;
    
    printf("Digite o código do produto cujo estoque deve ser alterado:\n>");
    
    scanf("%d%*c", &codigo);
    
    if( (posi = procura_codigo(ArvoreBinaria, codigo)) == -1){ //Caso o produto não exista
        printf("Produto nao existe\n");
    }
    else{ // Se não
        No_Arvore* aux = le_Arvore(ArvoreBinaria, posi); //Copia o produto para modificar só a informção desejada
        
        printf("Digite o novo estoque do produto em questão:\n>");
        scanf("%d%*c", &aux->produto.estoque); //Troca estoque
        
        escreve_Arvore(ArvoreBinaria, aux, posi); //Sobreescreve informação com ela alterada
        
        printf("Estoque do produto alterado!\n");
        free(aux);
    }
}

// Atualiza individualmente o estoque do produto desejado a partir de seu código lido do arquivo
// Entrada: arquivo binário com a árvore, codigo e estoque
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
void atualiza_Produto_estoque_LOTE(FILE* ArvoreBinaria, int codigo, int estoque){
    int posi;
    
    if( (posi = procura_codigo(ArvoreBinaria, codigo)) == -1) printf("Impossivel alterar estoque, codigo [%d] nao encontrado!\n", codigo); //Não faz nada
    else{
        No_Arvore* aux = le_Arvore(ArvoreBinaria, posi); //Copia o produto para modificar só a informção desejada
        
        aux->produto.estoque = estoque;
        escreve_Arvore(ArvoreBinaria, aux, posi); //Sobreescreve informação com ela alterada
        
        printf("Estoque do produto com codigo [%d] alterado!\n", codigo);
        free(aux);
    }
}

// Atualiza individualmente o valor do produto desejado a partir de seu código lido do arquivo
// Entrada: arquivo binário com a árvore, codigo e valor
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
void atualiza_Produto_valor_LOTE(FILE* ArvoreBinaria, int codigo, double valor){
    int posi;
    
    if( (posi = procura_codigo(ArvoreBinaria, codigo)) == -1) printf("Impossivel alterar valor, codigo [%d] nao encontrado!\n", codigo); //Não faz nada
    else{
        No_Arvore* aux = le_Arvore(ArvoreBinaria, posi); //Copia o produto para modificar só a informção desejada
        
        aux->produto.valor = valor;
        escreve_Arvore(ArvoreBinaria, aux, posi); //Sobreescreve informação com ela alterada
        printf("Valor do produto com codigo [%d] alterado!\n", codigo);
        free(aux);
    }
}

// Realiza a leitura do nome do arquivo e altera as informações desejadas
// Entrada: arquivo binário com a árvore e nome do arquivo que será lido
// Retorno: nenhum
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
void atualiza_Produto_Lote(FILE* ArvoreBinaria){
    FILE* finput;
    char nome[50];

    printf("Escreva o diretorio do arquivo:\n>");
    scanf("%[^\n]%*c", nome);

    finput = fopen(nome, "r");

    if(finput == NULL) printf("Diretorio invalido!\n"); //Caso o arquivo não exista
    else{ //Se não
        while(Atualiza_Produto_Arquivo(ArvoreBinaria, finput));
        printf("Produtos atualizados!\n");
    }
    
    free(finput);
}

// Realiza a leitura do arquivo e altera as informações desejadas
// Entrada: arquivo binário com a árvore e arquivo de leitura
// Retorno: 1 para dizer que não acabou o 0 para End Of File
// Pré-condição: Arquivo binário tem que estar inicializado e posição existentes
// Pós-condição: Arquivo binário modificado
int Atualiza_Produto_Arquivo(FILE* ArvoreBinaria, FILE* finput){
    char leitura[50], *aux, *aux1, *aux2, *aux3;
    int codigo, flagVirgula;

    if(fscanf(finput,"%[^\n]\n", leitura) == EOF) return 0;

    flagVirgula = 0; //Flag de verificação se é um valor em dinheiro (com virgula)
    aux = (char*) malloc(sizeof(strlen(leitura) + 1)); //Aloca dinamicamente para strtok
    strcpy(aux, leitura); //Copia para o auxiliar
    strtok(aux, ";"); //Lê até encontrar o ';'
    codigo = converte_String_Int(aux); //Sempre lê o código primeiro

    aux2 = strtok(NULL, ";");
    if(strchr(aux2,',') != NULL) flagVirgula = 1; //Verifica se vai manter o estoque
    if(aux2 != 0 && !flagVirgula){
        int estoque;
        estoque = converte_String_Int(aux2);
        atualiza_Produto_estoque_LOTE(ArvoreBinaria, codigo, estoque);
    }

    if(flagVirgula) aux3 = aux2;
    else aux3 = strtok(NULL, "\0");
    if(aux3 != 0){
        double valor;
        valor = converte_String_Double(aux3);
        atualiza_Produto_valor_LOTE(ArvoreBinaria, codigo, valor);
    }
    
    free(aux);
    return 1;
}

// Realiza a impressão das informações do produto a partir do código
// Entrada: arquivo binário com a árvore e o código do produto
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_produto_unico (FILE* arquivo){
    No_Arvore* aux;
    int pos, codigo;

    printf ("\nDigite o codigo do produto: ");
    scanf ("%d%*c", &codigo);

    pos = procura_codigo(arquivo,codigo); 

    if(pos == -1){ //Caso o código não exista
        printf ("Codigo nao encontrado...\n");
    }
    else{ //Se não imprime as informações
        aux = le_Arvore(arquivo, pos);

        printf ("\n------ PRODUTO ------\n");
        printf ("Codigo: %d  |  Nome: %s\n", aux->produto.codigo, aux->produto.nome);
        printf ("Marca: %s  | Categoria: %s\n", aux->produto.marca, aux->produto.categoria);
        printf ("Estoque: %d\n", aux->produto.estoque);
        printf ("Preco: R$ %.2lf\n", aux->produto.valor);
        printf ("---------------------\n");

        free(aux);
    }
}

// Verifica se a árvore é vazia
// Entrada: Lista que da Arvore_Binaria auxíliar
// Retorno: 1 para vazio, ou 0 para com conteúdo
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int vazia_arvorebin(Arvore_Bin* arvore){
	return (arvore == NULL);
}

// Encadeia na lista auxílizar de maneira ordenada por nível
// Entrada: Lista que da Arvore_Binaria auxíliar
// Retorno: Cabeça da lista alterada
// Pré-condição: nenhuma
// Pós-condição: Lista modificada
Arvore_Bin* inserir_arvore_ordenada (Arvore_Bin* arvore, int codigo, int nivel){
    if (vazia_arvorebin(arvore)){ //Caso base da recursão
        Arvore_Bin* aux;
        aux = (Arvore_Bin*) malloc (sizeof(Arvore_Bin));
        aux->codigo = codigo;
        aux->nivel = nivel;
        aux->prox = NULL;
        return aux; //Caso que acaba com a recursividade
    }
    else if (nivel < arvore->nivel){ // se o nível for menor
        Arvore_Bin* aux;
        aux = (Arvore_Bin*) malloc (sizeof(Arvore_Bin));
        aux->codigo = codigo;
        aux->nivel = nivel;
        aux->prox = arvore;
        return aux; //Caso que acaba com a recursividade
    }
    else{ // se o nível for maior
        arvore->prox = inserir_arvore_ordenada (arvore->prox, codigo, nivel); // Chamada recursiva
        return arvore;
    }
}

// Imprime a árvore em níveis
// Entrada: Lista que da Arvore_Binaria auxíliar e nível
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimir_arvorebin(Arvore_Bin* arvore, int nivel){
	if (!vazia_arvorebin(arvore)){
		if (arvore->nivel > nivel){
            printf ("\n");
            nivel += 1; //Incremento do nível
		}
		printf ("%d ", arvore->codigo);
		imprimir_arvorebin (arvore->prox, nivel); //Chamada recursiva
	}
	else
		printf ("\n\n"); //Caso base
}

// Função que cria a árvore
// Entrada: Arquivo binário, posição, arvore binária auxíliar e nível
// Retorno: Arvore auxíliar modificada
// Pré-condição: nenhuma
// Pós-condição: Lista modificada
Arvore_Bin* criar_lista_niveis_arvore (FILE* ArvoreBinaria, int pose, Arvore_Bin* arvore, int nivel){
    if(pose != -1){
        No_Arvore* aux = le_Arvore(ArvoreBinaria, pose);

        arvore = criar_lista_niveis_arvore (ArvoreBinaria, aux->noEsquerdo, arvore, nivel+1); //Esquerda
        arvore = inserir_arvore_ordenada(arvore,aux->codigo,nivel); //Meio
        arvore = criar_lista_niveis_arvore (ArvoreBinaria, aux->noDireito, arvore, nivel+1); //Direita

        free(aux);
        return arvore;
    }
    return arvore;
}

// Libera todos os elementos criados temporariamente para impressão de produtos
// Entrada: Lista que da Arvore_Binaria auxíliar
// Retorno: Cabeça da lista alterada
// Pré-condição: nenhuma
// Pós-condição: Lista modificada
Arvore_Bin* remover_arvorebin(Arvore_Bin* arvore){
	Arvore_Bin* ptr;

	while (!vazia_arvorebin(arvore)){
		ptr = arvore->prox;
		free(arvore);
		arvore = ptr;
	}

	return ptr;
}