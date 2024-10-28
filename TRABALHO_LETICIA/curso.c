#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cabecalho.h"
#include "curso.h"

//DESCRICAO:    FUNCAO RESPONSÁVEL PELA CRIAÇÃO DO ARQUIVO BINÁRIO. ELE PRIMIERO FAZ A TENTATIVA DE ABRIR UM ARQUIVO JA
//              EXISTENTE. SE NÃO FOR POSSÍVEL, ELE CRIA OUTRO ARQUIVO A INICIALIZA A ÁRVORE BINÁRIA (O CABEÇALHO)
//ENTRADA:      NOME DO ARQUIVO BINÁRIO EXISTENTE/A SER CRIADO
//SAIDA:        PONTEIRO NAO NULO PARA O ARQUIVO BINARIO
//PRE-CONDICAO: NOME VALIDO DE ARQUIVO
//POS-CONDICAO: ARQUIVO BINARIA CRIADO OU O SE RETORNA O PONTEIRO PARA O ARQUIVO
FILE* inicializarCurso_arqBin(char* file_name){
    FILE* fb = fopen(file_name, "r+b");//tenta abrir o arquivo binário, caso ele exista

    if(fb == NULL){//caso ele não exista, é criado um novo
        fb = fopen(file_name, "w+b");
        inicializarCurso(fb);//se inicializa o cabeçalho
    }

return fb;
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
void inicializarCurso(FILE* fb){
    Cabecalho *cab = (Cabecalho*)malloc(sizeof(Cabecalho));

    cab->posCabeca = -1;//inicializar "cabeca" como "NULL"
    cab->posTopo = 0;//indica que a proximo posicao livre como a primeira posicao disponivel
    cab->posLivre = -1;//inicializar lista de nós livres como "NULL"

    escreverCabecalho(fb, cab);//escreve o cabecalho inicializado
    free(cab);//desaloca memória do ponteiro auxiliar
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
void escreverCurso(FILE* fb, Curso* c, int pos){
    fseek(fb, sizeof(Cabecalho) + sizeof(Curso) * pos, SEEK_SET);//aponto para a Arvore na posicao desejada, pulando os bits do cabecalho
    fwrite(c, sizeof(Curso), 1, fb);//copia a estrutura da arvore para o ARQUIVO BINARIO, de acordo com o que foi apontado em FSEEK
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
Curso* lerCurso(FILE* fb, int pos){
    Curso* c = (Curso*)malloc(sizeof(Curso));

    fseek(fb, sizeof(Cabecalho) + sizeof(Curso) * pos, SEEK_SET);//aponta para a Arvore na posicao desejada, pulando os bits do cabec
    fread(c, sizeof(Curso), 1, fb);//copia para -r- a estrutura ARVORE de acordo com o que foi apontado em FSEEK no ARQUIVO BINARIO

    return c;
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
int inserirCurso_bin(FILE* fb, Curso* root){
    Cabecalho* cab = lerCabecalho(fb);
    int insertion_pos;

    if(cab->posLivre == -1){
        insertion_pos = cab->posTopo;
        
        escreverCurso(fb, root, cab->posTopo);
        cab->posTopo++;
    }
    else{
        insertion_pos = cab->posLivre;
        
        Curso* cLivre = lerCurso(fb, cab->posLivre);
        escreverCurso(fb, root, cab->posLivre);
        cab->posLivre = cLivre->esq;
        
        free(cLivre);
    }

    if(vazio(cab)) cab->posCabeca = insertion_pos;

    escreverCabecalho(fb, cab);

    free(cab);

    return insertion_pos;
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
void cadastrarCurso(FILE* fb){
    Cabecalho* cab = lerCabecalho(fb);
    Curso* c = (Curso*)malloc(sizeof(Curso));

    c->esq = c->dir = -1;//no ainda nao possui filhos. inicializados como "null"

    printf("\n*CADASTRAR CURSO*\n\n");

    printf("-> DIGITE O CODIGO DO CURSO: ");
    scanf("%d%*c", &c->cod);

    //não permite inserir um codigo já existente
    if(buscarCurso_pos(fb, c->cod, cab->posCabeca) == -1){

        printf("\n-> DIGITE O NOME DO CURSO (MAX. DE 50 CARACTERES): ");
        scanf("%[^\n]%*c", c->info_curso.nome);
        c->info_curso.nome[50] = '\0';//apaga o possível excesso de caracteres

        printf("\n-> DIGITE A AREA DO CURSO (*E-> EXATAS; *H-> HUMANAS; *B-> BIOLOGICAS): ");
        scanf("%c%*c", c->info_curso.area);

        inserirCurso(fb, c, cab->posCabeca);//função recursiva de inserir
        
        printf("\nCURSO INSERIDO COM SUCESSO...\n");
    }
    else printf("\nCODIGO EXISTENTE: NAO FOI POSSIVEL CONCLUIR O CADASTRO...\n");

    free(cab);
    free(c);
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
int buscarCurso_pos(FILE* fb, int cod, int pos){
//faz a busca no metodo árvore binaria de busca
    if(pos == -1) return -1;
    else{
        Curso* c=lerCurso(fb,pos);
    
        if(c->cod > cod) return buscarCurso_pos(fb, cod, c->esq);//todos os codigos menores que a raiz se encontram a esquerda
        else if(c->cod < cod) return buscarCurso_pos(fb, cod, c->dir);//todos os codigos maiores que a raiz se encontram a direita

        free(c);
    }
return pos;
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
int inserirCurso(FILE* fb, Curso* newCurso, int pos){
    if(pos == -1){ //significa que a arvore está vazia ou que foi encontrada uma posição livre a ser inserida o novo nós
        int insertion_pos = inserirCurso_bin(fb, newCurso);
        return insertion_pos;
    }
    else{
        Curso* currentCurso = lerCurso(fb, pos);

        if(newCurso->cod < currentCurso->cod){
            currentCurso->esq = inserirCurso(fb, newCurso, currentCurso->esq);
            escreverCurso(fb, currentCurso, pos);
        }
        else{
            currentCurso->dir = inserirCurso(fb, newCurso, currentCurso->dir);
            escreverCurso(fb, currentCurso, pos);
        }

        free(currentCurso);
    }
    return pos;
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
void imprimirCurso(FILE *fb){
    Cabecalho* cab=lerCabecalho(fb);

    printf("\n*LISTA DE CURSOS (IN-ORDEM)*\n");
    //faz uma verificação inicial apenas por questões de estética da interface
    if(vazio(cab)) printf("\nNAO HA CURSOS CADASTRADOS...\n");
    else printf("\n%-11s%-55s%-5s\n", "CODIGO", "NOME", "AREA");

    imprimirCurso_inOrdem(fb, cab->posCabeca);

    free(cab);
}

//DESCRICAO:    
//ENTRADA:      
//SAIDA:      
//PRE-CONDICAO:
//POS-CONDICAO:
void imprimirCurso_inOrdem(FILE* fb, int pos){
    if(pos!=-1){
        Curso* c = lerCurso(fb, pos);

        imprimirCurso_inOrdem(fb, c->esq);//imprime primeiro os elementos da esquerda
        printf("%-10.3d %-55s %-5c\n", c->cod, c->info_curso.nome, c->info_curso.area);//imprime a raiz
        imprimirCurso_inOrdem(fb, c->dir);//imprime então os elementos da direita
        
        free(c);
    }
}
