#ifndef FILA
#define FILA

#include <stdlib.h>
#include <stdio.h>
#include "jogador.h"

/* Interface para lidar com a fila de jogadores */
typedef struct No No;
typedef struct No* pno;

struct No {
	/* jogador: jogador,
	 * a: anterior
	 * p:proximo */
	pjog jogador;
	pno a;
	pno p;
};

void criar_fila(pno *ini, pno *fim);
/* Aloca duas cabeças da fila de jogadores, a partir de referencias a
 * elas no Stack */

void inserir_jogador(pno fim, pjog jogador);
/* Insere um novo No ao fim da fila.
 * pjog jogador é um ponteiro retornado por criar_jogador */

pjog remover_jogador(pno ini);
/* Remove o jogador ao início da fila */

void ordenar_fila(pno ini, pno fim);
/* Rotaciona os jogadores até que eles ocupem as posições iniciais.
 * Assume que a ordem geral deles não foi alterada (isto é, o jogador
 * 2 está entre o 1 e o 3) */

void imprimir_fila(pno ini, pno fim);
/* Imprime o valor das mãos dos jogadores, na ordem como se
	 encontram. */

void destruir_fila(pno ini, pno fim);
/* Destroi toda a fila de jogadores: os nós internos e as cabeças */

#endif
