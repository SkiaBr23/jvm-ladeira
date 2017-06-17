#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_classes.h"
#include "leitura.h"

classesCarregadas* CriarLista(){
	return NULL;
}

classesCarregadas* InserirFim(classesCarregadas* lis){
	classesCarregadas *novo;
	classesCarregadas *ant = NULL;
	classesCarregadas *p = lis;

	while(p!=NULL){
		ant = p;
		p=p->prox;
	}

	novo = (classesCarregadas*)malloc(sizeof(classesCarregadas));
	novo->arquivoClass = NULL;
	novo->prox = NULL;
	novo->ant = ant;
	if (ant != NULL) {
		ant->prox = novo;
		return (lis);
	} else {
		return novo;
	}
}

classesCarregadas* RemoverFim(classesCarregadas* lis){
	classesCarregadas *p = lis, *ant = NULL;

	while (p!=NULL){
		ant = p;
		p=p->prox;
	}

	if (ant != NULL) {
		if (ant->ant != NULL) {
			ant->ant->prox = NULL;
		} else {
			free(ant);
			return NULL;
		}
	}


	free(ant);

	return lis;
}

classesCarregadas* RemoverElemento(classesCarregadas* lis, char *string){
	classesCarregadas *p = BuscarElemento(lis, string);

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

classesCarregadas* BuscarElemento(classesCarregadas* lis, char *string){
	classesCarregadas *p;
	for(p=lis;p!=NULL;p=p->prox){
		if(strcmp(decodificaNIeNT(p->arquivoClass->constant_pool,p->arquivoClass->this_class,CLASS_INDEX),string)==0){
			return p;
		}
	}

	return(NULL);
}

void ImprimirLista(classesCarregadas *lis){
	classesCarregadas *p;

	for(p=lis;p!=NULL;p=p->prox){
		printf("%s",decodificaNIeNT(p->arquivoClass->constant_pool,p->arquivoClass->this_class,CLASS_INDEX));
		printf("\n");
	}
}

void LiberarLista(classesCarregadas *lis){
	classesCarregadas *p=lis;
	while(p!=NULL){
		classesCarregadas *t = p->prox;
		free(p);
		p=t;
	}
}
