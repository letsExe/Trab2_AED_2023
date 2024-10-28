#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cabecalho.h"
#include "professor.h"

    // DESCRIÇÃO:    FUNÇÃO RESPONSÁVEL PELA CRIAÇÃO DO ARQUIVO BINÁRIO. ELE PRIMIERO FAZ A TENTATIVA DE ABRIR UM ARQUIVO JA
    //               EXISTENTE. SE NÃO FOR POSSÍVEL, ELE CRIA OUTRO ARQUIVO A INICIALIZA A ÁRVORE BINÁRIA (O CABEÇALHO)
    // ENTRADA:      NOME DO ARQUIVO BINÁRIO EXISTENTE/A SER CRIADO
    // SAÍDA:        PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO
    // PRE-CONDICAO: NOME VALIDO DE ARQUIVO
    // POS-CONDICAO: ARQUIVO BINÁRIA CRIADO OU O SE RETORNA O PONTEIRO PARA O ARQUIVO
    FILE* inicializarProfessor_arqBin(char* file_name) {
        FILE* fb = fopen(file_name, "r+b"); // tenta abrir o arquivo binário, caso ele exista

        if (fb == NULL) { // caso ele não exista, é criado um novo
            fb = fopen(file_name, "w+b");
            inicializarProfessor(fb); // se inicializa o cabeçalho
        }

        return fb;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void inicializarProfessor(FILE* fb) {
        Cabecalho* cab = (Cabecalho*)malloc(sizeof(Cabecalho));

        cab->posCabeca = -1; // inicializar "cabeca" como "NULL"
        cab->posTopo = 0;    // indica que a próxima posição livre como a primeira posição disponível
        cab->posLivre = -1;  // inicializar lista de nós livres como "NULL"

        escreverCabecalho(fb, cab); // escreve o cabeçalho inicializado
        free(cab); // desaloca memória do ponteiro auxiliar
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void escreverProfessor(FILE* fb, Professor* p, int pos) {
        fseek(fb, sizeof(Cabecalho) + sizeof(Professor) * pos, SEEK_SET); // aponto para a Árvore na posição desejada, pulando os bits do cabeçalho
        fwrite(p, sizeof(Professor), 1, fb); // copia a estrutura da árvore para o ARQUIVO BINÁRIO, de acordo com o que foi apontado em FSEEK
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    Professor* lerProfessor(FILE* fb, int pos) {
        Professor* p = (Professor*)malloc(sizeof(Professor));

        fseek(fb, sizeof(Cabecalho) + sizeof(Professor) * pos, SEEK_SET); // aponta para a Árvore na posição desejada, pulando os bits do cabeçalho
        fread(p, sizeof(Professor), 1, fb); // copia para -r- a estrutura Árvore de acordo com o que foi apontado em FSEEK no ARQUIVO BINÁRIO

        return p;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int inserirProfessor_bin(FILE* fb, Professor* root) {
        Cabecalho* cab = lerCabecalho(fb);
        int insertion_pos;

        if (cab->posLivre == -1) {
            insertion_pos = cab->posTopo;

            escreverProfessor(fb, root, cab->posTopo);
            cab->posTopo++;
        }
        else {
            insertion_pos = cab->posLivre;

            Professor* pLivre = lerProfessor(fb, cab->posLivre);
            escreverProfessor(fb, root, cab->posLivre);
            cab->posLivre = pLivre->esq;

            free(pLivre);
        }

        if (vazio(cab))
            cab->posCabeca = insertion_pos;

        escreverCabecalho(fb, cab);

        free(cab);

        return insertion_pos;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void cadastrarProfessor(FILE* fb) {
        Cabecalho* cab = lerCabecalho(fb);
        Professor* p = (Professor*)malloc(sizeof(Professor));

        p->esq = p->dir = -1; // nó ainda não possui filhos. inicializados como "null"

        printf("\n*CADASTRAR PROFESSOR*\n\n");

        printf("-> DIGITE O CODIGO DO PROFESSOR: ");
        scanf("%d%*c", &p->cod);

        // não permite inserir um código já existente
        if (buscarProfessor_pos(fb, p->cod, cab->posCabeca) == -1) {

            printf("\n-> DIGITE O NOME DO PROFESSOR (MAX. DE 50 CARACTERES): ");
            scanf("%[^\n]%*c", p->nome);
            p->nome[50] = '\0'; // apaga o possível excesso de caracteres
            
            inserirProfessor(fb, p, cab->posCabeca); // função recursiva de inserir

            printf("\nPROFESSOR INSERIDO COM SUCESSO...\n");
        }
        else printf("\nCODIGO EXISTENTE: NAO FOI POSSIVEL CONCLUIR O CADASTRO...\n");

        free(cab);
        free(p);
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int buscarProfessor_pos(FILE* fb, int cod, int pos) {
        // faz a busca no método árvore binária de busca
        if (pos == -1)
            return -1;
        else {
            Professor* p = lerProfessor(fb, pos);

            if (p->cod > cod) return buscarProfessor_pos(fb, cod, p->esq); // todos os códigos menores que a raiz se encontram a esquerda
            else if (p->cod < cod) return buscarProfessor_pos(fb, cod, p->dir); // todos os códigos maiores que a raiz se encontram a direita

            free(p);
        }
        return pos;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int inserirProfessor(FILE* fb, Professor* newProfessor, int pos) {
        if (pos == -1) { // significa que a árvore está vazia ou que foi encontrada uma posição livre a ser inserida o novo nó
            int insertion_pos = inserirProfessor_bin(fb, newProfessor);
            return insertion_pos;
        }
        else {
            Professor* currentProfessor = lerProfessor(fb, pos);

            if (newProfessor->cod < currentProfessor->cod) {
                currentProfessor->esq = inserirProfessor(fb, newProfessor, currentProfessor->esq);
                escreverProfessor(fb, currentProfessor, pos);
            }
            else {
                currentProfessor->dir = inserirProfessor(fb, newProfessor, currentProfessor->dir);
                escreverProfessor(fb, currentProfessor, pos);
            }

            free(currentProfessor);
        }
        return pos;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void imprimirProfessor(FILE* fb) {
        Cabecalho* cab = lerCabecalho(fb);

        printf("\n*LISTA DE PROFESSORES (IN-ORDEM)*\n");
        // faz uma verificação inicial apenas por questões de estética da interface
        if (vazio(cab)) printf("\nNAO HA PROFESSORES CADASTRADOS...\n");
        else printf("\n%-11s%-55s\n", "CODIGO", "NOME");

        imprimirProfessor_inOrdem(fb, cab->posCabeca);

        free(cab);
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void imprimirProfessor_inOrdem(FILE* fb, int pos) {
        if (pos != -1) {
            Professor* p = lerProfessor(fb, pos);

            imprimirProfessor_inOrdem(fb, p->esq); // imprime primeiro os elementos da esquerda
            printf("%-10.3d %-55s\n", p->cod, p->nome); // imprime a raiz
            imprimirProfessor_inOrdem(fb, p->dir); // imprime então os elementos da direita

            free(p);
        }
    }
