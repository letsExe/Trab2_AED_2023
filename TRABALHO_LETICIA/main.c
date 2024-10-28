#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "curso.h"
#include "disciplina.h"
#include "professor.h"
#include "distribuicao.h"
#include "lote.h"
#include "interface.h"
    int main(){

        FILE* fbCurso = inicializarCurso_arqBin("binaries/curso.bin");
        FILE* fbDisciplina = inicializarDisciplina_arqBin("Binaries/disciplina.bin");
        FILE* fbProfessor = inicializarProfessor_arqBin("Binaries/professor.bin");
        FILE* fbMatricula = inicializarMatricula_arqBin("Binaries/matricula.bin");

        int op = 0;
        do{
            menuDeOpcoes(&op);
            if(op == 1){//cadastrar
                int opCadastrar = 0;
                
                do{
                    menuCadastrar(&opCadastrar);
                    if(opCadastrar == 1){//cadastrar novo curso
                        cadastrarCurso(fbCurso);
                    }
                    if(opCadastrar == 2){//cadastrar nova disciplina
                        cadastrarDisciplina(fbDisciplina, fbCurso);
                    }
                    if(opCadastrar == 3){//cadastrar novo professor
                        cadastrarProfessor(fbProfessor);
                    }
                    if(opCadastrar == 4){//cadastrar nova distribuicao de disciplina
                        cadastrarMatricula(fbMatricula, fbDisciplina, fbCurso);
                    }
                }while(opCadastrar != 5);
            }
            if(op == 2){//remover
                int opRemover = 0;
                
                do{
                    menuRemover(&opRemover);
                    if(opRemover == 1){//remover distribuicao de disciplina
                        removerMatricula(fbMatricula);
                    }
                }while(opRemover != 2);
            }
            if(op == 3){//imprimir
                int opImprimir = 0;

                do{
                    menuImprimir(&opImprimir);
                    if(opImprimir == 1){//imprimir cursos
                        imprimirCurso(fbCurso);
                    }
                    if(opImprimir == 2){//imprimir disciplinas
                        imprimirDisciplina(fbDisciplina);
                    }
                    if(opImprimir == 3){//imprimir professores
                        imprimirProfessor(fbProfessor);
                    }
                    if(opImprimir == 4){//imprimir cursos distribuicoes de disciplina
                        imprimirMatricula(fbMatricula);
                    }
                    if(opImprimir == 5){//imprimir lista de nos livres
                        imprimir_listaLivres(fbMatricula);
                    }
                    if(opImprimir == 6){//imprimir arvore binaria de distribuicoes de disciplina
                        imprimir_arvore(fbMatricula);
                    }
                }while(opImprimir != 7);
            }
            if(op == 4){//carregar arquivo de lote
                carregarArquivoLote(fbCurso, fbDisciplina, fbProfessor, fbMatricula);
            }
            if(op == 5){//resetar arquivo binario
                int opResetar = 0;

                do{
                    menuResetar(&opResetar);
                    if(opResetar == 1){//resetar cursos
                        fbCurso = fopen("Binaries/curso.bin","w+b");
                        inicializarCurso(fbCurso);
                    }
                    if(opResetar == 2){//resetar disciplinas
                        fbDisciplina = fopen("Binaries/disciplina.bin","w+b");
                        inicializarDisciplina(fbDisciplina);
                    }
                    if(opResetar == 3){//imprimir professores
                        fbProfessor = fopen("Binaries/professor.bin","w+b");
                        inicializarProfessor(fbProfessor);
                    }
                    if(opResetar == 4){//imprimir cursos distribuicoes de disciplina
                        fbMatricula = fopen("Binaries/matricula.bin","w+b");
                        inicializarMatricula(fbMatricula);
                    }
                    if(opResetar == 5){//imprimir cursos distribuicoes de disciplina
                        fbCurso = fopen("Binaries/curso.bin","w+b");
                        inicializarCurso(fbCurso);

                        fbDisciplina = fopen("Binaries/disciplina.bin","w+b");
                        inicializarDisciplina(fbDisciplina);

                        fbProfessor = fopen("Binaries/professor.bin","w+b");
                        inicializarProfessor(fbProfessor);

                        fbMatricula = fopen("Binaries/matricula.bin","w+b");
                        inicializarMatricula(fbMatricula);
                    }
                }while(opResetar != 6);
            }
        }while(op != 6);

        fclose(fbCurso);
        fclose(fbDisciplina);
        fclose(fbProfessor);
        fclose(fbMatricula);

        return 0;
    }