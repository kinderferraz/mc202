#include "jogador.h"

pjog criar_jogador(int pos) {
	pjog novo;
	novo = malloc(sizeof(Jogador));
	if (novo == NULL){
		printf("Não foi possível alocar uma struct Jogador.");
		exit(1);
	}

	novo->status = 1;
	novo->pos = pos;
	novo->hand = 0;
	novo->aces = 0;

	return novo;
}

void hit(pjog jogador, int carta) {
	/* se a nova carta não for um ás*/
	if (carta != 1)
		jogador->hand += carta;

	else {
		jogador->aces++;
		jogador->hand += 11;
	}

	/* se ele passar de 21, fica em stand se não puder diminuir sua mão
		 em 10 */
	if (jogador->hand >= MAX_MAO) {
		if (jogador->hand != MAX_MAO && jogador->aces > 0){
			jogador->hand -= 10;
			jogador->aces--;
		} else {
			stand(jogador);
		}
	}
}

void stand(pjog jogador) {
	jogador->status = 0;
}

int pode_jogar(pjog jogador) {
	return jogador->status;
}


void imprimir_mao(pjog jogador) {
	printf("%d\n", jogador->hand);
}


void destruir_jogador(pjog jogador) {
	free(jogador);
}
