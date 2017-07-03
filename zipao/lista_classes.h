/**
 * @file lista_classes.h
 * @brief Arquivo cabeçalho que contém a estrutura para armazenar a lista de classes carregadas
 */

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

/**
 * @brief Função para criar uma lista
 * @return Retorna um ponteiro nulo
*/
classesCarregadas* CriarLista_classes();
/**
 * @brief Função para inserir um elemento no fim da lista
 * 
 * @param lis Ponteiro apontando para o início da lista
 * @param arquivoClass Ponteiro de ClassFile que deve ser inserido na lista
 * 
 * @return A função retorna o ponteiro para o início da lista, com a lista atualizada
 * 
 * @see ClassFile
*/
classesCarregadas* InserirFim_classes(classesCarregadas *lis, ClassFile *arquivoClass);

/**
 * @brief Função para remover um elemento do fim da lista
 * 
 * @param lis Ponteiro apontando para o início da lista
 * @return A função retorna o ponteiro para o início da lista, com a lista atualizada
 */
classesCarregadas* RemoverFim_classes(classesCarregadas *lis);

/**
 * @brief Função para remover um elemento da lista
 * 
 * @param lis Ponteiro apontando para o início da lista
 * @param string Nome da classe que será buscado, e então a classe será removida da lista
 * 
 * @return A função retorna o ponteiro para o início da lista, com a lista atualizada
 */
classesCarregadas* RemoverElemento_classes(classesCarregadas *lis, char *string);

/**
 * @brief Funçao para buscar um elemento na lista
 * 
 * @param lis Ponteiro apontando para o início da lista
 * @param string Nome da classe que será buscada na lista
 * 
 * @return A função retorna o ponteiro para o elemento encontrado, ou um ponteiro nulo, caso o elemento não seja encontrado
 */
classesCarregadas* BuscarElemento_classes(classesCarregadas *lis, char *string);


/**
 * @brief Função que retorna a pool de constantes da classe corrente, passada como parâmetro
 * 
 * @param lis Ponteiro apontando para o início da lista
 * @param string Nome da classe cuja constant pool deve ser retornada
 * 
 * @return Um ponteiro do tipo cp_info que é a constant pool da classe passada como parâmetro
 * 
 * @see cp_info
 */
cp_info* BuscarCPClasseCorrente_classes(classesCarregadas *lis, char *string);

/**
 * @brief Função para buscar um método da classe corrente, passada como parâmetro
 * 
 * @param lis Ponteiro apontando para o início da lista
 * @param nomeClasse Nome da classe que contém o método que será buscado
 * @param nomeMetodo Nome do método que deve ser buscado na classe corrente
 * @return Estrutura method_info do método buscado
 * 
 * @see method_info
 */
method_info * BuscarMethodClasseCorrente_classes(classesCarregadas *lis, char *nomeClasse, char*nomeMetodo);

/**
 * @brief Função para imprimir os elementos da lista de classes
 * 
 * @param lis Ponteiro apontando para o início da lista
 */
void ImprimirLista_classes(classesCarregadas *lis);

/**
 * @brief Função para liberar uma lista da memória
 * 
 * @param lis Ponteiro apontando para o início da lista
 */
void LiberarLista_classes(classesCarregadas *lis);

/**
 * @brief Função para buscar um field da classe passada como parâmetro
 * 
 * @param lis Ponteiro apontando para o início da lista
 * @param nomeClasse Nome da classe que deve ter o field buscado
 * @param nomeField Nome do field que deve ser buscado na classe
 * @return Estrutura do field que foi buscado na classe
 * 
 * @see field_info
 */
field_info * BuscarFieldClasseCorrente_classes(classesCarregadas *lis, char * nomeClasse, char * nomeField);

#endif
