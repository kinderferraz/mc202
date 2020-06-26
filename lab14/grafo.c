#include "grafo.h"

pno criar_lista() {
	/* Retona uma lista vazia */
	return NULL;
}

pno inserir_lista(pno lista, int v) {
	pno novo;
	novo = malloc(sizeof(No));
	if (novo == NULL)
		exit(1);

	novo->viz = v;
	novo->prox = lista;

	return novo;
}

void destruir_lista(pno lista) {
	if (lista == NULL)
		return;
	else {
		destruir_lista(lista->prox);
		free(lista);
	}
}

pgr criar_grafo(int tam) {
	pgr novo;
	int i;
	novo = malloc(sizeof(Grafo));

	if (novo == NULL)
		exit(1);

	/* todas as idades marcadas com 0 */
	novo->idades = calloc(tam, sizeof(int));
	if (novo->idades == NULL)
	 	exit(1);

	novo->v = malloc(sizeof(pno) * tam);
	if (novo->v == NULL)
		exit(1);

	/* Cria uma lista de adjacencia para cada posição do grafo */
	for (i = 0; i < tam; i++)
		novo->v[i] = criar_lista();

	novo->tam = tam;
	return novo;
}

void inserir_idade(pgr grafo, int p, int i) {
	grafo->idades[p] = i;
}

void inserir_relacao(pgr grafo, int p, int q) {
	grafo->v[p] = inserir_lista(grafo->v[p], q);
	grafo->v[q] = inserir_lista(grafo->v[q], p);
}

void destruir_grafo(pgr grafo) {
	int i;
	for (i = 0; i < grafo->tam; i++)
		destruir_lista(grafo->v[i]);

	free(grafo->v);
	free(grafo->idades);
	free(grafo);
}
