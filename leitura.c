/*
Universidade de Brasília - 01/2017
Software Básico - Turma A
Projeto Leitor/Exibidor de arquivo .class

Alunos: Maximillian Fan Xavier - 12/0153271
				Rafael Dias da Costa - 12/0133253
				Murilo Cerqueira Medeiros - 12/0130637
				Eduardo Sousa da Silva - 13/0108405
				Eduardo Schuabb Duarte - 11/0010876

*/

/*Inclusão de estruturas e assinatura de funções de leitura*/
#include "leitura.h"
#include <string.h>

/*Função 'u1Read' que realiza a leitura de 1 byte do arquivo .class*/
u1 u1Read(FILE *fp){
	/*Variável 'destino' para conter o retorno da função*/
	u1 destino;
	/*Chamada da função 'fread' para ler um byte do arquivo .class*/
	if (fread(&destino,sizeof(u1),1,fp) != 1) {
		/*Caso ocorra um erro na leitura, retorna um valor de debug*/
		return MAXU1;
	} else {
		/*Caso contrário retorna o byte lido*/
		return destino;
	}
}

/*Função 'u2Read' que realiza a leitura de 2 bytes do arquivo .class*/
u2 u2Read(FILE *fp){
	/*Variável 'destino' para conter o retorno da função*/
	u2 destino;
	/*Variáveis 'lowByte' e 'highByte' para conter
	os bytes de maior nível e menor nível, respectivamente*/
	u1 lowByte, highByte;
	/*Leitura dos bytes*/
	highByte = u1Read(fp);
	lowByte = u1Read(fp);

	/*Estrutura condicional que verifica se a leitura dos bytes
	foi corretamente executada*/
	if(highByte != MAXU1 && lowByte != MAXU1) {
		/*Caso positivo, realiza o deslocamento do byte de maior nível
		para a esquerda e execução de operação OR bit a bit com o byte
		de menor nível, dado que a informação está em big endian order*/
		destino = ((highByte)<<8) | ((lowByte));
		return destino;
	} else {
		/*Caso contrário, retorna um valor de debug*/
		return MAXU2;
	}
}

/*Função 'u4Read' que realiza a leitura de 4 bytes do arquivo .class*/
u4 u4Read(FILE *fp){
	/*Variável 'destino' para conter o retorno da função*/
	u4 destino;
	/*Variáveis 'byteTres', 'byteDois', 'byteUm' e 'byteZero' para
	conter os bytes de maior nível para menor nível, respectivamente*/
	u1 byteZero, byteUm, byteDois, byteTres;
	/*Leitura dos bytes*/
	byteTres = u1Read(fp);
	byteDois = u1Read(fp);
	byteUm = u1Read(fp);
	byteZero = u1Read(fp);
	/*Estrutura condicional que verifica se a leitura dos bytes
	foi executada corretamente*/
	if(byteTres != MAXU1 && byteDois != MAXU1 && byteUm != MAXU1 && byteZero != MAXU1){
		/*Caso positivo, realiza o deslocamento do 'byteTres' para esquerda em 24 bits,
		deslocamento de 'byteDois' para a esquerda em 16 bits, deslocamento de 'byteUm'
		em 8 bits e realiza operação OR bit a bit com todos os bytes lidos, formando
		a informação representada pelos 4 bytes, dado que a informação está em big endian order*/
		destino = ((byteTres)<<24) | ((byteDois)<<16) | ((byteUm)<<8) | ((byteZero));
		return destino;
	} else {
		/*Caso contrário, retorna um valor de debug*/
		return MAXU4;
	}
}

