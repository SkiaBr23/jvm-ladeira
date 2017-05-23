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


struct ClassFile{
 
	uint32_t magic;								// Assinatura de um arquivo .class
	uint16_t minor_version;						// Versao minima do arquivo.
	uint16_t major_version;						// Versao maxima do arquivo.
	uint16_t constant_pool_count;				// Numero de entradas na tabela constant_pool + 1.
	cp_info constant_pool[constant_pool_count]; // DEFINIR A ESTRUTURA cp_info.
	uint16_t access_flags;						// Mascara de bits que especifica permissao de acesso da classe.
	uint16_t this_class;						// Representa a classe definida.
	uint16_t super_class;						// Representa a super classe direta da classe definida.
	uint16_t interfaces_count;					// Numero de entradas no array interfaces[].
	uint16_t interfaces[interfaces_count];		// Representa uma interface que eh uma superinterface direta da classe.
	uint16_t fields_count;						// Numero de variaveis de classe ou de instancias declaradas na classe.
	field_info fields [fields_count];			// DEFINIR A ESTRUTURA field_info.
	uint16_t methods_count;						// Numero de estruturas method_info na tabela de methods.
	method_info methods[methods_count];			// DEFINIR A ESTRUTURA method_info.
	uint16_t attributes_count;					// Numero de estruturas attributes_info na tabela attributes.
	attribute_info attibutes[attributes_count];	// DEFINIR A ESTRUTURA attribute_info.

};
typedef struct ClassFile ClassFile;
