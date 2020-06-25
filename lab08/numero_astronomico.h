#ifndef ASTRO
#define ASTRO

#include <stdio.h>

typedef struct No {
	int valor;
	struct No *ant;
	struct No *prox;
} No;

typedef struct No* p_no;

void criar_numero(p_no *ini, p_no *fim);
/* Entrada:
 * p_no *ini -> ponteiro para o p_no inicial (dummy) da lista que representa o
 * numero
 * p_no *fim -> ponteiro para o p_no final (dummy) para a mesma lista */

void add_algarismo(p_no fim, int x);
/* Entrada:
 * p_no fim -> ponteiro para o final da lista.
 * Adiciona um algarismo ao fim do numero, de forma a reproduzí-lo conforme é
 * lido */

void somar(p_no ini1, p_no fim1, p_no ini2, p_no fim2);
/* Entrada:
 * p_no ini1, fim1 -> ponteiros para o primeiro numero a ser somado
 * p_no ini2, fim2 -> ponteiros para o segundo numero */

void imprime_numero(p_no ini, p_no fim);
/* Entrada:
 * p_no ini1, fim1 -> ponteiros para o numero a ser impresso */

void destroi_numero(p_no ini, p_no fim);
/* Entrada:
 * p_no ini1, fim1 -> ponteiros para o numero a ser destruido
 * Saida: int -> booleano para verificar condição de recursão */

#endif
