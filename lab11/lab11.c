/* Tarefa de laborátorio 11 -- MC202 G
 * Alkindar Ferraz Rodrigues -- 154532 */

#include <time.h>
#include "treap.h"

pno ler_conjunto(int els);

int main () {
	/* Indices e variáveis de controle */
	int n_conjuntos, i;
	int n_els;

	/* Vetor para armazenar conjuntos de entrada */
	pno * conjuntos;

	/* Conjunto da diferença */
	pno diff;

	srand(time(0));

	scanf("%d ", &n_conjuntos);

	conjuntos = malloc(sizeof(pno) * n_conjuntos);
	if (conjuntos == NULL) {
		printf("Não foi possível alocar um vetor para os conjuntos.\n");
		exit(1);
	}

	/* Ler conjuntos com seus respectivos números de elementos, e
	 * salvando-os no vetor de conjuntos */
	for (i = 0; i < n_conjuntos; i++) {
		scanf("%d ", &n_els);
		conjuntos[i] = ler_conjunto(n_els);
	}

	/* Realizar a diferença entre os dois primeiros conjuntos, em
	 * seguida, se houver mais conjuntos no vetor, percorre-lo
	 * executando a diferença entre diff e os demais */
	diff = diferenca(conjuntos[0], conjuntos[1]);
	for (i = 2; i < n_conjuntos; i++)
		diff = diferenca(diff, conjuntos[i]);


	imprimir_treap(diff);
	printf("\n");

	destruir_treap(diff);
	free(conjuntos);
	return 0;
}


pno ler_conjunto(int els) {
	/* A partir do numero de elementos (els), ler e inserir um elemento no
	 * conjunto */
	int i;
	int el;
	pno novo = NULL;

	for(i = 0; i < els; i++){
		scanf("%d", &el);
		novo = inserir_no(novo, el, NULL);
	}
	return novo;
}
