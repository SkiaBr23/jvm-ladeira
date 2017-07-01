/**
 * @file pilha_frames.h
 * @brief Estrutura e cabeçalho da implementação da pilha de frames
 */

/** Definição da macro */
#ifndef PILHA_FRAMES_H
#define PILHA_FRAMES_H

#include <stdint.h>

#include "lista_frames.h"

/**
 * @struct pilha_frames
 * 
 * @brief Estrutura de dados da pilha de frames
 * @see lista_frames.h
 * 
 */
struct pilha_frames{
	struct lista_frames *topo; /**< Ponteiro para o topo da pilha de frames */
};

/**
 * @brief Definição de tipo 'pilha_frames' para a estrutura
 */
typedef struct pilha_frames pilha_frames;


/**
 * @brief Inicializa uma pilha de frames
 * @details Esta função inicializa uma pilha
 * de frames para utilização posterior
 * @return Pilha de frames com valor nulo
 */
pilha_frames* CriarPilha_frames();

/**
 * @brief Insere um frame no topo da pilha de frames
 * 
 * @param p Ponteiro da pilha de frames
 * @param f Frame a ser inserido
 * 
 * @return Pilha de frames com o novo frame inserido no topo
 */
pilha_frames* Push_frames(pilha_frames *p, frame *f);
/**
 * @brief Remove o frame localizado no topo da pilha de frames
 * 
 * @param p Ponteiro da pilha de frames
 * @return Pilha de frames com o topo removido
 */
pilha_frames* Pop_frames(pilha_frames *p);
/**
 * @brief Acessa o topo da pilha de frames
 * 
 * @param p Ponteiro da pilha de frames
 * @note Não deveria retornar lista_frames?
 * @return Ponteiro para o nó de topo da pilha de frames
 */
pilha_frames* Topo_frames(pilha_frames *p);
/**
 * @brief Imprime na tela uma representação da pilha de frames
 * 
 * @param p Ponteiro da pilha de frames
 */
void ImprimirPilha_frames(pilha_frames *p);
#endif