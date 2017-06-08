#include "lista.h"


struct pilha{
	struct lista *topo;
};
typedef struct pilha Pilha;

Pilha* CriarPilha();
Pilha* Push(Pilha *p, char *string);
char* Pop(Pilha *p, char *string);
void Top(Pilha *p);
void ImprimirPilha(Pilha *p);