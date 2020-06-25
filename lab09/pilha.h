#ifndef PILHA
#define PILHA

#include <stdlib.h>
#include <stdio.h>

/* Interface para lidar com as Cartas  */
typedef struct Carta Carta;
typedef struct Carta * pcarta;
struct Carta {
	int valor;
	pcarta ant;
};

void criar_pilha(pcarta *pilha);
/* Aloca uma Carta cabeça para a pilha.
 * Recebe recebe um ponteiro para pilha, guradado no stack */

void inserir_carta(pcarta pilha, int valor);
/* Insere uma Carta imediatamente antes da cabeça da pilha. */

int retirar_carta(pcarta pilha);
/* Retira a carta imediatamente anterior à cabeça */

void imprimir_pilha(pcarta pilha);
/* Imprime a pilha de Cartas. Pensada para uso no gdb */

int ver_topo(pcarta pilha);
/* Imprime o primeiro valor da pilha. Pensada para uso no gdb */

void destruir_pilha(pcarta pilha);
/* Desaloca toda a pilha de Cartas. */


#endif
