#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cabecalho.h"

    //DESCRICAO:    ESCREVE O CABECALHO NO INICIO DO ARQUIVO BINARIO JA ABERTO
    //ENTRADA:      PONTEIRO RETORNADO POR -fopen- E ESTRUTURA DO CABECALHO
    //SAIDA:        -
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA ARQUIVO BINARIO E CABECALHO INICIALIZADO
    //POS-CONDICAO: CABECALHO MODIFICADO ESCRITO NO ARQUIVO BINARIO
    void escreverCabecalho(FILE* fb, Cabecalho* cab){
        fseek(fb, 0, SEEK_SET);//aponta para o começo do ARQUIVO BINARIO
        fwrite(cab, sizeof(Cabecalho), 1, fb);//copia a ESTRUTURA do cabeçalho em CAB para o que foi aponteado em FSEEK
    }

    //DESCRICAO:    LE O CABECALHO DO ARQUIVO BINARIO E COPIA NA ESTRUTURA -cab-
    //ENTRADA:      PONTEIRO NAO VAZIO PARA O ARQUIVO BINARIO
    //SAIDA:        ESTRUTURA CABECALHO MODIFICADA
    //PRE-CONDICAO: PONTEIRO NAO VAZIO PARA O ARQUIVO BINARIO
    //POS-CONDICAO: ESTRUTURA CABECALHO MODIFICADA
    Cabecalho* lerCabecalho(FILE* fb){
        Cabecalho *cab = (Cabecalho*)malloc(sizeof(Cabecalho));

        fseek(fb, 0, SEEK_SET);//aponta para o começo do ARQUIVO BINARIO
        fread(cab, sizeof(Cabecalho), 1, fb);//copia a ESTUTURA do ARQUIVO BINARIA para CAB

        return cab;
    }

    //DESCRICAO:    
    //ENTRADA:      
    //SAIDA:      
    //PRE-CONDICAO:
    //POS-CONDICAO:
    int vazio(Cabecalho *cab){
        return (cab->posCabeca == -1);
    }
