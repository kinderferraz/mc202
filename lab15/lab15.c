/* Tarefa de laborátorio 15 -- MC202 G
 * Alkindar Ferraz Rodrigues -- 154532
 * Grafos II */

#include "grafo.h"
#define NAO_MARCADO -1

void ler_grupos(pgr g, int n_grupos);
void resetar_vetor(int * v, int n);
void busca_largura(pgr g, int id, int * distancias);
void imprime_distancias(int * v, int n);

int main () {
	pgr grafo;
	int n, k;
	int i;
	int * distancias;

	scanf("%d %d", &n, &k);
	grafo = criar_grafo(n);

	ler_grupos(grafo, k);

	distancias = malloc(sizeof(int) * grafo->tam);
	resetar_vetor(distancias, grafo->tam);
	for (i = 0; i < grafo->tam; i++){
		busca_largura(grafo, i, distancias);
		imprime_distancias(distancias, grafo->tam);
		resetar_vetor(distancias, grafo->tam);
	}
	free(distancias);

	return 0;
}

void ler_grupos(pgr g, int n_grupos) {
	/* Lê todos os grupos ('n_grupos'), e constrói o grafo com base
		 nisso */
	int i, j, k;
	int n;
	int * grupo;


	for (i = 0; i < n_grupos; i++){
		/* n de pessoas por grupo */
		scanf("%d", &n);

		grupo = malloc(sizeof(int) * n);
		if (grupo == NULL){
			printf("Falha de alocação.\n" );
			exit(1);
		}

		for (j = 0; j < n; j++)
			scanf("%d", &grupo[j]);

		/* Caso n seja maior que um, e portanto haja um grupo, as duplas
		 * são formadas percorrendo o vetor de trás pra frente, com dois
		 * índices diferentes. */
		if (n > 1) {
			for (j = n - 1; j > 0; j--)
				for (k = j - 1 ; k >= 0; k--)
					inserir_vizinho(g, grupo[j], grupo[k]);
		}
		free(grupo);
	}
}

void resetar_vetor(int * v, int n) {
	/* Reinicia todas as posições do vetor para a constante de NAO_MARCADO */
	int i;
	for (i = 0; i < n; i++)
		v[i] = NAO_MARCADO;
}

void busca_largura(pgr g, int id, int * distancias) {
	/* id       -> raiz sendo pesquisada
	 * ini, fim -> fila de pendencias
	 * v        -> vértice sendo analizado
	 * visitado -> flags para vertices já encontrados
	 * pai      -> vizinho de v que possui o menor caminho a id */
	pno ini, fim;
	int v;
	int i;
	int * visitado, * pai;

	pai = calloc(g->tam, sizeof(int));
	if (pai == NULL){
		printf("Problemas de alocação.\n");
		exit(1);
	}

	visitado = calloc(g->tam, sizeof(int));
	if (visitado == NULL){
		printf("Problemas de alocação.\n");
		exit(1);
	}

	criar_fila(&ini, &fim);
	enfilerar(fim, id);

	pai[id] = id;
	distancias[id] = 0;
	visitado[id] = 1;

	/* Para cada vizinho v desenfilerado, enfilerar seus vizinhos, e
	 * marcar o pai destes como v, as distâncias destes como
	 * distancia[v] + 1 */
	while (!eh_vazia(ini, fim)) {
		v = desenfilerar(ini);
		for (i = 0; i < g->tam; i++){
			if (g->adj[v][i] && !visitado[i]){
				visitado[i] = 1;
				pai[i] = v;
				distancias[i] = distancias[pai[i]] + 1;
				enfilerar(fim, i);
			}
		}
	}
	destruir_fila(ini, fim);
	free(pai);
	free(visitado);
}


void imprime_distancias(int * v, int n) {
	/* Para o vetor de distancias encontrado, imprime o identificador dos
	 * vértices para os quais não há caminho, seguido de um traço e a maior
	 * distancia entre o vertice raiz e qualquer outro vertice */
	int i;
	int maior = 0;

	for (i = 0; i < n; i++){
		if (v[i] == NAO_MARCADO)
			printf("%d ", i);
		if (v[i] > maior)
			maior = v[i];
	}
	printf("- %d\n", maior);
}
