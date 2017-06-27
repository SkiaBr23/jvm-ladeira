/*
	Observar os comentários das instruções. Praticamente todas precisam ser finalizadas.
	Entender como acessar a constant pool, e como fazer as invocações de métodos, obtenção de fields e campos static, etc.
*/

#include "interpretador.h"
#include "jvm.h"
#include "leitura.h"
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

/*
	Na hora de resolver a classe, executar o init dela
*/
ClassFile* resolverClasse(char* nome_classe){
	classesCarregadas *c = BuscarElemento_classes(jvm->classes,nome_classe);
	ClassFile *classe = NULL;

	if(c!=NULL){
		return c->arquivoClass;
	}
	else{
		char *nomearquivo = malloc((strlen(nome_classe)+7)*sizeof(char));
		strcpy(nomearquivo,nome_classe);
		strcat(nomearquivo,".class");
		printf("Nome Arquivo: %s\n",nomearquivo);
		classe = lerArquivo(nomearquivo);
		jvm->classes = InserirFim_classes(jvm->classes,classe);
	}

	return(classe);
}

/*
	Depois da resolverMetodo, analisar semanticamente. Ver o número de argumentos, o tipo deles, ver se está tudo coerente com o descritor do método.
*/
bool resolverMetodo(cp_info *cp, u2 indice_cp){

	cp_info *methodref = cp-1+indice_cp;
	char *nome_classe = decodificaNIeNT(cp,methodref->UnionCP.Methodref.class_index,NAME_INDEX);
	char *descriptor = decodificaNIeNT(cp,methodref->UnionCP.Methodref.name_and_type_index,NAME_AND_TYPE);

	if(resolverClasse(nome_classe)!=NULL){
		return true;
	}
	else{
		return false;
	}
}

char* obterNomeMetodo(cp_info *cp, u2 indice_cp){
	cp_info *methodref = cp-1+indice_cp;
	char *descriptor = decodificaNIeNT(cp,methodref->UnionCP.Methodref.name_and_type_index,NAME_AND_TYPE);
	char *pch = strtok(descriptor,":");

	return(pch);
}

char* obterDescriptorMetodo(cp_info *cp, u2 indice_cp){
	cp_info *methodref = cp-1+indice_cp;
	char *descriptor = decodificaNIeNT(cp,methodref->UnionCP.Methodref.name_and_type_index,NAME_AND_TYPE);
	char *pch = strtok(descriptor,":");
	pch = strtok(NULL,":");

	return(pch);
}

char* obterClasseDoMetodo(cp_info *cp, u2 indice_cp){
	cp_info *methodref = cp-1+indice_cp;
	char *nome_classe = decodificaNIeNT(cp,methodref->UnionCP.Methodref.class_index,NAME_INDEX);
	return(nome_classe);
}

frame* transferePilhaVetor(frame *anterior, frame *novo, int *parametros_cont){
	pilha_operandos *aux = CriarPilha_operandos();
	int cont = 0;
	while(anterior->p->topo!=NULL){
		pilha_operandos *p = Pop_operandos(anterior->p);
		aux = Push_operandos(aux,p->topo->operando,(void*)p->topo->referencia,p->topo->tipo_operando);
		cont++;
	}

	novo->v = malloc(cont*sizeof(vetor_locais));

	for(int i=0;i<cont;i++){
		pilha_operandos *p = Pop_operandos(aux);
		novo->v[i].variavel = malloc(sizeof(u4));
		if(p->topo->tipo_operando<=8){
			*(novo->v[i].variavel) = (u4) p->topo->operando;
		}
		else{
			*(novo->v[i].variavel) = (u4 *) p->topo->referencia;
		}
		novo->v[i].tipo_variavel = (u1) p->topo->tipo_operando;
	}

	*parametros_cont = cont;

	return(novo);
}

void nop_impl(frame *par0, u1 par1, u1 par2){
	// Não implementada
}

void aconst_null_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,0,NULL,REFERENCE_OP); // 0 do tipo referência quer dizer referência apontando para NULL
}

void iconst_m1_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) -1;
	Push_operandos(f->p,inteiro_sinal,NULL,INTEGER_OP);
}

void iconst_0_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 0;
	Push_operandos(f->p,inteiro_sinal,NULL,INTEGER_OP);
}

void iconst_1_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 1;
	Push_operandos(f->p,inteiro_sinal,NULL,INTEGER_OP);
}

void iconst_2_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 2;
	Push_operandos(f->p,inteiro_sinal,NULL,INTEGER_OP);
}

void iconst_3_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 3;
	Push_operandos(f->p,inteiro_sinal,NULL,INTEGER_OP);
}

void iconst_4_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 4;
	Push_operandos(f->p,inteiro_sinal,NULL,INTEGER_OP);
}

void iconst_5_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 5;
	Push_operandos(f->p,(u4)inteiro_sinal,NULL,INTEGER_OP);
}

//Insere 0L na pilha de operandos TOPO|lb|hb|...|base
void lconst_0_impl(frame *f, u1 par1, u1 par2){

	//Push 0L to stack
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,NULL,LONG_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,NULL,LONG_OP);
}

void lconst_1_impl(frame *f, u1 par1, u1 par2){

	//Push 1L to stack
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,NULL,LONG_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 1;
	Push_operandos(f->p,low_bytes,NULL,LONG_OP);
}
//Insere 0.0 na pilha de operandos
void fconst_0_impl(frame *f, u1 par1, u1 par2){

	i4 float_bytes = (i4) 0;
	Push_operandos(f->p,float_bytes,NULL,FLOAT_OP);

}

void fconst_1_impl(frame *f, u1 par1, u1 par2){

	i4 float_bytes = 0x3f800000;
	Push_operandos(f->p,float_bytes,NULL,FLOAT_OP);

}

void fconst_2_impl(frame *f, u1 par1, u1 par2){

	i4 float_bytes = 0x40000000;
	Push_operandos(f->p,float_bytes,NULL,FLOAT_OP);

}

//Insere 0.0d na pilha de operandos
void dconst_0_impl(frame *f, u1 par1, u1 par2){

	//Push 0.0 double to stack
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,NULL,DOUBLE_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,NULL,DOUBLE_OP);
}

void dconst_1_impl(frame *f, u1 par1, u1 par2){

	//Push 1.0 double to stack
	i4 high_bytes = 0x3FF00000;
	Push_operandos(f->p,high_bytes,NULL,DOUBLE_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,NULL,DOUBLE_OP);
}

//Push sexted byte para a pilha de operandos
void bipush_impl(frame *f, u1 byte, u1 par1){
	i1 aux = (i1)byte;
	i4 byte_int = (i4) aux;
	Push_operandos(f->p,byte_int,NULL,BYTE_OP);
}

