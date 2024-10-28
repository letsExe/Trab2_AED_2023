#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cabecalho.h"
#include "disciplina.h"
#include "curso.h"

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    FILE* inicializarDisciplina_arqBin(char* file_name) {
        FILE* fb = fopen(file_name, "r+b");

        if (fb == NULL) {
            fb = fopen(file_name, "w+b");
            inicializarDisciplina(fb);
        }

        return fb;
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void inicializarDisciplina(FILE* fb) {
        Cabecalho* cab = (Cabecalho*)malloc(sizeof(Cabecalho));

        cab->posCabeca = -1;
        cab->posTopo = 0;
        cab->posLivre = -1;

        escreverCabecalho(fb, cab);
        free(cab);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void escreverDisciplina(FILE* fb, Disciplina* d, int pos) {
        fseek(fb, sizeof(Cabecalho) + sizeof(Disciplina) * pos, SEEK_SET);
        fwrite(d, sizeof(Disciplina), 1, fb);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    Disciplina* lerDisciplina(FILE* fb, int pos) {
        Disciplina* d = (Disciplina*)malloc(sizeof(Disciplina));

        fseek(fb, sizeof(Cabecalho) + sizeof(Disciplina) * pos, SEEK_SET);
        fread(d, sizeof(Disciplina), 1, fb);

        return d;
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int inserirDisciplina_bin(FILE* fb, Disciplina* root) {
        Cabecalho* cab = lerCabecalho(fb);
        int insertion_pos;

        if (cab->posLivre == -1) {
            insertion_pos = cab->posTopo;

            escreverDisciplina(fb, root, cab->posTopo);
            cab->posTopo++;
        }
        else {
            insertion_pos = cab->posLivre;

            Disciplina* dLivre = lerDisciplina(fb, cab->posLivre);
            escreverDisciplina(fb, root, cab->posLivre);
            cab->posLivre = dLivre->esq;

            free(dLivre);
        }

        if (vazio(cab)) cab->posCabeca = insertion_pos;

        escreverCabecalho(fb, cab);
        free(cab);

        return insertion_pos;
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void cadastrarDisciplina(FILE* fb, FILE* fbCurso) {
        Cabecalho* cab = lerCabecalho(fb);
        Disciplina* d = (Disciplina*)malloc(sizeof(Disciplina));

        d->esq = d->dir = -1;

        printf("\n*CADASTRAR DISCIPLINA*\n\n");

        printf("-> DIGITE O CODIGO DA DISCIPLINA: ");
        scanf("%d%*c", &d->cod);

        if (buscarDisciplina_pos(fb, d->cod, cab->posCabeca) == -1) {

            printf("\n-> DIGITE O NOME DA DISCIPLINA (MAX. DE 50 CARACTERES): ");
            scanf("%[^\n]%*c", d->info_disciplina.nome);
            d->info_disciplina.nome[50] = '\0';

            imprimirCurso(fbCurso);
            printf("\n-> DIGITE O CODIGO DO CURSO A QUE PERTENCE A DISCIPLINA: ");
            scanf("%d%*c", &d->info_disciplina.cod_curso);

            printf("\n-> DIGITE A SERIE DA DISCIPLINA: ");
            scanf("%d%*c", &d->info_disciplina.serie);

            inserirDisciplina(fb, d, cab->posCabeca);

            printf("\nDISCIPLINA INSERIDA COM SUCESSO...\n");
        }
        else printf("\nCODIGO EXISTENTE: NAO FOI POSSIVEL CONCLUIR O CADASTRO...\n");

        free(cab);
        free(d);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int buscarDisciplina_pos(FILE* fb, int cod, int pos) {
        if (pos == -1) return -1;
        else {
            Disciplina* d = lerDisciplina(fb, pos);

            if (d->cod > cod) return buscarDisciplina_pos(fb, cod, d->esq);
            else if (d->cod < cod) return buscarDisciplina_pos(fb, cod, d->dir);

            free(d);
        }

        return pos;
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int inserirDisciplina(FILE* fb, Disciplina* newDisciplina, int pos) {
        if (pos == -1) {
            int insertion_pos = inserirDisciplina_bin(fb, newDisciplina);
            return insertion_pos;
        }
        else {
            Disciplina* currentDisciplina = lerDisciplina(fb, pos);

            if (newDisciplina->cod < currentDisciplina->cod) {
                currentDisciplina->esq = inserirDisciplina(fb, newDisciplina, currentDisciplina->esq);
                escreverDisciplina(fb, currentDisciplina, pos);
            }
            else {
                currentDisciplina->dir = inserirDisciplina(fb, newDisciplina, currentDisciplina->dir);
                escreverDisciplina(fb, currentDisciplina, pos);
            }

            free(currentDisciplina);
        }

        return pos;
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void imprimirDisciplina(FILE* fb) {
        Cabecalho* cab = lerCabecalho(fb);

        printf("\n*LISTA DE DISCIPLINAS (IN-ORDEM)*\n");

        if (vazio(cab)) printf("\nNAO HA DISCIPLINAS CADASTRADAS...\n"); 
        else printf("\n%-11s%-55s%-5s%-5s\n", "CODIGO", "NOME", "CURSO", "SERIE");
        
        imprimirDisciplina_inOrdem(fb, cab->posCabeca);

        free(cab);
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    void imprimirDisciplina_inOrdem(FILE* fb, int pos) {
        if (pos != -1) {
            Disciplina* d = lerDisciplina(fb, pos);

            imprimirDisciplina_inOrdem(fb, d->esq);
            printf("%-10.3d %-55s %-5d %-5d\n", d->cod, d->info_disciplina.nome, d->info_disciplina.cod_curso, d->info_disciplina.serie);
            imprimirDisciplina_inOrdem(fb, d->dir);

            free(d);
        }
    }