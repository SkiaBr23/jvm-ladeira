#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instrucoes.h"
#include "jvm.h"
// #include "pilha_frames.h"
#include "leitura.h"
#include "interpretador.h"

#define MAIN_NOME "main"
#define DESCRIPTOR_MAIN "([Ljava/lang/String;)V"
#define PUBLIC_STATIC 0x0009

JVM *jvm = NULL;
instrucao* instrucoes;
void (*func_ptr[202])(frame*,u1,u1) = {nop_impl,aconst_null_impl,iconst_m1_impl,iconst_0_impl,iconst_1_impl,iconst_2_impl,iconst_3_impl,iconst_4_impl,iconst_5_impl,lconst_0_impl,lconst_1_impl,fconst_0_impl,fconst_1_impl,fconst_2_impl,dconst_0_impl,dconst_1_impl,bipush_impl,sipush_impl,ldc_impl,ldc_w_impl,ldc2_w_impl,iload_impl,lload_impl,fload_impl,dload_impl,aload_impl,iload_0_impl,iload_1_impl,iload_2_impl,iload_3_impl,lload_0_impl,lload_1_impl,lload_2_impl,lload_3_impl,fload_0_impl,fload_1_impl,fload_2_impl,fload_3_impl,dload_0_impl,dload_1_impl,dload_2_impl,dload_3_impl,aload_0_impl,aload_1_impl,aload_2_impl,aload_3_impl,iaload_impl,laload_impl,faload_impl,daload_impl,aaload_impl,baload_impl,caload_impl,saload_impl,istore_impl,lstore_impl,fstore_impl,dstore_impl,astore_impl,istore_0_impl,istore_1_impl,istore_2_impl,istore_3_impl,lstore_0_impl,lstore_1_impl,lstore_2_impl,lstore_3_impl,fstore_0_impl,fstore_1_impl,fstore_2_impl,fstore_3_impl,dstore_0_impl,dstore_1_impl,dstore_2_impl,dstore_3_impl,astore_0_impl,astore_1_impl,astore_2_impl,astore_3_impl,iastore_impl,lastore_impl,fastore_impl,dastore_impl,aastore_impl,bastore_impl,castore_impl,sastore_impl,pop_fantasma,pop2_fantasma,dup_impl,dup_x1_impl,dup_x2_impl,dup2_impl,dup2_x1_impl,dup2_x2_impl,swap_impl,iadd_impl,ladd_impl,fadd_impl,dadd_impl,isub_impl,lsub_impl,fsub_impl,dsub_impl,imul_impl,lmul_impl,fmul_impl,dmul_impl,idiv_impl,ldiv_impl,fdiv_impl,ddiv_impl,irem_impl,lrem_impl,frem_impl,drem_impl,ineg_impl,lneg_impl,dneg_impl,ishl_impl,lshl_impl,ishr_impl,lshr_impl,iushr_impl,lushr_impl,iand_impl,land_impl,ior_impl,lor_impl,ixor_impl,lxor_impl,iinc_fantasma,i2l_impl,i2f_impl,i2d_impl,l2i_impl,l2f_impl,l2d_impl,f2i_impl,f2l_impl,f2d_impl,d2i_impl,d2l_impl,d2f_impl,i2b_impl,i2c_impl,i2d_impl,i2s_impl,lcmp_impl,fcmpl_impl,fcmpg_impl,dcmpl_impl,dcmpg_impl,ifeq_impl,ifne_impl,iflt_impl,ifge_impl,ifgt_impl,ifle_impl,if_icmpeq_impl,if_icmpne_impl,if_icmplt_impl,if_icmpge_impl,if_icmpgt_impl,if_icmple_impl,acmpeq_impl,acmpne_impl,inst_goto_impl,jsr_impl,ret_impl,tableswitch_fantasma,lookupswitch_fantasma,ireturn_impl,lreturn_impl,freturn_impl,dreturn_impl,areturn_impl,inst_return_impl,getstatic_impl,putstatic_impl,getfield_impl,putfield_impl,invokevirtual_impl,invokespecial_impl,invokestatic_impl,invokeinterface_impl,invokedynamic_fantasma,inst_new_impl,newarray_impl,anewarray_impl,arraylength_impl,athrow_impl,checkcast_impl,instanceof_impl,monitorenter_impl,monitorexit_impl,wide_impl,multianewarray_impl,ifnull_impl,ifnonnull_impl,goto_w_impl,jsr_w_impl};

JVM* CriarJVM(){
	return NULL;
}

JVM* InicializarJVM() {
	JVM *novo;

	novo = (JVM*)malloc(sizeof(JVM));
	novo->classes = CriarLista_classes();
	novo->frames = CriarPilha_frames();
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

frame* criarFrame(char *classeCorrente){
	frame *f = malloc(sizeof(frame));
	f->end_retorno = jvm->pc;
	f->p = CriarPilha_operandos();
	//TRES PARA DEBUG -ajustar!
	f->v = malloc(3*sizeof(vetor_locais));
	for (int i = 0; i < 3; i++) {
		f->v[i].variavel = malloc(sizeof(u4));
	}
	f->cp = BuscarCPClasseCorrente_classes(jvm->classes,classeCorrente);

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
			executarMetodo(aux,"Main",1);
		}
	}
}

void executarMetodo(method_info *m, char* classeCorrente, int chamador){
	attribute_info *aux;

	int posicao;

	for(posicao=0;posicao<m->attributes_count;posicao++){
		aux = (*(m->attributes+posicao));
		classesCarregadas *classeAtual = BuscarElemento_classes(jvm->classes,classeCorrente);
		// code_attribute * auxCodePontual = (code_attribute*)(*(auxAttrCompleto+posicao))->info;
		char *nameindex = decodificaStringUTF8(classeAtual->arquivoClass->constant_pool-1+aux->attribute_name_index);
		printf("%s\n",nameindex);
		// Se for o atributo code
		if(strcmp(nameindex,"Code")==0){
			if(chamador==1){
				frame *f = criarFrame(classeCorrente);
				jvm->frames = Push_frames(jvm->frames,f);
			}
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
		printf("%s\n",i.inst_nome);
		j++;
		u1 numarg = i.numarg;
		ImprimirPilha_operandos(jvm->frames->topo->f->p);
		if(numarg>0){

			u1 *argumentos = malloc(numarg*sizeof(u1));
			// Criar vetor de ponteiro de funções
			// Deixar todas as funções com a mesma assinatura
			for(u1 arg=0;arg<numarg;arg++){
				argumentos[arg] = *j;
				// printf("%01x\t",argumentos[arg]);
				j++;
			}

			switch(numarg){
				case 1:
					(*func_ptr[i.opcode])(jvm->frames->topo->f,argumentos[0],0);
				break;

				case 2:
					printf("Opcode Case 2: %02x\n",i.opcode);
					(*func_ptr[i.opcode])(jvm->frames->topo->f,argumentos[0],argumentos[1]);
				break;
			}
		}
		else if(numarg==0){
			(*func_ptr[i.opcode])(jvm->frames->topo->f,0,0);
		}

		printf("\n\n");
	}
}
