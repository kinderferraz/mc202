#ifndef HEAP
#define HEAP

#define NOME_TAM 21

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Caixa {
	int peso;
	char nome[NOME_TAM];
} Caixa;


typedef struct Heap Heap;
typedef Heap * php;

struct Heap {
	/* max -> Bool: o heap é ordenado de forma "decrescente"
	 * tam -> tamanho maximo do vetor
	 * n   -> numero de elementos alocados
	 * v   -> ponteiro para a sequencia de caixas armazenadas */
	int max;
	int n, tam;
	Caixa * v;
};

Caixa criar_caixa (char * nome, int peso);
	/* Entrada:
	 *    nome -> string a ser associada ao nome da caixa
	 *    peso -> peso da caixa, tido como a chave de prioridade
	 */

php criar_heap(int tam, int dec);
	/*Entrada:
	 *    tam -> numero de elementos maximo que o heap vai receber.
	 *    dec -> a maneira como heap vai se comportar, dando 
               prioridade aos elementos de menor (heap min, 0) 
               ou maior (heap max, 1) valor
	 */

void inserir_caixa(php heap, Caixa caixa);
	/* Insere uma caixa no heap na posição adequada. */

int ver_raiz(php heap);
	/* Retorna a prioridade da raiz do heap, sem removê-la. */

void trocar_raiz(php heap_max, php heap_min);
	/* Troca a raiz de dois heaps.  A ordem dos parametros importa, eles
	 * precisam se comportar como pedido */

Caixa remover_caixa(php heap);
	/* Retorna a caixa com a maior prioridade do heap, e faz os ajustes
	 * necessários de acordo com o critério de prioridade. */

void imprimir_caixa (Caixa cx);
	/* Imprime uma caixa, no formato -> "nome": "peso" */

void destruir_heap(php heap);
	/* Libera toda memória associada a um determinado heap */

#endif
