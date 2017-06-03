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

/*Macro para verificação de inclusão de estrutura ClassFile*/
#ifndef	STRUCTURES_H
#define STRUCTURES_H

/*
Nesse arquivo estão definidas as estruturas que sao utilizadas na Constant Pool

- Valores para tag:

CONSTANT_Class -> 7
CONSTANT_Fieldref -> 9
CONSTANT_Methodref -> 10
CONSTANT_InterfaceMethodref -> 11
CONSTANT_String -> 8
CONSTANT_Integer -> 3
CONSTANT_Float -> 4
CONSTANT_Long -> 5
CONSTANT_Double -> 6
CONSTANT_NameAndType ->12
CONSTANT_Utf8 -> 1
CONSTANT_MethodHandle -> 15
CONSTANT_MethodType -> 16
CONSTANT_InvokeDynamic -> 18
*/

/*Inclusão de biblioteca para tratamento de tipo inteiro com representatividade
alternada de acordo com a quantidade de bits*/
#include <stdint.h>

/*Definição de rótulos para os tipos uint8_t, uint16_t e uint32_t como
u1, u2 e u4, respectivamente*/
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

/*Definição de valores máximos, para debug - PENSAR OUTRO MODO*/
#define MAXU1 255
#define MAXU2 65535
#define MAXU4 2147483647
#define NAME_INDEX 1
#define NAME_AND_TYPE 2
#define STRING_INDEX 3
#define CLASS_INDEX 4
#define NAME_AND_TYPE_INFO_NAME_INDEX 5
#define NAME_AND_TYPE_INFO_DESCRIPTOR_INDEX 6


/*Definição da estrutura de Constant Pool*/
struct cp_info{
	/*Byte tag para designar o tipo de entrada na Constant Pool*/
	u1 tag;
	/*Estrutura union para conter os tipos de entrada na Constant Pool.
	Cada entrada assume a forma de estrutura, com seus respectivos atributos
	de informação*/
	union{
		/*Estrutura representando uma classe ou interface*/
		struct{
			/*Índice válido em Constant Pool, indicando
			o nome completo qualificado da classe ou
			interface*/
			u2 name_index;
		} Class;
		/*Estrutura representando um field*/
		struct{
			/*Índice válido em Constant Pool, indicando
			o nome completo da classe ou interface que
			contém a declaração desse field*/
			u2 class_index;
			/*Índice válido em Constant Pool, indicando
			o nome e o descritor do field*/
			u2 name_and_type_index;
		} Fieldref;
		/*Estrutura representando um método*/
		struct{
			/*Índice válido em Constant Pool, indicando
			o nome completo da classe que contém a
			declaração desse método*/
			u2 class_index;
			/*Índice válido em Constant Pool, indicando
			o nome e o descritor do método*/
			u2 name_and_type_index;
		} Methodref;
		/*Estrutura representando interfaceamento
		de métodos*/
		struct{
			/*Índice válido em Constant Pool, indicando
			o nome completo da interface que contém a
			declaração desse método*/
			u2 class_index;
			/*Índice válido em Constant Pool, indicando
			o nome e o descritor do método*/
			u2 name_and_type_index;
		} InterfaceMethodref;
		/*Estrutura representando objetos
		constantes do tipo String*/
		struct{
			/*Índice válido em Constant Pool, indicando
			a sequência de caracteres com a qual o
			objeto String será iniciado*/
			u2 string_index;
		} String;
		/*Estrutura representando uma
		constante inteira de 4 bytes*/
		struct{
			/*Representa o valor da constante
			int, em big-endian*/
			u2 bytes;
		} Integer;
		/*Estrutura representando uma
		constante de ponto flutuante de
		4 bytes*/
		struct{
			/*Representa o valor da constante
			float, em big-endian, no formato de
			precisão simples de ponto flutuante
			padrão IEEE 754*/
			u4 bytes;
		} Float;
		/*Estrutura representando uma
		constante inteira de 8 bytes*/
		struct{
			/*Representa a parte alta do valor, 4 bytes*/
			u4 high_bytes;
			/*Representa a parte baixa do valor, 4 bytes*/
			u4 low_bytes;
		} Long;
		/*Estrutura representando uma
		constante de ponto flutuante de
		8 bytes, big-endian, no formato precisão
		dupla IEEE 754*/
		struct{
			/*Representa a parte alta do valor, 4 bytes*/
			u4 high_bytes;
			/*Representa a parte baixa do valor, 4 bytes*/
			u4 low_bytes;
		} Double;
		/*Estrutura representando um field ou
		método sem indicar classe ou interface
		a que pertence*/
		struct{
			/*Índice válido em Constant Pool, indicando
			o nome simples do field ou método ou ainda
			o nome do método especial <init>*/
			u2 name_index;
			/*Índice válido em Constant Pool, indicando
			o descritor válido do field ou de método*/
			u2 descriptor_index;
		} NameAndType;
		/*Estrutura representando valores strings
		constantes, inclusive Unicode*/
		struct{
			/*Representa o número de bytes no array
			bytes*/
			u2 length;
			/*Contém os bytes da string*/
			u1 *bytes;
		} UTF8;
		/*Estrutura representando um método handle*/
		struct{
			/*Valor denotando o tipo deste método handle
			, que caracteriza o comportamento do bytecode*/
			u1 reference_kind;
			/*Índice válido em Constant Pool, indicando uma
			estrutura de Method, Field ou InterfaceMethod*/
			u2 reference_index;
		} MethodHandle;
		/*Estrutura representando um tipo de método*/
		struct{
			/*Índice válido em Constant Pool, indicando
			o descritor do método*/
			u2 descriptor_index;
		} MethodType;
		/*Estrutura utilizada pela instrução invokecdynamic*/
		struct{
			/*Índice válido em Bootstrap Methods*/
			u2 bootstrap_method_attr_index;
			/**Índice válido em Constant Pool, indicando
			o nome e o descritor do método*/
    		u2 name_and_type_index;
		} InvokeDynamicInfo;
	}UnionCP;

};
typedef struct cp_info cp_info;

