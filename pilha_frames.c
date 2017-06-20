#include "pilha_frames.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pilha_frames* CriarPilha_frames(){
	return NULL;
}

pilha_frames* Push_frames(pilha_frames *p, frame *f){
	p->topo = InserirInicio_frames(p->topo,f);
	return (p);
}

pilha_frames* Pop_frames(pilha_frames *p){
	pilha_frames *elementotopo = Topo_frames(p);
	if(elementotopo->topo==NULL){
		return(NULL);
	}
	p->topo = RemoverInicio_frames(p->topo);
	return (elementotopo);
}

pilha_frames* Topo_frames(pilha_frames *p){
	return(p);
}

void ImprimirPilha_frames(pilha_frames *p){
	ImprimirLista_frames(p->topo);
}
