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

	/*Alocação da estrutura para o arquivo .class*/
	ClassFile *arquivoClass = malloc(sizeof(ClassFile));

	/*Estrutura condicional que analisa se foi passado o nome do arquivo como parâmetro*/
	if(argc>1){
		//Se for, copia a string contendo o nome do arquivo para uma string pré alocada
		strcpy(nomearquivo,argv[1]);
	} else {
		/*Caso contrário, o usuário precisa inserir o nome do arquivo .class*/
		printf("Digite o nome do arquivo\n");
		scanf("%s",nomearquivo);
	}

	/*Chamada da função que realiza a leitura do arquivo .class*/
	arquivoClass = lerArquivo(nomearquivo);
	if (arquivoClass != NULL) {
		imprimirClassFile(arquivoClass);
	}


	/*Retorno da função main*/
	return (0);
}
