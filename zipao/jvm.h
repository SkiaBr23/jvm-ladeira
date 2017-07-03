/**
 * @file jvm.h
 * @brief Arquivo cabeçalho contendo funções relacionadas à execução do arquivo
 */

/** Macro para verificar se a biblioteca já foi definida */
#ifndef JVM_H
#define JVM_H

/** Inclusão de bibliotecas necessárias */
#include "lista_classes.h"
#include "pilha_frames.h"
#include "instrucoes.h"

/**
 * @struct lista_objetos
 *
 * @brief Estrutura de dados para armazenar os objetos instanciados
 *
 */
struct lista_objetos {
	ClassFile * obj;
	u1 sizeData;
	u4 * data;
	struct lista_objetos * prox;
	struct lista_objetos * ant;
};
typedef struct lista_objetos Lista_Objetos;

/**
 * @struct jvm
 * @brief Estrutura da jvm, que será utilizada para controlar a execução do programa
 * 
 */
struct jvm{
	classesCarregadas * classes; /**< Ponteiro para a lista de classes carregadas */
	pilha_frames *frames; /**< Ponteiro para a pilha de frames */
	u4 pc; /**< Contador de programa */
	u2 excecao; /**< Flag para indicar se houve alguma exceção */
	Lista_Objetos * objetos; /**< Lista de objetos instanciados */
	char *excecao_nome; /**< Nome da exceção se for lançada */
};
/** Definição do tipo \c JVM */
typedef struct jvm JVM;

/** Declarar as variáveis globais que serão utilizadas no processo de execução */
extern JVM *jvm;
extern instrucao* instrucoes;

/**
 * @brief Função para inicializar a estrutura da JVM com nulo
 * @return Retorna a estrutura da JVM setada para um ponteiro nulo
 */
JVM* CriarJVM();

/**
 * @brief Função para inicializar a estrutura da JVM, alocando os campos da estrutura, e setando os valores iniciais
 * @return A função retorna a estrutura da JVM alocada
 * 
 * @see JVM
 */
JVM* InicializarJVM();

/**
 * @brief Função para apresentar o menu para o usuário
 * @return Retorna um inteiro, representando a opção escolhida pelo usuário
 */
int opcaoMenu();

/**
 * @brief Função para criar um frame e inicializar com os valores default
 * 
 * @param classeCorrente Nome da classe corrente do frame
 * @param max_locals Tamanho do vetor de variáveis locais do frame
 * 
 * @return A função retorna um ponteiro para uma estrutura frame alocada
 * 
 * @see frame
 */
frame* criarFrame(char *classeCorrente, u2 max_locals);

/**
 * @brief A função inicia a interpretação do arquivo .class, chamando outras funções da interpretação
 */
void executarJVM();

/**
 * @brief Função para atualizar o PC, de acordo com a instrução branch previamente executada, verificando se o branch foi executado ou não
 * 
 * @param code Ponteiro para o code do método atual
 * @param length Tamanho do código que deve ser analisado
 * 
 * @return Retorna o valor atualizado de PC
 */
u1 * atualizarPCMetodoAtual (u1 * code, u4 length);

/**
 * @brief Função para imprimir um Atributo Code de um método
 * 
 * @param code Ponteiro para o código que deve ser impresso
 * @param length Tamanho do código que deve ser percorrido
 * 
 * @see code
 */
void ImprimeCode (u1 * code, u4 length);

/**
 * @brief Avalia se a instrução passada como parâmetro é uma instrução do tipo branch
 * 
 * @param nomeInstrucao Nome da instrução sendo analisada
 * @return A função retorna um booleano, indicando se a instrução é uma instrução do tipo branch ou não.
 */
bool instrucaoBranch (char * nomeInstrucao);

/**
 * @brief Função que executa o código de um método
 * 
 * @param m Estrutura method_info representando o método que deve ser executado
 * @param classeCorrente Ponteiro para a classe corrente do método
 * @param chamador Inteiro que é 1 se o chamador foi o arquivo da JVM, 2 se foi uma instrução do tipo invoke que vai executar um método
 */
void executarMetodo(method_info *m, char *classeCorrente, int chamador);

/**
 * @brief Função para interpretar as instruções do Code de um método
 * 
 * @param code Ponteiro para o código que deve ser interpretado
 * @param length Tamanho do código que deve ser interpretado
 * @param m Estrutura representando o método que deve ter seu code interpretado
 */
void interpretarCode(u1 *code, u4 length,method_info *m);

/**
 * @brief Função para liberar o vetor de variáveis locais da memória
 * 
 * @param v Vetor do tipo \c vetor_locais que deve ser desalocado
 * @param vetor_length Tamanho do vetor que deve ser desalocado
 * 
 * @see vetor_locais
 */
void freeVetorLocais(vetor_locais *v, u2 vetor_length);

/**
 * @brief Função para encontrar em um método o PC do handler da exceção lançada na JVM
 * 
 * @param m A estrutura do método no qual o handler da exceção será buscado
 * @return A função retorna o PC do handler do método, ou o número máximo short, caso o handler não seja encontrado
 */
u2 verificaHandlerMetodo(method_info *m);

/** Definição de algumas macros relativas aos nomes e descritores de métodos main, init e clinit */
#define MAIN_NOME "main"
#define DESCRIPTOR_MAIN "([Ljava/lang/String;)V"
#define PUBLIC_STATIC 0x0009
#define CLINIT_NOME "<clinit>"
#define DESCRIPTOR_CLINIT "()V"
#define STATICCLINIT 0x0008
#define INIT_NOME "<init>"
#define DESCRIPTOR_INIT "()V"

#endif
