/* Tarefa de laborátorio 14 -- MC202 G
 * Alkindar Ferraz Rodrigues -- 154532
 * grafos I */

#include "grafo.h"
#define TRES 3
 	/* Constante: tamanho do ciclo desejado */

void ler_idades(pgr grafo);
	/* Lê as idades e as insere no grafo */

void ler_relacoes(pgr grafo, int r);
	/* Lê uma relação de vizinhança e a insere no grafo */

void marcar_entediados(pgr grafo, int * entediados);
	/* Entrada -> grafo
	 * Saida   -> entediados: vetor de booleanos */

void imprimir_entediados(int * vetor, int n);
	/* Para cada posição do vetor retornado por marcar_entediados, imprime
	 * índice da posição se estiver marcada. */

int main () {
	pgr festa;
	int p, r;
	int * entediados;

	scanf("%d %d", &p, &r);
	festa = criar_grafo(p);

	ler_idades(festa);
	ler_relacoes(festa, r);

	entediados = calloc(p, sizeof(int));
	if (entediados == NULL)
		exit(1);

	marcar_entediados(festa, entediados);
	imprimir_entediados(entediados, p);

	free(entediados);
	destruir_grafo(festa);

	return 0;
}

void ler_idades(pgr grafo) {
	int i, idade;
	for (i = 0; i < grafo->tam; i++) {
		scanf("%d", &idade);
		inserir_idade(grafo, i, idade);
	}
}

void ler_relacoes(pgr grafo, int r) {
	int p, q;
	int i;
	for (i = 0; i < r; i++) {
		scanf("%d %d", &p, &q);
		inserir_relacao(grafo, p, q);
	}
}

void imprimir_entediados(int * vetor, int n) {
	int i;
	for (i = 0; i < n; i++)
		if (vetor[i])
			printf("%d\n", i);
}

int tedio(pgr grafo, int * trio) {
	/* Calcula o tédio de um dado trio:
	 * Saida -> BOOLEANO */
	double media = 0;
	int i;

	for (i = 0; i < 3; i++)
		media += grafo->idades[trio[i]];
	media /= 3;

	for (i = 0; i < 3; i++)
		if (media > 2 * grafo->idades[trio[i]] )
			return 1;
	return 0;
}

void identificar_trios(pgr grafo, int i, int c, int * trio, int * vetor){
	/* Entrada:
	 *    i -> posição da pessoa em questão
	 *    c -> contador, para que o caminho não seja maior do que a
	           constante TRES */
	int t; /* "tédio" -> Bool */
	pno aux;

	trio[c] = i;

	/* Quando o caminho estiver cheio, verifica se é um ciclo
	 * se sim, calcula o tédio do trio e marca-os se necessário */
	if (c == TRES){
		if (trio[0] == trio[TRES]) {
			t = tedio(grafo, trio);
			if (t)
				for (i = 0; i < TRES; i++)
					vetor[trio[i]] = 1;
		}
		return;
	}

	/* para cada vizinho da pessoa i, verificar se ela está em um trio */
	for (aux = grafo->v[i]; aux != NULL; aux = aux->prox){
		identificar_trios(grafo, aux->viz, c+1, trio, vetor);
	}
}

void marcar_entediados(pgr grafo, int * entediados) {
	/* trio: vetor de 4 posições, marca o caminho percorrido */
	int i;
	int * trio;

	trio = malloc(sizeof(int) * TRES + 1);
	for (i = 0; i < TRES + 1; i++)
		trio[i] = -1;

	for (i = 0; i < grafo->tam; i++){
		identificar_trios(grafo, i, 0, trio, entediados);
	}
}
