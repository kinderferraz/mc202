#ifndef GRAFO
#define GRAFO

#include <stdlib.h>
#include <stdio.h>

typedef struct No No;
typedef struct No * pno;
struct No {
	int viz;
	pno prox;
};

typedef struct Grafo Grafo;
typedef struct Grafo * pgr;
struct Grafo {
	int * idades;
	pno * v;
	int tam;
};

pno criar_lista();
	/* Cria uma lista ligada, a ser usada pelo vetor de adjacencias */

pno inserir_lista(pno lista, int v);
	/* Insere um elemento na lista */

void destruir_lista(pno lista);
	/* Libera a memória ocupada numa lista */

pgr criar_grafo(int tam);
	/* Cria um grafo, alocando os dois vetores necessários */

void inserir_idade(pgr grafo, int p, int i);
	/* Insere uma idade (i) relativa à pessoa (p), no vetor de idades do
		 grafo */

void inserir_relacao(pgr grafo, int p, int q);
	/* Insere uma adjacencia entre as pessoas p e q, de modo simétrico */

void destruir_grafo(pgr grafo);
	/* Libera toda a memória ocupada pelo grafo */

#endif
