#ifndef JOGADOR
#define JOGADOR

#include <stdlib.h>
#define MAX_MAO 21

#include <stdio.h>
/* Interface para lidar apenas um jogador */

typedef struct Jogador * pjog;
typedef struct Jogador {
	/* pos: posição do jogador numa mesa.
	 * hand: o valor de sua mão (a soma de suas cartas)
	 * status: (bool) pode jogar ainda
	 * aces: quantidade de azes o jogador possui */
	int pos;
	int hand;
	int status;
	int aces;
} Jogador;

pjog criar_jogador(int pos);
/* Alocar espaço para uma struct Jogador */

void hit(pjog jogador, int carta);
/* Adiciona o valor de carta à mão do jogador.
 * Confere se ultrapassa o limite de pontos:
 *     sim -> confere a disponinbilidade de áses na mão do jogador.
 *         -> se houver um deles é retirado, passando a valer 1
 *         -> se não houver, é colocado em stand */

void stand(pjog jogador);
/* Coloca o jogador em stand (status = 0) */

int pode_jogar(pjog jogador);
/* Retorna o valor de jogador.status */

void imprimir_mao(pjog jogador);
/* Imprime o valor da mão do jogador.
 * Usado na função imprimir_fila, de fila.h */

void destruir_jogador(pjog jogador);
/* Desaloca uma struct Jogador */

#endif
