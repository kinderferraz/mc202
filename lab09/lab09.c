/* Tarefa de laborátorio 09 -- MC202 G
Alkindar Ferraz Rodrigues -- 154532
Blackjack */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"
#include "jogador.h"

#define PREP_ROUNDS 2
#define MAX_BUFFER 3

void iniciar_deck (pcarta * deck, int n_c);
void iniciar_fila (pno * ini, pno * fim, int n_jogs);

int main () {
	/* Fila de jogadores, ponteiros auxiliares para jogador e deck de cartas */
	pno fila_i, fila_f;
	pjog jogando;
	pcarta deck;

	/* Variáveis para receber as leituras da entrada */
	int n_cartas, n_jogadores;
	char acao[MAX_BUFFER];
	int valor;


	/* Genéricos: Indíces para os loops e sentinelas */
	int i, jogs;

	scanf("%d ", &n_cartas);
	scanf("%d", &n_jogadores);

	/* Criar e ler a pilha de cartas e */
	iniciar_deck(&deck, n_cartas);
	iniciar_fila(&fila_i, &fila_f, n_jogadores);


	/* Primeiras duas rodadas para cada jogador */
	for (i = 0; i < PREP_ROUNDS; i++){
		for (jogs = 0; jogs <= n_jogadores; jogs++) {
			jogando = remover_jogador(fila_i);
			valor = retirar_carta(deck);
			hit(jogando, valor);
			inserir_jogador(fila_f, jogando);
		}
	}

	/* Loop principal, termina com a ordem '#' */
	scanf("%s", acao);
	while (acao[0] != '#') {

		/* Avalia se o dealer está inserindo carta na pilha */
		if (isdigit(acao[0])){
			inserir_carta(deck, atoi(acao));
			scanf("%s", acao);
			continue;
		} else if (acao[0] == 'V' || acao[0] == 'D' || acao[0] == 'R') {
			inserir_carta(deck, 10);
			scanf("%s", acao);
			continue;
		} else if (acao[0] == 'A') {
			inserir_carta(deck, 1);
			scanf("%s", acao);
			continue;
		}

		/* Retirar o próximo jogador e conferir se ele está em stand
		 * (status != 0) e procurar o próximo */
		i = 0;
		jogando = remover_jogador(fila_i);
		while (pode_jogar(jogando) == 0 && i <= n_jogadores) {
			inserir_jogador(fila_f, jogando);
			jogando = remover_jogador(fila_i);
			i ++;
		}

		/* Ações principais do jogo; HIT e STAND */
		if (acao[0] == 'H') {
				valor = retirar_carta(deck);
				hit(jogando, valor);

		} else if (acao[0] == 'S')
			stand(jogando);

		inserir_jogador(fila_f, jogando);
		scanf("%s", acao);
	}

	/* Ordenar a fila e imprimí-la */
	ordenar_fila(fila_i, fila_f);
	imprimir_fila(fila_i, fila_f);

	destruir_pilha(deck);
	destruir_fila(fila_i, fila_f);

	return 0;
}

void iniciar_deck(pcarta *deck, int n_c) {
	/* Inicia o deck de cartas e lê os valores de entrada a serem incluidos */
	char carta[MAX_BUFFER];
	int i, valor;

	criar_pilha(deck);

	for (i = 0; i < n_c; i++){
		scanf("%s", carta);

		/* a carta é um dígito?*/
		if (isdigit(carta[0]))
			valor = atoi(carta);
		
		/* Família real */
		else if (carta[0] != 'A')
			valor = 10;

		/* Ás */
		else
			valor = 1;
		
		inserir_carta(*deck, valor);
	}

}

void iniciar_fila (pno * ini, pno * fim, int n_jogs) {
	/* Inicia a fila de jogadores e adiciona um jogador em sua devida posição.
	 * O jogador de posição = n_jogs é o dealer. */
	pjog novo;
	int i;

	criar_fila(ini, fim);
	for(i = 0; i <= n_jogs; i++) {
		novo = criar_jogador(i);
		inserir_jogador(*fim, novo);
	}
}
