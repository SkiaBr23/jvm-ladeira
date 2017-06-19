#ifndef JVM_H
#define JVM_H

#include "lista_classes.h"
#include "pilha_frames.h"

struct jvm{
	classesCarregadas * classes;
	pilha_frames * frames;
	//O ENDERECO É DADO PELA "POSICAO DO PONTEIRO",POR EXEMPLO, NEWARRAY UTILIZA DOIS VALORES, O OPCODE DA INSTRUCAO E O VALOR DO
	//TIPO, LOGO SOMA +2 EM PC, PERGUNTAR PARA O MAX!
	u4 pc;
};
typedef struct jvm JVM;

JVM* CriarJVM();
JVM* InicializarJVM();
int opcaoMenu ();
//CODIFICAR FUNCAO PARA LIBERAR JVM, CHAMANDO FUNCOES INTERNAS DE FREE DAS ESTRUTURAS
//void LiberarLista_frames(lista_frames *lis);

#endif
