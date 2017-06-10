#ifndef LISTA_OPERANDOS_H
#define LISTA_OPERANDOS_H

#include <stdio.h>
#include <stdint.h>

#ifndef TIPOS_U
#define TIPOS_U
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
#endif

/* Essa lista foi implementada utilizando strings. Substituir a string pelo elemento que será utilizado */
struct lista_operandos{
	u4 operando;
	u1 tipo_operando;
	struct lista_operandos *prox,*ant;
};
typedef struct lista_operandos lista_operandos;

enum tipos_operandos{
	INTEGER_OP = 1,
	FLOAT_OP,
	LONG_OP,
	DOUBLE_OP,
	RETURN_ADDRESS_OP,
	REFERENCE_OP
};

typedef enum tipos_operandos tipos_operandos;

lista_operandos* CriarLista();
lista_operandos* InserirInicio(lista_operandos *lis, u4 operando, u1 tipo_operando); 
lista_operandos* InserirFim(lista_operandos *lis, u4 operando, u1 tipo_operando);
lista_operandos* RemoverInicio(lista_operandos *lis);
lista_operandos* RemoverFim(lista_operandos *lis);
lista_operandos* RemoverElemento(lista_operandos *lis,u4 operando, u1 tipo_operando);
lista_operandos* BuscarElemento(lista_operandos *lis, u4 operando, u1 tipo_operando);
lista_operandos* BuscarPosicao(lista_operandos *lis, int posicao);
lista_operandos* InserirPosicao(lista_operandos *lis, u4 operando, u1 tipo_operando, int posicao);
lista_operandos* RemoverPosicao(lista_operandos *lis, int posicao);
void ImprimirLista(lista_operandos *lis);
void LiberarLista(lista_operandos *lis);

#endif