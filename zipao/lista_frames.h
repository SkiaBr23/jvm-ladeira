/**
 * @file lista_frames.h
 * @brief Estrutura e cabeçalho da implementação da lista de frames
 */

/** Definição da macro */
#ifndef LISTA_FRAMES_H
#define LISTA_FRAMES_H

#include <stdio.h>
#include <stdint.h>
#include "structures.h"

/**
 * @struct lista_frames
 * 
 * @brief Estrutura de dados da lista de frames
 * 
 * @see structures.h
 */
struct lista_frames{
	frame *f; 						 	/**< Ponteiro para uma variável de frame. @see frame */
	struct lista_frames *prox;          /**< Ponteiro de acesso ao próximo nó da lista.*/
	struct lista_frames *ant;  	        /**< Ponteiro de acesso ao nó anterior da lista.*/
};

/** Definição do tipo lista_frames */
typedef struct lista_frames lista_frames;

/**
 * @brief Inicializa uma lista de frames sem valor
 * @return Uma lista de frames com valor nulo
 */
lista_frames* CriarLista_frames();
/**
 * @brief Insere um frame no início da lista de frames do programa
 * @details 
 * 
 * @param lis Ponteiro da lista de frames
 * @param f Frame a ser inserido na lista
 * 
 * @return Lista de frames com o novo frame inserido no início
 */
lista_frames* InserirInicio_frames(lista_frames *lis, frame *f); 
/**
 * @brief Insere um frame no fim da lista de frames do programa
 * @details 
 * 
 * @param lis Ponteiro da lista de frames
 * @param f Frame a ser inserido na lista
 * 
 * @return Lista de frames com o novo frame inserido no final
 */
lista_frames* InserirFim_frames(lista_frames *lis, frame *f);
/**
 * @brief Remove o frame do início da lista de frames do programa
 * @details 
 * 
 * @param lis Ponteiro da lista de frames
 * @return Lista de frames com o primeiro elemento removido
 */
lista_frames* RemoverInicio_frames(lista_frames *lis);
/**
 * @brief Remove o frame do fim da lista de frames do programa
 * @details 
 * 
 * @param lis Ponteiro da lista de frames
 * @return Lista de frames com o último elemento removido
 */
lista_frames* RemoverFim_frames(lista_frames *lis);

/**
 * @brief Imprime na tela uma representação textual da lista de frames.
 * @details O campo end_retorno (endereço de retorno) de todos os frames
 * da lista é impresso na tela em formato hexadecimal.
 * @param lis Lista de frames a ser impressa
 * @note A definir impressão definitiva
 */
void ImprimirLista_frames(lista_frames *lis);
/**
 * @brief Libera a memória utilizada por toda a lista de frames
 * @details A lista de frames é iterada e todos os elementos são
 * liberados com o comando free(p). Evita vazamentos de memória.
 * 
 * @param lis Lista de frames a ser liberada
 */
void LiberarLista_frames(lista_frames *lis);


// lista_frames* BuscarPosicao_frames(lista_frames *lis, int posicao);
// lista_frames* InserirPosicao_frames(lista_frames *lis, frame *f, int posicao);
// lista_frames* RemoverPosicao_frames(lista_frames *lis, int posicao);
// lista_frames* BuscarElemento_frames(lista_frames *lis, frame *f);
// lista_frames* RemoverElemento_frames(lista_frames *lis,frame *f);
#endif