#ifndef LISTA_CLASSES_H
#define LISTA_CLASSES_H

#include <stdio.h>
#include "classFileStruct.h"


struct classesCarregadas {

	ClassFile * arquivoClass;
	struct classesCarregadas * prox;
	struct classesCarregadas * ant;

};
typedef struct classesCarregadas classesCarregadas;

classesCarregadas* CriarLista_classes();
classesCarregadas* InserirFim_classes(classesCarregadas *lis, ClassFile *arquivoClass);
classesCarregadas* RemoverFim_classes(classesCarregadas *lis);
classesCarregadas* RemoverElemento_classes(classesCarregadas *lis, char *string);
classesCarregadas* BuscarElemento_classes(classesCarregadas *lis, char *string);
cp_info* BuscarCPClasseCorrente_classes(classesCarregadas *lis, char *string);
method_info * BuscarMethodClasseCorrente_classes(classesCarregadas *lis, char *nomeClasse,char*nomeMetodo);
void ImprimirLista_classes(classesCarregadas *lis);
void LiberarLista_classes(classesCarregadas *lis);

#endif
