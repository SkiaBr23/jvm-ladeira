#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instrucoes.h"
#include "jvm.h"
// #include "pilha_frames.h"
#include "leitura.h"

#define MAIN_NOME "main"
#define DESCRIPTOR_MAIN "([Ljava/lang/String;)V"
#define PUBLIC_STATIC 0x0009

JVM *jvm = NULL;
instrucao* instrucoes;

JVM* CriarJVM(){
	return NULL;
}

JVM* InicializarJVM() {
	JVM *novo;

	novo = (JVM*)malloc(sizeof(JVM));
	novo->classes = malloc(sizeof(classesCarregadas));
	novo->frames = malloc(sizeof(pilha_frames));
	novo->frames->topo = NULL;
	novo->pc = 0; 

	instrucoes = construirInstrucoes();

	return novo;
}

int opcaoMenu () {

	int op = 0;
	printf("Software Basico 01/2017 - Universidade de Brasilia\n");
	printf("Maquina Virtual Java\n");
	while (op < 1 || op > 3) {
		printf("Por favor, selecione uma das opcoes abaixo para prosseguir com a execucao do programa:\n");
		printf("[1] - Impressao de arquivo .class\n");
		printf("[2] - Execucao de arquivo .class\n");
		printf("[3] - Encerrar programa\n");
		printf("Opcao: ");
		scanf("%d",&op);
		getchar();
	}
	return op;
}

frame* criarFrame(){
	frame *f = malloc(sizeof(frame));
	f->end_retorno = jvm->pc;
	f->p = CriarPilha_operandos();
	f->v = NULL;
	f->cp = jvm->classes->arquivoClass->constant_pool;

	return(f);
}

void executarJVM(){

	method_info *metodos = jvm->classes->arquivoClass->methods;

	int i=0;

	for(method_info *aux=metodos;i<jvm->classes->arquivoClass->methods_count;aux++,i++){
		char *stringmetodo = decodificaStringUTF8(jvm->classes->arquivoClass->constant_pool-1+aux->name_index);
		char *stringdescriptor = decodificaStringUTF8(jvm->classes->arquivoClass->constant_pool-1+aux->descriptor_index);

		// Se for o método main
		if(strcmp(stringmetodo,MAIN_NOME)==0 && strcmp(stringdescriptor,DESCRIPTOR_MAIN)==0 && aux->access_flags==PUBLIC_STATIC){
			executarMetodo(aux);
		}
	}
}

void executarMetodo(method_info *m){
	attribute_info *aux;

	int posicao;

	for(posicao=0;posicao<m->attributes_count;posicao++){
		aux = (*(m->attributes+posicao));
		// code_attribute * auxCodePontual = (code_attribute*)(*(auxAttrCompleto+posicao))->info;
		char *nameindex = decodificaStringUTF8(jvm->classes->arquivoClass->constant_pool-1+aux->attribute_name_index);
		printf("%s\n",nameindex);
		// Se for o atributo code
		if(strcmp(nameindex,"Code")==0){
			frame *f = criarFrame();
			jvm->frames = Push_frames(jvm->frames,f);

			code_attribute *c = (code_attribute *) aux->info;

			interpretarCode(c->code,c->code_length);

		}
	}
}

void interpretarCode(u1 *code,u4 length){
	u1 opcode;
	for (u1 *j=code;j<code+length;){
		opcode = *j;

		instrucao i = instrucoes[opcode];
		printf("%s\t",i.inst_nome);
		j++;
		u1 numarg = i.numarg;
		if(numarg>0){

			u1 *argumentos = malloc(numarg*sizeof(u1));
			// Criar vetor de ponteiro de funções
			// Deixar todas as funções com a mesma assinatura
			for(u1 i=0;i<numarg;i++){
				argumentos[i] = *j;
				printf("%01x\t",argumentos[i]);
				j++;
			}
		}

		printf("\n\n");
	}
}

