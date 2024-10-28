#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "interface.h"

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void menuDeOpcoes(int *op){

        printf("\n*MENU DE OPCOES: DIGITE O NUMERO CORRESPONDENTE A OPCAO DESEJADA*\n\n");

        printf("1 - CADASTRAR\n");
        printf("2 - REMOVER\n");    
        printf("3 - IMPRIMIR\n");
        printf("4 - CARREGAR ARQUIVO DE LOTE\n");
        printf("5 - RESETAR ARQUIVO BINARIO\n");
        printf("6 - SAIR\n");

        printf("\n-> ");
        scanf("%d%*c",op);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void menuCadastrar(int *op){

        printf("\n*CADASTRAR: DIGITE O NUMERO CORRESPONDENTE A OPCAO DESEJADA*\n\n");

        printf("1 - CURSO\n");
        printf("2 - DISCIPLINA\n");    
        printf("3 - PROFESSOR\n");
        printf("4 - DISTRIBUICAO DE DISCIPLINA\n");
        printf("5 - VOLTAR\n");
        
        printf("\n-> ");
        scanf("%d%*c",op);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void menuRemover(int *op){

        printf("\n*REMOVER: DIGITE O NUMERO CORRESPONDENTE A OPCAO DESEJADA*\n\n");

        printf("1 - DISTRIBUICAO DE DISCIPLINA\n");
        printf("2 - VOLTAR\n");

        printf("\n-> ");
        scanf("%d%*c",op);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void menuImprimir(int *op){

        printf("\n*IMPRIMIR: DIGITE O NUMERO CORRESPONDENTE A OPCAO DESEJADA*\n\n");

        printf("1 - CURSO\n");
        printf("2 - DISCIPLINA\n");
        printf("3 - PROFESSOR\n");
        printf("4 - DISTRIBUICAO DE DISCIPLINA\n");
        printf("5 - LISTA DE NOS LIVRES\n");
        printf("6 - ARVORE BINARIA DE DISTRIBUICAO DE DISCIPLINA\n");
        printf("7 - VOLTAR\n");

        printf("\n-> ");
        scanf("%d%*c",op);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void menuResetar(int *op){

        printf("\n*RESETAR: DIGITE O NUMERO CORRESPONDENTE A OPCAO DESEJADA*\n\n");

        printf("1 - CURSO\n");
        printf("2 - DISCIPLINA\n");
        printf("3 - PROFESSOR\n");
        printf("4 - DISTRIBUICAO DE DISCIPLINA\n");
        printf("5 - TODOS\n");
        printf("6 - VOLTAR\n");

        printf("\n-> ");
        scanf("%d%*c",op);
    }
