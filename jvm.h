#ifndef JVM_H
#define JVM_H

#include "lista_classes.h"
#include "pilha_frames.h"
#include "instrucoes.h"

struct lista_objetos {
	ClassFile * obj;
	u1 sizeData;
	u4 * data;
	struct lista_objetos * prox;
	struct lista_objetos * ant;
};
typedef struct lista_objetos Lista_Objetos;

struct jvm{
	classesCarregadas * classes;
	pilha_frames *frames;
	u4 pc;
	u2 excecao;
	Lista_Objetos * objetos;
	char *excecao_nome;
};
typedef struct jvm JVM;

extern JVM *jvm;
extern instrucao* instrucoes;

JVM* CriarJVM();
JVM* InicializarJVM();
int opcaoMenu();
frame* criarFrame(char *classeCorrente, u2 max_locals);
void executarJVM();
u1 * atualizarPCMetodoAtual (u1 * code, u4 length);
void ImprimeCode (u1 * code, u4 length);
bool instrucaoBranch (char * nomeInstrucao);
/*
	Função executarMetodo: chamador 1 quer dizer que a JVM está chamando a função.
	Chamador 2 quer dizer que uma função de implementação de instruções chamou essa função (exemplo: invokestatic)
*/
void executarMetodo(method_info *m, char *classeCorrente, int chamador);
//CODIFICAR FUNCAO PARA LIBERAR JVM, CHAMANDO FUNCOES INTERNAS DE FREE DAS ESTRUTURAS
//void LiberarLista_frames(lista_frames *lis);
void interpretarCode(u1 *code, u4 length,method_info *m);
void freeVetorLocais(vetor_locais *v, u2 vetor_length);
u2 verificaHandlerMetodo(method_info *m);

#define MAIN_NOME "main"
#define DESCRIPTOR_MAIN "([Ljava/lang/String;)V"
#define PUBLIC_STATIC 0x0009

#define CLINIT_NOME "<clinit>"
#define DESCRIPTOR_CLINIT "()V"
#define STATICCLINIT 0x0008

#define INIT_NOME "<init>"
#define DESCRIPTOR_INIT "()V"

#endif
