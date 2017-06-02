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
			arquivoClass->interfaces = lerInterfaces(fp, arquivoClass->interfaces_count);
		}

		/*Leitura do valor 'fields_count', representando
		a quantidade de entradas na tabela Fields*/
		arquivoClass->fields_count = u2Read(fp);

		/*Estrutura condicional que verifica se a quantidade de entradas
		na tabela Fields é maior que zero. Se for, prossegue com a leitura
		das entradas, caso contrário prossegue com a leitura dos próximos campos*/
		if (arquivoClass->fields_count > 0) {
			// Preencher com leitura de fields - CODIFICAR
			arquivoClass->fields = lerField(fp, arquivoClass->fields_count, arquivoClass->constant_pool);
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
			arquivoClass->attributes = (attribute_info**)malloc(arquivoClass->attributes_count*sizeof(attribute_info*));
			for (int posicao = 0; posicao < arquivoClass->attributes_count; posicao++) {
				*(arquivoClass->attributes+posicao) = lerAttributes(fp, arquivoClass->constant_pool);
			}
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

u2 * lerInterfaces (FILE * fp, u2 size) {
	u2 * interfaces = malloc(size*sizeof(u2));
	for (u2 * auxInterfaces = interfaces; auxInterfaces < interfaces+size; auxInterfaces++) {
		*auxInterfaces = u2Read(fp);
	}
	return interfaces;
}

field_info * lerField (FILE * fp, u2 fields_count, cp_info * cp) {
	field_info * fields = (field_info*)malloc(fields_count*sizeof(field_info));
	for (field_info * i = fields; i < fields + fields_count; i++) {
		i->access_flags = u2Read(fp);
		i->name_index = u2Read(fp);
		i->descriptor_index = u2Read(fp);
		i->attributes_count = u2Read(fp);

		if (i->attributes_count > 0) {
			i->attributes = (attribute_info**)malloc(i->attributes_count*sizeof(attribute_info*));
			for (int posicao = 0; posicao < i->attributes_count; posicao++) {
				*(i->attributes+posicao) = lerAttributes(fp, cp);
			}
		}
	}

	return fields;
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
		// attribute_info *attributes = (attribute_info*) malloc(i->attributes_count*sizeof(attribute_info));

		if (i->attributes_count > 0) {
			i->attributes = (attribute_info**)malloc(i->attributes_count*sizeof(attribute_info*));
			for (int posicao = 0; posicao < i->attributes_count; posicao++) {
				*(i->attributes+posicao) = lerAttributes(fp, cp);
			}
		}



		//FUNCIONOU - LIXAO
		/*if (i->attributes_count > 0) {
			u2 ida, vinda;
			ida = i->attributes_count;
			vinda = i->attributes_count;
			i->attributes = NULL;
			i->attributes = (attribute_info*)malloc(sizeof(attribute_info)*i->attributes_count);
			while (ida){
				//(code_attribute*) malloc(i->attributes_count*sizeof(code_attribute));
				i->attributes = lerAttributes(fp, cp);
				ida--;
				i->attributes++;
				getchar();
			}
			while (vinda) {
				i->attributes--;
				vinda--;
			}
		}*/
	}

	/*Retorno da estrutura Method alocada, com as informações lidas*/
	return methods;
}

