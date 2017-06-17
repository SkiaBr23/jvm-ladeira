#include "interpretador.h"
#include <stdlib.h>

void aconst_null_impl(frame *f){
	Push_operandos(f->p,0,REFERENCE_OP); // 0 do tipo referência quer dizer referência apontando para NULL
}

void iconst_m1_impl(frame *f){
	/* 
		Tem um "shift" de -3. Ou seja, constant é um valor sem sinal.
		Esse valor é subtraído de 3 para descobrir a constante que vai ser armazenada na pilha.
	*/
	i4 inteiro_sinal = (i4) -1;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_0_impl(frame *f){
	i4 inteiro_sinal = (i4) 0;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_1_impl(frame *f){
	i4 inteiro_sinal = (i4) 1;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_2_impl(frame *f){
	i4 inteiro_sinal = (i4) 2;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_3_impl(frame *f){
	i4 inteiro_sinal = (i4) 3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_4_impl(frame *f){
	i4 inteiro_sinal = (i4) 4;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_5_impl(frame *f){
	i4 inteiro_sinal = (i4) 5;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void lconst_0_impl(frame *f){

	//Push 0L to stack
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,LONG_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,LONG_OP);
}

void lconst_1_impl(frame *f){

	//Push 1L to stack 
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,LONG_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 1;
	Push_operandos(f->p,low_bytes,LONG_OP);
}

void fconst_0_impl(frame *f){

	i4 float_bytes = (i4) 0;
	Push_operandos(f->p,float_bytes,FLOAT_OP);

}

void fconst_1_impl(frame *f){

	i4 float_bytes = 0x3f800000;
	Push_operandos(f->p,float_bytes,FLOAT_OP);

}

void fconst_2_impl(frame *f){

	i4 float_bytes = 0x40000000;
	Push_operandos(f->p,float_bytes,FLOAT_OP);

}

void dconst_0_impl(frame *f){

	//Push 0.0 double to stack
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,DOUBLE_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,DOUBLE_OP);
}

void dconst_1_impl(frame *f){

	//Push 1.0 double to stack
	i4 high_bytes = 0x3FF00000;	
	Push_operandos(f->p,high_bytes,DOUBLE_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,DOUBLE_OP);
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

void iload_impl(u1 index, frame *f){
	Push_operandos(f->p,(i4) *(f->v[index].variavel),INTEGER_OP);
}

void fload_impl(u1 index, frame *f){
	Push_operandos(f->p, (i4) *(f->v[index].variavel),FLOAT_OP);
}

void aload_impl(u1 index, frame *f){
	Push_operandos(f->p, (i4) *(f->v[index].variavel),REFERENCE_OP);
}

void iload_0_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),INTEGER_OP);
}

void iload_1_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),INTEGER_OP);
}

void iload_2_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),INTEGER_OP);
}

void iload_3_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),INTEGER_OP);
}

void fload_0_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),FLOAT_OP);
}

void fload_1_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),FLOAT_OP);
}

void fload_2_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),FLOAT_OP);
}

void fload_3_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),FLOAT_OP);
}

void aload_0_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),REFERENCE_OP);
}

void aload_1_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),REFERENCE_OP);
}

void aload_2_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),REFERENCE_OP);
}

void aload_3_impl(frame *f){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),REFERENCE_OP);
}


/* Verificar endereçamento */
/* Vale para iaload a saload */
void iaload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i4 *endereco = malloc(sizeof(i4 ));
	endereco = referencia->topo->operando + indice->topo->operando;

	// Objetivo: Acessar o conteúdo do endereço "referencia+indice"
	// O código para esse acesso não parece correto, tem que analisar
	Push_operandos(f->p,(i4) *endereco,INTEGER_OP);
}

void faload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	// Acessar o conteúdo do endereço "referencia+indice"
	// O código para esse acesso não parece correto, tem que analisar
	Push_operandos(f->p,(i4) ,FLOAT_OP);
}

void aaload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	Push_operandos(f->p,(i4) *((&(referencia->topo->operando))+(&(indice->topo->operando))),REFERENCE_OP);
}

void baload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	Push_operandos(f->p,(i4) *(&(referencia->topo->operando)+&(indice->topo->operando)),BYTE_OP);
}

void caload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	Push_operandos(f->p,(i4) *(&(referencia->topo->operando)+&(indice->topo->operando)),CHAR_OP);
}

void saload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	Push_operandos(f->p,(i4) *(&(referencia->topo->operando)+&(indice->topo->operando)),SHORT_OP);
}

void istore_impl(u1 index,frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);

	*(f->v[index].variavel) = (u4) valor->topo->operando;
}

void fstore_impl(u1 index, frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[index].variavel) = (u4) valor->topo->operando;
}