/*Função 'lerArquivo' para realizar a leitura do arquivo .class*/
ClassFile* lerArquivo (char * nomeArquivo) {
	/*Declaração do ponteiro que irá conter a estrutura do arquivo .class*/
	ClassFile *arquivoClass = NULL;
	/*Chamada da função 'fopen' para abrir o arquivo .class*/
	FILE * fp = fopen(nomeArquivo,"rb");
	/*Estrutura condicional que avalia se o ponteiro do arquivo é nulo*/
	if (fp == NULL) {
		/*Caso positivo, encerra o programa*/
		printf("Ocorreu um problema ao abrir o arquivo, finalizando programa!\n");
		return NULL;
	} else {
		/*Caso contrário, prossegue com a leitura do arquivo .class*/
		/*Alocação da estrutura ClassFile em memória*/
		arquivoClass = (ClassFile*) malloc(sizeof(ClassFile));

		/*Leitura do valor 'magic', representando a Assinatura
		do arquivo .class*/
		arquivoClass->magic = u4Read(fp);
		/*Leitura do valor 'minor_version', representando a versão
		do arquivo .class*/
		arquivoClass->minor_version = u2Read(fp);
		/*Leitura do valor 'major_version', representando a versão
		do arquivo .class*/
		arquivoClass->major_version = u2Read(fp);
		/*Leitura do valor 'constant_pool_count', representando
		a quantidade de entradas na tabela Constant Pool*/
		arquivoClass->constant_pool_count = u2Read(fp);

		/*Leitura da tabela Constant Pool*/
		arquivoClass->constant_pool = NULL;
		arquivoClass->constant_pool = lerConstantPool(fp, arquivoClass->constant_pool_count);

		/*Leitura do valor 'access_flags', representando a especificação
		de permissão de acesso da classe*/
		arquivoClass->access_flags = u2Read(fp);
		/*Leitura do valor 'this_class' representandoc a classe definida*/
		arquivoClass->this_class = u2Read(fp);
		/*Leitura do valor 'super_class' representando a super classe
		direta da classe definida*/
		arquivoClass->super_class = u2Read(fp);
		/*Leitura do valor 'interfaces_count', representando
		a quantidade de entradas na tabela Interfaces*/
		arquivoClass->interfaces_count = u2Read(fp);

		/*Estrutura condicional que verifica se a quantidade de entradas
		na tabela Interfaces é maior que zero. Se for, prossegue com a leitura
		das entradas, caso contrário prossegue com a leitura dos próximos campos*/
		if (arquivoClass->interfaces_count > 0) {
			// Preencher com leitura de interfaces - CODIFICAR
			arquivoClass->interfaces = malloc(arquivoClass->interfaces_count*sizeof(u2));
		}

		/*Leitura do valor 'fields_count', representando
		a quantidade de entradas na tabela Fields*/
		arquivoClass->fields_count = u2Read(fp);

		/*Estrutura condicional que verifica se a quantidade de entradas
		na tabela Fields é maior que zero. Se for, prossegue com a leitura
		das entradas, caso contrário prossegue com a leitura dos próximos campos*/
		if (arquivoClass->fields_count > 0) {
			// Preencher com leitura de fields - CODIFICAR
			arquivoClass->fields = malloc(arquivoClass->fields_count*sizeof(u2));
		}

		/*Leitura do valor 'methods_count', representando
		a quantidade de entradas na tabela Method*/
		arquivoClass->methods_count = u2Read(fp);

		/*Estrutura condicional que verifica se a quantidade de entradas
		na tabela Method é maior que zero. Se for, prossegue com a leitura
		das entradas, caso contrário prossegue com a leitura dos próximos campos*/
		if (arquivoClass->methods_count > 0) {
			/*Chamada da função 'lerMethod' para realizar a leitura da tabela Method*/
			arquivoClass->methods = lerMethod(fp, arquivoClass->methods_count,arquivoClass->constant_pool);
		}

		/*Leitura do valor 'attributes_count', representando
		a quantidade de entradas na tabela Attributes*/
		arquivoClass->attributes_count = u2Read(fp);

		/*Estrutura condicional que verifica se a quantidade de entradas
		na tabela Attributes é maior que zero. Se for, prossegue com a leitura
		das entradas, caso contrário prossegue com a leitura dos próximos campos*/
		if(arquivoClass->attributes_count > 0){
			/*Chamada da função 'lerAttributes' para realizar a leitura da tabela Attributes*/
			arquivoClass->attributes = lerAttributes(fp, arquivoClass->attributes_count);
		}
		/*Fechamento do arquivo .class*/
		fclose(fp);

		/*Retorno do ponteiro da estrutura contendo o conteúdo do arquivo .class*/
		return arquivoClass;
	}
}

