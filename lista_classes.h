#ifndef LISTA_CLASSES_H
#define LISTA_CLASSES_H

#include <stdio.h>
#include "classFileStruct.h"



/**
 * @struct classesCarregadas
 *
 * @brief Estrutura de dados da lista de classes carregadas no programa.
 * @see classFileStruct.h
 *
 */
struct classesCarregadas {

	ClassFile * arquivoClass; 			/**< Ponteiro para uma estrutura de ClassFile */
	struct classesCarregadas * prox;	/**< Ponteiro de acesso ao próximo nó da lista*/
	struct classesCarregadas * ant;		/**< Ponteiro de acesso ao nó anterior da lista*/

};
/** Definição do tipo \c classesCarregadas*/
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
field_info * BuscarFieldClasseCorrente_classes(classesCarregadas *lis, char * nomeClasse, char * nomeField);

#endif
