#include "pilha_operandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pilha_operandos* CriarPilha_operandos(){
	pilha_operandos *p = malloc(sizeof(pilha_operandos));
	p->topo = NULL;
	return(p);
}

pilha_operandos* Push_operandos(pilha_operandos *p, u4 operando, void *referencia, u1 tipo_operando){
	p->topo = InserirInicio_operandos(p->topo,operando,referencia,tipo_operando);
	return (p);
}

pilha_operandos* Pop_operandos(pilha_operandos *p){

	pilha_operandos *aux = CriarPilha_operandos();
	aux = Push_operandos(aux,p->topo->operando,p->topo->referencia,p->topo->tipo_operando);
	p->topo = RemoverInicio_operandos(p->topo);
	return (aux);
}

pilha_operandos* Topo_operandos(pilha_operandos *p){
	return(p);
}

void ImprimirPilha_operandos(pilha_operandos *p){
	ImprimirLista_operandos(p->topo);
}