/*Função 'lerConstantPool' que realiza a leitua da tabela Constant Pool*/
cp_info * lerConstantPool (FILE * fp, u2 constant_pool_count) {
	/*Alocação da estrutura Constant Pool que será retornada para a estrutura
	principal do arquivo .class*/
	cp_info * constantPool = (cp_info *) malloc((constant_pool_count-1)*sizeof(cp_info));
	/*Ponteiro auxiliar do tipo cp_info para fazer a varredura de leitura*/
	cp_info * aux = NULL;

	/*Estrutura de repetição contada que realiza a leitura das informações
	contidas na Constant Pool presente no arquvo .class*/
	for (aux = constantPool; aux < constantPool+constant_pool_count-1; aux++){
		/*Leitura do byte tag de uma entrada da Constant Pool*/
		aux->tag = u1Read(fp);
		/*Estrutura 'switch case' que analisa o byte tag lido e de acordo com o valor
		realiza um procedimento específico de leitura*/
		switch(aux->tag) {
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_Class,
			realiza a leitura do atributo name_index da estrutura Class*/
			case CONSTANT_Class:
				aux->UnionCP.Class.name_index = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_Fieldref,
			realiza a leitura dos atributos class_index e name_and_type_index
			da estrutura Fieldref*/
			case CONSTANT_Fieldref:
				aux->UnionCP.Fieldref.class_index = u2Read(fp);
				aux->UnionCP.Fieldref.name_and_type_index = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_Methodref,
			realiza a leitura dos atributos class_index e name_and_type_index
			da estrutura Methodref*/
			case CONSTANT_Methodref:
				aux->UnionCP.Methodref.class_index = u2Read(fp);
				aux->UnionCP.Methodref.name_and_type_index = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_InterfaceMethodref,
			realiza a leitura dos atributos class_index e name_and_type_index da estrutura
			InterfaceMethodref*/
			case CONSTANT_InterfaceMethodref:
				aux->UnionCP.InterfaceMethodref.class_index = u2Read(fp);
				aux->UnionCP.InterfaceMethodref.name_and_type_index = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_String,
			realiza a leitura do atributo string_index da estrutura String*/
			case CONSTANT_String:
				aux->UnionCP.String.string_index = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_Integer,
			realiza a leitura do atributo bytes da estrutura Integer*/
			case CONSTANT_Integer:
				aux->UnionCP.Integer.bytes = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_Float,
			realiza a leitura do atributo bytes da estrutura Float*/
			case CONSTANT_Float:
				aux->UnionCP.Float.bytes = u4Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_Long,
			realiza a leitura dos atributos high_bytes e low_bytes da estrutura
			Long*/
			case CONSTANT_Long:
				aux->UnionCP.Long.high_bytes = u4Read(fp);
				aux->UnionCP.Long.low_bytes = u4Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_Double,
			realiza a leitura dos atributos high_bytes e low_bytes da estrutura
			Double*/
			case CONSTANT_Double:
				aux->UnionCP.Double.high_bytes = u4Read(fp);
				aux->UnionCP.Double.low_bytes = u4Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_NameAndType,
			realiza a leitura dos atributos name_index e descriptor_index da estrutura
			NameAndType*/
			case CONSTANT_NameAndType:
				aux->UnionCP.NameAndType.name_index = u2Read(fp);
				aux->UnionCP.NameAndType.descriptor_index = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_Long,
			realiza a leitura dos atributos length e bytes da estrutura UTF8*/
			case CONSTANT_Utf8:
				aux->UnionCP.UTF8.length = u2Read(fp);
				aux->UnionCP.UTF8.bytes = malloc(aux->UnionCP.UTF8.length*sizeof(u1));
				for (u1 *i=aux->UnionCP.UTF8.bytes;i<aux->UnionCP.UTF8.bytes+aux->UnionCP.UTF8.length;i++){
					*i = u1Read(fp);
				}
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_MethodHandle,
			realiza a leitura dos atributos reference_kind e reference_index da estrutura
			MethodHandle*/
			case CONSTANT_MethodHandle:
				aux->UnionCP.MethodHandle.reference_kind = u1Read(fp);
				aux->UnionCP.MethodHandle.reference_index = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_MethodType,
			realiza a leitura do atributo descriptor_index da estrutura MethodType*/
			case CONSTANT_MethodType:
				aux->UnionCP.MethodType.descriptor_index = u2Read(fp);
				break;
			/*Caso o byte tag lido represente o valor de tag de CONSTANT_InvokeDynamic,
			realiza a leitura dos atributos bootstrap_method_attr_index e
			name_and_type_index da estrutura InvokeDynamicInfo*/
			case CONSTANT_InvokeDynamic:
				aux->UnionCP.InvokeDynamicInfo.bootstrap_method_attr_index = u2Read(fp);
				aux->UnionCP.InvokeDynamicInfo.name_and_type_index = u2Read(fp);
				break;
			/*Caso um byte tag lido não tenha sido tratado na estrutura switch case,
			realiza a impressão de uma mensagem de debug*/
			default:
				printf("Default\n");
				break;
		}
	}

	/*Retorno da estrutura Constant Pool alocada, com as informações lidas*/
	return constantPool;
}

