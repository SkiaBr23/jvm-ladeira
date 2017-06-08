#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pilha* CriarPilha(){
	return NULL;
}

Pilha* Push(Pilha *p, char *string){
	p->topo = InserirInicio(p->topo,string);
	return (p);
}

char* Pop(Pilha *p, char *string){
	char *elementotopo = Topo(p);
	if(elementotopo==NULL){
		return(NULL);
	}
	p->topo = RemoverInicio(p->topo);
	return (elementotopo);
}

void Top(Pilha *p){
	printf("O elemento do topo é: ",p->topo->string);
}

void ImprimirPilha(Pilha *p){
	ImprimirLista(p->topo);
}