/*Definição de estrutura enum para designar o valor do byte
tag de cada entrada na tabela Constant Pool*/
enum tag_values {

	CONSTANT_Class = 7,
	CONSTANT_Fieldref = 9,
	CONSTANT_Methodref = 10,
	CONSTANT_InterfaceMethodref = 11,
	CONSTANT_String = 8,
	CONSTANT_Integer = 3,
	CONSTANT_Float = 4,
	CONSTANT_Long = 5,
	CONSTANT_Double = 6,
	CONSTANT_NameAndType = 12,
	CONSTANT_Utf8 = 1,
	CONSTANT_MethodHandle = 15,
	CONSTANT_MethodType = 16,
	CONSTANT_InvokeDynamic = 18
};

enum access_flags{
	PUBLIC = 1,
	PRIVATE = 2,
	PROTECTED = 4,
	STATIC = 8,
	FINAL = 16,
	VOLATILE = 64,
	TRANSIENT = 128
};

typedef enum access_flags access_flags;

/*Definição da estrutura de Attributes*/
struct attribute_info {
	/*Índice válido em Constant Pool, indicando
	o nome do atributo*/
	u2 attribute_name_index;
	/*Indica o tamanho, em bytes, do restante
	do atributo*/
	u4 attribute_length;
	/*Array contendo a informação no formato
	String - ANALISAR*/
	void *info;
};
typedef struct attribute_info attribute_info;

/*Definição de estrutura de Field*/
struct field_info{
	/*Denota a permissão de acesso ao field e suas
	propriedades*/
	u2 access_flags;
	/*Índice válido em Constant Pool, indicando
	o nome simples do field*/
	u2 name_index;
	/*Índice válido em Constant Pool, indicando
	o descritor do field*/
	u2 descriptor_index;
	/*Indica o número de atributos adicionais
	deste campo*/
	u2 attributes_count;
	/*Array de estruturas Attribute Info*/
	attribute_info *attributes;
};
typedef struct field_info field_info;