/*Função 'lerMethod' para realizar a leitura da tabela Method*/
method_info * lerMethod (FILE * fp, u2 methods_count, cp_info *cp) {
	/*Alocação da estrutura Method que será retornada para a estrutura
	principal do arquivo .class*/
	method_info * methods = (method_info*) malloc(methods_count*sizeof(method_info));

	/*Estrutura de repetição contada que realiza a leitura das informações
	contidas na tabela Method presente no arquvo .class*/
	for (method_info * i = methods; i < methods + methods_count; i++) {
		/*Leitura do atributo access_flags do respectivo método*/
		i->access_flags = u2Read(fp);
		/*Leitura do atributo name_index do respectivo método*/
		i->name_index = u2Read(fp);
		/*Leitura do atributo descriptor_index do respectivo método*/
		i->descriptor_index = u2Read(fp);
		/*Leitura do atributo attributes_count do respectivo método*/
		i->attributes_count = u2Read(fp);

		/*Estrutura condicional que avalia se a quantidade de atributos
		do método é maior que zero. Se for, prossegue com a leitura dos
		atributos do método*/
		u2 auxcount = i->attributes_count;
		// attribute_info *attributes = (attribute_info*) malloc(i->attributes_count*sizeof(attribute_info));
		u2 name_index;
		char * string_name_index = malloc(100*sizeof(char));
		while (auxcount > 0) {
			/*Estrutura de repetição contada que realiza a leitura das informações
			contidas na tabela Attribute presente no arquvo .class*/
				/*Leitura do atributo name_index do respectivo atributo*/
				name_index = u2Read(fp);
				string_name_index = decodificaStringUTF8(cp+name_index-1);


				//FAZER FOR PARA LER MAIS DE UM CODE PARA UM MESMO METODO? OU SO EXISTE UM CODE POR METODO?


				if(strcmp(string_name_index,"Code") == 0){
					code_attribute *code_attributes = NULL;//(code_attribute*) malloc(i->attributes_count*sizeof(code_attribute));
					code_attributes = lerCode(fp, name_index, auxcount, cp);
					i->UnionAttr.code_attributes = NULL;//malloc(i->attributes_count*sizeof(code_attribute));
					i->UnionAttr.code_attributes = code_attributes;
				}
				/*else if(strcmp(string_name_index,"Attribute Info")==0){

				}*/
				/*Leitura do atributo length do respectivo atributo
				a->attribute_length = u4Read(fp);
				Estrutura condicional que avalia se o tamanho do atributo
				é maior que zero. Se for, prossegue com a leitura da informação
				do atributo
				if (a->attribute_length > 0) {
					Alocação do espaço para informação do atributo
					switch(decodificaStringUTF8(cp))
					a->UnionAttr.attributes = malloc((a->attribute_length)*sizeof(u1));
					Estrutura de repetição contada para fazer a leitura dos dados
					e gravá-los na estrutura de informação
					for(u1 * c = (a->info); c < (a->info)+(a->attribute_length); c++) {
						Leitura dos dados
						*c = u1Read(fp);
					}
				}*/

				auxcount--;
		}


			// i->attributes = lerAttributesInfo(fp, i->attributes_count, cp);
	}

	/*Retorno da estrutura Method alocada, com as informações lidas*/
	return methods;
}

code_attribute * lerCode (FILE * fp, u2 name_index, u2 size, cp_info *cp) {
	code_attribute * code_attributes = NULL;
	code_attributes = (code_attribute*) malloc(size*sizeof(code_attribute));
	code_attributes->attribute_name_index = name_index;
	code_attributes->attribute_length = u4Read(fp);
	code_attributes->max_stack = u2Read(fp);
	code_attributes->max_locals = u2Read(fp);
	code_attributes->code_length = u4Read(fp);
	if(code_attributes->code_length > 0) {
		code_attributes->code = malloc(code_attributes->code_length*sizeof(u1));
		for(u1 *p = code_attributes->code; p < code_attributes->code + code_attributes->code_length; p++){
			*p = u1Read(fp);
		}
	}

	code_attributes->exception_table_length = u2Read(fp);

	if(code_attributes->exception_table_length>0){
		code_attributes->table = NULL;//malloc(code_attributes->exception_table_length*sizeof(exception_table));
		code_attributes->table = lerExceptionTable(fp, code_attributes->exception_table_length);
	}

	code_attributes->attributes_count = u2Read(fp);
	u2 auxCodeAttrCount = code_attributes->attributes_count;
	char * string_name_index = malloc(100*sizeof(char));

	while (auxCodeAttrCount > 0){
		u2 attr_name_index = u2Read(fp);
		string_name_index = decodificaStringUTF8(cp+attr_name_index-1);

		//VERIFICAR SE ELE SO ALOCA NO MAXIMO 1 TIPO, LINENUMBER-CODE-ETC,por chamada
			if(strcmp(string_name_index,"LineNumberTable") == 0){
				line_number_table * LineNumberTable = NULL;//(code_attribute*) malloc(i->attributes_count*sizeof(code_attribute));
				LineNumberTable = lerLineNumberTable(fp, attr_name_index, auxCodeAttrCount);
				code_attributes->UnionCodeAttr.lineNumberTable = NULL;//malloc(i->attributes_count*sizeof(code_attribute));
				code_attributes->UnionCodeAttr.lineNumberTable = LineNumberTable;
			}
				/*else if(strcmp(string_name_index,"Attribute Info")==0){

				}*/
				/*Leitura do atributo length do respectivo atributo
				a->attribute_length = u4Read(fp);
				Estrutura condicional que avalia se o tamanho do atributo
				é maior que zero. Se for, prossegue com a leitura da informação
				do atributo
				if (a->attribute_length > 0) {
					Alocação do espaço para informação do atributo
					switch(decodificaStringUTF8(cp))
					a->UnionAttr.attributes = malloc((a->attribute_length)*sizeof(u1));
					Estrutura de repetição contada para fazer a leitura dos dados
					e gravá-los na estrutura de informação
					for(u1 * c = (a->info); c < (a->info)+(a->attribute_length); c++) {
						Leitura dos dados
						*c = u1Read(fp);
					}
				}*/

		auxCodeAttrCount--;
	}

	//code_attributes->attributes = lerAttributes(fp, code_attributes->attributes_count);//malloc(code_attributes->attributes_count*sizeof(attribute_info));

	return code_attributes;
}

