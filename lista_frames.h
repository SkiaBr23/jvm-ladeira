#ifndef LISTA_FRAMES_H
#define LISTA_FRAMES_H

#include <stdio.h>
#include <stdint.h>
#include "structures.h"

/* Essa lista foi implementada utilizando strings. Substituir a string pelo elemento que será utilizado */
struct lista_frames{
	frame *f;
	struct lista_frames *prox,*ant;
};
typedef struct lista_frames lista_frames;

lista_frames* CriarLista_frames();
lista_frames* InserirInicio_frames(lista_frames *lis, frame *f); 
lista_frames* InserirFim_frames(lista_frames *lis, frame *f);
lista_frames* RemoverInicio_frames(lista_frames *lis);
lista_frames* RemoverFim_frames(lista_frames *lis);
lista_frames* RemoverElemento_frames(lista_frames *lis,frame *f);
lista_frames* BuscarElemento_frames(lista_frames *lis, frame *f);
lista_frames* BuscarPosicao_frames(lista_frames *lis, int posicao);
lista_frames* InserirPosicao_frames(lista_frames *lis, frame *f, int posicao);
lista_frames* RemoverPosicao_frames(lista_frames *lis, int posicao);
void ImprimirLista_frames(lista_frames *lis);
void LiberarLista_frames(lista_frames *lis);

#endif