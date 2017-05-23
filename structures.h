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

*/

#include <stdint.h>		// Biblioteca para definicao do tamanho de um inteiro.


// CADA entrada na constant_pool possui a forma (O que seria info[]?):
struct cp_info{	

	uint8_t tag;
	uint8_t info[];			// VERIFICAR COMO DEFINIR UM PADRAO PARA CRIACAO DE VETOR NAS ESTRUTURAS.

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
};


struct CONSTANT_Class
{
	uint8_t tag; 							// Valor de tag = 7
	uint16_t name_index;

};
typedef struct CONSTANT_Class CONSTANT_Class_info;


struct CONSTANT_Fieldref
{
	uint8_t tag; 							// Valor de tag = 9
	uint16_t class_index;
	uint16_t name_and_type_index;
};
typedef struct CONSTANT_Fieldref CONSTANT_Fieldref_info;


struct CONSTANT_Methodref
{
	uint8_t tag; 							// Valor de tag = 10
	uint16_t class_index;
	uint16_t name_and_type_index;

};
typedef struct CONSTANT_Methodref CONSTANT_Methodref_info;


struct CONSTANT_InterfaceMethodref
{
	uint8_t tag; 							// Valor de tag = 11
	uint16_t class_index;
	uint16_t name_and_type_index;

};
typedef struct CONSTANT_InterfaceMethodref CONSTANT_InterfaceMethodref_info;


struct CONSTANT_String
{
	uint8_t tag; 							// Valor de tag = 8
	uint16_t string_index;
	
};
typedef struct CONSTANT_String CONSTANT_String_info;


struct CONSTANT_Integer
{
	uint8_t tag; 							// Valor de tag = 3
	uint16_t bytes;

};
typedef struct CONSTANT_Integer CONSTANT_Integer_info;


struct CONSTANT_Float
{
	uint8_t tag; 							// Valor de tag = 4
	uint16_t bytes;

};
typedef struct CONSTANT_Float CONSTANT_Float_info;


struct CONSTANT_Long
{
	uint8_t tag; 							// Valor de tag = 5
	uint16_t high_bytes;
	uint16_t low_bytes;

};
typedef struct CONSTANT_Long CONSTANT_Long_info;


struct CONSTANT_Double
{
	uint8_t tag; 							// Valor de tag = 6
	uint16_t high_bytes;
	uint16_t low_bytes;

};
typedef struct CONSTANT_Double CONSTANT_Double_info;


struct CONSTANT_NameAndType
{
	uint8_t tag; 							// Valor de tag = 12
	uint16_t name_index;
	uint16_t descriptor_index;

};
typedef struct CONSTANT_NameAndType CONSTANT_NameAndType_info;


struct CONSTANT_Utf8
{
	uint8_t tag; 							// Valor de tag = 1
	uint16_t length;
	uint16_t bytes[length];					// VERIFICAR COMO DEFINIR UM PADRAO PARA CRIACAO DE VETOR NAS ESTRUTURAS.

};
typedef struct CONSTANT_Utf8 CONSTANT_Utf8_info;