line_number_table * lerLineNumberTable(FILE * fp, u2 attr_name_index, u2 size) {
	line_number_table * lnt = (line_number_table*)malloc(size*sizeof(line_number_table));
	for(line_number_table *l = lnt; l < lnt + size; l++){
		l->attribute_name_index = attr_name_index;
		l->attribute_length = u4Read(fp);
		l->line_number_table_length = u2Read(fp);
		if (l->line_number_table_length > 0) {
			l->info = (line_number_tableInfo*)malloc(l->line_number_table_length*sizeof(line_number_tableInfo));
			for (line_number_tableInfo * linfo = l->info; linfo < l->info+l->line_number_table_length; linfo++) {
				linfo->start_pc = u2Read(fp);
				linfo->line_number = u2Read(fp);
			}
		}
	}
	return lnt;
}

exception_table * lerExceptionTable (FILE * fp, u2 size) {
	exception_table * exception_tableAux = (exception_table*)malloc(size*sizeof(exception_table));
	for(exception_table *e = exception_tableAux; e < exception_tableAux + size; e++){
		e->start_pc = u2Read(fp);
		e->end_pc = u2Read(fp);
		e->handler_pc = u2Read(fp);
		e->catch_type = u2Read(fp);
	}
	return exception_tableAux;
}



/*Função 'lerAttributes' para realizar a leitura da tabela Attribute*/
attribute_info * lerAttributes (FILE * fp, u2 attributes_count) {

	/*Alocação da estrutura Attribute que será retornada para a estrutura
	principal do arquivo .class*/
	attribute_info * attributes = (attribute_info*) malloc(attributes_count*sizeof(attribute_info));

	/*Estrutura de repetição contada que realiza a leitura das informações
	contidas na tabela Attribute presente no arquvo .class*/
	for (attribute_info * a = attributes; a < attributes+attributes_count; a++) {
		/*Leitura do atributo name_index do respectivo atributo*/
		a->attribute_name_index = u2Read(fp);
		/*Leitura do atributo length do respectivo atributo*/
		a->attribute_length = u4Read(fp);
		/*Estrutura condicional que avalia se o tamanho do atributo
		é maior que zero. Se for, prossegue com a leitura da informação
		do atributo*/
		if (a->attribute_length > 0) {
			/*Alocação do espaço para informação do atributo*/
			a->info = malloc((a->attribute_length)*sizeof(u1));
			/*Estrutura de repetição contada para fazer a leitura dos dados
			e gravá-los na estrutura de informação*/
			for(u1 * c = (a->info); c < (a->info)+(a->attribute_length); c++) {
				/*Leitura dos dados*/
				*c = u1Read(fp);
			}
		}
	}

	/*Retorno da estrutura Attribute alocada, com as informações lidas*/
	return attributes;
}

char* buscaNomeTag(u1 tag){
	char *nometag = malloc(30*sizeof(char));
	switch(tag){
		case CONSTANT_Class:
				strcpy(nometag,"CONSTANT_Class_Info");
				break;
		case CONSTANT_Fieldref:
			strcpy(nometag,"CONSTANT_Fieldref_Info");
			break;
		case CONSTANT_Methodref:
			strcpy(nometag,"CONSTANT_Methodref_Info");
			break;
		case CONSTANT_InterfaceMethodref:
			strcpy(nometag,"CONSTANT_InterfaceMethodref_Info");
			break;
		case CONSTANT_String:
			strcpy(nometag,"CONSTANT_String_Info");
			break;
		case CONSTANT_Integer:
			strcpy(nometag,"CONSTANT_Integer_Info");
			break;
		case CONSTANT_Float:
			strcpy(nometag,"CONSTANT_Float_Info");
			break;
		case CONSTANT_Long:
			strcpy(nometag,"CONSTANT_Long_Info");
			break;
		case CONSTANT_Double:
			strcpy(nometag,"CONSTANT_Double_Info");
			break;
		case CONSTANT_NameAndType:
			strcpy(nometag,"CONSTANT_NameAndType_Info");
			break;
		case CONSTANT_Utf8:
			strcpy(nometag,"CONSTANT_Utf8_Info");
			break;
		case CONSTANT_MethodHandle:
			strcpy(nometag,"CONSTANT_MethodHandle_Info");
			break;
		case CONSTANT_MethodType:
			strcpy(nometag,"CONSTANT_MethodType_Info");
			break;
		case CONSTANT_InvokeDynamic:
			strcpy(nometag,"CONSTANT_InvokeDynamic_Info");
			break;
		default:
			return NULL;
			break;
	}

	return(nometag);
}

