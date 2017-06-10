#include "pilha_operandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pilha_operandos* CriarPilha(){
	return NULL;
}

pilha_operandos* Push(pilha_operandos *p, u4 operando, u1 tipo_operando){
	p->topo = InserirInicio(p->topo,string);
	return (p);
}

pilha_operandos* Pop(pilha_operandos *p){
	pilha_operandos *elementotopo = Topo(p);
	if(elementotopo==NULL){
		return(NULL);
	}
	p->topo = RemoverInicio(p->topo);
	return (elementotopo);
}

pilha_operandos* Topo(pilha_operandos *p){
	return(p->topo);
}

void ImprimirPilha(pilha_operandos *p){
	ImprimirLista(p->topo);
}
