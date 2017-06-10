#ifndef PILHA_FRAMES_H
#define PILHA_FRAMES_H

#include <stdint.h>

#include "lista_frames.h"

struct pilha_frames{
	struct lista_frames *topo;
};
typedef struct pilha_frames pilha_frames;

pilha_frames* CriarPilha_frames();
pilha_frames* Push_frames(pilha_frames *p, frame *f);
pilha_frames* Pop_frames(pilha_frames *p);
pilha_frames* Topo_frames(pilha_frames *p);
void ImprimirPilha_frames(pilha_frames *p);
#endif