char* decodificaStringUTF8(cp_info *cp){
	char* retorno = malloc((cp->UnionCP.UTF8.length+1)*sizeof(char));
	char *auxretorno = retorno;

	for (u1 *aux=cp->UnionCP.UTF8.bytes;aux<cp->UnionCP.UTF8.bytes+cp->UnionCP.UTF8.length;aux++){
		*auxretorno = (char) *aux;
		auxretorno++;
	}

	*auxretorno = '\0';

	return(retorno);
}

// LEMBRAR QUE CP INFO COMEÇA DE 1, POR ISSO QUE SUBTRAI 1 NA SOMA
// Decodifica Name Index e Name Type
char* decodificaNIeNT(cp_info *cp, u2 index, u1 tipo){

	char *retorno = malloc(100*sizeof(u1));

	cp_info *aux;
	cp_info *aux2;
	cp_info *aux3;

	aux = cp+index-1;

	switch(tipo){
		case NAME_INDEX:

			/*for (aux=cp;aux<cp+index;aux++){
				printf("Tag no for: %02x\n",aux->tag);
			}*/

			//aux--;
			/*
			printf("Index: %02x\n",index);

			printf("Impressao: %02x\n",aux->UnionCP.Class.name_index);
			printf("Tag depois da impressao: %02x\n",aux->tag);*/

			aux2 = cp+(aux->UnionCP.Class.name_index-1);

			retorno = decodificaStringUTF8(aux2);
		break;

		case NAME_AND_TYPE:

			aux2 = cp+(aux->UnionCP.NameAndType.name_index-1);
			aux3 = cp+(aux->UnionCP.NameAndType.descriptor_index-1);

			strcpy(retorno,decodificaStringUTF8(aux2));
			strcat(retorno,":");
			strcat(retorno,decodificaStringUTF8(aux3));
		break;

		case STRING_INDEX:
		case CLASS_INDEX:
			retorno = decodificaStringUTF8(aux);
		break;

		case NAME_AND_TYPE_INFO_NAME_INDEX:
			retorno = decodificaStringUTF8(aux);
		break;

		case NAME_AND_TYPE_INFO_DESCRIPTOR_INDEX:
			retorno = decodificaStringUTF8(aux);
		break;
	}

	return(retorno);
}

char* decodificaAccessFlags(u2 flag){

	char *retorno = malloc(100*sizeof(char));
	strcpy(retorno,"");

	while(flag){
		if(flag>=TRANSIENT){
			flag-=TRANSIENT;
			strcat(retorno,"TRANSIENT;");
		}
		if(flag>=VOLATILE){
			flag-=VOLATILE;
			strcat(retorno,"VOLATILE;");
		}

		if(flag>=FINAL){
			flag-=FINAL;
			strcat(retorno,"FINAL;");
		}

		if(flag>=STATIC){
			flag-=STATIC;
			strcat(retorno,"STATIC;");
		}

		if(flag>=PROTECTED){
			flag-=PROTECTED;
			strcat(retorno,"PROTECTED;");
		}

		if(flag>=PRIVATE){
			flag-=PRIVATE;
			strcat(retorno,"PRIVATE;");
		}

		if(flag>=PUBLIC){
			flag-=PUBLIC;
			strcat(retorno,"PUBLIC;");
		}
	}

	return(retorno);

}

