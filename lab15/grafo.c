#include "grafo.h"

/* Implementação da fila */
void criar_fila(pno * ini, pno * fim) {
	*ini = malloc(sizeof(No));
	*fim = malloc(sizeof(No));

	if (*ini == NULL || *fim == NULL){
		printf("Falha de alocação.\n");
		exit(1);
	}

	(*ini)->v = DUMMY;
	(*ini)->a = NULL;
	(*ini)->p = *fim;

	(*fim)->v = DUMMY;
	(*fim)->a = *ini;
	(*fim)->p = NULL;
}

void enfilerar(pno fim, int v){
	pno novo = malloc(sizeof(No));

	if (novo == NULL){
		printf("Falha de alocação.\n");
		exit(1);
	}

	novo->v = v;

	fim->a->p = novo;
	fim->a = novo;

	novo->a = fim->a;
	novo->p = fim;
}

int desenfilerar(pno ini) {
	pno aux;
	int v;

	aux = ini->p;
	v = aux->v;

	ini->p = aux->p;
	aux->p->a = ini;

	free(aux);
	return v;
}

int eh_vazia(pno ini, pno fim) {
	if (ini->p == fim)
		return 1;
	return 0;
}

void imprimir_fila(pno ini, pno fim) {
	pno aux;
	for (aux = ini->p; aux != fim; aux = aux->p)
		printf("%d ", aux->v);
}

void destruir_fila(pno ini, pno fim) {
	pno aux, info = NULL;

	for (aux = ini->p; aux != fim; aux = info){
		info = aux->p;
		free(aux);
	}

	free(ini);
	free(fim);
}

/* Interface do grafo */
pgr criar_grafo(int tam) {
	pgr novo;
	int i;

	novo = malloc(sizeof(Grafo));
	if (novo == NULL){
		printf("Falha de alocação.\n");
		exit(1);
	}

	/* Vetor de ponteiros para as linhas da matriz */
	novo->adj = malloc(sizeof(int * ) * tam);
	if (novo->adj == NULL) {
		printf("Falha de alocação.\n");
		exit(1);
	}

	/* linhas da matriz, iniciados com 0 */
	for (i = 0; i < tam; i++){
		novo->adj[i] = calloc(tam, sizeof(int));
		if (novo->adj[i] == NULL){
			printf("Problemas de alocação de memória\n");
			exit(1);
		}
	}
	novo->tam = tam;
	return novo;
}

void inserir_vizinho(pgr g, int p, int q) {
	g->adj[p][q] = 1;
	g->adj[q][p] = 1;
}

void imprime_grafo(pgr g){
	int i, j;
	for (i = 0; i < g->tam; i++){
		printf("%d -> ", i);
		for (j = 0; j < g->tam; j++)
			if (g->adj[i][j])
				printf("%d ", j);
		printf("\n");
	}
}


void destruir_grafo(pgr g) {
	/* Libera todas as linhas da matriz, seguido do vetor de ponteiros que
	 * as armazenava, e por fim o grafo */
	int i;
	for (i = 0; i < g->tam; i++)
		free(g->adj[i]);
	free(g->adj);
	free(g);
}
