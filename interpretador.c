#include "interpretador.h"
#include <stdlib.h>

void aconst_null_impl(frame *f){
	Push_operandos(f->p,0,REFERENCE_OP); // 0 do tipo referência quer dizer referência apontando para NULL
}

void iconst_m1_impl(frame *f){
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

void astore_impl(u1 index, frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[index].variavel) = (u4) valor->topo->operando;
}

void istore_0_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (u4) valor->topo->operando;
}

void istore_1_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (u4) valor->topo->operando;
}

void istore_2_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (u4) valor->topo->operando;
}

void istore_3_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (u4) valor->topo->operando;
}

void fstore_0_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (u4) valor->topo->operando;
}

void fstore_1_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (u4) valor->topo->operando;
}

void fstore_2_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (u4) valor->topo->operando;
}

void fstore_3_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (u4) valor->topo->operando;
}

void astore_0_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (u4) valor->topo->operando;
}

void astore_1_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (u4) valor->topo->operando;
}

void astore_2_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (u4) valor->topo->operando;
}

void astore_3_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (u4) valor->topo->operando;
}

/*
	Objetivo da instrução: atribuir um valor a uma posição de um array de inteiros
	Exemplo: v[2] = 3.
	Pegar o endereço de v, somar com 2 "endereços de v" e o valor dessa posição de memória será igual a 3.
	
	Não sabemos se isso está logicamente/semanticamente correto.
*/
void iastore_impl(frame *f){
	// Convém criar função pra desempilhar 3 valores, sei lá. Pra generalizar isso. Vamos analisar.
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	*(array->topo->operando+indice->topo->operando) = valor->topo->operando;
}

void fastore_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	*(array->topo->operando+indice->topo->operando) = valor->topo->operando;
}

void bastore_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	*(array->topo->operando+indice->topo->operando) = (i1) valor->topo->operando;
}

void castore_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	// i1 também pois char tem 1 byte
	*(array->topo->operando+indice->topo->operando) = (i1) valor->topo->operando;
}

void sastore_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	*(array->topo->operando+indice->topo->operando) = (i2) valor->topo->operando;
}

pilha_operandos* pop_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);

	return(valor);
}

pilha_operandos** pop2_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *vetor_retorno = malloc(2*sizeof(pilha_operandos));
	vetor_retorno[0] = valor1;	
	vetor_retorno[1] = valor2;	

	// Optamos por não montar o valor aqui, pois depende da instrução seguinte, que realizará alguma operação
	// A instrução de operação com os valores manipula do jeito que a gente precisar.
	/*// Se for categoria 2
	if(valor1->topo->tipo_operando == DOUBLE_OP || valor1->topo->tipo_operando == LONG_OP){
		vetor_retorno[0]->topo = malloc
	}
	// Se for categoria 1
	else{

	}*/

	return(vetor_retorno);
}

void dup(frame *f){
	pilha_operandos *valor = Topo_operandos(f->p);
	f->p = Push_operandos(f->p,valor->topo->operando,valor->topo->tipo_operando);
}

void dup_x1(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup_x2(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);

	// Se for categoria 2
	// Teoricamente não precisa desse if
	// Se valor2 for categoria 2, tem que desempilhar o próximo
	// Se não for, também tem que desempilhar o próximo 
	/*if(valor2->topo->tipo_operando == LONG_OP || valor2->topo->tipo_operando == DOUBLE_OP){

	}
	else{

	}*/

	// Valor 1,3,2,1 ou 1,2,1
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	// Se valor2 for categoria 2, valor3 e valor2 se referem ao mesmo número
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup2(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	// Se for 32 ou 64 bits, não faz diferença, como na instrução anterior.
	// Porém, verificar se isso é valido.
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup2_x1(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup2_x2(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);
	pilha_operandos *valor4 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor4->topo->operando,valor4->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}











