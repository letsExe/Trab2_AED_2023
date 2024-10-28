#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

    typedef struct{
        int cod_disciplina;
        int ano_letivo;
        int cod_professor;
    }Info_Matricula;

    typedef struct{
        Info_Matricula info_matricula;
        char cod[7];

        int esq;
        int dir;
    }Matricula;

    //DESCRICAO:    ESTRUTURA-LISTA DE MODO A AUXILIAR A IMPRESSÃO DOS CÓDIGOS DOS PRODUTOS EM FORMATO DE ÁRVORE BINÁRIA.
    //              A LISTA GUARDA OS CÓDIGOS DOS NÓS DE FORMA ORDENADA COM ALTURA DO NÓ EM RELAÇÃO A RAIZ DA ÁRVORE.
    typedef struct no{
        char cod[7];//código do produto
        int h_node;//altura do nó
        struct no* prox;
    }Lista;

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    FILE* inicializarMatricula_arqBin(char* file_name);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void inicializarMatricula(FILE* fb);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void escreverMatricula(FILE* fb, Matricula* m, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    Matricula* lerMatricula(FILE* fb, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int inserirMatricula_bin(FILE* fb, Matricula* root);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void cadastrarMatricula(FILE* fbMatricula, FILE* fbDisciplina, FILE* fbProfessor);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int buscarMatricula_pos(FILE* fb, char* cod, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int inserirMatricula(FILE* fb, Matricula* newMatricula, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void imprimirMatricula(FILE *fb);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void imprimirMatricula_inOrdem(FILE* fb, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void removerMatricula(FILE* fbMatricula);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int removerNo(FILE *fb, int pos, char cod[]);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void trocar_info(FILE* fb, int pos_dest, int pos_source);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void maximo(FILE* fb, int pos, char cod[]);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void minimo(FILE* fb, int pos, char cod[]);

    //DESCRICAO:    FUNÇÃO RECURSIVA QUE RETORNA A ALTURA DA ÁRVORE BINÁRIA
    //ENTRADA:      PONTEIRO NAO VAZIO PARA O ARQUIVO BINARIO E POSICAO pos DA CABECA DO ARQUIVO (-1 OU 0)
    //              QUE IRÁ SE ALTERAR A CADA CHAMADA RECURSIVA DE MODO A PERCORRER A ARVORE BINÁRIA
    //SAIDA:        ALTURA DA ÁRVORE BINARIA    
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA O ARQUIVO BINARIO
    //POS-CONDICAO: ALTURA DA ÁRVORE BINÁRIA É RETORNADA
    //              NENHUMA MUDANÇA É REALIZADA DENTRO DO ARQUIVO BINARIO
    int altura_arvore(FILE* fb, int pos);

    //DESCRICAO:    FUNÇÃO DE INTERAÇÃO COM O USUÁRIO. TEM A FUNCIONALIDADE FINAL DE IMPRIMIR OS CÓDIGOS DOS PRODUTOS
    //              CADASTRADOS EM FORMATO DE ÁRVORE BINÁRIO. ELE FAZ ISSO DA SEGUINTE FORMA: CHAMA A FUNÇÃO percorrer_arvore
    //              QUE PASSA POR TODOS OS NÓS DA ÁRVORE E OS INSERE EM UMA LISTA ENCADEADA ORDENADA PELA ALTURA DO NÓ.
    //              EM SEGUIDA, CHAMA A FUNÇÃO imprimir_em_arvore QUE IMPRIME ESSA LISTA NO FORMATO DE ÁRVORE.
    //              ENTÃO A FUNÇÃO LIBERA A MEMÓRIA ALOCADA PARA A LISTA ATÉ A PRÓXIMA CHAMADA DE FUNÇÃO
    //ENTRADA:      PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO
    //SAIDA:        -
    //PRE-CONDICAO: PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO
    //POS-CONDICAO: CÓDIGOS DOS PRODUTOS IMPRESSOS NA TELA EM FORMATO DE ÁRVORE BINÁRIA.
    //              NENHUMA MUDANÇA É REALIZADA DENTRO DO ARQUIVO BINÁRIO
    void imprimir_arvore(FILE* fb);

    //DESCRICAO:    FUNÇÃO RECRUSIVA QUE PERCORRE A ÁRVORE DE MODO pre_Ordem E FAZ A INSERSÃO DOS NÓS EM UMA
    //              LISTA ENCADEADA ORDENADA PELA ALTURA DESSES NÓS
    //ENTRADA:      PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO, LISTA INICALIZADA, POSIÇÃO DA RAIZ (0 OU -1) E INTEIRO
    //              PARA A ALTURA DOS NÓS, INICIADO COMO 0, SENDO INCREMENTADO A CADA CHAMADA RECURSIVA
    //SAIDA:        LISTA ENCADEADA ORDENADA COM OS NÓS INSERIDOS
    //PRE-CONDICAO: PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO E LISTA INICALIZADA. CABEÇALHO INICALIZADO E ALTURA DOS NÓS
    //              INICIADA COMO 0
    //POS-CONDICAO: LISTA ENCADEADA ALTERADA.
    //              NENHUMA MUDANÇA É RELIZADA DENTRO DO ARQUIVO BINÁRIO
    Lista* percorrer_arvore(FILE* fb, Lista* l, int pos, int h_node);

    //DESCRICAO:    FUNÇÃO RECURSIVA DE INSERSÃO ORDENADA EM UMA LISTA ENCADEADA DINAMICAMENTE.
    //              O CRITÉRIO DE ORDENAÇÃO É A ALTURA DO NÓ (h_node), DO MENOR (0) PARA O MAIOR (altura_arvore)
    //ENTRADA:      LISTA ENCADEADA, CODIGO DO PRODUTO (INFORMACAO NECESSARIA A LISTA) E ALTURA DO NÓ (h_node)
    //SAIDA:        LISTA COM OS NÓS INSERIDOS
    //PRE-CONDICAO: LISTA INICIALIZADA, CÓDIGOS E ALTURAS VÁLIDAS E EXISTENTES
    //POS-CONDICAO: LISTA ENCADEADA ALTERADA.
    //              NENHUMA MUDANÇA É RELIZADA DENTRO DO ARQUIVO BINÁRIO
    Lista* inserir_ordenado(Lista* l, char* cod, int h_node);

    //DESCRICAO:    IMPRIME A LISTA ENCADEADA EM FORMATO DE ÁRVORE BINÁRIA. IMPRIME CADA NÓ EM ORDEM, E QUANDO O ATRIBUTO
    //              h_node MUDA DE UM NÓ PARA O OUTRO, UMA LINHA É PULADA.
    //ENTRADA:      LISTA INICIALIZADA E ALTURA DA ÁRVORE BINÁRIA
    //SAIDA:        -
    //PRE-CONDICAO: LISTA INICIALIZADA E ALTURA VÁLIDA DA ÁRVORE (VALOR DADO PELA FUNÇÃO altura_arvore)
    //POS-CONDICAO: CÓDIGOS DOS PRODUTOS IMPRESSOS NA TELA EM FORMATO DE ÁRVORE BINÁRIA.
    //              NENHUMA MUDANÇA É REALIZADA DENTRO DO ARQUIVO BINÁRIO
    void imprimir_em_arvore(Lista* l, int altura_arvore);

    //DESCRICAO:    LIBERA A MEMÓRIA ALOCADA PARA TODOS OS NÓS DA LISTA ENCADEADA
    //ENTRADA:      LISTA ENCADEADA
    //SAIDA:        -
    //PRE-CONDICAO: LISTA INICIALIZADA
    //POS-CONDICAO: MEMÓRIA LIBERADA
    void liberar_lista(Lista *l);

    //DESCRICAO:    IMPRIME A LISTA DE NÓS LIVRES (REMOVIDOS)
    //ENTRADA:      PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO
    //SAIDA:        -
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO
    //POS-CONDICAO: CHAMA A FUNCAO imprimir_nosLivres E LISTA DE NOS LIVRES IMPRESSAS NO TERMINAL
    //              NENHUMA MUDANCA É FEITA NO ARQUIVO BINARIO
    void imprimir_listaLivres(FILE *fb);

    //DESCRICAO:    FUNCAO RECURSIVA QUE PERCORRE A LISTA DE NOS LIVRES E IMPRIME OS NÓS
    //ENTRADA:      PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO E posLivre (CABECA DA LISTA DE NOS LIVRES/REMOVIDOS)
    //SAIDA:        -
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO E POSICAO VALIDA (-1 OU MAIOR)
    //POS-CONDICAO: LISTA DE NOS LIVRES IMPRESSAS NO TERMINAL
    //              NENHUMA MUDANCA É FEITA NO ARQUIVO BINARIO
    void imprimir_nosLivres(FILE *fb, int pos);

#endif