//Push sexted short para a pilha de operandos
void sipush_impl(frame *f, u1 byte1, u1 byte2){
	u2 byte_short = (byte1 << 8) | byte2;
	i4 byte_int = (i4) byte_short;
	Push_operandos(f->p,byte_int,NULL,SHORT_OP);
}

void ldc_impl(frame *f, u1 indexbyte1, u1 par2){
	cp_info *item = f->cp-1 + indexbyte1;
	void *valor=NULL;
	u4 num=0;
	void *classe=NULL;

	printf("\n\nEXECUTANDO LDC\n\n");
	printf("\nitem->tag: %d\n",item->tag);

	switch(item->tag){
		case CONSTANT_String:
			valor = (char*) decodificaStringUTF8(f->cp-1+item->UnionCP.String.string_index);
			f->p = Push_operandos(f->p,-INT_MAX,valor,REFERENCE_OP);
			u4 *endereco = (u4*) f->p->topo->referencia;

			printf("STRING EMPILHADA: %s\n",(char*) endereco);
		break;
		case CONSTANT_Float:
			num = item->UnionCP.Float.bytes;
			f->p = Push_operandos(f->p,num,NULL,FLOAT_OP);
		break;
		case CONSTANT_Integer:
			num = item->UnionCP.Integer.bytes;
			f->p = Push_operandos(f->p,num,NULL,INTEGER_OP);
		break;
		case CONSTANT_Class:
			valor = (char*) decodificaStringUTF8(f->cp-1+item->UnionCP.Class.name_index);
			classe = resolverClasse(valor);
			f->p = Push_operandos(f->p,-INT_MAX,classe,REFERENCE_OP);
		break;
		default:
			printf("\nName index: %d\n",item->UnionCP.Methodref.class_index);
			printf("\nName and type index: %d\n",item->UnionCP.Methodref.name_and_type_index);
			valor = (char *) decodificaNIeNT(f->cp,item->UnionCP.Methodref.class_index,NAME_INDEX);
			printf("\nPORCARIA: %s\n",valor);
			valor = (char *) decodificaNIeNT(f->cp,item->UnionCP.Methodref.name_and_type_index,NAME_AND_TYPE);
			printf("\nPORCARIA: %s\n",valor);

		break;

		/* Implementar depois, pois não temos no arquivo */
		/*case CONSTANT_MethodHandle:
		break;
		case CONSTANT_MethodType:
		break;*/
	}

}

void ldc_w_impl(frame *par0, u1 par1, u1 par2){

}

void ldc2_w_impl(frame *par0, u1 par1, u1 par2){

}
//Carrega inteiro do frame para a pilha de operandos
void iload_impl(frame *f, u1 index, u1 par1){
	Push_operandos(f->p,(i4) *(f->v[index].variavel),NULL,INTEGER_OP);
}

//Carrega long do frame para a pilha de operandos
void lload_impl(frame *f, u1 index, u1 par1){
	//Checar se a ordem ta certa, o topo da pilha deveria ser o LOW
	Push_operandos(f->p,(i4) *(f->v[index].variavel),NULL,LONG_OP);//high
	Push_operandos(f->p,(i4) *(f->v[index+1].variavel),NULL,LONG_OP);//low
}

//Carrega float do frame para a pilha de operandos
void fload_impl(frame *f, u1 index, u1 par1){
	Push_operandos(f->p, (i4) *(f->v[index].variavel),NULL,FLOAT_OP);
}

//Carrega double do frame para a pilha de operandos
void dload_impl(frame *f, u1 index, u1 par2){
	//Checar se a ordem ta certa, o topo da pilha deveria ser o LOW
	Push_operandos(f->p,(i4) *(f->v[index].variavel),NULL,DOUBLE_OP);
	Push_operandos(f->p,(i4) *(f->v[index+1].variavel),NULL,DOUBLE_OP);
}

//Carrega referencia de array para a pilha de operandos
void aload_impl(frame *f, u1 index, u1 par1){
	Push_operandos(f->p,-INT_MAX,f->v[index].variavel,REFERENCE_OP);
}

//Carrega inteiro na posicao 0 para a pilha
void iload_0_impl(frame *f, u1 par1, u1 par2){
	//Implementar assim ou chamando iload_impl(0)?
	Push_operandos(f->p,(i4) *(f->v[0].variavel),NULL,INTEGER_OP);
}
void iload_1_impl(frame *f, u1 par1, u1 par2){
	printf("Valor iload1: %d\n",*(f->v[1].variavel));
	Push_operandos(f->p,(i4) *(f->v[1].variavel),NULL,INTEGER_OP);
}

void iload_2_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),NULL,INTEGER_OP);
}

void iload_3_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),NULL,INTEGER_OP);
}

//Carrega long na posicao 0 para a pilha
void lload_0_impl(frame *f, u1 par, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),NULL,LONG_OP);//high
	Push_operandos(f->p,(i4) *(f->v[1].variavel),NULL,LONG_OP);//low
}
void lload_1_impl(frame *f, u1 par, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),NULL,LONG_OP);
	Push_operandos(f->p,(i4) *(f->v[2].variavel),NULL,LONG_OP);
}
void lload_2_impl(frame *f, u1 par, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),NULL,LONG_OP);
	Push_operandos(f->p,(i4) *(f->v[3].variavel),NULL,LONG_OP);
}
void lload_3_impl(frame *f, u1 par, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),NULL,LONG_OP);
	Push_operandos(f->p,(i4) *(f->v[4].variavel),NULL,LONG_OP);
}

//Carrega float na posicao 0
void fload_0_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),NULL,FLOAT_OP);
}

void fload_1_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),NULL,FLOAT_OP);
}

void fload_2_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),NULL,FLOAT_OP);
}

void fload_3_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),NULL,FLOAT_OP);
}
//Carrega double na posicao 0 para a pilha
void dload_0_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),NULL,DOUBLE_OP);//high
	Push_operandos(f->p,(i4) *(f->v[1].variavel),NULL,DOUBLE_OP);//low
}
void dload_1_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),NULL,DOUBLE_OP);
	Push_operandos(f->p,(i4) *(f->v[2].variavel),NULL,DOUBLE_OP);
}
void dload_2_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),NULL,DOUBLE_OP);
	Push_operandos(f->p,(i4) *(f->v[3].variavel),NULL,DOUBLE_OP);
}
void dload_3_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),NULL,DOUBLE_OP);
	Push_operandos(f->p,(i4) *(f->v[4].variavel),NULL,DOUBLE_OP);
}

//Carrega referencia na posicao 0 para a pilha
void aload_0_impl(frame *f, u1 par1, u1 par2){
	printf("\n\nEXECUTANDO ALOAD_0\n\n");
	Push_operandos(f->p,-INT_MAX,f->v[0].variavel,REFERENCE_OP);
}

void aload_1_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,-INT_MAX,f->v[1].variavel,REFERENCE_OP);
}

