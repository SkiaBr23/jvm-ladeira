#include "interpretador.h"

void iload_impl(u1 index, frame *f){
	Push_operandos(f->p,(i4) *(f->v[index].variavel),INTEGER_OP);
}


void aconst_null_impl(frame *f){
	Push_operandos(f->p,0,REFERENCE_OP); // 0 do tipo referência quer dizer referência apontando para NULL
}

void iconst_m1_impl(u1 constant, frame *f){
	/* 
		Tem um "shift" de -3. Ou seja, constant é um valor sem sinal.
		Esse valor é subtraído de 3 para descobrir a constante que vai ser armazenada na pilha.
	*/
	i4 inteiro_sinal = (i4) constant-3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_0_impl(u1 constant, frame *f){
	i4 inteiro_sinal = (i4) constant-3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_1_impl(u1 constant, frame *f){
	i4 inteiro_sinal = (i4) constant-3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_2_impl(u1 constant, frame *f){
	i4 inteiro_sinal = (i4) constant-3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_3_impl(u1 constant, frame *f){
	i4 inteiro_sinal = (i4) constant-3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_4_impl(u1 constant, frame *f){
	i4 inteiro_sinal = (i4) constant-3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_5_impl(u1 constant, frame *f){
	i4 inteiro_sinal = (i4) constant-3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

/*
	Long: pensar como faz
*/
void lconst_0_impl(u1 constant, frame *f){
	Push_operandos(f->p,constant,LONG_OP);
}

/*
	Long: pensar como faz
*/
void lconst_1_impl(u1 constant, frame *f){
	Push_operandos(f->p,constant,LONG_OP);
}


/*
	Float: pensar como faz.
	A leitura é diferente, no formato IEEE754
*/
void fconst_0_impl(u1 constant, frame *f){
	Push_operandos(f->p,constant,FLOAT_OP);
}

/*
	Float: pensar como faz.
	A leitura é diferente, no formato IEEE754
*/
void fconst_1_impl(u1 constant, frame *f){
	Push_operandos(f->p,constant,FLOAT_OP);
}

/*
	Float: pensar como faz.
	A leitura é diferente, no formato IEEE754
*/
void fconst_2_impl(u1 constant, frame *f){
	Push_operandos(f->p,constant,FLOAT_OP);
}

/*
	Double: pensar como faz.
	A leitura é diferente, no formato IEEE754
*/
void dconst_0_impl(u1 constant, frame *f){
	Push_operandos(f->p,constant,DOUBLE_OP);
}

/*
	Double: pensar como faz.
	A leitura é diferente, no formato IEEE754
*/
void dconst_1_impl(u1 constant, frame *f){
	Push_operandos(f->p,constant,DOUBLE_OP);
}

void bipush_impl(u1 byte, frame *f){
	i4 byte_int = (i4) byte;
	Push_operandos(f->p,byte_int,BYTE_OP);
}

void sipush_impl(u1 byte1, u1 byte2, frame *f){
	u2 byte_short = (byte1 << 8) | byte2;
	i4 byte_int = (i4) byte_short;
	Push_operandos(f->p,byte_int,SHORT_OP);
	Push_operandos(f->p,byte_int,SHORT_OP);
}