code_attribute * lerCode (FILE * fp, cp_info *cp) {
	code_attribute * code_attributes = NULL;
	code_attributes = (code_attribute*) malloc(sizeof(code_attribute));
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

	if(code_attributes->exception_table_length > 0){
		code_attributes->table = NULL;//malloc(code_attributes->exception_table_length*sizeof(exception_table));
		code_attributes->table = lerExceptionTable(fp, code_attributes->exception_table_length);
	}

	code_attributes->attributes_count = u2Read(fp);

	if (code_attributes->attributes_count > 0){
		code_attributes->attributes = (attribute_info**)malloc(code_attributes->attributes_count*sizeof(attribute_info*));
		for (int posicao = 0; posicao < code_attributes->attributes_count; posicao++) {
			*(code_attributes->attributes+posicao) = lerAttributes(fp, cp);
		}
	}


		/*u2 ida, vinda;
		ida = code_attributes->attributes_count;
		vinda = code_attributes->attributes_count;
		code_attributes->attributes = NULL;
		code_attributes->attributes = (attribute_info*)malloc(sizeof(attribute_info)*code_attributes->attributes_count);

		while (ida){
			code_attributes->attributes = lerAttributes(fp, cp);
			ida--;
			code_attributes->attributes++;
		}
		while (vinda) {
			code_attributes->attributes--;
			vinda--;
		}*/

		/*code_attributes->attributes = NULL;
		attribute_info * attr = (attribute_info*)malloc(sizeof(attribute_info)*code_attributes->attributes_count);
		attribute_info * aux;
		for (aux = attr; aux < attr+code_attributes->attributes_count; aux++) {
			attribute_info * attrAux = NULL;//(code_attribute*) malloc(i->attributes_count*sizeof(code_attribute));
			attrAux = lerAttributes(fp, cp);
			aux = attrAux;
		}
		code_attributes->attributes = attr;
	}*/

	return code_attributes;
}

line_number_table * lerLineNumberTable(FILE * fp, cp_info * cp) {
	line_number_table * lnt = (line_number_table*)malloc(sizeof(line_number_table));
	lnt->line_number_table_length = u2Read(fp);
	if (lnt->line_number_table_length > 0) {
		lnt->info = (line_number_tableInfo*)malloc(lnt->line_number_table_length*sizeof(line_number_tableInfo));
		for (line_number_tableInfo * linfo = lnt->info; linfo < lnt->info+lnt->line_number_table_length; linfo++) {
			linfo->start_pc = u2Read(fp);
			linfo->line_number = u2Read(fp);
		}
	}
	return lnt;
}

exception_table * lerExceptionTable (FILE * fp, u2 size) {
	exception_table * exception_tableAux = (exception_table*)malloc(size*sizeof(exception_table));
	for(exception_table * e = exception_tableAux; e < exception_tableAux + size; e++){
		e->start_pc = u2Read(fp);
		e->end_pc = u2Read(fp);
		e->handler_pc = u2Read(fp);
		e->catch_type = u2Read(fp);
	}
	return exception_tableAux;
}



/*Função 'lerAttributes' para realizar a leitura da tabela Attribute*/
attribute_info * lerAttributes (FILE * fp, cp_info * cp) {

	/*Alocação da estrutura Attribute que será retornada para a estrutura
	principal do arquivo .class*/
	attribute_info * attributes = (attribute_info*) malloc(sizeof(attribute_info));
	/*Leitura do atributo name_index do respectivo atributo*/
	attributes->attribute_name_index = u2Read(fp);
	/*Leitura do atributo length do respectivo atributo*/
	attributes->attribute_length = u4Read(fp);
	/*Estrutura condicional que avalia se o tamanho do atributo
	é maior que zero. Se for, prossegue com a leitura da informação
	do atributo*/
	if (attributes->attribute_length > 0) {
			char * string_name_index = malloc(100*sizeof(char));
			string_name_index = decodificaStringUTF8(cp+attributes->attribute_name_index-1);
			//VERIFICAR SE ELE SO ALOCA NO MAXIMO 1 TIPO, LINENUMBER-CODE-ETC,por chamada
			if(strcmp(string_name_index,"SourceFile") == 0){
				source_file_attribute * SourceFile = NULL;//(code_attribute*) malloc(i->attributes_count*sizeof(code_attribute));
				SourceFile = lerSourceFile(fp);
				attributes->info = NULL;//malloc(i->attributes_count*sizeof(code_attribute));
				attributes->info = (source_file_attribute*) SourceFile;
			} else if (strcmp(string_name_index,"Code") == 0) {
				code_attribute * code_attr = NULL;
				code_attr = lerCode(fp ,cp);
				attributes->info = (code_attribute*) code_attr;
			} else if (strcmp(string_name_index,"LineNumberTable") == 0) {
				line_number_table * lnt = NULL;
				lnt = lerLineNumberTable(fp, cp);
				attributes->info = (line_number_table*)lnt;
			} else if (strcmp(string_name_index,"StackMapTable") == 0) {
				printf("Atributo STACKMAPTABLE não implementado!\n");
				exit(1);
				stackMapTable_attribute * stackMapTable = NULL;
				stackMapTable = lerStackMapTable(fp);
				attributes->info = (stackMapTable_attribute*)stackMapTable;
			}
	}
	/*Retorno da estrutura Attribute alocada, com as informações lidas*/
	return attributes;
}

