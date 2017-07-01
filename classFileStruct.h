/**
 * @file classFileStruct.h
 * @brief Arquivo cabeçalho de definição da estrutura de ClassFile
 * @details 
 * 
 * 
 * Definição da estrutura de ClassFile.
 * Uma estrutura de um arquivo .class no Java possui as seguintes características:
 * @code
 * u4 magic;
 * u2 minor_version;
 * u2 major_version;
 * u2 constant_pool_count;
 * cp_info constant_pool[constant_pool_count];
 * u2 access_flags;
 * u2 this_class;
 * u2 super_class;
 * u2 interfaces_count;
 * u2 interfaces[interfaces_count];
 * u2 fields_count;
 * field_info fields[fields_count]; 
 * u2 methods_count;
 * method_info methods[methods_count]; 
 * u2 attributes_count;
 * attribute_info attibutes[attributes_count];
 * @endcode
 *  
 * Onde:
 * @code
 * u1 = typedef unsigned char -> uint8_t
 * u2 = typedef unsigned short	-> uint16_t
 * u4 = typedef unsigned int -> uint32_t
 * @endcode
 */
/** Macro para verificação de inclusão de estrutura ClassFile */
#ifndef	CLASSFILESTRUCT_H
#define CLASSFILESTRUCT_H


/*Inclusão de biblioteca para tratamento de tipo inteiro com representatividade
alternada de acordo com a quantidade de bits e inclusão do arquivo com as estruturas
internas do ClassFile*/
#include <stdint.h>
#include "structures.h"


/**
 * @struct classfile
 * 
 * @brief Estrutura de dados de um arquivo .class Java
 * 
*/
struct classFile{

	u4 magic;								/**< Assinatura de um arquivo .class */
	u2 minor_version;						/**< Versao mínima do arquivo - Relação com a versão do Java */
	u2 major_version;						/**< Versao máxima do arquivo - Relação com a versão do Java */
	u2 constant_pool_count;					/**< Numero de entradas na estrutura Constant Pool */
	cp_info *constant_pool; 				/**< Tabela Constant Pool */
	u2 access_flags;						/**< Mascara de bits que especifica permissão de acesso da classe */
	u2 this_class;							/**< Representa a classe definida */
	u2 super_class;							/**< Representa a super classe direta da classe definida */
	u2 interfaces_count;					/**< Numero de entradas na estrutura Interfaces */
	u2 *interfaces;							/**< Interfaces que são superinterfaces diretas da classe */
	u2 fields_count;						/**< Numero de variáveis de classe ou de instâncias declaradas na classe presentes na estrutura Field */
	field_info *fields;						/**< Estrutura de Field */
	u2 methods_count;						/**< Numero de estruturas method_info na tabela de Methods */
	method_info *methods;					/**< Tabela Method */
	u2 attributes_count;					/**< Numero de estruturas attributes_info na tabela Attributes */
	attribute_info ** attributes;			/**< Tabela Attributes */

};

/**
 * @brief Definição de tipo 'ClassFile' para a estrutura
 */
typedef struct classFile ClassFile;



#endif
