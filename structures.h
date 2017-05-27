#ifndef	STRUCTURES_H
#define STRUCTURES_H

/**

	Nesse arquivo, sera definido as estruturas que sao utilizadas na constant_pool.


	Para o constante_pool temos que:
	-	Informacoes simbolicas sao salvas no constant_pool.
	-	Cada entrada em constant_pool tem a forma:
			cp_info{
				
				u1 tag;			// O byte tag define o tipo de informacao
				u1 info[];		// 
			}
		Lembrando que:
			u1 = typedef unsigned char;		// u1 = uint8_t
			u2 = typedef unsigned short; 	// u2 = uint16_t
			u4 = typedef unsigned int;		// u4 = uint32_t

	- 	Valores para tag:
			CONSTANT_Class 					7
			CONSTANT_Fieldref 				9
			CONSTANT_Methodref 				10
			CONSTANT_InterfaceMethodref 	11
			CONSTANT_String					8
			CONSTANT_Integer				3
			CONSTANT_Float 					4
			CONSTANT_Long					5
			CONSTANT_Double					6
			CONSTANT_NameAndType			12
			CONSTANT_Utf8					1
			CONSTANT_MethodHandle	15
			CONSTANT_MethodType	16
			CONSTANT_InvokeDynamic	18

*/

#include <stdint.h>		// Biblioteca para definicao do tamanho de um inteiro.

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

#define MAXU1 255
#define MAXU2 65535
#define MAXU4 2147483647


// CADA entrada na constant_pool possui a forma (O que seria info[]?):
struct cp_info{	

	u1 tag;
	union{
		struct{
			u2 name_index;
		} Class;

		struct{
			u2 class_index;
			u2 name_and_type_index;
		} Fieldref;

		struct{
			u2 class_index;
			u2 name_and_type_index;
		} Methodref;

		struct{
			u2 class_index;
			u2 name_and_type_index;
		} InterfaceMethodref;

		struct{	
			u2 string_index;
		} String;

		struct{
			u2 bytes;
		} Integer;

		struct{
			u4 bytes;
		} Float;

		struct{
			u4 high_bytes;
			u4 low_bytes;
		} Long;

		struct{
			u4 high_bytes;
			u4 low_bytes;
		} Double;

		struct{
			u2 name_index;
			u2 descriptor_index;
		} NameAndType;

		struct{
			u2 length;
			u1 *bytes;
		} UTF8;

		struct{
			u1 reference_kind;
			u2 reference_index;
		} MethodHandle;

		struct{
			u2 descriptor_index;
		} MethodType;

		struct{
			u2 bootstrap_method_attr_index;
    		u2 name_and_type_index;
		} InvokeDynamicInfo;
	}UnionCP;

};
typedef struct cp_info cp_info;

	
enum tag_values{			// Essas sao os tipos de estruturas que serao salvas no constant_pool.
							// DUVIDA: Nesse caso, definiremos uma estrutura para cada CONSTANT.
							// 		   dessa forma, ainda usaremos cp_info? Nao entendi...
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

struct attribute_info{
	u2 attribute_name_index;
	u4 attribute_length;
	u1 *info;
};

typedef struct attribute_info attribute_info;

struct field_info{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info *attributes;
};

typedef struct field_info field_info;

struct method_info{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info *attributes;
};

typedef struct method_info method_info;

struct code_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code; // Alocar com code_length
    u2 exception_table_length;
    /*{   u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
    } *exception_table;*/ // Alocar com exception_table_length
    u2 attributes_count;
    attribute_info *attributes; // Alocar com attributes_count
};

typedef struct code_attribute code_attribute;

#endif