struct exception_table{
	u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

typedef struct exception_table exception_table;

struct line_number_tableInfo {
	u2 start_pc;
	u2 line_number;
};
typedef struct line_number_tableInfo line_number_tableInfo;

struct line_number_table {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 line_number_table_length;
	line_number_tableInfo * info;
};
typedef struct line_number_table line_number_table;

/*Definição de estrutura Code - ANALISAR!*/
struct code_attribute {
	/*Índice válido em Constant Pool, indicando
	a string "Code"*/
  u2 attribute_name_index;
	/*Indica o tamanho do atributo*/
  u4 attribute_length;
	/*Determina a profundidade máxima do operando
	na pilha deste método, em qualquer ponto
	durante a execução deste método*/
  u2 max_stack;
	/*Número de variáveis locais no array de
	variáveis locais alocado na chamada deste
	método, incluindo as variáveis locais utilizadas
	para passar parâmetros para o método*/
  u2 max_locals;
	/*Determina o número de bytes no array do código
	para este método*/
  u4 code_length;
	/*Arrat de bytes designando o código que implementa
	o método*/
  u1 * code;
	/*Número de entrada na tabela de exceções*/
  u2 exception_table_length;
  exception_table * table; // Alocar com exception_table_length
	/*Número de atributos do Code Attribute*/
  u2 attributes_count;
	/*Array de atributos para este Code*/
	union{
		line_number_table * lineNumberTable;
		attribute_info * attributes;
	}UnionCodeAttr;
};
typedef struct code_attribute code_attribute;

/*Definição de estrutura Method*/
struct method_info{
	/*Denota a permissão de acesso ao método
	e suas propriedades*/
	u2 access_flags;
	/*Índice válido em Constant Pool, indicando
	o nome simples do método ou ainda
	o nome do método especial <init> ou <clinit>*/
	u2 name_index;
	/*Índice válido em Constant Pool, indicando
	o descritor do método*/
	u2 descriptor_index;
	/*Indica o número de atributos adicionais
	deste método*/
	u2 attributes_count;
	/*Array de estruturas Attribute Info*/
	union{
		code_attribute * code_attributes;
		attribute_info * attributes;
	}UnionAttr;
};
typedef struct method_info method_info;

struct source_file_attribute {
	u2 source_file_index;
};
typedef struct source_file_attribute source_file_attribute;

/************************************************************/

struct constantValue_attribute {

    u2 constantvalue_index;
};
typedef struct constantValue_attribute constantValue_attribute;


struct exceptions_attribute {

	u2 number_of_exceptions;
	u2 *exception_index_table; 	// Alocar com number_of_exceptions
							   	// Each value in the exception_index
								// table array must be a valid
								// index into the constant_pool table.

};
typedef struct exceptions_attribute exceptions_attribute;

struct classes {
	
	u2 inner_class_info_index;	// Todos essas variaveis devem apontar para constant_pool;
	u2 outer_class_info_index;	// If C is not a member of a class or an interface
								// (that is, if C is a top-level class or interface
								// or a local class or an anonymous class), the value
								// of the outer_class_info_index item must be zero.
	u2 inner_name_index;		// If C is anonymous, the value of the
								// inner_name_index item must be zero.
	
	u2 inner_class_access_flags; // It is used by a compiler to recover the original
								 // information when source code is not available.

};
typedef struct classes classes;

	/* Sobre: inner_class_access_flags
		
		Flag Name     	Value(Decimal)

		ACC_PUBLIC			1
		ACC_PRIVATE			2
		ACC_PROTECTED		4
		ACC_STATIC			8
		ACC_FINAL			16
		ACC_INTERFACE		512
		ACC_ABSTRACT		1024
		ACC_SYNTHETIC		4096
		ACC_ANNOTATION		8192
		ACC_ENUM			16384
	*/

struct innerClasses_attribute{

	u2 number_of_classes;		
	classes *classes_vector; 	// Alocar com number_of_classes;

};
typedef struct innerClasses_attribute innerClasses_attribute;


struct enclosingMethod_attribute {

	u2 class_index;			// The constant_pool entry at that index must be a
							// CONSTANT_Class_info structure representing the
							// innermost class that encloses the declaration
							// of the current class.	
	
	u2 method_index;		// If the current class is not immediately enclosed
							// by a method or constructor, then the value of the
							// method_index item must be zero.	

