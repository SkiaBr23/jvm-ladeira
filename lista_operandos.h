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

#ifndef TIPOS_I
#define TIPOS_I
typedef int8_t i1;
typedef int16_t i2;
typedef int32_t i4;
#endif

/* Essa lista foi implementada utilizando strings. Substituir a string pelo elemento que será utilizado */
struct lista_operandos{
	i4 operando;
	u1 tipo_operando;
	struct lista_operandos *prox,*ant;
};
typedef struct lista_operandos lista_operandos;

enum tipos_operandos{
	BOOLEAN_OP = 1,
	BYTE_OP,
	CHAR_OP,
	SHORT_OP,
	INTEGER_OP,
	FLOAT_OP,
	LONG_OP,
	DOUBLE_OP,
	RETURN_ADDRESS_OP,
	REFERENCE_OP
};

typedef enum tipos_operandos tipos_operandos;

lista_operandos* CriarLista_operandos();
lista_operandos* InserirInicio_operandos(lista_operandos *lis, i4 operando, u1 tipo_operando); 
lista_operandos* InserirFim_operandos(lista_operandos *lis, i4 operando, u1 tipo_operando);
lista_operandos* RemoverInicio_operandos(lista_operandos *lis);
lista_operandos* RemoverFim_operandos(lista_operandos *lis);
lista_operandos* RemoverElemento_operandos(lista_operandos *lis,i4 operando, u1 tipo_operando);
lista_operandos* BuscarElemento_operandos(lista_operandos *lis, i4 operando, u1 tipo_operando);
lista_operandos* BuscarPosicao_operandos(lista_operandos *lis, int posicao);
lista_operandos* InserirPosicao_operandos(lista_operandos *lis, i4 operando, u1 tipo_operando, int posicao);
lista_operandos* RemoverPosicao_operandos(lista_operandos *lis, int posicao);
void ImprimirLista_operandos(lista_operandos *lis);
void LiberarLista_operandos(lista_operandos *lis);

#endif