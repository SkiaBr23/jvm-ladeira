#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_classes.h"
#include "leitura.h"

classesCarregadas* CriarLista_classes(){
	return NULL;
}

classesCarregadas* InserirFim_classes(classesCarregadas* lis, ClassFile *arquivoClass){
	classesCarregadas *novo;
	classesCarregadas *ant = NULL;
	classesCarregadas *p = lis;

	while(p!=NULL){
		ant = p;
		p=p->prox;
	}

	novo = (classesCarregadas*)malloc(sizeof(classesCarregadas));
	novo->arquivoClass = arquivoClass;
	novo->prox = NULL;
	novo->ant = ant;
	if (ant != NULL) {
		ant->prox = novo;
		return (lis);
	} else {
		return novo;
	}
}

classesCarregadas* RemoverFim_classes(classesCarregadas* lis){
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

classesCarregadas* RemoverElemento_classes(classesCarregadas* lis, char *string){
	classesCarregadas *p = BuscarElemento_classes(lis, string);

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

classesCarregadas* BuscarElemento_classes(classesCarregadas* lis, char *string){
	classesCarregadas *p;
	for(p=lis;p!=NULL;p=p->prox){
		if(strcmp(decodificaNIeNT(p->arquivoClass->constant_pool,p->arquivoClass->this_class,NAME_INDEX),string)==0){
			return p;
		}
	}

	return(NULL);
}

cp_info* BuscarCPClasseCorrente_classes(classesCarregadas *lis, char *string){
	classesCarregadas *classeCorrente = BuscarElemento_classes(lis,string);
	return(classeCorrente->arquivoClass->constant_pool);
}

void ImprimirLista_classes(classesCarregadas *lis){
	classesCarregadas *p;

	for(p=lis;p!=NULL;p=p->prox){
		printf("%s",decodificaNIeNT(p->arquivoClass->constant_pool,p->arquivoClass->this_class,CLASS_INDEX));
		printf("\n");
	}
}

void LiberarLista_classes(classesCarregadas *lis){
	classesCarregadas *p=lis;
	while(p!=NULL){
		classesCarregadas *t = p->prox;
		free(p);
		p=t;
	}
}
