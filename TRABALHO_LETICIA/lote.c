#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cabecalho.h"
#include "lote.h"
#include "curso.h"
#include "disciplina.h"
#include "professor.h"
#include "distribuicao.h"

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void carregarArquivoLote(FILE* fbCurso, FILE* fbDisciplina, FILE* fbProfessor, FILE* fbMatricula){
        FILE* fr;
        char caminho_arq[100];

        //nao permite sair da iteração até um caminho válido de arquivo texto ser digitado
        do{
            printf("\n-> DIGITE O CAMINHO DO ARQUIVO TEXTO (MAX. DE 100 CARACTERES): ");
            scanf("%[^\n]%*c",caminho_arq);
            fr = fopen(caminho_arq, "r");
        }while(fr == NULL);

        lerArquivoTexto(fbCurso, fbDisciplina, fbProfessor, fbMatricula, fr);

        printf("\nARQUIVO LIDO COM SUCESSO...\n");

        fclose(fr);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void lerArquivoTexto(FILE* fbCurso, FILE* fbDisciplina, FILE* fbProfessor, FILE* fbMatricula, FILE *fr){
        char op;

        while(fscanf(fr, "%c;", &op) != EOF){
            if(op == 'C') inserirCurso_lote(fbCurso, fr);
            if(op == 'D') inserirDisciplina_lote(fbDisciplina, fr);
            if(op == 'P') inserirProfessor_lote(fbProfessor, fr);
            if(op == 'M') inserirMatricula_lote(fbMatricula, fr);
            if(op == 'R') removerMatricula_lote(fbMatricula, fr);
        }
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inserirCurso_lote(FILE *fb, FILE* fr){
        Cabecalho* cab = lerCabecalho(fb);
        Curso* c = (Curso*)malloc(sizeof(Curso));

        c->esq = c->dir = -1;//nó ainda não possui ramos. inicializados como "null"

        fscanf(fr, "%d;", &c->cod);
        fscanf(fr, "%[^;]%*c", c->info_curso.nome);
        c->info_curso.nome[50] = '\0';
        fscanf(fr, "%c\n", &c->info_curso.area);

        inserirCurso(fb, c, cab->posCabeca);

        free(cab);
        free(c);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inserirDisciplina_lote(FILE *fb, FILE* fr){
        Cabecalho* cab = lerCabecalho(fb);
        Disciplina* d = (Disciplina*)malloc(sizeof(Disciplina));

        d->esq = d->dir = -1;//nó ainda não possui ramos. inicializados como "null"

        fscanf(fr, "%d;", &d->cod);
        fscanf(fr, "%[^;]%*c", d->info_disciplina.nome);
        d->info_disciplina.nome[50] = '\0';
        fscanf(fr, "%d;", &d->info_disciplina.cod_curso);
        fscanf(fr, "%d\n", &d->info_disciplina.serie);

        inserirDisciplina(fb, d, cab->posCabeca);

        free(cab);
        free(d);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inserirProfessor_lote(FILE *fb, FILE* fr){
        Cabecalho* cab = lerCabecalho(fb);
        Professor* p = (Professor*)malloc(sizeof(Professor));

        p->esq = p->dir = -1;//nó ainda não possui ramos. inicializados como "null"

        fscanf(fr, "%d;", &p->cod);
        fscanf(fr, "%[^\n]%*c", p->nome);
        p->nome[50] = '\0';

        inserirProfessor(fb, p, cab->posCabeca);

        free(cab);
        free(p);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inserirMatricula_lote(FILE *fb, FILE* fr){
        Cabecalho* cab = lerCabecalho(fb);
        Matricula* m = (Matricula*)malloc(sizeof(Matricula));

        m->esq = m->dir = -1;//nó ainda não possui ramos. inicializados como "null"

        fscanf(fr, "%d;", &m->info_matricula.cod_disciplina);
        fscanf(fr, "%d;", &m->info_matricula.ano_letivo);
        fscanf(fr, "%d\n", &m->info_matricula.cod_professor);

        snprintf(m->cod, 7, "%04d%02d", m->info_matricula.ano_letivo, m->info_matricula.cod_disciplina);

        inserirMatricula(fb, m, cab->posCabeca);

        free(cab);
        free(m);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void removerMatricula_lote(FILE* fb, FILE* fr){
        Cabecalho* cab = lerCabecalho(fb);
        int cod_disciplina, ano_letivo;
        char cod[7];

        fscanf(fr, "%d;", &cod_disciplina);
        fscanf(fr, "%d\n", &ano_letivo);

        snprintf(cod, 7, "%04d%02d", ano_letivo, cod_disciplina);

        removerNo(fb, cab->posCabeca, cod);

        free(cab);
    } 