stackMapTable_attribute * lerStackMapTable (FILE * fp) {
	stackMapTable_attribute * stackMapTable = (stackMapTable_attribute*)malloc(sizeof(stackMapTable_attribute));
	stackMapTable->number_of_entries = u2Read(fp);
	if (stackMapTable->number_of_entries > 0) {
		stackMapTable->entries = (stack_map_frame**)malloc(stackMapTable->number_of_entries*sizeof(stack_map_frame*));
		for (int posicao = 0; posicao < stackMapTable->number_of_entries; posicao++) {
			*(stackMapTable->entries+posicao) = lerStackMapFrame(fp);
		}
	}
	return stackMapTable;
}

stack_map_frame * lerStackMapFrame (FILE * fp) {
	stack_map_frame * StackMapFrame = (stack_map_frame*)malloc(sizeof(stack_map_frame));
	StackMapFrame->frame_type = u1Read(fp);
	if (StackMapFrame->frame_type >= 0 && StackMapFrame->frame_type <= 63) {
	} else if (StackMapFrame->frame_type >= 64 && StackMapFrame->frame_type <= 127) {
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame.stack = (verification_type_info**)malloc(sizeof(verification_type_info*));
		*(StackMapFrame->map_frame_type.same_locals_1_stack_item_frame.stack) = lerVerificationTypeInfo(fp);
	} else if (StackMapFrame->frame_type == 247) {
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta = u2Read(fp);
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.stack = (verification_type_info**)malloc(sizeof(verification_type_info*));
		*(StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.stack) = lerVerificationTypeInfo(fp);
	} else if (StackMapFrame->frame_type >= 248 && StackMapFrame->frame_type <= 250) {
		StackMapFrame->map_frame_type.chop_frame.offset_delta = u2Read(fp);
	} else if (StackMapFrame->frame_type == 251) {
		StackMapFrame->map_frame_type.same_frame_extended.offset_delta = u2Read(fp);
	} else if (StackMapFrame->frame_type >= 252 && StackMapFrame->frame_type <= 254) {
		StackMapFrame->map_frame_type.append_frame.offset_delta = u2Read(fp);
		printf("Leu: %d\n",StackMapFrame->map_frame_type.append_frame.offset_delta);
		StackMapFrame->map_frame_type.append_frame.locals = (verification_type_info**)malloc(sizeof(verification_type_info*));
		*(StackMapFrame->map_frame_type.append_frame.locals) = lerVerificationTypeInfo(fp);
	} else if (StackMapFrame->frame_type == 255) {
		StackMapFrame->map_frame_type.full_frame.offset_delta = u2Read(fp);
		StackMapFrame->map_frame_type.full_frame.number_of_locals = u2Read(fp);
		if (StackMapFrame->map_frame_type.full_frame.number_of_locals > 0) {
			StackMapFrame->map_frame_type.full_frame.locals = (verification_type_info**)malloc(StackMapFrame->map_frame_type.full_frame.number_of_locals*sizeof(verification_type_info*));
			for (int posicao = 0; posicao < StackMapFrame->map_frame_type.full_frame.number_of_locals; posicao++) {
				*(StackMapFrame->map_frame_type.full_frame.locals+posicao) = lerVerificationTypeInfo(fp);
			}
		}
		StackMapFrame->map_frame_type.full_frame.number_of_stack_items = u2Read(fp);
		if (StackMapFrame->map_frame_type.full_frame.number_of_stack_items > 0) {
			StackMapFrame->map_frame_type.full_frame.stack = (verification_type_info**)malloc(StackMapFrame->map_frame_type.full_frame.number_of_stack_items*sizeof(verification_type_info*));
			for (int posicao = 0; posicao < StackMapFrame->map_frame_type.full_frame.number_of_locals; posicao++) {
				*(StackMapFrame->map_frame_type.full_frame.stack+posicao) = lerVerificationTypeInfo(fp);
			}
		}
	}
	return StackMapFrame;
}

