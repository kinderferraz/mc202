#ifndef GRAFO
#define GRAFO

#include <stdlib.h>
#include <stdio.h>

#define DUMMY -1

typedef struct No No;
typedef struct No * pno;
struct No {
	int v;
	pno p, a;
};

/* Grafo de matriz de adjacencias */
typedef struct Grafo Grafo;
typedef struct Grafo * pgr;
struct Grafo {
	int ** adj;
	int tam;
};

/* Interface para a fila, necessára para a busca em largura  */

void criar_fila(pno * ini, pno * fim);
	/* Recebe o endereço de dois ponteiros, para inicio e fim da fila,
	 * e constroi uma lista vazia a partir deles */

void enfilerar(pno fim, int v);
	/* Insere um elemento 'v' ao fim da fila */

int desenfilerar(pno ini);
	/* Retorna o elemento ao inicio da fila */

int eh_vazia(pno ini, pno fim);
	/* Retorna um booleano indicando se a lista é vazia */

void imprimir_fila(pno ini, pno fim);
	/* Imprime todos os elementos de uma fila */

void destruir_fila(pno ini, pno fim);
	/* Libera toda a memória utilizada por uma fila */

/* Interface do grafo*/

pgr criar_grafo(int tam);
	/* Retorna um ponteiro para o grafo de tamanho 'tam' recém criado
	 * e inicializado */

void inserir_vizinho(pgr g, int p, int q);
	/* Insere uma aresta, de p a q, no grafo */

void imprime_grafo(pgr g);
	/* Imprime o identificador de cada nó seguido de seus vizinhos */

void destruir_grafo(pgr g);
	/* Desaloca toda a mémoria relacionada ao grafo */

#endif
