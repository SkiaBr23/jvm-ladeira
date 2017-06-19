/*
	Observar os comentários das instruções. Praticamente todas precisam ser finalizadas.
	Entender como acessar a constant pool, e como fazer as invocações de métodos, obtenção de fields e campos static, etc.
*/

#include "interpretador.h"
#include <stdlib.h>
#include <limits.h>

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
	endereco = ((i4*) referencia->topo->operando) + (indice->topo->operando * sizeof(i4));

	// Objetivo: Acessar o conteúdo do endereço "referencia+indice"
	// O código para esse acesso não parece correto, tem que analisar
	Push_operandos(f->p,*endereco,INTEGER_OP);
}

void faload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i4 *endereco = malloc(sizeof(i4));
	endereco = ((i4*) referencia->topo->operando) + (indice->topo->operando * sizeof(i4));

	// Acessar o conteúdo do endereço "referencia+indice"
	// O código para esse acesso não parece correto, tem que analisar
	Push_operandos(f->p,*endereco,FLOAT_OP);
}

void aaload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	u4 *endereco = malloc(sizeof(u4));
	endereco = ((u4*) referencia->topo->operando) + (indice->topo->operando * sizeof(u4));

	Push_operandos(f->p,*endereco,REFERENCE_OP);
}

void baload_impl(frame *f){

	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i1 *endereco = malloc(sizeof(i1));
	endereco = ((i1*) referencia->topo->operando) + (indice->topo->operando * sizeof(i1));
	i1 byte = *endereco;
	//O Sign Extend foi feito?
	Push_operandos(f->p,(i4) byte,BYTE_OP);
}

void caload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	u2 *endereco = malloc(sizeof(u2));
	endereco = ((u2*) referencia->topo->operando) + (indice->topo->operando * sizeof(u2));
	u2 caracter = *endereco;
	//O Zero Extend foi feito?
	Push_operandos(f->p,(u4) caracter,CHAR_OP);
}

void saload_impl(frame *f){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i2 *endereco = malloc(sizeof(i2));
	endereco = ((i2*) referencia->topo->operando) + (indice->topo->operando * sizeof(i2));
	i2 ashort = *endereco;
	//O Sign Extend foi feito?
	Push_operandos(f->p,(i4) ashort,SHORT_OP);
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

	i4 *endereco = malloc(sizeof(i4));
	endereco = ((i4*) array->topo->operando) + (indice->topo->operando * sizeof(i4));

	*endereco = valor->topo->operando;
}

void fastore_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i4 *endereco = malloc(sizeof(i4));
	endereco = ((i4*) array->topo->operando) + (indice->topo->operando * sizeof(i4));

	*endereco = valor->topo->operando;
}

void bastore_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i1 *endereco = malloc(sizeof(i1));
	endereco = ((i1*) array->topo->operando) + (indice->topo->operando * sizeof(i1));

	*endereco = valor->topo->operando;
}

void castore_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	u2 *endereco = malloc(sizeof(u2));
	endereco = ((u2*) array->topo->operando) + (indice->topo->operando * sizeof(u2));

	*endereco = valor->topo->operando;
}

void sastore_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i2 *endereco = malloc(sizeof(i2));
	endereco = ((i2*) array->topo->operando) + (indice->topo->operando * sizeof(i2));

	*endereco = valor->topo->operando;
}

pilha_operandos* pop_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);

	return(valor);
}

pilha_operandos** pop2_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos **vetor_retorno = malloc(2*sizeof(pilha_operandos));
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

void dup_impl(frame *f){
	pilha_operandos *valor = Topo_operandos(f->p);
	f->p = Push_operandos(f->p,valor->topo->operando,valor->topo->tipo_operando);
}

void dup_x1_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup_x2_impl(frame *f){
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

void dup2_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	// Se for 32 ou 64 bits, não faz diferença, como na instrução anterior.
	// Porém, verificar se isso é valido.
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup2_x1_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup2_x2_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);
	pilha_operandos *valor4 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor4->topo->operando,valor4->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void swap_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
}

