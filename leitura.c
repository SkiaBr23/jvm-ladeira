#include "leitura.h"

u1 u1Read(FILE *fp){
	u1 destino;
	if (fread(&destino,sizeof(u1),1,fp) != 1) {
		return MAXU1;
	} else {
		return destino;
	}
}

u2 u2Read(FILE *fp){
	u2 destino;
	u1 lowByte, highByte;
	highByte = u1Read(fp);
	lowByte = u1Read(fp);

	if(highByte != MAXU1 && lowByte != MAXU1) {
		destino = ((highByte)<<8) | ((lowByte));
		return destino;
	} else {
		return MAXU2;
	}
}

u4 u4Read(FILE *fp){
	u4 destino;
	u1 byteZero, byteUm, byteDois, byteTres;
	byteTres = u1Read(fp);
	byteDois = u1Read(fp);
	byteUm = u1Read(fp);
	byteZero = u1Read(fp);
	if(byteTres != MAXU1 && byteDois != MAXU1 && byteUm != MAXU1 && byteZero != MAXU1){
		destino = ((byteTres)<<24) | ((byteDois)<<16) | ((byteUm)<<8) | ((byteZero));
		return destino;
	} else {
		return MAXU4;
	}
}

ClassFile* lerArquivo (char * nomeArquivo) {
	ClassFile *arquivoClass = NULL;
	FILE * fp = fopen(nomeArquivo,"rb");
	// Se o ponteiro do arquivo for nulo, encerrar o programa e dar erro
	if (fp == NULL) {
		printf("Ocorreu um problema ao abrir o arquivo, finalizando programa!\n");
		exit(1);
	} else {
		arquivoClass = (ClassFile*) malloc(sizeof(ClassFile));

		arquivoClass->magic = u4Read(fp); 
		arquivoClass->minor_version = u2Read(fp);
		arquivoClass->major_version = u2Read(fp);
		arquivoClass->constant_pool_count = u2Read(fp); 

		printf("%08x\n",arquivoClass->magic);
		printf("%04x\n",arquivoClass->minor_version);
		printf("%04x\n",arquivoClass->major_version);
		printf("%04x\n",arquivoClass->constant_pool_count);

		// Alocar o constant pool com constant_pool_count-1
		cp_info *constantPool = (cp_info *) malloc((arquivoClass->constant_pool_count-1)*sizeof(cp_info));

		cp_info *aux = NULL;

		// Leitura do Constant Pool
		for (aux=constantPool;aux<constantPool+arquivoClass->constant_pool_count-1;aux++){
			aux->tag = u1Read(fp);
			printf("TAG: %02x\n",aux->tag);
			switch(aux->tag){
				case CONSTANT_Class:
					aux->UnionCP.Class.name_index = u2Read(fp);
					printf("%04x\n",aux->UnionCP.Class.name_index);
				break;
				case CONSTANT_Fieldref:
					aux->UnionCP.Fieldref.class_index = u2Read(fp);
					aux->UnionCP.Fieldref.name_and_type_index = u2Read(fp);
					printf("%04x\n",aux->UnionCP.Fieldref.class_index);
					printf("%04x\n",aux->UnionCP.Fieldref.name_and_type_index);
				break;
				case CONSTANT_Methodref:
					aux->UnionCP.Methodref.class_index = u2Read(fp);
					aux->UnionCP.Methodref.name_and_type_index = u2Read(fp);
					printf("%04x\n",aux->UnionCP.Methodref.class_index);
					printf("%04x\n",aux->UnionCP.Methodref.name_and_type_index);
				break;
				case CONSTANT_InterfaceMethodref:
					aux->UnionCP.InterfaceMethodref.class_index = u2Read(fp);
					aux->UnionCP.InterfaceMethodref.name_and_type_index = u2Read(fp);
					printf("%04x\n",aux->UnionCP.InterfaceMethodref.class_index);
					printf("%04x\n",aux->UnionCP.InterfaceMethodref.name_and_type_index);
				break;
				case CONSTANT_String:
					aux->UnionCP.String.string_index = u2Read(fp);
					printf("%04x\n",aux->UnionCP.String.string_index);
				break;
				case CONSTANT_Integer:
					aux->UnionCP.Integer.bytes = u2Read(fp);
					printf("%04x\n",aux->UnionCP.Integer.bytes);
				break;
				case CONSTANT_Float:
					aux->UnionCP.Float.bytes = u4Read(fp);
					printf("%04x\n",aux->UnionCP.Float.bytes);
				break;
				case CONSTANT_Long:
					aux->UnionCP.Long.high_bytes = u4Read(fp);
					aux->UnionCP.Long.low_bytes = u4Read(fp);
					printf("%04x\n",aux->UnionCP.Long.high_bytes);
					printf("%04x\n",aux->UnionCP.Long.low_bytes);
				break;
				case CONSTANT_Double:
					aux->UnionCP.Double.high_bytes = u4Read(fp);
					aux->UnionCP.Double.low_bytes = u4Read(fp);
					printf("%04x\n",aux->UnionCP.Double.high_bytes);
					printf("%04x\n",aux->UnionCP.Double.low_bytes);
				break;
				case CONSTANT_NameAndType:
					aux->UnionCP.NameAndType.name_index = u2Read(fp);
					aux->UnionCP.NameAndType.descriptor_index = u2Read(fp);
					printf("%04x\n",aux->UnionCP.NameAndType.name_index);
					printf("%04x\n",aux->UnionCP.NameAndType.descriptor_index);
				break;
				case CONSTANT_Utf8:
					aux->UnionCP.UTF8.length = u2Read(fp);
					aux->UnionCP.UTF8.bytes = malloc(aux->UnionCP.UTF8.length*sizeof(u1));
					for (u1 *i=aux->UnionCP.UTF8.bytes;i<aux->UnionCP.UTF8.bytes+aux->UnionCP.UTF8.length;i++){
						*i = u1Read(fp);
					}
					printf("%02x\n",aux->UnionCP.UTF8.length);
					for (u1 *i=aux->UnionCP.UTF8.bytes;i<aux->UnionCP.UTF8.bytes+aux->UnionCP.UTF8.length;i++){
						printf("%02x\n",*i);
					}
				break;
				case CONSTANT_MethodHandle:
					aux->UnionCP.MethodHandle.reference_kind = u1Read(fp);
					aux->UnionCP.MethodHandle.reference_index = u2Read(fp);
					printf("%02x\n",aux->UnionCP.MethodHandle.reference_kind);
					printf("%04x\n",aux->UnionCP.MethodHandle.reference_index);
				break;
				case CONSTANT_MethodType:
					aux->UnionCP.MethodType.descriptor_index = u2Read(fp);
					printf("%04x\n",aux->UnionCP.MethodType.descriptor_index);
				break;
				case CONSTANT_InvokeDynamic:
					aux->UnionCP.InvokeDynamicInfo.bootstrap_method_attr_index = u2Read(fp);
					aux->UnionCP.InvokeDynamicInfo.name_and_type_index = u2Read(fp);
					printf("%04x\n",aux->UnionCP.InvokeDynamicInfo.bootstrap_method_attr_index);
					printf("%04x\n",aux->UnionCP.InvokeDynamicInfo.name_and_type_index);
				break;
				default:
					printf("Default\n");
				break;
			}
		}

		arquivoClass->access_flags = u2Read(fp);
		arquivoClass->this_class = u2Read(fp);
		arquivoClass->super_class = u2Read(fp);
		arquivoClass->interfaces_count = u2Read(fp);

		printf("Access Flags: %04x\n",arquivoClass->access_flags);
		printf("This Class: %04x\n",arquivoClass->this_class);
		printf("Super Class: %04x\n",arquivoClass->super_class);
		printf("Interfaces Count: %04x\n",arquivoClass->interfaces_count);

		if(arquivoClass->interfaces_count>0){
			// Preencher com leitura de interfaces
			arquivoClass->interfaces = malloc(arquivoClass->interfaces_count*sizeof(u2));
		}

		arquivoClass->fields_count = u2Read(fp);
		printf("Fields Count: %04x\n",arquivoClass->fields_count);

		if(arquivoClass->fields_count>0){
			// Preencher com leitura de fields
			arquivoClass->fields = malloc(arquivoClass->fields_count*sizeof(u2));
		}

		arquivoClass->methods_count = u2Read(fp);
		printf("Methods Count: %04x\n",arquivoClass->methods_count);

		// Leitura de métodos
		if(arquivoClass->methods_count>0){
			arquivoClass->methods = malloc(arquivoClass->methods_count*sizeof(u2));

			// Leitura da estrutura method_info, que é o vetor methods dentro do ClassFile
			for (method_info *i=arquivoClass->methods;i<arquivoClass->methods+arquivoClass->methods_count;i++){
				i->access_flags = u2Read(fp);
				i->name_index = u2Read(fp);
				i->descriptor_index = u2Read(fp);
				i->attributes_count = u2Read(fp);

				printf("Access Flags do método: %04x\n",i->access_flags);
				printf("Name index do método: %04x\n",i->name_index);
				printf("Descriptor Index do método: %04x\n",i->descriptor_index);
				printf("Attributes Count do método: %04x\n",i->attributes_count);

				// Leitura dos atributos de métodos
				// Attributes count é o número de atributos
				if(i->attributes_count>0){
					i->attributes = malloc((i->attributes_count)*sizeof(attribute_info));
					// Isso aqui é louco
					// Leitura das strings
					// Aqui lê cada atributo
					for (attribute_info *a=i->attributes;a<(i->attributes)+(i->attributes_count);a++){
						// Atribuir os dados do atributo
						a->attribute_name_index = u2Read(fp);
						printf("Attribute name index: %04x\n",a->attribute_name_index);
						// Tamanho da string do atributo
						a->attribute_length = u4Read(fp);
						printf("Attribute length: %08x\n",a->attribute_length);
						if(a->attribute_length>0){
							a->info = malloc((a->attribute_length)*sizeof(u1));
							// Tô loucasso
							// Leitura dos caracteres da string pra armazenar em info
							// Ler o info do atributo
							for(u1 *c=(a->info);c<(a->info)+(a->attribute_length);c++){
								*c = u1Read(fp);
								printf("%02x\t",*c);
							}

							printf("\n");
						}
					}
				}
			}
		}


		// Leitura de atributos da classe
		arquivoClass->attributes_count = u2Read(fp);
		printf("Atributos da Classe: %02x\n",arquivoClass->attributes_count);

		if(arquivoClass->attributes_count>0){
			// Preencher com leitura de atributos
		}

		fclose(fp);

		return arquivoClass;
	}
}
