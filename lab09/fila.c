#include "fila.h"

void criar_fila(pno *ini, pno *fim) {
	*ini = malloc(sizeof(No));
	*fim = malloc(sizeof(No));
	if (*ini == NULL || *fim == NULL){
		printf("Não foi possível alocar uma cabeça ");
		printf("para a fila de jogadores.\n");
		exit(1);
	}

	(*ini)->a = NULL;
	(*ini)->p = *fim;

	(*fim)->a = *ini;
	(*fim)->p = NULL;

	(*ini)->jogador = NULL;
	(*fim)->jogador = NULL;
}


void inserir_jogador(pno fim, pjog jogador) {
	pno novo;

	novo = malloc(sizeof(No));
	if (novo == NULL) {
		printf("Não foi possível alocar um novo nó à ");
		printf("fila de jogadores.\n");
		exit(1);
	}
	novo->jogador = jogador;
	novo->a = fim->a;
	novo->p = fim;

	novo->a->p = novo;
	fim->a = novo;
}

pjog remover_jogador(pno ini) {
	pno aux;
	aux = ini->p;

	ini->p = aux->p;
	(aux->p)->a = aux->a;

	return aux->jogador;
}

void ordenar_fila(pno ini, pno fim) {
	pjog aux;
	while ((ini->p)->jogador->pos != 0) {
		aux = remover_jogador(ini);
		inserir_jogador(fim, aux);
	}
}


void imprimir_fila(pno ini, pno fim) {
	pno aux;
	for (aux = ini->p; aux != fim; aux = aux->p){
		imprimir_mao(aux->jogador);
	}
}

void destruir_fila(pno ini, pno fim) {
	/* Aux: pno para um nó a ser removido.  Info: o nó seguinte a aux,
	 * passado para aux na atualização do loop */
	pno aux, info;
	info = NULL;

	for (aux = ini->p; aux != fim; aux = info) {
		info = aux->p;
		destruir_jogador(aux->jogador);
		free(aux);
	}
	
	free(ini);
	free(fim);
}
