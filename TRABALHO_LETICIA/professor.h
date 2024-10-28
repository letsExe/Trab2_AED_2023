#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    typedef struct{
        char nome[50];
        int cod;
        
        int esq;
        int dir;
    }Professor;

    // DESCRIÇÃO:    FUNÇÃO RESPONSÁVEL PELA CRIAÇÃO DO ARQUIVO BINÁRIO. ELE PRIMIERO FAZ A TENTATIVA DE ABRIR UM ARQUIVO JA
    //               EXISTENTE. SE NÃO FOR POSSÍVEL, ELE CRIA OUTRO ARQUIVO A INICIALIZA A ÁRVORE BINÁRIA (O CABEÇALHO)
    // ENTRADA:      NOME DO ARQUIVO BINÁRIO EXISTENTE/A SER CRIADO
    // SAÍDA:        PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO
    // PRE-CONDICAO: NOME VALIDO DE ARQUIVO
    // POS-CONDICAO: ARQUIVO BINÁRIA CRIADO OU O SE RETORNA O PONTEIRO PARA O ARQUIVO
    FILE* inicializarProfessor_arqBin(char* file_name);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void inicializarProfessor(FILE* fb);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void escreverProfessor(FILE* fb, Professor* p, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    Professor* lerProfessor(FILE* fb, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int inserirProfessor_bin(FILE* fb, Professor* root);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void cadastrarProfessor(FILE* fb);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int buscarProfessor_pos(FILE* fb, int cod, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int inserirProfessor(FILE* fb, Professor* newProfessor, int pos);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void imprimirProfessor(FILE* fb);

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void imprimirProfessor_inOrdem(FILE* fb, int pos);

#endif