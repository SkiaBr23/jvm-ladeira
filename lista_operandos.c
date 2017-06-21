#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_operandos.h"

lista_operandos* Criarlista_operandos(){
	return NULL;
}

lista_operandos* InserirInicio_operandos(lista_operandos* lis, i4 operando, u1 tipo_operando){
	lista_operandos *novo= malloc(sizeof(lista_operandos));
	novo->operando = operando;
	novo->tipo_operando = tipo_operando;
	novo->prox = lis;
	novo->ant = NULL;
	
	if (lis!=NULL){
		lis->ant = novo;
	}
	
	return novo;
}

lista_operandos* InserirFim_operandos(lista_operandos* lis, i4 operando, u1 tipo_operando){
	lista_operandos *novo; lista_operandos *ant = NULL; lista_operandos *p = lis;
	
	while(p!=NULL){
		ant = p;
		p=p->prox;
	}
	
	novo = malloc(sizeof(lista_operandos));
	novo->operando = operando;
	novo->tipo_operando = tipo_operando;
	novo->prox = NULL;
	novo->ant = ant;
	ant->prox = novo;
	
	return (lis);
}

lista_operandos* RemoverInicio_operandos(lista_operandos* lis){
	lista_operandos* p=lis;
	
	lis = p->prox;
	if(lis!=NULL){
		lis->ant = NULL;
	}
	
	free(p);
	return (lis);
}

lista_operandos* RemoverFim_operandos(lista_operandos* lis){
	lista_operandos *p=lis, *ant=NULL;
	
	while (p!=NULL){
		ant = p;
		p=p->prox;
	}

	ant->ant->prox = NULL;
	
	free(ant);

	return lis;
}

lista_operandos* RemoverElemento_operandos(lista_operandos* lis,i4 operando,u1 tipo_operando){
	lista_operandos *p = BuscarElemento_operandos(lis, operando, tipo_operando);
	
	if(p==NULL){
		return lis;
	}

	if (lis == p){
		lis=p->prox;
	}else{
		p->ant->prox = p->prox;
	}
	
	if (p->prox!=NULL){
		p->prox->ant = p->ant;
	}

	free(p);
	
	return lis;
}

lista_operandos* BuscarElemento_operandos(lista_operandos* lis, i4 operando, u1 tipo_operando){
	lista_operandos *p;
	for(p=lis;p!=NULL;p=p->prox){
		if(p->operando == operando && p->tipo_operando == tipo_operando){
			return p;
		}
	}

	return(NULL);
}

lista_operandos* BuscarPosicao_operandos(lista_operandos *lis, int posicao){
	lista_operandos *p;
	int cont;

	for(p=lis,cont=0;p!=NULL && cont<posicao;){
		p=p->prox;
		cont++;
	}

	return(p);
}

lista_operandos* InserirPosicao_operandos(lista_operandos *lis, i4 operando, u1 tipo_operando, int posicao){
	lista_operandos *novo; lista_operandos *ant=NULL; lista_operandos *p;
	int cont;

	for(p=lis,cont=0;p!=NULL && cont<posicao;){
		ant=p;
		p=p->prox;
		cont++;
	}

	novo = malloc(sizeof(lista_operandos));
	novo->operando = operando;
	novo->tipo_operando = tipo_operando;

	if (ant==NULL){
		novo->prox = lis;
		novo->ant = NULL;
		lis = novo;
	}else{
		ant->prox = novo;
		novo->ant = ant;
		novo->prox = p;
		if(p!=NULL){
			p->ant = novo;
		}
	}

	return(lis);
}

lista_operandos* RemoverPosicao_operandos(lista_operandos *lis, int posicao){

	lista_operandos *p = BuscarPosicao_operandos(lis, posicao);
	
	if(p==NULL){
		return lis;
	}

	if (lis == p){
		lis=p->prox;
	}else{
		p->ant->prox = p->prox;
	}
	
	if (p->prox!=NULL){
		p->prox->ant = p->ant;
	}

	free(p);
	
	return (lis);
}

void ImprimirLista_operandos(lista_operandos *lis){
	lista_operandos *p;
	
	for(p=lis;p!=NULL;p=p->prox){
		printf("%01x\t",p->tipo_operando);
		printf("%d\n",p->operando);
	}
}

void LiberarLista_operandos(lista_operandos *lis){
	lista_operandos *p=lis;
	while(p!=NULL){
		lista_operandos *t = p->prox;
		free(p);
		p=t;
	}
}