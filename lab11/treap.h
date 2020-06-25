#ifndef TREAP
#define TREAP

#include <stdlib.h>
#include <stdio.h>

typedef struct No No;
typedef struct No * pno;

struct No {
	int dado;
	int pri;
	pno pai, esq, dir;
};

pno criar_no(int dado, pno pai);
	/* Cria uma folha da treap, a partir de um dado e um nó pai.
	 * Chamada pela função inserir nó */

pno inserir_no(pno raiz, int dado, pno pai);
	/* Insere nós numa treap.  Se ela ainda não existir, raiz e pai
	 * devem ser chamados como NULL */

pno buscar(pno raiz, int dado);
	/* Se dado existir na treap, este nó é retornado,
	 * Do contrário, retorna NULL */

pno girar_esq(pno raiz);
	/* Performa uma rotação à esquerda entre um nó e seu filho à
	 * direita.  Função para uso interno à inserir nó */

pno girar_dir(pno raiz);
	/* Performa uma rotação à direita entre um nó e seu filho à
	 * esquerda.  Função para uso interno à inserir nó */

pno minimo(pno treap);
	/* Retorna um ponteiro para o nó de menor valor */

pno sucessor(pno x);
	/* Retorna o ponteiro para o sucessor de um nó */

pno ancestral_direita(pno x);
	/* Retorna um ponteiro para o ancestral de maior valor de um nó */

pno diferenca(pno conj1, pno conj2);
	/* Retorna uma nova treap, constituída pela diferença entre 2
	 * conjuntos.  Os dois conjuntos de entrada são destruídos ao fim do
	 * processo */

void imprimir_treap(pno raiz);
	/* Imprime uma treap em ordem decrescente */

void destruir_treap(pno raiz);
	/* Destroi completamente uma treap */

#endif