	// Otherwise, The constant_pool entry at that index must be a
	// CONSTANT_NameAndType_info structure representing the name
	// and type of a method in the class referenced by the class_index attribute above.

};
typedef struct enclosingMethod_attribute enclosingMethod_attribute;


/*struct synthetic_attribute {		// COMO FAZ COM ESSA?

	u2 attribute_name_index;
	u4 attribute_length;		// The value of the attribute_length item is zero.
};
typedef struct synthetic_attribute synthetic_attribute;*/

struct signature_attribute {

	u2 signature_index;			

};
typedef struct signature_attribute signature_attribute;



struct sourceDebugExtension_attribute {

	u1 * debug_extension; 		// Alocar com o tamanho de attribute_length

};
typedef struct sourceDebugExtension_attribute sourceDebugExtension_attribute;


struct local_variable_table {

	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;

};
typedef struct local_variable_table local_variable_table;


struct localVariableTable_attributes {

	u2 local_variable_table_length;
	local_variable_table *local_variables; // Alocar com o tamanho de local_variable_table_length

};
typedef struct localVariableTable_attributes localVariableTable_attributes;



struct localVariableTypeTable {

	u2 local_variable_type_table_length;
	local_variable_table *local_variables; // Alocar com o tamanho de local_variable_table_length

};
typedef struct localVariableTypeTable localVariableTypeTable;


/*struct deprecated_attribute{	// O que fazer com essa estrutura?

	u2 attribute_name_index;
	u4 attribute_length;

};
typedef struct deprecated_attribute deprecated_attribute; */

struct annotation;
struct element_value;

struct element_value{

	u1 tag;
	union{

		u2 const_value_index;
		u2 outer_class_info_index;
		
		struct annotation *annotation_value;	// ISSO DAQUI EH MUITO ERRADO! VERIFICAR

		struct {

			u2 type_name_index;
			u2 const_name_index;

		} enum_const_index;

		struct {
						
			u2 num_values;
			struct element_value *element_values;

		} array_value;

	} value;

};
typedef struct element_value element_value;


struct element_value_pairs {

	u2 element_name_index;
	element_value value;

};
typedef struct element_value_pairs element_value_pairs;


struct annotation {

	u2 type_index;
	u2 num_element_value_pairs;
	element_value_pairs *elementes_pairs;

};
typedef struct annotation annotation;


struct runTimeVisibleAnnotations_attribute {

	u2 num_annotations;
	annotation *annotations;


};
typedef struct runTimeVisibleAnnotations_attribute runTimeVisibleAnnotations_attribute;


struct runTimeInvisibleAnnotations_attribute {

	u2 num_annotations;
	annotation *annotations;	// Alocar com o tamanho de num_annotations;

};
typedef struct runTimeInvisibleAnnotations_attribute runTimeInvisibleAnnotations_attribute;

	
struct parameter_annotations {		// ESSA ESTRUTURA EH IGUAL A DE CIMA.

	u2 num_annotations;
	annotation *annotations;	// Alocar com o tamanho de num_annotations;


};
typedef struct parameter_annotations parameter_annotations;


struct runtimeVisibleParameterAnnotations_attribute {

    u1 num_parameters;
    parameter_annotations *parameters_annotations;	// Alocar com o tamanho de num_parameters;

};
typedef struct runtimeVisibleParameterAnnotations_attribute runtimeVisibleParameterAnnotations_attribute;



struct runtimeInvisibleParameterAnnotations_attribute {

    u1 num_parameters;
	parameter_annotations *parameters_annotations;	// Alocar com o tamanho de num_parameters;

};
typedef struct runtimeInvisibleParameterAnnotations_attribute runtimeInvisibleParameterAnnotations_attribute;


struct annotationDefault_attribute {

    element_value default_value;

};
typedef struct annotationDefault_attribute annotationDefault_attribute;

struct bootstrap_methods {

	u2 bootstrap_method_ref;
	u2 num_bootstrap_arguments;
    u2 *bootstrap_arguments;		// Alocar com o tamanho num_bootstrap_arguments;


};
typedef struct bootstrap_methods bootstrap_methods;


struct bootstrapMethods_attribute {

    u2 num_bootstrap_methods;

    bootstrap_methods *bt_methods; // Alocar com o tamanho de num_bootstrap_methods;

};
typedef struct bootstrapMethods_attribute bootstrapMethods_attribute;



#endif
