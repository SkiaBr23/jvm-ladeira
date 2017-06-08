#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Lista* CriarLista(){
	return NULL;
}

Lista* InserirInicio(Lista* lis, char *string){
	Lista *novo= malloc(sizeof(Lista));
	novo->string = malloc(strlen(string)*sizeof(char));
	strcpy(novo->string,string);
	novo->prox = lis;
	novo->ant = NULL;
	
	if (lis!=NULL){
		lis->ant = novo;
	}
	
	return novo;
}

Lista* InserirFim(Lista* lis, char *string){
	Lista *novo; Lista *ant = NULL; Lista *p = lis;
	
	while(p!=NULL){
		ant = p;
		p=p->prox;
	}
	
	novo = malloc(sizeof(Lista));
	novo->string = malloc(strlen(string)*sizeof(char));
	strcpy(novo->string,string);
	novo->prox = NULL;
	novo->ant = ant;
	ant->prox = novo;
	
	return (lis);
}

Lista* RemoverInicio(Lista* lis){
	Lista* p=lis;
	
	lis = p->prox;
	lis->ant = NULL;
	
	free(p);
	return (lis);
}

Lista* RemoverFim(Lista* lis){
	Lista *p=lis, *ant=NULL;
	
	while (p!=NULL){
		ant = p;
		p=p->prox;
	}

	ant->ant->prox = NULL;
	
	free(ant);

	return lis;
}

Lista* RemoverElemento(Lista* lis, char *string){
	Lista *p = BuscarElemento(lis, string);
	
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

Lista* BuscarElemento(Lista* lis, char *string){
	Lista *p;
	for(p=lis;p!=NULL;p=p->prox){
		if(strcmp(p->string,string)==0){
			return p;
		}
	}

	return(NULL);
}

Lista* BuscarPosicao(Lista *lis, int posicao){
	Lista *p;
	int cont;

	for(p=lis,cont=1;p!=NULL && cont<posicao;){
		p=p->prox;
		cont++;
	}

	return(p);
}

Lista* InserirPosicao(Lista *lis, char *string, int posicao){
	Lista *novo; Lista *ant=NULL; Lista *p;
	int cont;

	for(p=lis,cont=1;p!=NULL && cont<posicao;){
		ant=p;
		p=p->prox;
		cont++;
	}

	novo = malloc(sizeof(Lista));
	novo->string = malloc(strlen(string)*sizeof(char));
	strcpy(novo->string,string);

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

Lista* RemoverPosicao(Lista *lis, int posicao){

	Lista *p = BuscarPosicao(lis, posicao);
	
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

void ImprimirLista(Lista *lis){
	Lista *p;
	
	for(p=lis;p!=NULL;p=p->prox){
		printf("%s",p->string);
		printf("\n");
	}
}

void LiberarLista(Lista *lis){
	Lista *p=lis;
	while(p!=NULL){
		Lista *t = p->prox;
		free(p);
		p=t;
	}
}