void aload_2_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,-INT_MAX,f->v[2].variavel,REFERENCE_OP);
}

void aload_3_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,-INT_MAX,f->v[3].variavel,REFERENCE_OP);
}


/* Verificar endereçamento */
/* Vale para iaload a saload */
void iaload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) referencia->topo->operando) + (indice->topo->operando * sizeof(i4));

	// Objetivo: Acessar o conteúdo do endereço "referencia+indice"
	// O código para esse acesso não parece correto, tem que analisar
	// Push_operandos(f->p,endereco,INTEGER_OP);
}

void laload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i4 *endereco = malloc(sizeof(i4 ));
	endereco = ((i4*) referencia->topo->operando) + (indice->topo->operando * sizeof(i4));

	//Verificar ordem
	Push_operandos(f->p,*endereco,NULL,LONG_OP);
	Push_operandos(f->p,*(endereco++),NULL,LONG_OP);
}

void faload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) referencia->topo->operando) + (indice->topo->operando * sizeof(i4));

	// Acessar o conteúdo do endereço "referencia+indice"
	// O código para esse acesso não parece correto, tem que analisar
	// Push_operandos(f->p,endereco,FLOAT_OP);
}

void daload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i4 *endereco = malloc(sizeof(i4 ));
	endereco = ((i4*) referencia->topo->operando) + (indice->topo->operando * sizeof(i4));

	//Verificar ordem
	Push_operandos(f->p,*endereco,NULL,DOUBLE_OP);
	Push_operandos(f->p,*(endereco++),NULL,DOUBLE_OP);
}

void aaload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	u4 endereco;
	endereco = ((u4) referencia->topo->operando) + (indice->topo->operando * sizeof(u4));

	// Push_operandos(f->p,endereco,REFERENCE_OP);
}

void baload_impl(frame *f, u1 par1, u1 par2){

	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i1 endereco;
	endereco = ((i1) referencia->topo->operando) + (indice->topo->operando * sizeof(i1));
	i1 byte = endereco;
	//O Sign Extend foi feito?
	Push_operandos(f->p,(i4) byte,NULL,BYTE_OP);
}

void caload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	u2 endereco;
	endereco = ((u2) referencia->topo->operando) + (indice->topo->operando * sizeof(u2));
	u2 caracter = endereco;
	//O Zero Extend foi feito?
	Push_operandos(f->p,(u4) caracter,NULL,CHAR_OP);
}

void saload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i2 endereco;
	endereco = ((i2) referencia->topo->operando) + (indice->topo->operando * sizeof(i2));
	i2 ashort = endereco;
	//O Sign Extend foi feito?
	Push_operandos(f->p,(i4) ashort,NULL,SHORT_OP);
}

void istore_impl(frame *f, u1 index,u1 par1){
	pilha_operandos *valor = Pop_operandos(f->p);

	*(f->v[index].variavel) = (i4) valor->topo->operando;
}

void lstore_impl(frame *f, u1 index, u1 par1){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[index].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[index+1].variavel) = (u4) low_bytes->topo->operando;
}

void fstore_impl(frame *f, u1 index,u1 par1){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[index].variavel) = (u4) valor->topo->operando;
}

void dstore_impl(frame *f, u1 index, u1 par1){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[index].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[index+1].variavel) = (u4) low_bytes->topo->operando;
}

void astore_impl(frame *f, u1 index,u1 par1){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[index].variavel) = (u4) valor->topo->operando;
}

void istore_0_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (i4) valor->topo->operando;
}

void istore_1_impl(frame *f, u1 par1, u1 par2){

	printf("EXECUÇÃO ISTORE_1\n\n");

	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (i4) valor->topo->operando;
}

void istore_2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (i4) valor->topo->operando;
}

void istore_3_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (i4) valor->topo->operando;
}

void lstore_0_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[0].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[1].variavel) = (u4) low_bytes->topo->operando;
}

void lstore_1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[1].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[2].variavel) = (u4) low_bytes->topo->operando;
}

void lstore_2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[2].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[3].variavel) = (u4) low_bytes->topo->operando;
}

void lstore_3_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[3].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[4].variavel) = (u4) low_bytes->topo->operando;
}

void fstore_0_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (u4) valor->topo->operando;
}

void fstore_1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (u4) valor->topo->operando;
}

void fstore_2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (u4) valor->topo->operando;
}

void fstore_3_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (u4) valor->topo->operando;
}

void dstore_0_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[0].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[1].variavel) = (u4) low_bytes->topo->operando;
}

void dstore_1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[1].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[2].variavel) = (u4) low_bytes->topo->operando;
}

void dstore_2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[2].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[3].variavel) = (u4) low_bytes->topo->operando;
}

void dstore_3_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);

	*(f->v[3].variavel) = (u4) high_bytes->topo->operando;
	*(f->v[4].variavel) = (u4) low_bytes->topo->operando;
}

void astore_0_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (u4) valor->topo->operando;
}

void astore_1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (u4) valor->topo->operando;
}

void astore_2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (u4) valor->topo->operando;
}

void astore_3_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (u4) valor->topo->operando;
}

/*
	Objetivo da instrução: atribuir um valor a uma posição de um array de inteiros
	Exemplo: v[2] = 3.
	Pegar o endereço de v, somar com 2 "endereços de v" e o valor dessa posição de memória será igual a 3.

	Não sabemos se isso está logicamente/semanticamente correto.

	FORCA: Mudei enderecos para i4 em vez de i4*, acho que ta errado, mas vcs fizeram assim entao convem ver nos testes
*/
void iastore_impl(frame *f, u1 par1, u1 par2){
	// Convém criar função pra desempilhar 3 valores, sei lá. Pra generalizar isso. Vamos analisar.
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) array->topo->operando) + (indice->topo->operando * sizeof(i4));

	endereco = valor->topo->operando;
}

void lastore_impl(frame *f, u1 par1, u1 par2){

	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) array->topo->operando) + (indice->topo->operando * sizeof(i4));

	endereco = high_bytes->topo->operando;
	endereco = endereco + sizeof(i4);
	endereco = low_bytes->topo->operando;
}

void fastore_impl(frame *f, u1 par1, u1 par2){

	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) array->topo->operando) + (indice->topo->operando * sizeof(i4));

	endereco = valor->topo->operando;
}

void dastore_impl(frame *f, u1 par1, u1 par2){

	pilha_operandos *low_bytes = Pop_operandos(f->p);
	pilha_operandos *high_bytes = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) array->topo->operando) + (indice->topo->operando * sizeof(i4));

	endereco = high_bytes->topo->operando;
	endereco = endereco + sizeof(i4);
	endereco = low_bytes->topo->operando;
}

void bastore_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i1 endereco;
	endereco = ((i1) array->topo->operando) + (indice->topo->operando * sizeof(i1));

	endereco = valor->topo->operando;
}