void iadd_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	// Se os tipos dos valores forem iguais, e se esse tipo for inteiro
	valor3 = Push_operandos(valor3,valor1->topo->operando+valor2->topo->operando,valor1->topo->tipo_operando);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);

}

// Overflow pode ocorrer, mas mesmo assim, exceção não é lançada. Ou seja, é só subtrair
void isub_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	valor3 = Push_operandos(valor3,valor1->topo->operando-valor2->topo->operando, INTEGER_OP);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
}

void imul_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	valor3 = Push_operandos(valor3,valor1->topo->operando*valor2->topo->operando, INTEGER_OP);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
}

void idiv_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();
	if(valor2->topo->operando == 0){
		// Lançar exceção ArithmeticException
	}
	valor3 = Push_operandos(valor3,valor1->topo->operando/valor2->topo->operando, INTEGER_OP);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;

	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
}

void irem_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	if(valor2->topo->operando == 0){
		// Lançar Arithmetic Exception
	}

	i4 valor_push = valor1->topo->operando - (valor1->topo->operando/valor2->topo->operando) * valor2->topo->operando;

	valor3 = Push_operandos(valor3,valor_push,valor1->topo->tipo_operando);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;

	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
}

void ineg_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	// Colocar o valor na pilha negado
	f->p = Push_operandos(f->p,-(valor1->topo->operando),valor1->topo->tipo_operando);
}

void ishl_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 s = (valor2->topo->operando << 27) >> 27;

	i4 resultado = valor1->topo->operando << s;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}


void ishr_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 s = (i4) (valor2->topo->operando << 27) >> 27;

	i4 resultado = (i4) valor1->topo->operando >> s;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

// Verificar se a implementação é essa mesmo, para fazer a extensão do sinal
void iushr_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	u4 s = (u4) (valor2->topo->operando << 27) >> 27;

	u4 resultado = (u4) valor1->topo->operando >> s;

	f->p = Push_operandos(f->p,(i4) resultado,valor1->topo->tipo_operando);
}

void iand_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor1->topo->operando & valor2->topo->operando;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

void ior_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor1->topo->operando | valor2->topo->operando;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

void ixor_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor1->topo->operando ^ valor2->topo->operando;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

void iinc_impl(frame *f,u1 index, i1 constante){
	// Estender o sinal para 32 bits
	i4 inteiro_constante = (i4) constante;

	f->v[index] += inteiro_constante;
}

void i2b_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i1 truncado = (i1) valor1->topo->operando;

	i4 resultado = (i4) truncado;

	f->p = Push_operandos(f->p,resultado,BYTE_OP);
}

void i2c_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i1 truncado = (i1) valor1->topo->operando;

	i4 resultado = (i4) truncado;

	f->p = Push_operandos(f->p,resultado,CHAR_OP);
}

void i2s_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i2 truncado = (i2) valor1->topo->operando;

	i4 resultado = (i4) valor1->topo->operando;

	f->p = Push_operandos(f->p,resultado,SHORT_OP);
}

void ifeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2){

	
	pilha_operandos *valor1 = Pop_operandos(f->p);

	if(valor1->topo->operando == 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
		// Alterar o PC aqui para fazer o branch
	}
}

