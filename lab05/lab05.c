/* Tarefa de laborátorio 05 -- MC202 G
Alkindar Ferraz Rodrigues -- 154532 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30

typedef struct pes {
	char nome[30];
	int telefone;
} pessoa;

pessoa cria_pessoa (char nome[], int telefone);
void adiciona_pessoa (pessoa *lista, pessoa pessoa, int c);
pessoa *dobra_lista (pessoa *lista, int n);
pessoa *ordena_lista (pessoa *lista, int fim);
void imprime_ganhador (pessoa *lista, int ganhador);
int checa_fim (char nome[], char const fim[]);


int main () {
	int n, c;
	char nome[MAX];
	int telefone;
	int ganhador;
	pessoa pessoa;
	struct pes *lista;

	n = 4;
	c = 0;
	lista = malloc(n * sizeof(pessoa));

	while (1) {
		scanf(" %s", nome);
		if (checa_fim(nome, "fim")) {
			break;
		}
		scanf(" %d", &telefone);

		pessoa = cria_pessoa(nome, telefone);
		adiciona_pessoa(lista, pessoa, c);
		c++;

		if (c == n){
			n *= 2;
			lista = dobra_lista(lista, n);
		}
	}

	lista = ordena_lista(lista, c);
	scanf(" %d", &ganhador);
	imprime_ganhador(lista, ganhador);

	free(lista);
	return 0;
}

pessoa cria_pessoa (char nome[], int telefone) {
	pessoa nova;

	strcpy(nova.nome, nome);
	nova.telefone = telefone;

	return nova;
}

void adiciona_pessoa(pessoa *lista, pessoa pessoa, int i) {
	lista[i] = pessoa;
}

pessoa *dobra_lista(pessoa *lista, int n){
	pessoa *lst;
	int i;

	lst = malloc(n * sizeof(pessoa));

	for (i = 0; i < n; i ++){
		lst[i] = lista[i];
	}
	free(lista);
	return lst;
}

pessoa *ordena_lista(pessoa *lista, int c) {
	/*bubblesort*/
	int k, j;
	pessoa aux;

	for (k = 1; k < c; k++) {
		for (j = 0; j < c - 1; j++) {
			if (lista[j].telefone > lista[j + 1].telefone) {
				aux = lista[j];
				lista[j] = lista[j + 1];
				lista[j + 1] = aux;
			}
		}
	}
	return lista;
}



void imprime_ganhador(pessoa *lista, int fim) {
	printf("%s %d\n", lista[fim-1].nome, lista[fim-1].telefone);
}

int checa_fim(char nome[], char const fim[]) {
	int i;
	i = 0;

	while (nome[i] != '\0') {
		i++;
	}

	if (i > 4) {
		return 0;
	}

	for (i = 0; i < 3; i++){
		if (nome[i] != fim[i]){
			return 0;
		}
	}
	return 1;
}