void castore_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	u2 endereco;
	endereco = ((u2) array->topo->operando) + (indice->topo->operando * sizeof(u2));

	endereco = valor->topo->operando;
}

void sastore_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i2 endereco;
	endereco = ((i2) array->topo->operando) + (indice->topo->operando * sizeof(i2));

	endereco = valor->topo->operando;
}

void aastore_impl(frame *f, u1 par1, u1 par2){

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

void pop_fantasma(frame *f, u1 par1, u1 par2){
	pilha_operandos *desempilhado = pop_impl(f);
}

void pop2_fantasma(frame *par0, u1 par1, u1 par2){

}

void dup_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Topo_operandos(f->p);
	f->p = Push_operandos(f->p,valor->topo->operando,valor->topo->referencia,valor->topo->tipo_operando);
}

void dup_x1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->referencia,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
}

void dup_x2_impl(frame *f, u1 par1, u1 par2){
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
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
	// Se valor2 for categoria 2, valor3 e valor2 se referem ao mesmo número
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->referencia,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->referencia,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
}

void dup2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	// Se for 32 ou 64 bits, não faz diferença, como na instrução anterior.
	// Porém, verificar se isso é valido.
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->referencia,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->referencia,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
}

void dup2_x1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->referencia,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->referencia,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
}

void dup2_x2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);
	pilha_operandos *valor4 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor4->topo->operando,valor4->topo->referencia,valor4->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->referencia,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->referencia,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
}

void swap_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->referencia,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->referencia,valor2->topo->tipo_operando);
}

void iadd_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();
	// Se os tipos dos valores forem iguais, e se esse tipo for inteiro
	valor3 = Push_operandos(valor3,valor1->topo->operando+valor2->topo->operando,NULL,valor1->topo->tipo_operando);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;
	f->p = Push_operandos(f->p,valor3->topo->operando,NULL,valor3->topo->tipo_operando);

}

void ladd_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes1 = Pop_operandos(f->p);
	pilha_operandos *high_bytes1 = Pop_operandos(f->p);

	u8 long1 = ((u8)high_bytes1->topo->operando << 32) | low_bytes1->topo->operando;


	pilha_operandos *low_bytes2 = Pop_operandos(f->p);
	pilha_operandos *high_bytes2 = Pop_operandos(f->p);

	u8 long2 = ((u8)high_bytes2->topo->operando << 32) | low_bytes2->topo->operando;

	u8 result = long1 + long2;

	f->p = Push_operandos(f->p, (u4)(result>>32), NULL,LONG_OP);
	f->p = Push_operandos(f->p, (u4)result,NULL, LONG_OP);

}

void fadd_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	u4 op1 = valor1->topo->operando;
	u4 op2 = valor2->topo->operando;
	u4 big_op, small_op;

	if(expoente(op1)>expoente(op2)){
		big_op = op1;
		small_op = op2;
	}else if(expoente(op2)>expoente(op1)){
		big_op = op2;
		small_op = op1;
	}else if(mantissa(op2)>mantissa(op1)){
		big_op = op2;
		small_op = op1;
	}else{
		big_op = op1;
		small_op = op2;
	}
	i4 operacao = (sinal(op1)!=sinal(op2))? -1:1;
	i4 result_exp = expoente(big_op);
	u4 result_mant = mantissa(big_op) + (operacao*(mantissa(small_op) << (expoente(big_op) - expoente(small_op))));
	u4 result_sin = sinal(big_op);

	//Normaliza float
	while((result_mant>>23) != 0){
		result_mant = result_mant>>1;
		result_exp++;
	}

	//Constroi float
	u4 result = (result_sin<<31) | (result_exp<<23) | result_mant;

	f->p = Push_operandos(f->p,result,NULL,FLOAT_OP);

}
void dadd_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1_low = Pop_operandos(f->p);
	pilha_operandos *valor1_high = Pop_operandos(f->p);
	pilha_operandos *valor2_low = Pop_operandos(f->p);
	pilha_operandos *valor2_high = Pop_operandos(f->p);

	u8 op1 = ((u8)valor1_high->topo->operando << 32) | valor1_low->topo->operando;
	u8 op2 = ((u8)valor2_high->topo->operando << 32) | valor2_low->topo->operando;
	u8 big_op, small_op;

	if(expoente_d(op1)>expoente_d(op2)){
		big_op = op1;
		small_op = op2;
	}else if(expoente_d(op2)>expoente_d(op1)){
		big_op = op2;
		small_op = op1;
	}else if(mantissa_d(op2)>mantissa_d(op1)){
		big_op = op2;
		small_op = op1;
	}else{
		big_op = op1;
		small_op = op2;
	}
	i4 operacao = (sinal_d(op1)!=sinal_d(op2))? -1:1;
	i8 result_exp = expoente_d(big_op);
	u8 result_mant = mantissa_d(big_op) + (operacao*(mantissa_d(small_op) << (expoente_d(big_op) - expoente_d(small_op))));
	u8 result_sin = sinal_d(big_op);

	//Normaliza double
	while((result_mant>>52) != 0){
		result_mant = result_mant>>1;
		result_exp++;
	}

	//Constroi float
	u8 result = (result_sin<<63) | (result_exp<<52) | result_mant;

	f->p = Push_operandos(f->p, (u4)(result>>32),NULL, DOUBLE_OP);
	f->p = Push_operandos(f->p, (u4)result,NULL, DOUBLE_OP);

}
// Overflow pode ocorrer, mas mesmo assim, exceção não é lançada. Ou seja, é só subtrair
void isub_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	// Se os tipos dos valores forem iguais, e se esse tipo for inteiro
	i4 result = valor1->topo->operando-valor2->topo->operando;
	f->p = Push_operandos(f->p,result,NULL,INTEGER_OP);
}

void lsub_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes1 = Pop_operandos(f->p);
	pilha_operandos *high_bytes1 = Pop_operandos(f->p);

	u8 long1 = ((u8)high_bytes1->topo->operando << 32) | low_bytes1->topo->operando;


	pilha_operandos *low_bytes2 = Pop_operandos(f->p);
	pilha_operandos *high_bytes2 = Pop_operandos(f->p);

	u8 long2 = ((u8)high_bytes2->topo->operando << 32) | low_bytes2->topo->operando;

	u8 result = long1 - long2;

	f->p = Push_operandos(f->p, (u4)(result>>32),NULL, LONG_OP);
	f->p = Push_operandos(f->p, (u4)result,NULL, LONG_OP);

}

