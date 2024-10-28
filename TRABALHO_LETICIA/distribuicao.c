#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cabecalho.h"
#include "distribuicao.h"
#include "disciplina.h"
#include "professor.h"

    // DESCRIÇÃO:    FUNÇÃO RESPONSÁVEL PELA CRIAÇÃO DO ARQUIVO BINÁRIO. ELE PRIMIERO FAZ A TENTATIVA DE ABRIR UM ARQUIVO JA
    //               EXISTENTE. SE NÃO FOR POSSÍVEL, ELE CRIA OUTRO ARQUIVO A INICIALIZA A ÁRVORE BINÁRIA (O CABEÇALHO)
    // ENTRADA:      NOME DO ARQUIVO BINÁRIO EXISTENTE/A SER CRIADO
    // SAÍDA:        PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO
    // PRE-CONDICAO: NOME VALIDO DE ARQUIVO
    // POS-CONDICAO: ARQUIVO BINÁRIA CRIADO OU O SE RETORNA O PONTEIRO PARA O ARQUIVO
    FILE* inicializarMatricula_arqBin(char* file_name) {
        FILE* fb = fopen(file_name, "r+b"); // tenta abrir o arquivo binário, caso ele exista

        if (fb == NULL) { // caso ele não exista, é criado um novo
            fb = fopen(file_name, "w+b");
            inicializarMatricula(fb); // se inicializa o cabeçalho
        }

        return fb;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void inicializarMatricula(FILE* fb) {
        Cabecalho *cab = (Cabecalho*)malloc(sizeof(Cabecalho));

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
    void escreverMatricula(FILE* fb, Matricula* m, int pos) {
        fseek(fb, sizeof(Cabecalho) + sizeof(Matricula) * pos, SEEK_SET); // aponto para a Árvore na posição desejada, pulando os bits do cabeçalho
        fwrite(m, sizeof(Matricula), 1, fb); // copia a estrutura da árvore para o ARQUIVO BINÁRIO, de acordo com o que foi apontado em FSEEK
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    Matricula* lerMatricula(FILE* fb, int pos) {
        Matricula* m = (Matricula*)malloc(sizeof(Matricula));

        fseek(fb, sizeof(Cabecalho) + sizeof(Matricula) * pos, SEEK_SET); // aponta para a Árvore na posição desejada, pulando os bits do cabeçalho
        fread(m, sizeof(Matricula), 1, fb); // copia para -r- a estrutura Árvore de acordo com o que foi apontado em FSEEK no ARQUIVO BINÁRIO

        return m;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int inserirMatricula_bin(FILE* fb, Matricula* root) {
        Cabecalho* cab = lerCabecalho(fb);
        int insertion_pos;

        if (cab->posLivre == -1) {
            insertion_pos = cab->posTopo;

            escreverMatricula(fb, root, cab->posTopo);
            cab->posTopo++;
        }
        else {
            insertion_pos = cab->posLivre;

            Matricula* mLivre = lerMatricula(fb, cab->posLivre);
            escreverMatricula(fb, root, cab->posLivre);
            cab->posLivre = mLivre->esq;

            free(mLivre);
        }

        if (vazio(cab)) cab->posCabeca = insertion_pos;

        escreverCabecalho(fb, cab);

        free(cab);

        return insertion_pos;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void cadastrarMatricula(FILE* fbMatricula, FILE* fbDisciplina, FILE* fbProfessor) {
        Cabecalho* cab = lerCabecalho(fbMatricula);
        Matricula* m = (Matricula*)malloc(sizeof(Matricula));

        m->esq = m->dir = -1;//nó ainda não possui filhos. inicializados como "null"

        printf("\n*CADASTRAR MATRICULA*\n\n");

        imprimirDisciplina(fbDisciplina);
        printf("\n-> DIGITE O CODIGO DA DISCIPLINA: ");
        scanf("%d%*c", &m->info_matricula.cod_disciplina);

        printf("\n-> DIGITE O ANO LETIVO: ");
        scanf("%d%*c", &m->info_matricula.ano_letivo);

        imprimirProfessor(fbProfessor);
        printf("\n-> DIGITE O CODIGO DO PROFESSOR: ");
        scanf("%d%*c", &m->info_matricula.cod_professor);

        snprintf(m->cod, 7, "%04d%02d", m->info_matricula.ano_letivo, m->info_matricula.cod_disciplina);

        inserirMatricula(fbMatricula, m, cab->posCabeca);// função recursiva de inserir

        printf("\nMATRICULA INSERIDA COM SUCESSO...\n");
        
        free(cab);
        free(m);
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int buscarMatricula_pos(FILE* fb, char* cod, int pos) {
        // faz a busca no método árvore binária de busca
        if (pos == -1) return -1;
        else {
            Matricula* m = lerMatricula(fb, pos);

            if (strcmp(m->cod, cod) > 0) return buscarMatricula_pos(fb, cod, m->esq); 
            else if (strcmp(m->cod, cod) < 0) return buscarMatricula_pos(fb, cod, m->dir);

            free(m);
        }
        return pos;
    }

    // DESCRIÇÃO:// DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int inserirMatricula(FILE* fb, Matricula* newMatricula, int pos) {
        if (pos == -1) {//Significa que a árvore está vazia ou que foi encontrada uma posição livre a ser inserida o novo nó
            int insertion_pos = inserirMatricula_bin(fb, newMatricula);
            return insertion_pos;
        }
        else {
            Matricula* currentMatricula = lerMatricula(fb, pos);

            if (strcmp(newMatricula->cod, currentMatricula->cod) < 0) {
                currentMatricula->esq = inserirMatricula(fb, newMatricula, currentMatricula->esq);
                escreverMatricula(fb, currentMatricula, pos);
            }
            else {
                currentMatricula->dir = inserirMatricula(fb, newMatricula, currentMatricula->dir);
                escreverMatricula(fb, currentMatricula, pos);
            }

            free(currentMatricula);
        }
        return pos;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void imprimirMatricula(FILE *fb) {
        Cabecalho* cab = lerCabecalho(fb);

        printf("\n*LISTA DE MATRICULAS (IN-ORDEM)*\n");
        // Faz uma verificação inicial apenas por questões de estética da interface
        if (vazio(cab)) printf("\nNAO HA MATRICULAS CADASTRADAS...\n");
        else printf("%-10s%-15s%-15s%-15s\n", "CODIGO", "DISCIPLINA", "ANO LETIVO", "PROFESSOR");

        imprimirMatricula_inOrdem(fb, cab->posCabeca);

        free(cab);
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void imprimirMatricula_inOrdem(FILE* fb, int pos) {
        if (pos != -1) {
            Matricula* m = lerMatricula(fb, pos);

            imprimirMatricula_inOrdem(fb, m->esq);  // Imprime primeiro os elementos da esquerda
            printf("%-10s %-15d %-15d %-15d\n", m->cod, m->info_matricula.cod_disciplina,
            m->info_matricula.ano_letivo, m->info_matricula.cod_professor);// Imprime a raiz
            imprimirMatricula_inOrdem(fb, m->dir);  // Imprime então os elementos da direita

            free(m);
        }
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void removerMatricula(FILE* fbMatricula){
    //função de interação com o usuário
        Cabecalho* cab = lerCabecalho(fbMatricula);
        char cod[7];
        int cod_disciplina, ano_letivo;

        printf("\n*REMOVER MATRICULA*\n");

        imprimirMatricula(fbMatricula);

        printf("\n-> DIGITE O CODIGO DA DISCIPLINA QUE DESEJA REMOVER: ");
        scanf("%d%*c", &cod_disciplina);

        printf("\n-> DIGITE O ANO LETIVO QUE DESEJA REMOVER: ");
        scanf("%d%*c", &ano_letivo);

        snprintf(cod, 7, "%04d%02d", ano_letivo, cod_disciplina);

        removerNo(fbMatricula, cab->posCabeca, cod);//função recursiva de remoção no arquivo binário

        free(cab);
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int removerNo(FILE *fb, int pos, char cod[]){
        Cabecalho* cab = lerCabecalho(fb);

        if(pos == -1){//se posCabeca for -1 (arvore vazia) ou se root->(esq || drt) for -1 (ramos vazios)
            if(vazio(cab)) printf("\nNAO HA MATRICULA: ");
            else printf("\nCODIGO DISCIPINA OU ANO LETIVO INEXISTENTES: ");
            printf("NAO FOI POSSIVEL REALIZAR A REMOCAO...\n");
            
            return -1;
        }
        else{
            Matricula* m = lerMatricula(fb, pos);

            if(strcmp(m->cod, cod) > 0){
                m->esq = removerNo(fb, m->esq, cod);//pode receber novamente sua propria posicao esquerda ou -1 (ramo-folha removido)
                escreverMatricula(fb, m, pos);
            }
            else{
                if(strcmp(m->cod, cod) < 0){
                    m->dir = removerNo(fb, m->dir, cod);//pode receber novamente sua propria posicao direito ou -1 (ramo-folha removido)
                    escreverMatricula(fb, m, pos);
                }
                else{//nó encontrado
                    if(m->esq == -1 && m->dir == -1){
                    //nó folha. esse é o nó que será removido
                    //encadeia-se a lista de nós livres
                        if(pos == cab->posCabeca) cab->posCabeca = -1;//árvore fica vazia
                        
                        m->esq = m->dir = cab->posLivre;
                        cab->posLivre = pos;
                        escreverCabecalho(fb, cab);//escreve o cabecalho atualizado
                        escreverMatricula(fb, m, pos);
                        
                        pos = -1;//sinaliza que essa folha foi removida e -1 (null) retorna para sua raiz imediata
                        
                        printf("\nPRODUTO REMOVIDO COM SUCESSO...\n");
                    }
                    else{
                        if(m->esq == -1){//possui apenas ramo direito
                            char* cod_min = (char*)malloc(7);
                            minimo(fb, m->dir, cod_min);//recebe o menor codigo do ramo direito
                            
                            trocar_info(fb, pos, buscarMatricula_pos(fb, cod_min, cab->posCabeca));
                            m = lerMatricula(fb, pos);//lê a nova arvore que teve suas informacoes trocacadas
                            m->dir = removerNo(fb, m->dir, cod_min);//remove o no minimo cujo as informacoes foram copiadas
                            escreverMatricula(fb, m, pos);//escreve novamente a arvore atualizada
                        }
                        else{//possui apenas ramo esquerdo ou dois ramos
                            char cod_max[7];
                            maximo(fb, m->esq, cod_max);//recebe o maior codigo do ramo esquerdo
                            
                            trocar_info(fb, pos, buscarMatricula_pos(fb, cod_max, cab->posCabeca));
                            m = lerMatricula(fb, pos);//lê a nova arvore que teve suas informacoes copiadas do no maximo
                            m->esq = removerNo(fb, m->esq, cod_max);//remove o no minimo cujo as informacoes foram copiadas
                            escreverMatricula(fb, m, pos);//escreve novamente a arvore atualizada
                        }
                    }
                }
            }
            free(m);
        }
        free(cab);

    return pos;
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void trocar_info(FILE* fb, int pos_dest, int pos_source){
        Matricula* dest = lerMatricula(fb, pos_dest);
        Matricula* source = lerMatricula(fb, pos_source);
        Matricula* aux = (Matricula*)malloc(sizeof(Matricula));

        aux->info_matricula.ano_letivo = dest->info_matricula.ano_letivo;
        aux->info_matricula.cod_disciplina = dest->info_matricula.cod_disciplina;
        aux->info_matricula.cod_professor = dest->info_matricula.cod_professor;

        dest->info_matricula.ano_letivo = source->info_matricula.ano_letivo;
        dest->info_matricula.cod_disciplina = source->info_matricula.cod_disciplina;
        dest->info_matricula.cod_professor = source->info_matricula.cod_professor;
        strcpy(dest->cod, source->cod);

        source->info_matricula.ano_letivo = aux->info_matricula.ano_letivo;
        source->info_matricula.cod_disciplina = aux->info_matricula.cod_disciplina;
        source->info_matricula.cod_professor = aux->info_matricula.cod_professor;

        escreverMatricula(fb,dest, pos_dest);
        escreverMatricula(fb,source, pos_source);
        free(dest);
        free(source);
        free(aux);
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void maximo(FILE* fb, int pos, char cod[]) {
        if (pos != -1) {
            Matricula* m = lerMatricula(fb, pos);
            
            if (m->dir != -1) maximo(fb, m->dir, cod);
            else strncpy(cod, m->cod, 7);

            free(m);
        }
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    void minimo(FILE* fb, int pos, char cod[]) {
        if (pos != -1) {
            Matricula* m = lerMatricula(fb, pos);
            
            if (m->esq != -1) minimo(fb, m->esq, cod);
            else strncpy(cod, m->cod, 7);

            free(m);
        }
    }

    // DESCRIÇÃO:    
    // ENTRADA:      
    // SAÍDA:      
    // PRE-CONDICAO:
    // POS-CONDICAO:
    int altura_arvore(FILE* fb, int pos){
        if(pos == -1) return -1;
        else{
            Matricula* m = lerMatricula(fb,pos);

            int h_esq = altura_arvore(fb, m->esq);//recebe a altura da subarove esquerda
            int h_drt = altura_arvore(fb, m->dir);//recebe a altura da subarove direita
            return (h_esq > h_drt) ? h_esq + 1 : h_drt + 1;//compara a altura entre os ramos. o ramo maior representa a altura

            free(m);
        }
    }

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
    void imprimir_arvore(FILE* fb){
        Cabecalho* cab = lerCabecalho(fb);
        Lista* l = NULL;//inicialização padrão de lista

        printf("\n*ARVORE BINARIA*\n\n");

        //verificação feita apenas para a estética da interface do programa
        if(vazio(cab)) printf("NAO HA MATRICULAS...\n");

        l = percorrer_arvore(fb, l, cab->posCabeca, 0);//passa a arvore para uma lista encadeada, ordenada pela altura do nó
        imprimir_em_arvore(l, altura_arvore(fb, cab->posCabeca));//imprime no formato de árvore binária

        free(cab);
        liberar_lista(l);
    }

    //DESCRICAO:    FUNÇÃO RECRUSIVA QUE PERCORRE A ÁRVORE DE MODO pre_Ordem E FAZ A INSERSÃO DOS NÓS EM UMA
    //              LISTA ENCADEADA ORDENADA PELA ALTURA DESSES NÓS
    //ENTRADA:      PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO, LISTA INICALIZADA, POSIÇÃO DA RAIZ (0 OU -1) E INTEIRO
    //              PARA A ALTURA DOS NÓS, INICIADO COMO 0, SENDO INCREMENTADO A CADA CHAMADA RECURSIVA
    //SAIDA:        LISTA ENCADEADA ORDENADA COM OS NÓS INSERIDOS
    //PRE-CONDICAO: PONTEIRO NÃO NULO PARA O ARQUIVO BINÁRIO E LISTA INICALIZADA. CABEÇALHO INICALIZADO E ALTURA DOS NÓS
    //              INICIADA COMO 0
    //POS-CONDICAO: LISTA ENCADEADA ALTERADA.
    //              NENHUMA MUDANÇA É RELIZADA DENTRO DO ARQUIVO BINÁRIO
    Lista* percorrer_arvore(FILE* fb, Lista* l, int pos, int h_node){
        if(pos!=-1){
            Matricula* m = lerMatricula(fb,pos);

            l = inserir_ordenado(l, m->cod, h_node);//insere os códigos na lista de maneira ordenada pela altura do nó
            percorrer_arvore(fb, l, m->esq, h_node+1);//incrementa a altura do nó, passando para o próximo nível
            percorrer_arvore(fb, l, m->dir, h_node+1);//incrementa a altura do nó, passando para o próximo nível

            free(m);
        }
    return l;
    }

    //DESCRICAO:    FUNÇÃO RECURSIVA DE INSERSÃO ORDENADA EM UMA LISTA ENCADEADA DINAMICAMENTE.
    //              O CRITÉRIO DE ORDENAÇÃO É A ALTURA DO NÓ (h_node), DO MENOR (0) PARA O MAIOR (altura_arvore)
    //ENTRADA:      LISTA ENCADEADA, CODIGO DO PRODUTO (INFORMACAO NECESSARIA A LISTA) E ALTURA DO NÓ (h_node)
    //SAIDA:        LISTA COM OS NÓS INSERIDOS
    //PRE-CONDICAO: LISTA INICIALIZADA, CÓDIGOS E ALTURAS VÁLIDAS E EXISTENTES
    //POS-CONDICAO: LISTA ENCADEADA ALTERADA.
    //              NENHUMA MUDANÇA É RELIZADA DENTRO DO ARQUIVO BINÁRIO
    Lista* inserir_ordenado(Lista* l, char* cod, int h_node){
        if(l == NULL || l->h_node > h_node){
            Lista* aux = (Lista*)malloc(sizeof(Lista));
            
            strncpy(aux->cod, cod, 7);
            aux->h_node = h_node;
            aux->prox = l;
            
            return aux;
        }
        else{
            l->prox = inserir_ordenado(l->prox, cod, h_node);
            return l;
        }
    }

    //DESCRICAO:    IMPRIME A LISTA ENCADEADA EM FORMATO DE ÁRVORE BINÁRIA. IMPRIME CADA NÓ EM ORDEM, E QUANDO O ATRIBUTO
    //              h_node MUDA DE UM NÓ PARA O OUTRO, UMA LINHA É PULADA.
    //ENTRADA:      LISTA INICIALIZADA E ALTURA DA ÁRVORE BINÁRIA
    //SAIDA:        -
    //PRE-CONDICAO: LISTA INICIALIZADA E ALTURA VÁLIDA DA ÁRVORE (VALOR DADO PELA FUNÇÃO altura_arvore)
    //POS-CONDICAO: CÓDIGOS DOS PRODUTOS IMPRESSOS NA TELA EM FORMATO DE ÁRVORE BINÁRIA.
    //              NENHUMA MUDANÇA É REALIZADA DENTRO DO ARQUIVO BINÁRIO
    void imprimir_em_arvore(Lista* l, int altura_arvore){
        if(l!=NULL){
            Lista* aux = l;
            int altura_no = aux->h_node;//altura atual em que os nós serão impressos

            while(aux != NULL){
                printf("|%s|", aux->cod);
                if(aux->prox != NULL && aux->h_node != aux->prox->h_node){//pula uma linha ao mudar o nível do nó
                    altura_no = aux->prox->h_node;
                    printf("\n");
                }
                aux = aux->prox;
            }
            printf("\n");
        }
    }

    //DESCRICAO:    LIBERA A MEMÓRIA ALOCADA PARA TODOS OS NÓS DA LISTA ENCADEADA
    //ENTRADA:      LISTA ENCADEADA
    //SAIDA:        -
    //PRE-CONDICAO: LISTA INICIALIZADA
    //POS-CONDICAO: MEMÓRIA LIBERADA
    void liberar_lista(Lista *l){
        if(l != NULL){
            liberar_lista(l->prox);
            free(l);
        }
    }

    //DESCRICAO:    IMPRIME A LISTA DE NÓS LIVRES (REMOVIDOS)
    //ENTRADA:      PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO
    //SAIDA:        -
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO
    //POS-CONDICAO: CHAMA A FUNCAO imprimir_nosLivres E LISTA DE NOS LIVRES IMPRESSAS NO TERMINAL
    //              NENHUMA MUDANCA É FEITA NO ARQUIVO BINARIO
    void imprimir_listaLivres(FILE *fb){
        Cabecalho* cab = lerCabecalho(fb);

        printf("\n*LISTA DE NOS LIVRES (REMOVIDOS)*\n");

        //verificação necessária apenas para a estética da função
        if(cab->posLivre == -1) printf("\nNAO HA NOS LIVRES...\n");

        imprimir_nosLivres(fb, cab->posLivre);

        free(cab);
    }

    //DESCRICAO:    FUNCAO RECURSIVA QUE PERCORRE A LISTA DE NOS LIVRES E IMPRIME OS NÓS
    //ENTRADA:      PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO E posLivre (CABECA DA LISTA DE NOS LIVRES/REMOVIDOS)
    //SAIDA:        -
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO E POSICAO VALIDA (-1 OU MAIOR)
    //POS-CONDICAO: LISTA DE NOS LIVRES IMPRESSAS NO TERMINAL
    //              NENHUMA MUDANCA É FEITA NO ARQUIVO BINARIO
    void imprimir_nosLivres(FILE *fb, int pos){
        if(pos != -1){
            Matricula* m = lerMatricula(fb, pos);

            printf("-> %.2d\n", pos);
            imprimir_nosLivres(fb, m->esq);//posicão esquerda e direita são iguais, pois é uma lista, não uma árvore

            free(m);
        }
    }