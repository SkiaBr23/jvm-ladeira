#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_frames.h"

lista_frames* Criarlista_frames(){
	return NULL;
}

lista_frames* InserirInicio_frames(lista_frames* lis,frame *f){
	lista_frames *novo= malloc(sizeof(lista_frames));
	novo->f = malloc(sizeof(frame));
	novo->f = f;
	novo->prox = lis;
	novo->ant = NULL;
	
	if (lis!=NULL){
		lis->ant = novo;
	}
	
	return novo;
}

lista_frames* InserirFim_frames(lista_frames* lis,frame *f){
	lista_frames *novo; lista_frames *ant = NULL; lista_frames *p = lis;
	
	while(p!=NULL){
		ant = p;
		p=p->prox;
	}
	
	novo = malloc(sizeof(lista_frames));
	novo->f = f;
	novo->prox = NULL;
	novo->ant = ant;
	ant->prox = novo;
	
	return (lis);
}

lista_frames* RemoverInicio_frames(lista_frames* lis){
	lista_frames* p=lis;
	
	lis = p->prox;
	lis->ant = NULL;
	
	free(p);
	return (lis);
}

lista_frames* RemoverFim_frames(lista_frames* lis){
	lista_frames *p=lis, *ant=NULL;
	
	while (p!=NULL){
		ant = p;
		p=p->prox;
	}

	ant->ant->prox = NULL;
	
	free(ant);

	return lis;
}

lista_frames* RemoverElemento_frames(lista_frames* lis,frame *f){
	lista_frames *p = BuscarElemento(lis, f);
	
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

void ImprimirLista_frames(lista_frames *lis){
	lista_frames *f;
	
	for(f=lis;f!=NULL;f=f->prox){
		printf("%04x\n\n",f->retorno);
		ImprimirPilha(f->p);
	}
}

void LiberarLista_frames(lista_frames *lis){
	lista_frames *p=lis;
	while(p!=NULL){
		lista_frames *t = p->prox;
		free(p);
		p=t;
	}
}