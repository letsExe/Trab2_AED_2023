#ifndef CABECALHO_H
#define CABECALHO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    //DESCRICAO:    CARREGA AS INFORMACOES ESSENCIAIS DA ARVORE BINARIA
    //              É SEMPRE ATUALIZADO COM A ALTERACAO DE ALGUMA INFORMACAO NA ARVORE BINARIA (INSERSAO E REMOCAO)  
    //              FICA NO INICIO DO ARQUIVO BINARIO
    typedef struct{
        int posCabeca;//posicao da raiz da arvore. varia excluisamente entre -1 (vazia) e 0 (não-vazia)
        int posTopo;//proxima posicao LIVRE
        int posLivre;//posicao do inicio da lists de NOS LIVRES (removidos)
    }Cabecalho;

    //DESCRICAO:    ESCREVE O CABECALHO NO INICIO DO ARQUIVO BINARIO JA ABERTO
    //ENTRADA:      PONTEIRO RETORNADO POR -fopen- E ESTRUTURA DO CABECALHO
    //SAIDA:        -
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO E CABECALHO INICIALIZADO
    //POS-CONDICAO: CABECALHO MODIFICADO ESCRITO NO ARQUIVO BINARIO
    void escreverCabecalho(FILE* fb,Cabecalho* cab);

    //DESCRICAO:    LE O CABECALHO DO ARQUIVO BINARIO E COPIA NA ESTRUTURA -cab-
    //ENTRADA:      PONTEIRO NAO VAZIO PARA O ARQUIVO BINARIO
    //SAIDA:        ESTRUTURA CABECALHO MODIFICADA
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA O ARQUIVO BINARIO
    //POS-CONDICAO: ESTRUTURA CABECALHO MODIFICADA   
    Cabecalho* lerCabecalho(FILE* fb);

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int vazio(Cabecalho *cab);

    #endif // CABECALHO_H
