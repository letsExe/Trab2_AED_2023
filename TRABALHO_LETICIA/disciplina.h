#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    typedef struct{
        char nome[51];
        int cod_curso;
        int serie;
    }Info_Disciplina;

    typedef struct{
        Info_Disciplina info_disciplina;
        int cod;
        
        int esq;
        int dir;
    }Disciplina;

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    FILE* inicializarDisciplina_arqBin(char* file_name);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inicializarDisciplina(FILE* fb);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void escreverDisciplina(FILE* fb, Disciplina* d, int pos);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    Disciplina* lerDisciplina(FILE* fb, int pos);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int inserirDisciplina_bin(FILE* fb, Disciplina* root);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void cadastrarDisciplina(FILE* fb, FILE* fbCurso);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int buscarDisciplina_pos(FILE* fb, int cod, int pos);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int inserirDisciplina(FILE* fb, Disciplina* newDisciplina, int pos);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void imprimirDisciplina(FILE* fb);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void imprimirDisciplina_inOrdem(FILE* fb, int pos);

#endif