void ifne_impl_imple(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	if(valor1->topo->operando !=0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void iflt(frame *f, u1 branchbyte1, u1 branchbyte2){

	pilha_operandos *valor1 = Pop_operandos(f->p);

	if(valor->topo->valor1<0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifge_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->valor1 >= 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor1->topo->operando > 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifle_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	if(valor1->topo->operando <= 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void icmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando == valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void icmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando != valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void icmplt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando < valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void icmpge_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando >= valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void icmpgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando > valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void icmple_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando <= valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void acmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando == valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void acmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando != valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void inst_goto(frame *f,u1 branchbyte1, u1 branchbyte2){
	u2 branchoffset = (branchbyte1 << 8) | branchbyte2;

	// Efetuar o branch com branch offset
}

void jsr_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	u2 branchoffset = (branchbyte1 << 8) | branchbyte2;

	// Efetuar o branch com branch offset
}

void ret_impl(frame *f,u1 index){
	u1 endereco_retorno = f->v[index];

	// Escrever no registrador PC
}

/***** O valor retornado é entre frames. Analisar como acessar a estrutura global *****/
void ireturn_impl(frame *f){
	// Analisar as condições do método que deve ser retornado

	pilha_operandos *valor = Pop_operandos(f->p);

	// Empilhar na pilha de operandos do frame do chamador
	jvm->pilha_frames->prox = Push_operandos(valor);
}

void areturn_impl(frame *f){
	// Analisar mesmas coisas do ireturn
	pilha_operandos *valor = Pop_operandos(f->p);
}

void inst_return_impl(frame *f){

	// Empilhar NULL na pilha de operandos do frame chamador, ou seja, o próximo frame na pilha
	jvm->pilha_frames->prox = Push_operandos(NULL);
}

void getstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field
	struct Fieldref campo = f->cp[indice_cp];

	f->p = Push_operandos(f->p,(i4) indice_cp,REFERENCE_OP);
}

void putstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field

	struct Fieldref campo = f->cp[indice_cp];
}

void getfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	pilha_operandos *objeto = Pop_operandos(f->p);

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field

	struct Fieldref campo = f->cp[indice_cp];
}

void putfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field 

	struct Fieldref campo = f->cp[indice_cp];
}

void invokevirtual_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	struct Methodref metodo = f->cp[indice_cp];
}

void inst_new_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver a classe

	// Alocar memória

	// Colocar o ponteiro na pilha de operandos
}

void newarray_impl(frame *f, u1 atype){
	i4 count = Pop_operandos(f->p);

	void *endereco = NULL;
	i4 referencia = 0;

	if(count<0){
		// Lançar exceção
	}
	else{
		switch(atype){
			case T_BOOLEAN:
				endereco = malloc((count+1)*sizeof(u1));
				referencia = (i4) endereco;
			break;
	
			case T_CHAR:
				endereco = malloc((count+1)*sizeof(i2));
				referencia = (i4) endereco;
			break;
	
			case T_FLOAT:
				endereco = malloc((count+1)*sizeof(u4));
				referencia = (i4) endereco;
			break;
	
			case T_DOUBLE:
				endereco = malloc(2*(count+1)*sizeof(u4));
				referencia = (i4) endereco;
			break;
	
			case T_BYTE:
				endereco = malloc((count+1)*sizeof(i1));
				referencia = (i4) endereco;
			break;
	
			case T_SHORT:
				endereco = malloc((count+1)*sizeof(i2));
				referencia = (i4) endereco;
			break;
	
			case T_INT:
				endereco = malloc((count+1)*sizeof(i4));
				referencia = (i4) endereco;
			break;
	
			case T_LONG:
				endereco = malloc(2*(count+1)*sizeof(i4));
				referencia = (i4) endereco;
			break;
		}
	
		// Inicializar com os valores default
		for(void *p=endereco,i=0;i<=count;i++,p++){
			// Alocar com -INT_MAX para marcar o fim do array
			if(i==count){
				*p = -INT_MAX;
			}
			else{
				*p=0;
			}
		}
	
		f->p = Push_operandos(f->p,referencia,REFERENCE_OP);
	}
}

void arraylength_impl(frame *f){
	pilha_operandos *array_ref = Pop_operandos(f->p);
	i4 referencia = array_ref->operando;
	int tamanho = 0;

	/* Observação */
	// Não tem como descobrir o tipo do elemento, a princípio.
	// Como fazer esse incremento? Foi alocado como void, mas com sizeofs diferentes (observar instrução newarray)
	// O void vai garantir que o incremento é o mesmo?
	for (void *p = referencia;*p!=-INT_MAX;p++,tamanho++){
		
	}

	f->p = Push_operandos(f->p,tamanho,INTEGER_OP);

}

void ifnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	u2 offset = 0;

	if(valor==NULL){
		offset = (branchbyte1 << 8) | branchbyte2;
	}
	else{
		// Continuar execução normalmente
	}
}

void ifnonnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	u2 offset = 0;

	if(valor!=NULL){
		offset = (branchbyte1 << 8) | branchbyte2;
	}
	else{
		// Continuar execução normalmente
	}
}



























