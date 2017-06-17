#ifndef JVM_H
#define JVM_H

#include "lista_classes.h"
#include "pilha_frames.h"

struct jvm{
	classesCarregadas * classes;
	pilha_frames * frames;
};
typedef struct jvm JVM;

JVM* CriarJVM();
JVM* InicializarJVM();
int opcaoMenu ();
//CODIFICAR FUNCAO PARA LIBERAR JVM, CHAMANDO FUNCOES INTERNAS DE FREE DAS ESTRUTURAS
//void LiberarLista_frames(lista_frames *lis);

#endif