void fsub_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	u4 op1 = valor1->topo->operando;
	u4 op2 = valor2->topo->operando;
	u4 big_op, small_op;

	if(expoente(op1)>expoente(op2)){
		big_op = op1;
		small_op = op2;
	}else if(expoente(op2)>expoente(op1)){
		big_op = op2;
		small_op = op1;
	}else if(mantissa(op2)>mantissa(op1)){
		big_op = op2;
		small_op = op1;
	}else{
		big_op = op1;
		small_op = op2;
	}
	i4 operacao = (sinal(op1)!=sinal(op2))? 1:-1;
	i4 result_exp = expoente(big_op);
	u4 result_mant = mantissa(big_op) + (operacao*(mantissa(small_op) << (expoente(big_op) - expoente(small_op))));
	u4 result_sin = sinal(big_op);

	//Normaliza float
	while((result_mant>>23) != 0){
		result_mant = result_mant>>1;
		result_exp++;
	}

	//Constroi float
	u4 result = (result_sin<<31) | (result_exp<<23) | result_mant;

	f->p = Push_operandos(f->p,result,NULL,FLOAT_OP);
}

void dsub_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1_low = Pop_operandos(f->p);
	pilha_operandos *valor1_high = Pop_operandos(f->p);
	pilha_operandos *valor2_low = Pop_operandos(f->p);
	pilha_operandos *valor2_high = Pop_operandos(f->p);

	u8 op1 = ((u8)valor1_high->topo->operando << 32) | valor1_low->topo->operando;
	u8 op2 = ((u8)valor2_high->topo->operando << 32) | valor2_low->topo->operando;
	u8 big_op, small_op;

	if(expoente_d(op1)>expoente_d(op2)){
		big_op = op1;
		small_op = op2;
	}else if(expoente_d(op2)>expoente_d(op1)){
		big_op = op2;
		small_op = op1;
	}else if(mantissa_d(op2)>mantissa_d(op1)){
		big_op = op2;
		small_op = op1;
	}else{
		big_op = op1;
		small_op = op2;
	}
	i4 operacao = (sinal_d(op1)!=sinal_d(op2))? 1:-1;
	i8 result_exp = expoente_d(big_op);
	u8 result_mant = mantissa_d(big_op) + (operacao*(mantissa_d(small_op) << (expoente_d(big_op) - expoente_d(small_op))));
	u8 result_sin = sinal_d(big_op);

	//Normaliza double
	while((result_mant>>52) != 0){
		result_mant = result_mant>>1;
		result_exp++;
	}

	//Constroi float
	u8 result = (result_sin<<63) | (result_exp<<52) | result_mant;

	f->p = Push_operandos(f->p, (u4)(result>>32),NULL, DOUBLE_OP);
	f->p = Push_operandos(f->p, (u4)result,NULL, DOUBLE_OP);
}


void imul_impl(frame *f, u1 par1, u1 par2){

	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	// Se os tipos dos valores forem iguais, e se esse tipo for inteiro
	i4 result = valor1->topo->operando*valor2->topo->operando;
	f->p = Push_operandos(f->p,result,NULL,INTEGER_OP);
}

void lmul_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes1 = Pop_operandos(f->p);
	pilha_operandos *high_bytes1 = Pop_operandos(f->p);

	u8 long1 = ((u8)high_bytes1->topo->operando << 32) | low_bytes1->topo->operando;


	pilha_operandos *low_bytes2 = Pop_operandos(f->p);
	pilha_operandos *high_bytes2 = Pop_operandos(f->p);

	u8 long2 = ((u8)high_bytes2->topo->operando << 32) | low_bytes2->topo->operando;

	u8 result = long1 * long2;

	f->p = Push_operandos(f->p, (u4)(result>>32),NULL, LONG_OP);
	f->p = Push_operandos(f->p, (u4)result,NULL, LONG_OP);

}

void fmul_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	u4 op1 = valor1->topo->operando;
	u4 op2 = valor2->topo->operando;

	i4 result_exp = expoente(op1) + expoente(op2);
	u4 result_mant = mantissa(op1) * mantissa(op2);
	u4 result_sin = sinal(op1) ^ sinal(op2);

	//Normaliza float
	while((result_mant>>23) != 0){
		result_mant = result_mant>>1;
		result_exp++;
	}

	//Constroi float
	u4 result = (result_sin<<31) | (result_exp<<23) | result_mant;

	f->p = Push_operandos(f->p,result,NULL,FLOAT_OP);
}

void dmul_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1_low = Pop_operandos(f->p);
	pilha_operandos *valor1_high = Pop_operandos(f->p);
	pilha_operandos *valor2_low = Pop_operandos(f->p);
	pilha_operandos *valor2_high = Pop_operandos(f->p);

	u8 op1 = ((u8)valor1_high->topo->operando << 32) | valor1_low->topo->operando;
	u8 op2 = ((u8)valor2_high->topo->operando << 32) | valor2_low->topo->operando;

	i8 result_exp = expoente_d(op1) + expoente_d(op2);
	u8 result_mant = mantissa_d(op1) * mantissa_d(op2);
	u8 result_sin = sinal_d(op1) ^ sinal_d(op2);

	//Normaliza double
	while((result_mant>>52) != 0){
		result_mant = result_mant>>1;
		result_exp++;
	}

	//Constroi float
	u8 result = (result_sin<<63) | (result_exp<<52) | result_mant;

	f->p = Push_operandos(f->p, (u4)(result>>32), NULL,DOUBLE_OP);
	f->p = Push_operandos(f->p, (u4)result, NULL,DOUBLE_OP);
}

void idiv_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	// Se os tipos dos valores forem iguais, e se esse tipo for inteiro
	i4 result = valor1->topo->operando/valor2->topo->operando;
	f->p = Push_operandos(f->p,result,NULL,INTEGER_OP);
}

void ldiv_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes1 = Pop_operandos(f->p);
	pilha_operandos *high_bytes1 = Pop_operandos(f->p);

	u8 long1 = ((u8)high_bytes1->topo->operando << 32) | low_bytes1->topo->operando;


	pilha_operandos *low_bytes2 = Pop_operandos(f->p);
	pilha_operandos *high_bytes2 = Pop_operandos(f->p);

	u8 long2 = ((u8)high_bytes2->topo->operando << 32) | low_bytes2->topo->operando;

	u8 result = long1 / long2;

	f->p = Push_operandos(f->p, (u4)(result>>32), NULL,LONG_OP);
	f->p = Push_operandos(f->p, (u4)result, NULL,LONG_OP);

}

void fdiv_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	u4 op1 = valor1->topo->operando;
	u4 op2 = valor2->topo->operando;

	i4 result_exp = expoente(op1) - expoente(op2);
	u4 result_mant = mantissa(op1) / mantissa(op2);
	u4 result_sin = sinal(op1) ^ sinal(op2);

	//Normaliza float
	while((result_mant>>23) != 0){
		result_mant = result_mant>>1;
		result_exp++;
	}

	//Constroi float
	u4 result = (result_sin<<31) | (result_exp<<23) | result_mant;

	f->p = Push_operandos(f->p,result,NULL,FLOAT_OP);
}

