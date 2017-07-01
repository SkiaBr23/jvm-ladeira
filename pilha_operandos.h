#ifndef PILHA_OPERANDOS_H
#define PILHA_OPERANDOS_H

#include <stdint.h>
#include <stdbool.h>

#ifndef TIPOS_U
#define TIPOS_U
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;
#endif

#include "lista_operandos.h"

struct pilha_operandos{
	struct lista_operandos *topo;
};
typedef struct pilha_operandos pilha_operandos;

pilha_operandos* CriarPilha_operandos();
pilha_operandos* Push_operandos(pilha_operandos *p, u4 operando, void *referencia, u1 tipo_operando);
pilha_operandos* Pop_operandos(pilha_operandos *p);
pilha_operandos* Topo_operandos(pilha_operandos *p);
bool pilhaVazia (pilha_operandos * p);
void ImprimirPilha_operandos(pilha_operandos *p);
#endif
