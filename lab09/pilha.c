#include "pilha.h"

void criar_pilha(pcarta *pilha) {
	/* Cria uma cabeça para a pilha. O endereço de memória dela é
	 * armazenado no Stack */
	*pilha = malloc(sizeof(Carta));

	if (*pilha == NULL){
		printf("Não foi possível alocar a pilha de cartas.\n");
		exit(1);
	}

	(*pilha)->ant = NULL;
}

void inserir_carta(pcarta pilha, int valor) {
	pcarta nova;
	nova = malloc(sizeof(Carta));

	if (nova == NULL) {
		printf("Não foi possível adicionar uma carta à pilha.\n");
		exit(1);
	}

	nova->valor = valor;
	nova->ant = pilha->ant;
	pilha->ant = nova;
}

int retirar_carta(pcarta pilha) {
	int carta;
	pcarta aux;

	aux = pilha->ant;
	pilha->ant = aux->ant;
	carta = aux->valor;
	free(aux);

	return carta;
}

void imprimir_pilha(pcarta topo) {
	/* Imprime a pilha a partir do nó mais visível, até chegar ao fim */

	topo = topo->ant;
	while (topo != NULL){
		printf("%d ", topo->valor);
		topo = topo->ant;
	}
	printf("\n");
}

int ver_topo(pcarta pilha) {
	return pilha->ant->valor;
}

void destruir_pilha(pcarta pilha) {
	if (pilha != NULL) {
		destruir_pilha(pilha->ant);
		free (pilha);
	}
}
