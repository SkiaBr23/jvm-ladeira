/*
Universidade de Brasília - 01/2017
Software Básico -Turma A
Projeto Leitor/Exibidor de arquivo .class

Alunos: Maximillian Fan Xavier - 12/0153271
				Rafael Dias da Costa - 12/0133253
				Murilo Cerqueira Medeiros - 12/0130637
				Eduardo Sousa da Silva - 13/0108405
				Eduardo Schuabb Duarte - 11/0010876

*/

/*Inclusão de estruturas e assinatura de funções de leitura*/
#include "leitura.h"

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
			arquivoClass->methods = lerMethod(fp, arquivoClass->methods_count);
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
method_info * lerMethod (FILE * fp, u2 methods_count) {
	/*Alocação da estrutura Method que será retornada para a estrutura
	principal do arquivo .class*/
	method_info * methods = (method_info*) malloc(methods_count*sizeof(u2));

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
		if (i->attributes_count > 0) {
			i->attributes = lerAttributes(fp, i->attributes_count);
		}
	}

	/*Retorno da estrutura Method alocada, com as informações lidas*/
	return methods;
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

void imprimirClassFile (ClassFile * arquivoClass) {

	cp_info * aux;
	method_info * auxMethod;
	attribute_info * auxAttribute;

	printf("Magic: %08x\n",arquivoClass->magic);
	printf("Minor Version: %04x\n",arquivoClass->minor_version);
	printf("Major Version: %04x\n",arquivoClass->major_version);
	printf("Constant Pool Count: %04x\n",arquivoClass->constant_pool_count);

	for (aux = arquivoClass->constant_pool; aux < arquivoClass->constant_pool+arquivoClass->constant_pool_count-1; aux++) {
		printf("TAG: %02x\n",aux->tag);
		switch(aux->tag) {
			case CONSTANT_Class:
				printf("Class Name Index: %04x\n",aux->UnionCP.Class.name_index);
				break;
			case CONSTANT_Fieldref:
				printf("Fieldref Class Index: %04x\n",aux->UnionCP.Fieldref.class_index);
				printf("Fieldref Name and Type Index: %04x\n",aux->UnionCP.Fieldref.name_and_type_index);
				break;
			case CONSTANT_Methodref:
				printf("Methodref Class Index: %04x\n",aux->UnionCP.Methodref.class_index);
				printf("Methodref Name and Type Index: %04x\n",aux->UnionCP.Methodref.name_and_type_index);
				break;
			case CONSTANT_InterfaceMethodref:
				printf("InterfaceMethodref Class Index: %04x\n",aux->UnionCP.InterfaceMethodref.class_index);
				printf("InterfaceMethodref Name and Type Index: %04x\n",aux->UnionCP.InterfaceMethodref.name_and_type_index);
				break;
			case CONSTANT_String:
				printf("String Index: %04x\n",aux->UnionCP.String.string_index);
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
				printf("Name and Type - Name Index: %04x\n",aux->UnionCP.NameAndType.name_index);
				printf("Name and Type - Descriptor Index: %04x\n",aux->UnionCP.NameAndType.descriptor_index);
				break;
			case CONSTANT_Utf8:
				printf("UTF8 Length: %02x\n",aux->UnionCP.UTF8.length);
				printf("Bytes: ");
				for (u1 * i = aux->UnionCP.UTF8.bytes; i < aux->UnionCP.UTF8.bytes + aux->UnionCP.UTF8.length; i++) {
					printf("%02x ",*i);
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

	printf("Access Flags: %04x\n",arquivoClass->access_flags);
	printf("This Class: %04x\n",arquivoClass->this_class);
	printf("Super Class: %04x\n",arquivoClass->super_class);
	printf("Interfaces Count: %04x\n",arquivoClass->interfaces_count);
	printf("Fields Count: %04x\n",arquivoClass->fields_count);
	printf("Methods Count: %04x\n",arquivoClass->methods_count);

	for (auxMethod = arquivoClass->methods; auxMethod < arquivoClass->methods + arquivoClass->methods_count; auxMethod++) {
		printf("Access Flags do método: %04x\n",auxMethod->access_flags);
		printf("Name index do método: %04x\n",auxMethod->name_index);
		printf("Descriptor Index do método: %04x\n",auxMethod->descriptor_index);
		printf("Attributes Count do método: %04x\n",auxMethod->attributes_count);

		for (auxAttribute = auxMethod->attributes; auxAttribute < auxMethod->attributes+auxMethod->attributes_count; auxAttribute++) {
			printf("Attribute Name Index: %04x\n",auxAttribute->attribute_name_index);
			printf("Attribute Length: %08x\n",auxAttribute->attribute_length);
			if (auxAttribute->attribute_length > 0) {
				printf("Attribute Info: ");
				for(u1 * c = (auxAttribute->info); c < (auxAttribute->info)+(auxAttribute->attribute_length); c++) {
					printf("%02x ",*c);
				}
				printf("\n");
			}
		}
	}

	printf("Atributos da Classe: %02x\n",arquivoClass->attributes_count);
	for (auxAttribute = arquivoClass->attributes; auxAttribute < arquivoClass->attributes+arquivoClass->attributes_count; auxAttribute++) {
		printf("Attribute Name Index: %04x\n",auxAttribute->attribute_name_index);
		printf("Attribute Length: %08x\n",auxAttribute->attribute_length);
		if (auxAttribute->attribute_length > 0) {
			printf("Attribute Info: ");
			for(u1 * c = (auxAttribute->info); c < (auxAttribute->info)+(auxAttribute->attribute_length); c++) {
				printf("%02x ",*c);
			}
			printf("\n");
		}
	}

}