void ddiv_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1_low = Pop_operandos(f->p);
	pilha_operandos *valor1_high = Pop_operandos(f->p);
	pilha_operandos *valor2_low = Pop_operandos(f->p);
	pilha_operandos *valor2_high = Pop_operandos(f->p);

	u8 op1 = ((u8)valor1_high->topo->operando << 32) | valor1_low->topo->operando;
	u8 op2 = ((u8)valor2_high->topo->operando << 32) | valor2_low->topo->operando;

	i8 result_exp = expoente_d(op1) - expoente_d(op2);
	u8 result_mant = mantissa_d(op1) / mantissa_d(op2);
	u8 result_sin = sinal_d(op1) ^ sinal_d(op2);

	//Normaliza double
	while((result_mant>>52) != 0){
		result_mant = result_mant>>1;
		result_exp++;
	}

	//Constroi float
	u8 result = (result_sin<<63) | (result_exp<<52) | result_mant;

	f->p = Push_operandos(f->p, (u4)(result>>32), NULL,DOUBLE_OP);
	f->p = Push_operandos(f->p, (u4)result, NULL,DOUBLE_OP);
}


void irem_impl(frame *f, u1 par1, u1 par2){
	printf("IREM------------------------------------------\n");
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	if(valor1->topo->operando == 0){
		// Lançar Arithmetic Exception
	}

	i4 valor_push = valor2->topo->operando - (valor2->topo->operando/valor1->topo->operando) * valor1->topo->operando;

	valor3 = Push_operandos(valor3,valor_push,NULL,valor1->topo->tipo_operando);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;

	f->p = Push_operandos(f->p,valor3->topo->operando,NULL,valor3->topo->tipo_operando);
}

void lrem_impl(frame *f, u1 par1, u1 par2){

}

void frem_impl(frame *f, u1 par1, u1 par2){

}

void drem_impl(frame *f, u1 par1, u1 par2){

}

void ineg_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i4 result = -valor1->topo->operando;
	f->p = Push_operandos(f->p,result,NULL,INTEGER_OP);
}

void lneg_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *low_bytes1 = Pop_operandos(f->p);
	pilha_operandos *high_bytes1 = Pop_operandos(f->p);

	u8 long1 = ((u8)high_bytes1->topo->operando << 32) | low_bytes1->topo->operando;

	u8 result = -long1;

	f->p = Push_operandos(f->p, (u4)(result>>32), NULL,LONG_OP);
	f->p = Push_operandos(f->p, (u4)result, NULL,LONG_OP);

}

void fneg_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	u4 op1 = valor1->topo->operando;

	//Constroi float
	u4 result = op1 ^ 0X80000000; //Invert signal

	f->p = Push_operandos(f->p,result,NULL,FLOAT_OP);
}

void dneg_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1_low = Pop_operandos(f->p);
	pilha_operandos *valor1_high = Pop_operandos(f->p);

	u4 high_bytes = valor1_high->topo->operando;
	u4 low_bytes = valor1_low->topo->operando;

	u4 result = high_bytes ^ 0X80000000; //Invert signal on high_bytes

	f->p = Push_operandos(f->p, result,NULL, DOUBLE_OP);
	f->p = Push_operandos(f->p, low_bytes,NULL, DOUBLE_OP);
}


void ishl_impl(frame *f, u1 par1, u1 par2){
	printf("Entrou no shl---------------------------------------------\n");
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 s = (valor1->topo->operando << 27) >> 27;

	i4 resultado = valor2->topo->operando << s;

	f->p = Push_operandos(f->p,resultado,NULL,valor1->topo->tipo_operando);
}

void lshl_impl(frame *f, u1 par1, u1 par2){

}


void ishr_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 s = (i4) (valor1->topo->operando << 27) >> 27;

	i4 resultado = (i4) valor2->topo->operando >> s;

	f->p = Push_operandos(f->p,resultado,NULL,valor1->topo->tipo_operando);
}

void lshr_impl(frame *f, u1 par1, u1 par2){

}

// Verificar se a implementação é essa mesmo, para fazer a extensão do sinal
void iushr_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	u4 s = (u4) (valor2->topo->operando << 27) >> 27;

	u4 resultado = (u4) valor1->topo->operando >> s;

	f->p = Push_operandos(f->p,(i4) resultado,NULL,valor1->topo->tipo_operando);
}

void lushr_impl(frame *f, u1 par1, u1 par2){

}

void iand_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor2->topo->operando & valor1->topo->operando;

	f->p = Push_operandos(f->p,resultado,NULL,valor1->topo->tipo_operando);
}

void land_impl(frame *f, u1 par1, u1 par2){

}

void ior_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor1->topo->operando | valor2->topo->operando;

	f->p = Push_operandos(f->p,resultado,NULL,valor1->topo->tipo_operando);
}

void lor_impl(frame *f, u1 par1, u1 par2){

}

void ixor_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor1->topo->operando ^ valor2->topo->operando;

	f->p = Push_operandos(f->p,resultado,NULL,valor1->topo->tipo_operando);
}

void lxor_impl(frame *f, u1 par1, u1 par2){

}

void iinc_impl(frame *f,u1 index, i1 constante){
	// Estender o sinal para 32 bits
	i4 inteiro_constante = (i4) constante;

	*f->v[index].variavel += inteiro_constante;
}

void iinc_fantasma(frame *par0, u1 par1, u1 par2){
	i1 valor = (i1)par2;
	iinc_impl(par0,par1,valor);
}

void i2l_impl(frame *f, u1 par1, u1 par2){

}

void i2f_impl(frame *f, u1 par1, u1 par2){

}

void i2d_impl(frame *f, u1 par1, u1 par2){

}

void l2i_impl(frame *f, u1 par1, u1 par2){

}

void l2f_impl(frame *f, u1 par1, u1 par2){

}

void l2d_impl(frame *f, u1 par1, u1 par2){

}

void f2i_impl(frame *f, u1 par1, u1 par2){

}

void f2l_impl(frame *f, u1 par1, u1 par2){

}

void f2d_impl(frame *f, u1 par1, u1 par2){

}

void d2i_impl(frame *f, u1 par1, u1 par2){

}

void d2l_impl(frame *f, u1 par1, u1 par2){

}

void d2f_impl(frame *f, u1 par1, u1 par2){

}

void i2b_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i1 truncado = (i1) valor1->topo->operando;

	i4 resultado = (i4) truncado;

	f->p = Push_operandos(f->p,resultado,NULL,BYTE_OP);
}

void i2c_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i1 truncado = (i1) valor1->topo->operando;

	i4 resultado = (i4) truncado;

	f->p = Push_operandos(f->p,resultado,NULL,CHAR_OP);
}

void i2s_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i2 truncado = (i2) valor1->topo->operando;

	i4 resultado = (i4) truncado;

	f->p = Push_operandos(f->p,resultado,NULL,SHORT_OP);
}

