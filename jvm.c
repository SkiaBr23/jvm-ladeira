#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jvm.h"

JVM* CriarJVM(){
	return NULL;
}

JVM* InicializarJVM() {
	JVM *novo;

	novo = (JVM*)malloc(sizeof(JVM));
	novo->classes = NULL;
	novo->frames = NULL;
	novo->pc = 0;
	return novo;
}

int opcaoMenu () {

	int op = 0;
	printf("Software Basico 01/2017 - Universidade de Brasilia\n");
	printf("Maquina Virtual Java\n");
	while (op < 1 || op > 3) {
		printf("Por favor, selecione uma das opcoes abaixo para prosseguir com a execucao do programa:\n");
		printf("[1] - Impressao de arquivo .class\n");
		printf("[2] - Execucao de arquivo .class\n");
		printf("[3] - Encerrar programa\n");
		printf("Opcao: ");
		scanf("%d",&op);
		getchar();
	}
	return op;
}

JVM *jvm = NULL;