verification_type_info * lerVerificationTypeInfo (FILE * fp) {
	verification_type_info * VTI = (verification_type_info*)malloc(sizeof(verification_type_info));
	VTI->tag = u1Read(fp);
	switch (VTI->tag) {
		case 7:
			VTI->type_info.object_variable_info.cpool_index = u2Read(fp);
			break;
		case 8:
			VTI->type_info.uninitialized_variable_info.offset = u2Read(fp);
			break;
		default:
			break;
	}

	return VTI;
}

source_file_attribute * lerSourceFile (FILE * fp) {
	source_file_attribute * SourceFile = NULL;
	SourceFile = (source_file_attribute*)malloc(sizeof(source_file_attribute));
	SourceFile->source_file_index = u2Read(fp);
	return SourceFile;
}

char* buscaNomeTag(u1 tag){
	char *nometag = malloc(40*sizeof(char));
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
	field_info * auxField;
	attribute_info ** auxAttributeClasse;
	exception_table * exceptionTableAux;
	uint32_t contador = 1;
	u1 * auxBytesCode;
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

	printf("\n\n-----INTERFACES-----\n\n");
	contador = 0;
	for (u2 * auxInterfaces = arquivoClass->interfaces; auxInterfaces < arquivoClass->interfaces+arquivoClass->interfaces_count; auxInterfaces++) {
		printf("%02x ",*auxInterfaces);
	}

	printf("\n\n-----FIELDS-----\n\n");
	contador = 0;
	for (auxField = arquivoClass->fields; auxField < arquivoClass->fields + arquivoClass->fields_count; auxField++,contador++) {
		printf("--------------Field [%d]--------------\n\n",contador);
		ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1+auxField->name_index);
		printf("Name: cp_info#%d <%s>\n",auxField->name_index,ponteiroprint);
		ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1+auxField->descriptor_index);
		printf("Descriptor: cp_info#%d <%s>\n",auxField->descriptor_index,ponteiroprint);
		ponteiroprint = decodificaAccessFlags(auxField->access_flags);
		printf("Access Flags: 0x%04x [%s]\n",auxField->access_flags,ponteiroprint);
		printf("Attributes Count: %04x\n",auxField->attributes_count);
		//Incluir impressao de atributos dos fields
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

		printf("Atributos:\n");
		attribute_info ** auxAttrCompleto = auxMethod->attributes;
		for (int posicao = 0; posicao < auxMethod->attributes_count; posicao++) {
			ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1+(*(auxAttrCompleto+posicao))->attribute_name_index);
			printf("Attribute Name Index: cp_info#%02x <%s>\n",(*(auxAttrCompleto+posicao))->attribute_name_index,ponteiroprint);
			printf("Attribute Length: %d\n",(*(auxAttrCompleto+posicao))->attribute_length);

			if (strcmp(ponteiroprint,"Code") == 0) {
				code_attribute * auxCodePontual = (code_attribute*)(*(auxAttrCompleto+posicao))->info;
				printf("Max Stack: %02x\n",auxCodePontual->max_stack);
				printf("Max Locals: %02x\n",auxCodePontual->max_locals);
				printf("Code length: %04x\n",auxCodePontual->code_length);
				printf("Code: ");
				if(auxCodePontual->code_length > 0) {
					for(auxBytesCode = auxCodePontual->code; auxBytesCode < auxCodePontual->code + auxCodePontual->code_length; auxBytesCode++){
						printf("%02x ",*auxBytesCode);
					}
					printf("\n\n");
				}
				if(auxCodePontual->exception_table_length > 0) {
					for(exceptionTableAux = auxCodePontual->table; exceptionTableAux < auxCodePontual->table + auxCodePontual->exception_table_length; exceptionTableAux++){
						printf("Start PC: %02x\n",exceptionTableAux->start_pc);
						printf("End PC: %02x\n",exceptionTableAux->end_pc);
						printf("Handler PC: %02x\n",exceptionTableAux->handler_pc);
						printf("Catch Type: %02x\n",exceptionTableAux->catch_type);
					}
					printf("\n\n");
				}
				printf("Attributes Count: %02x\n",auxCodePontual->attributes_count);
				if (auxCodePontual->attributes_count > 0) {
					int lntContador = 0;
					attribute_info ** auxAttributesFromCode = auxCodePontual->attributes;
					for (int posicaoDois = 0; posicaoDois < auxCodePontual->attributes_count; posicaoDois++) {
						ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1+(*(auxAttributesFromCode+posicaoDois))->attribute_name_index);
						printf("Attributo %d: \n",contadorAttr);
						printf("Attribute Name Index: cp_info#%02x <%s>\n",(*(auxAttributesFromCode+posicaoDois))->attribute_name_index,ponteiroprint);
						printf("Attribute Length: %d\n",(*(auxAttributesFromCode+posicaoDois))->attribute_length);
						if (strcmp(ponteiroprint,"LineNumberTable") == 0) {
							line_number_table * lntAux = (line_number_table*)(*(auxAttributesFromCode+posicaoDois))->info;
							for(line_number_table * lnt = lntAux; lnt < lntAux + auxCodePontual->attributes_count; lnt++) {
								ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool-1 + (*(auxAttributesFromCode+posicaoDois))->attribute_name_index);
								printf("Attribute name index: cp_info#%d <%s>\n",(*(auxAttributesFromCode+posicaoDois))->attribute_name_index,ponteiroprint);
								printf("Attribute Length: %d\n",(int)lnt->line_number_table_length);
								printf("Attribute Info: \n");
								printf("Nr.\t\tStartPC\t\tLineNumber\n");
								for (line_number_tableInfo * linfo = lnt->info; linfo < lnt->info + lnt->line_number_table_length; linfo++) {
									printf("%d\t\t%d\t\t%d\n",lntContador,linfo->start_pc,linfo->line_number);
									lntContador++;
								}
								printf("\n");
							}
						}
					}
				}
			}
		}
	}

	printf("\n\n-----AtRIBUTOS DA CLASSE-----\n\n");
	auxAttributeClasse = arquivoClass->attributes;
	for (int posicao = 0; posicao < arquivoClass->attributes_count; posicao++) {
		ponteiroprint = decodificaStringUTF8(arquivoClass->constant_pool+(*(auxAttributeClasse+posicao))->attribute_name_index-1);
		printf("Attribute Name Index: cp_info#%d <%s>\n",(*(auxAttributeClasse+posicao))->attribute_name_index,ponteiroprint);
		printf("Attribute Length: %d\n",(int) (*(auxAttributeClasse+posicao))->attribute_length);
		if (strcmp(ponteiroprint,"SourceFile") == 0) {
		 	source_file_attribute * SourceFile = ((source_file_attribute*)((*(auxAttributeClasse+posicao))->info));
			printf("Source File Name Index: cp_info#%d <%s>\n",SourceFile->source_file_index,decodificaStringUTF8(arquivoClass->constant_pool+SourceFile->source_file_index-1));
		}
	}
}