void lcmp_impl(frame *f, u1 par1, u1 par2){

}

void fcmpl_impl(frame *f, u1 par1, u1 par2){

}

void fcmpg_impl(frame *f, u1 par1, u1 par2){

}

void dcmpl_impl(frame *f, u1 par1, u1 par2){

}

void dcmpg_impl(frame *f, u1 par1, u1 par2){

}

void ifeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2){


	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando == 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
		// Alterar o PC aqui para fazer o branch
	}
}

void ifne_impl(frame *f, u1 branchbyte1, u1 branchbyte2){

	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando != 0){
		int8_t v1 = (int8_t)branchbyte1;
		int8_t v2 = (int8_t)branchbyte2;
		int16_t branchoffset = (v1 << 8) | v2;
		jvm->pc += branchoffset;
	}
}

void iflt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){

	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando<0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifge_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando >= 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando > 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifle_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando <= 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando == valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando != valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmplt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando < valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmpge_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando >= valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmpgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor2->topo->operando > valor1->topo->operando){
		printf("Entrou....\n");
		int8_t v1 = (int8_t)branchbyte1;
		int8_t v2 = (int8_t)branchbyte2;
		int16_t branchoffset = (v1 << 8) | v2;
		printf("Branch Offset: %d\n",branchoffset);
		jvm->pc += branchoffset;
	}
}

void if_icmple_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
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

void inst_goto_impl(frame *f,u1 branchbyte1, u1 branchbyte2){
	int8_t bb1 = (int8_t)branchbyte1;
	int8_t bb2 = (int8_t)branchbyte2;
	int16_t branchoffset = (branchbyte1 << 8) | branchbyte2;

	printf("Branch Goto: %d\n",branchoffset);

	jvm->pc += branchoffset;
	// Efetuar o branch com branch offset
}

void jsr_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	u2 branchoffset = (branchbyte1 << 8) | branchbyte2;

	// Efetuar o branch com branch offset
}

void ret_impl(frame *f,u1 index, u1 par){
	// u1 endereco_retorno = f->v[index]->variavel;

	// Escrever no registrador PC
}

void tableswitch_fantasma(frame *par0, u1 par1, u1 par2){

}

void lookupswitch_fantasma(frame *par0, u1 par1, u1 par2){

}

void ireturn_impl(frame *f, u1 par1, u1 par2){
	// Analisar as condições do método que deve ser retornado
	pilha_operandos *valor = Pop_operandos(f->p);

	// Empilhar na pilha de operandos do frame do chamador
	jvm->frames->topo->prox->f->p = Push_operandos(jvm->frames->topo->prox->f->p,(i4)valor->topo->operando,NULL,valor->topo->tipo_operando);
	pilha_frames *desempilhado = Pop_frames(jvm->frames);
	ImprimirPilha_frames(jvm->frames);
}

void lreturn_impl(frame *f, u1 par1, u1 par2){

}

void freturn_impl(frame *f, u1 par1, u1 par2){

}

void dreturn_impl(frame *f, u1 par1, u1 par2){

}

void areturn_impl(frame *f, u1 par1, u1 par2){
	// Analisar mesmas coisas do ireturn
	pilha_operandos *valor = Pop_operandos(f->p);
}

void inst_return_impl(frame *f, u1 par1, u1 par2){

	printf("EXECUÇÃO RETURN\n\n");

	// Empilhar NULL na pilha de operandos do frame chamador, ou seja, o próximo frame na pilha
	//jvm->frames->topo->prox->f->p = Push_operandos(jvm->frames->topo->prox->f->p,-INT_MAX,NULL,-1);
	pilha_frames *desempilhado = Pop_frames(jvm->frames);
}

void getstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	cp_info *aux = f->cp-1+indice_cp;

	// Descobrir a classe do field
	char *classedoField = decodificaNIeNT(f->cp,aux->UnionCP.Fieldref.class_index,NAME_INDEX);
	if(strcmp(classedoField,"java/lang/System")==0){
		f->p = Push_operandos(f->p,-INT_MAX,"out",REFERENCE_OP);
	}
	else{
		// Não vai empilhar string, vai ser uma referência pro field, isso aqui é só placeholder
		f->p = Push_operandos(f->p,-INT_MAX,classedoField,REFERENCE_OP);
	}
}

void putstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field

	// Fieldref campo = f->cp[indice_cp];
}

void getfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	pilha_operandos *objeto = Pop_operandos(f->p);

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field

	// struct Fieldref campo = f->cp[indice_cp];
}

void putfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field

	// struct Fieldref campo = f->cp[indice_cp];
}

void invokevirtual_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	char *nomemetodo = obterNomeMetodo(f->cp,indice_cp);
	char *descriptormetodo = obterDescriptorMetodo(f->cp,indice_cp);

	/*method_info *metodos = f->classes->topo->arquivoClass->methods;
	method_info *aux = metodos;*/

	int achou = 0;

	/*for(aux=metodos;aux<metodos+f->classes->topo->arquivoClass->methods_count;aux++){
		char *nome_metodo_lista = decodificaStringUTF8(f->cp-1+aux->name_index);
		// O método está na classe corrente
		if(strcmp(nomemetodo,nome_metodo_lista)==0){
			// Achei o método
			// Verificar access flags
			// Aqui dentro, private é legal, por exemplo
			achou = 1;
			break;

		}
	}

	if(achou==1){
		// Se o método tiver access flag private, não tem problema
	}
	else{
		// O método não está na classe corrente
		//Se o método não for encontrado na classe corrente, buscar o método na super_class da classe corrente
		// Verificar se ele é private
		// Se ele for private, o acesso é ilegal, retorna exceção
		// Se ele for encontrado na super_class e for protected, tá tudo ok
	}*/

	if(strcmp(nomemetodo,"println")==0){
		printf("Entrou no println\n");
		// Imprimir com o printf do c
		// Esvaziar a pilha de operandos
		// ImprimirPilha_operandos(f->p);
		if (!pilhaVazia(f->p)) {
			if (!printVazio(f->p)) {
				pilha_operandos *string = Pop_operandos(f->p);
				pilha_operandos *fieldOut = Pop_operandos(f->p);

				if (string->topo->tipo_operando == 10) {
					printf("\nString imprimir: %s\n",(char*) string->topo->referencia);
				} else if(string->topo->tipo_operando == 3) {
					printf("\nChar imprimir: %c\n",(char)string->topo->operando);
				} else {
					printf("\nValor imprimir: %d\n",(i4) string->topo->operando);
				}
			} else {
				pilha_operandos *fieldOut = Pop_operandos(f->p);
				printf("\nSaltoDeLinha\n");
			}
		}
	}
	else{
		if(resolverMetodo(f->cp,indice_cp)){

		}
	}

}

