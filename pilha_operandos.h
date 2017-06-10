#ifndef PILHA_OPERANDOS_H
#define PILHA_OPERANDOS_H

#include <stdint.h>

#ifndef TIPOS_U
#define TIPOS_U
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
#endif

#include "lista_operandos.h"

struct pilha_operandos{
	struct lista_operandos *topo;
};
typedef struct pilha_operandos pilha_operandos;

pilha_operandos* CriarPilha();
pilha_operandos* Push(pilha_operandos *p, u4 operando, u1 tipo_operando);
pilha_operandos* Pop(pilha_operandos *p);
pilha_operandos* Topo(pilha_operandos *p);
void ImprimirPilha(pilha_operandos *p);
#endif