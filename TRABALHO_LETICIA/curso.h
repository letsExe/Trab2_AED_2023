#ifndef CURSO_H
#define CURSO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    typedef struct{
        char nome[51];
        char area;
    }Info_Curso;

    typedef struct{
        Info_Curso info_curso;
        int cod;
        
        int esq;
        int dir;
    }Curso;

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    FILE* inicializarCurso_arqBin(char* file_name);
    
    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inicializarCurso(FILE* fb);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void escreverCurso(FILE* fb, Curso* c, int pos);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    Curso* lerCurso(FILE* fb, int pos);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int inserirCurso_bin(FILE* fb, Curso* root);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void cadastrarCurso(FILE* fb);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int buscarCurso_pos(FILE* fb, int cod, int pos);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int inserirCurso(FILE* fb, Curso* newCurso, int pos);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void imprimirCurso(FILE *fb);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void imprimirCurso_inOrdem(FILE* fb, int pos);

    #endif