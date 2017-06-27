#ifndef JVM_H
#define JVM_H

#include "lista_classes.h"
#include "pilha_frames.h"
#include "instrucoes.h"

struct jvm{
	classesCarregadas * classes;
	pilha_frames *frames;
	//O ENDERECO É DADO PELA "POSICAO DO PONTEIRO",POR EXEMPLO, NEWARRAY UTILIZA DOIS VALORES, O OPCODE DA INSTRUCAO E O VALOR DO
	//TIPO, LOGO SOMA +2 EM PC, PERGUNTAR PARA O MAX!
	u4 pc;
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
/*
	Função executarMetodo: chamador 1 quer dizer que a JVM está chamando a função.
	Chamador 2 quer dizer que uma função de implementação de instruções chamou essa função (exemplo: invokestatic)
*/
void executarMetodo(method_info *m, char *classeCorrente, int chamador);
//CODIFICAR FUNCAO PARA LIBERAR JVM, CHAMANDO FUNCOES INTERNAS DE FREE DAS ESTRUTURAS
//void LiberarLista_frames(lista_frames *lis);
void interpretarCode(u1 *code, u4 length);

#endif
