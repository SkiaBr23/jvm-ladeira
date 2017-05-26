#ifndef	CLASSFILESTRUCT_H
#define CLASSFILESTRUCT_H

/**

	Definicao da estrutura de ClassFile.

	Uma estrutura de um arquivo .class no java possui
	as seguintes caracteristicas:

	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	cp_info constant_pool[constant_pool_count]; // Obs.: cp_info eh outra estrutura
	u2 access_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 interfaces[interfaces_count];
	u2 fields_count;
	field_info fields[fields_count]; // Obs. field_info eh outra estrutura
	u2 methods_count;
	method_info methods[methods_count]; // Obs. method_info eh outra estrutura
	u2 attributes_count;
	attribute_info attibutes[attributes_count]; // Obs. attribute_info eh outra estrutura

Onde:

	u1 = typedef unsigned char;		// u1 = uint8_t
	u2 = typedef unsigned short; 	// u2 = uint16_t
	u4 = typedef unsigned int;		// u4 = uint32_t


*/

#include <stdint.h>		// Biblioteca para definicao do tamanho de um inteiro.
#include "structures.h"


struct classFile{

	u4 magic;								// Assinatura de um arquivo .class
	u2 minor_version;						// Versao minima do arquivo.
	u2 major_version;						// Versao maxima do arquivo.
	u2 constant_pool_count;				// Numero de entradas na tabela constant_pool.
	cp_info *constant_pool; // DEFINIR A ESTRUTURA cp_info. Alocar com constantpoolcount-1
	u2 access_flags;						// Mascara de bits que especifica permissao de acesso da classe.
	u2 this_class;						// Representa a classe definida.
	u2 super_class;						// Representa a super classe direta da classe definida.
	u2 interfaces_count;					// Numero de entradas no array interfaces[].
	u2 *interfaces;		// Representa uma interface que eh uma superinterface direta da classe. Aloca com interfaces_count
	u2 fields_count;						// Numero de variaveis de classe ou de instancias declaradas na classe.
	field_info *fields;			// DEFINIR A ESTRUTURA field_info. Aloca com fields_count
	u2 methods_count;						// Numero de estruturas method_info na tabela de methods.
	method_info *methods;			// DEFINIR A ESTRUTURA method_info. Aloca com methods_count
	u2 attributes_count;					// Numero de estruturas attributes_info na tabela attributes.
	attribute_info *attributes;	// DEFINIR A ESTRUTURA attribute_info. Aloca com attributes_count

};
typedef struct classFile ClassFile;

#endif