void invokespecial_impl(frame *f, u1 par1, u1 par2){

}

/*
	Falta implementar o PC.

	Antes de colocar as variáveis no vetor de variáveis locais do frame do método que será invocado,
	elas devem ser convertidas para o tipo indicado no descriptor do método que será invocado

*/
void invokestatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;
	char *nomemetodo = obterNomeMetodo(f->cp,indice_cp);
	char *descriptormetodo = obterDescriptorMetodo(f->cp,indice_cp);
	printf("Vai rodar invoke static...\n");
	if(resolverMetodo(f->cp,indice_cp)){
		int *parametros_cont = malloc(sizeof(int));
		char *classeNova = obterClasseDoMetodo(f->cp,indice_cp);
		method_info * methodAux = BuscarMethodClasseCorrente_classes(jvm->classes, classeNova, nomemetodo);
		attribute_info *aux;
		int posicao;
		for(posicao = 0; posicao < methodAux->attributes_count; posicao++) {
			aux = (*(methodAux->attributes+posicao));
			classesCarregadas *classeAtual = BuscarElemento_classes(jvm->classes,classeNova);
			char *nameindex = decodificaStringUTF8(classeAtual->arquivoClass->constant_pool-1+aux->attribute_name_index);
			if(strcmp(nameindex,"Code")==0){
				code_attribute *c = (code_attribute *) aux->info;
				frame *f_novo = criarFrame(classeNova,c->max_locals);
				f_novo = transferePilhaVetor(f,f_novo,parametros_cont);
				jvm->frames = Push_frames(jvm->frames,f_novo);
				// printf("%lu\n",sizeof(vetor_locais));
				for(int i=0;i<*(parametros_cont);i++){
					printf("VARIÁVEL LOCAL: %04x\n",*(jvm->frames->topo->f->v[i].variavel));
				}


				printf("Classe nova: %s\n",classeNova);
				classesCarregadas *classe = BuscarElemento_classes(jvm->classes,classeNova);
				if (classe != NULL) {
					printf("Buscou a classe carregada...\n");
				}

				// Achar o método na classe que o contém
				method_info *metodos = classe->arquivoClass->methods;
				for(method_info *aux=metodos;aux<metodos+classe->arquivoClass->methods_count;aux++){
					// Verificar se o nome e o descriptor do método que deve ser invocado são iguais ao que está sendo analisado no .class
					char * nomeMetodoAux = decodificaStringUTF8(classe->arquivoClass->constant_pool-1+aux->name_index);
					char * descriptorMetodoAux = decodificaStringUTF8(classe->arquivoClass->constant_pool-1+aux->descriptor_index);

					if(strcmp(nomemetodo,nomeMetodoAux) == 0 && strcmp(descriptormetodo,descriptorMetodoAux) == 0){
						printf("Metodo da classe: %s\n",nomeMetodoAux);
						// Executar o code do método invocado
						printf("Executando método...\n");
						executarMetodo(aux,classeNova,2);

					}
				}

			}
		}
	}

}

void invokeinterface_impl(frame *f, u1 par1, u1 par2){

}

void invokedynamic_fantasma(frame *par0, u1 par1, u1 par2){

}

void inst_new_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;
	char *nomeClasse = decodificaNIeNT(f->cp,indice_cp,NAME_INDEX);
	printf("Nome da classe: %s\n",nomeClasse);

	ClassFile *classe = resolverClasse(nomeClasse);

	f->p = Push_operandos(f->p,-INT_MAX,classe,REFERENCE_OP);
}

void newarray_impl(frame *f, u1 atype, u1 par1){
	pilha_operandos *count = Pop_operandos(f->p);
	i4 countnum = count->topo->operando;

	void *endereco = NULL;
	i4 referencia = 0;

	if(count<0){
		// Lançar exceção
	}
	else{
		switch(atype){
			case T_BOOLEAN:
				endereco = (u1*) malloc((countnum+1)*sizeof(u1));
				referencia = (u1) *((u1*) endereco);
			break;

			case T_CHAR:
				endereco = (i2*) malloc((countnum+1)*sizeof(i2));
				referencia = (i2) *((i2*) endereco);
			break;

			case T_FLOAT:
				endereco = (u4*) malloc((countnum+1)*sizeof(u4));
				referencia = (u4) *((u4*) endereco);
			break;

			case T_DOUBLE:
				endereco = (u4*) malloc(2*(countnum+1)*sizeof(u4));
				referencia = (u4) *((u4*) endereco);
			break;

			case T_BYTE:
				endereco = (i1*) malloc((countnum+1)*sizeof(i1));
				referencia = (i1) *((i1*) endereco);
			break;

			case T_SHORT:
				endereco = (i2*) malloc((countnum+1)*sizeof(i2));
				referencia = (i2) *((i2*) endereco);
			break;

			case T_INT:
				endereco = (i4*) malloc((countnum+1)*sizeof(i4));
				referencia = (i4) *((i4*) endereco);
			break;

			case T_LONG:
				endereco = (i4*) malloc(2*(countnum+1)*sizeof(i4));
				referencia = (i4) *((i4*) endereco);
			break;
		}

		/*// Inicializar com os valores default
		for(void *p=endereco,i=0;i<=countnum;i++,p++){
			// Alocar com -INT_MAX para marcar o fim do array
			if(i==countnum){
				*p = -INT_MAX;
			}
			else{
				*p=0;
			}
		}*/

		f->p = Push_operandos(f->p,-INT_MAX,referencia,REFERENCE_OP);
	}
}

void anewarray_impl(frame *f, u1 par1, u1 par2){

}

void arraylength_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *array_ref = Pop_operandos(f->p);
	i4 referencia = array_ref->topo->operando;
	int tamanho = 0;

	/* Observação */
	// Não tem como descobrir o tipo do elemento, a princípio.
	// Como fazer esse incremento? Foi alocado como void, mas com sizeofs diferentes (observar instrução newarray)
	// O void vai garantir que o incremento é o mesmo?
	/*for (void *p = referencia;*p!=-INT_MAX;p++,tamanho++){

	}*/

	f->p = Push_operandos(f->p,tamanho,NULL,INTEGER_OP);

}

void athrow_impl(frame *f, u1 par1, u1 par2){

}

void checkcast_impl(frame *f, u1 par1, u1 par2){

}

void instanceof_impl(frame *f, u1 par1, u1 par2){

}

void monitorenter_impl(frame *f, u1 par1, u1 par2){

}

void monitorexit_impl(frame *f, u1 par1, u1 par2){

}

void wide_impl(frame *f, u1 par1, u1 par2){

}

void multianewarray_impl(frame *f, u1 par1, u1 par2){

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

void goto_w_impl(frame *f, u1 par1, u1 par2){

}

void jsr_w_impl(frame *f, u1 par1, u1 par2){

}