void imprimirClassFile (ClassFile * arquivoClass) {

	cp_info * aux;
	method_info * auxMethod;
	code_attribute *auxAttribute;
	attribute_info *auxAttributeClasse;
	exception_table *eAux;
	uint32_t contador = 1;
	u1 *auxcode;
	char *ponteiroprint;

	printf("\n-----GENERAL INFORMATION-----\n\n");
	printf("Magic: %08x\n",arquivoClass->magic);
	printf("Minor Version: %04x\n",arquivoClass->minor_version);
	printf("Major Version: %04x\n",arquivoClass->major_version);
	printf("Constant Pool Count: %04x\n",arquivoClass->constant_pool_count);
	printf("Access Flags: %04x\n",arquivoClass->access_flags);
	printf("This Class: %04x\n",arquivoClass->this_class);
	printf("Super Class: %04x\n",arquivoClass->super_class);
	printf("Interfaces Count: %04x\n",arquivoClass->interfaces_count);
	printf("Fields Count: %04x\n",arquivoClass->fields_count);
	printf("Methods Count: %04x\n",arquivoClass->methods_count);
	printf("Atributes Count: %02x\n",arquivoClass->attributes_count);

	printf("\n\n-----CONSTANT POOL-----\n\n");

	for (aux = arquivoClass->constant_pool; aux < arquivoClass->constant_pool+arquivoClass->constant_pool_count-1; aux++) {
		printf("--------------Entrada [%d]--------------\n",contador);
		contador++;
		printf("TAG: %02x: %s\n",aux->tag,buscaNomeTag(aux->tag));
		switch(aux->tag) {
			case CONSTANT_Class:
				ponteiroprint = decodificaNIeNT(arquivoClass->constant_pool,aux->UnionCP.Class.name_index,CLASS_INDEX);
				printf("Class Name: cp_info#%02x <%s>\n",aux->UnionCP.Class.name_index,ponteiroprint);
				break;
			case CONSTANT_Fieldref:
				ponteiroprint = decodificaNIeNT(arquivoClass->constant_pool,aux->UnionCP.Fieldref.class_index,NAME_INDEX);
				printf("Class Name: cp_info#%02x %s\n",aux->UnionCP.Fieldref.class_index,ponteiroprint);
				ponteiroprint = decodificaNIeNT(arquivoClass->constant_pool,aux->UnionCP.Fieldref.name_and_type_index,NAME_AND_TYPE);
				printf("Name and Type: cp_info#%02x %s\n",aux->UnionCP.Fieldref.name_and_type_index,ponteiroprint);
				break;
			case CONSTANT_Methodref:
				ponteiroprint = decodificaNIeNT(arquivoClass->constant_pool,aux->UnionCP.Methodref.class_index,NAME_INDEX);
				printf("Class Name: cp_info#%02x %s\n",aux->UnionCP.Methodref.class_index,ponteiroprint);
				ponteiroprint = decodificaNIeNT(arquivoClass->constant_pool,aux->UnionCP.Methodref.name_and_type_index,NAME_AND_TYPE);
				printf("Name and Type: cp_info#%02x %s\n",aux->UnionCP.Methodref.name_and_type_index,ponteiroprint);
				break;
			case CONSTANT_InterfaceMethodref:
				printf("InterfaceMethodref Class Index: %04x\n",aux->UnionCP.InterfaceMethodref.class_index);
				printf("InterfaceMethodref Name and Type Index: %04x\n",aux->UnionCP.InterfaceMethodref.name_and_type_index);
				break;
			case CONSTANT_String:
				ponteiroprint = decodificaNIeNT(arquivoClass->constant_pool,aux->UnionCP.String.string_index,STRING_INDEX);
				printf("String: cp_info#%02x <%s>\n",aux->UnionCP.String.string_index,ponteiroprint);
				break;
			case CONSTANT_Integer:
				printf("Integer Bytes: %04x\n",aux->UnionCP.Integer.bytes);
				break;
			case CONSTANT_Float:
				printf("Float Bytes: %04x\n",aux->UnionCP.Float.bytes);
				break;
			case CONSTANT_Long:
				printf("Long High Bytes: %04x\n",aux->UnionCP.Long.high_bytes);
				printf("Long Low Bytes: %04x\n",aux->UnionCP.Long.low_bytes);
				break;
			case CONSTANT_Double:
				printf("Double High Bytes: %04x\n",aux->UnionCP.Double.high_bytes);
				printf("Double Low Bytes: %04x\n",aux->UnionCP.Double.low_bytes);
				break;
			case CONSTANT_NameAndType:
				ponteiroprint = decodificaNIeNT(arquivoClass->constant_pool,aux->UnionCP.NameAndType.name_index,NAME_AND_TYPE_INFO_NAME_INDEX);
				printf("Name: cp_info#%02x <%s>\n",aux->UnionCP.NameAndType.name_index,ponteiroprint);
				ponteiroprint = decodificaNIeNT(arquivoClass->constant_pool,aux->UnionCP.NameAndType.descriptor_index,NAME_AND_TYPE_INFO_DESCRIPTOR_INDEX);
				printf("Descriptor: cp_info#%02x <%s>\n",aux->UnionCP.NameAndType.descriptor_index,ponteiroprint);
				break;
			case CONSTANT_Utf8:
				printf("Length of byte array: %d\n",(int)aux->UnionCP.UTF8.length);
				printf("Length of string: %d\n",(int)aux->UnionCP.UTF8.length);
				printf("String: ");
				for (u1 * i = aux->UnionCP.UTF8.bytes; i < aux->UnionCP.UTF8.bytes + aux->UnionCP.UTF8.length; i++) {
					printf("%c",(char) (*i));
				}
				printf("\n");
				break;
			case CONSTANT_MethodHandle:
				printf("MethodHandle Reference Kind: %02x\n",aux->UnionCP.MethodHandle.reference_kind);
				printf("MethodHandle Reference Index: %04x\n",aux->UnionCP.MethodHandle.reference_index);
				break;
			case CONSTANT_MethodType:
				printf("MethodType Descriptor Index: %04x\n",aux->UnionCP.MethodType.descriptor_index);
				break;
			case CONSTANT_InvokeDynamic:
				printf("InvokeDynamic - Bootstrap Method Attr Index: %04x\n",aux->UnionCP.InvokeDynamicInfo.bootstrap_method_attr_index);
				printf("InvokeDynamic - Name and Type Index: %04x\n",aux->UnionCP.InvokeDynamicInfo.name_and_type_index);
				break;
			default:
				printf("Default\n");
				break;
		}
	}

	printf("\n\n-----MÉTODOS-----\n\n");

	contador = 0;

	for (auxMethod = arquivoClass->methods; auxMethod < arquivoClass->methods + arquivoClass->methods_count; auxMethod++,contador++) {
		printf("--------------Método [%d]--------------\n\n",contador);
		ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1+auxMethod->name_index);
		printf("Name: cp_info#%d <%s>\n",auxMethod->name_index,ponteiroprint);
		ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1+auxMethod->descriptor_index);
		printf("Descriptor: cp_info#%d <%s>\n",auxMethod->descriptor_index,ponteiroprint);
		ponteiroprint = decodificaAccessFlags(auxMethod->access_flags);
		printf("Access Flags: 0x%04x [%s]\n",auxMethod->access_flags,ponteiroprint);
		printf("Attributes Count: %04x\n",auxMethod->attributes_count);

		for (auxAttribute = auxMethod->UnionAttr.code_attributes; auxAttribute < auxMethod->UnionAttr.code_attributes+auxMethod->attributes_count; auxAttribute++) {

			ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1+auxAttribute->attribute_name_index);
			printf("Attribute Name Index: cp_info#%02x <%s>\n",auxAttribute->attribute_name_index,ponteiroprint);
			printf("Attribute Length: %d\n",auxAttribute->attribute_length);
			printf("Max Stack: %02x\n",auxAttribute->max_stack);
			printf("Max Locals: %02x\n",auxAttribute->max_locals);
			printf("Code length: %04x\n",auxAttribute->code_length);


			printf("Code: ");
			if(auxAttribute->code_length>0){
				for(auxcode=auxAttribute->code;auxcode<auxAttribute->code+auxAttribute->code_length;auxcode++){
					printf("%02x ",*auxcode);
				}
				printf("\n\n");
			}


			if(auxAttribute->exception_table_length>0){
				for(eAux=auxAttribute->table;eAux<auxAttribute->table+auxAttribute->exception_table_length;eAux++){
					printf("Start PC: %02x\n",eAux->start_pc);
					printf("End PC: %02x\n",eAux->end_pc);
					printf("Handler PC: %02x\n",eAux->handler_pc);
					printf("Catch Type: %02x\n",eAux->catch_type);
				}

				printf("\n\n");
			}

			printf("Attributes Count: %02x\n",auxAttribute->attributes_count);
			int contadorAttr = 0;
			int lntContador = 0;
			if (auxAttribute->attributes_count > 0) {
				printf("Attributo %d: \n",contadorAttr);
				for(line_number_table * lnt = auxAttribute->UnionCodeAttr.lineNumberTable; lnt < auxAttribute->UnionCodeAttr.lineNumberTable + auxAttribute->attributes_count;lnt++){
					ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1+lnt->attribute_name_index);
					printf("Attribute name index: cp_info#%d <%s>\n",lnt->attribute_name_index,ponteiroprint);
					printf("Attribute Length: %d\n",(int)lnt->attribute_length);
					printf("Attribute Info: \n");
					printf("Nr.\t\tStartPC\t\tLineNumber\n");
					for (line_number_tableInfo * linfo = lnt->info; linfo < lnt->info + lnt->line_number_table_length; linfo++) {
						printf("%d\t\t%d\t\t%d\n",lntContador,linfo->start_pc,linfo->line_number);
						lntContador++;
					}
					printf("\n");
					//for(u1 * c = (a->info); c < (a->info)+(a->attribute_length); c++) {
						//printf("%02x ",*c);
					//}
				}
				contadorAttr++;
			}
		}
	}

	printf("\n\n-----AtRIBUTOS DA CLASSE-----\n\n");
	for (auxAttributeClasse = arquivoClass->attributes; auxAttributeClasse < arquivoClass->attributes+arquivoClass->attributes_count; auxAttributeClasse++) {
		printf("Attribute Name Index: %04x\n",auxAttributeClasse->attribute_name_index);
		printf("Attribute Length: %08x\n",auxAttributeClasse->attribute_length);
		if (auxAttributeClasse->attribute_length > 0) {
			printf("Attribute Info: ");
			for(u1 * c = (auxAttributeClasse->info); c < (auxAttributeClasse->info)+(auxAttributeClasse->attribute_length); c++) {
				printf("%02x ",*c);
			}
			printf("\n");
		}
	}
}
