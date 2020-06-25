/* Tarefa de laborátorio 12 -- MC202 G
 * Alkindar Ferraz Rodrigues -- 154532 */

#include <stdio.h>
#include "heap.h"

void processar_entrada (php cx_grd, php cx_peq);
void mediana (php cx_grd, php cx_peq);

int main () {
	/* caixas:
	 * peq -> armazena os menores valores, a raiz é o maior deles
	 * grd -> armazena os maiores valores, a raiz é o menor deles
	 * Ambos os heaps tem metade do número de elementos informado.
	 */

	int i, n_els;
	php cx_grd, cx_peq;

	scanf("%d", &n_els);


	cx_peq = criar_heap(n_els / 2 +1, 1);
	cx_grd = criar_heap(n_els / 2 +1, 0);

	for (i = 0; i < n_els; i++){
		processar_entrada(cx_grd, cx_peq);
		mediana(cx_grd, cx_peq);
	}

	destruir_heap(cx_grd);
	destruir_heap(cx_peq);

	return 0;
}


void processar_entrada (php cx_grd, php cx_peq) {
	/* Lê uma linha de entrada e cria uma caixa com as informações.
	 * Insere-a na metade correspondente do heap com base na prioridade
	 * do primeiro elemento do heap cx_grd.  Ao fim, garante-se que os
	 * heaps tenham no máximo 1 elemento de diferença. */
	Caixa in;
	char nome[NOME_TAM];
	int peso;

	scanf("%s", nome);
	scanf("%d", &peso);
	in = criar_caixa(nome, peso);

	if (cx_peq->v[0].peso < peso)
		inserir_caixa(cx_grd, in);
	else
		inserir_caixa(cx_peq, in);

	if (cx_peq->n > cx_grd->n + 1) {
		in = remover_caixa(cx_peq);
		inserir_caixa(cx_grd, in);
	}
	if (cx_grd->n > cx_peq->n +1) {
		in = remover_caixa(cx_grd);
		inserir_caixa(cx_peq, in);
	}
}


void mediana (php cx_grd, php cx_peq) {
	/* Imprime dois valores caso ambos tenham o mesmo número de
	 * elementos.  Do contrário, o elemento de maior prioridade do heap
	 * de maior n. */
	if (cx_grd->n == cx_peq->n) {
		imprimir_caixa(cx_peq->v[0]);
		imprimir_caixa(cx_grd->v[0]);
		return;
	}

	if (cx_grd->n > cx_peq->n)
		imprimir_caixa(cx_grd->v[0]);
	else
		imprimir_caixa(cx_peq->v[0]);
}
