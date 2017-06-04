/*
Universidade de Brasília - 01/2017
Software Básico - Turma A
Projeto Leitor/Exibidor de arquivo .class

Alunos: Maximillian Fan Xavier - 12/0153271
				Rafael Dias da Costa - 12/0133253
				Murilo Cerqueira Medeiros - 12/0130637
				Eduardo Sousa da Silva - 13/0108405
				Eduardo Schuabb Duarte - 11/0010876

*/

/*Inclusão de bibliotecas para entrada e saída de dados, tratamento de strings e estruturas e mecanismos de leitura do arquivo .class*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"


/*Função main*/
int main(int argc, char const *argv[]){

	/*Alocação de string para conter o nome do arquivo .class a ser lido*/
	char *nomearquivo = malloc(100*sizeof(char));
	char *outputName = malloc(100*sizeof(char));
	int outset = 0, inputset = 0;

	/*Alocação da estrutura para o arquivo .class*/
	ClassFile *arquivoClass = malloc(sizeof(ClassFile));

	/*Estrutura condicional que analisa se foi passado o nome do arquivo como parâmetro*/
	if(argc > 1){
		if(strlen(argv[1]) > 4 && !strcmp(argv[1] + strlen(argv[1]) - 4, ".txt")){
			strcpy(outputName, argv[1]);
			outset = 1;
		} else if(strlen(argv[1]) > 6 && !strcmp(argv[1] + strlen(argv[1]) - 6, ".class")){
			strcpy(nomearquivo, argv[1]);
			inputset = 1;
		}
		if(argc > 2){
			if(strlen(argv[2]) > 4 && !strcmp(argv[2] + strlen(argv[2]) - 4, ".txt")){
				strcpy(outputName, argv[2]);
				outset = 1;
			} else if(strlen(argv[2]) > 6 && !strcmp(argv[2] + strlen(argv[2]) - 6, ".class")){
				strcpy(nomearquivo, argv[2]);
				inputset = 1;
			}	
		}
	}
	if(!inputset){
		printf("Digite o nome do arquivo .class\n");
		scanf("%s",nomearquivo);
	}
	if(!outset){
		printf("Digite o nome do arquivo de saida\n");
		scanf("%s",outputName);
	}	

	/*Chamada da função que realiza a leitura do arquivo .class*/
	arquivoClass = lerArquivo(nomearquivo);

	FILE *outputFile = fopen(outputName, "w");
	if (arquivoClass != NULL && outputFile != NULL) {
		imprimirClassFile(arquivoClass, stdout);
		imprimirClassFile(arquivoClass, outputFile);
		fclose(outputFile);
	}else{
		printf("Erro ao criar arquivo de saida\n");
	}

	free(arquivoClass);
	free(nomearquivo);
	free(outputName);


	/*Retorno da função main*/
	return (0);
}
