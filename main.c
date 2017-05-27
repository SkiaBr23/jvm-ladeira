#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"

int main(int argc, char const *argv[]){

	char *nomearquivo = malloc(100*sizeof(char));
	ClassFile *arquivoclass = malloc(sizeof(ClassFile));
	
	if(argc>1){
		strcpy(nomearquivo,argv[1]);
	}
	else{
		printf("Digite o nome do arquivo\n");
		scanf("%s",nomearquivo);
	}

	arquivoclass = lerArquivo(nomearquivo);

	
	return (0);
}