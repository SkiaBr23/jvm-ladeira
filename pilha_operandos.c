#include "pilha_operandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pilha_operandos* CriarPilha_operandos(){
	return NULL;
}

pilha_operandos* Push_operandos(pilha_operandos *p, u4 operando, u1 tipo_operando){
	p->topo = InserirInicio_operandos(p->topo,operando,tipo_operando);
	return (p);
}

pilha_operandos* Pop_operandos(pilha_operandos *p){
	pilha_operandos *elementotopo = Topo_operandos(p);
	if(elementotopo==NULL){
		return(NULL);
	}
	p->topo = RemoverInicio_operandos(p->topo);
	return (elementotopo);
}

pilha_operandos* Topo_operandos(pilha_operandos *p){
	return(p);
}

void ImprimirPilha_operandos(pilha_operandos *p){
	ImprimirLista_operandos(p->topo);
}