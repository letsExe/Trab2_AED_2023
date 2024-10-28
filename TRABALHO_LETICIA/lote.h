#ifndef LOTE_H
#define LOTE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void carregarArquivoLote(FILE* fbCurso, FILE* fbDisciplina, FILE* fbProfessor, FILE* fbMatricula);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void lerArquivoTexto(FILE* fbCurso, FILE* fbDisciplina, FILE* fbProfessor, FILE* fbMatricula, FILE* fr);
 
    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inserirCurso_lote(FILE *fb, FILE* fr);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inserirDisciplina_lote(FILE *fb, FILE* fr);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inserirProfessor_lote(FILE *fb, FILE* fr);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inserirMatricula_lote(FILE *fb, FILE* fr);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void removerMatricula_lote(FILE* fb, FILE* fr);

#endif  