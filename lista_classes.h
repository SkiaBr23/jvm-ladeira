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

classesCarregadas* CriarLista();
classesCarregadas* InserirFim(classesCarregadas *lis);
classesCarregadas* RemoverFim(classesCarregadas *lis);
classesCarregadas* RemoverElemento(classesCarregadas *lis, char *string);
classesCarregadas* BuscarElemento(classesCarregadas *lis, char *string);
void ImprimirLista(classesCarregadas *lis);
void LiberarLista(classesCarregadas *lis);

#endif
