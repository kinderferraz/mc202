#include "heap.h"

/* Funções Auxialiares
 * pai     -> dado um indice, retorna o pai
 * filho_* -> dado um indice, retorna seu filho
 * trocar  -> troca dois elementos de posição no vetor de um heap
 * subir_elemento -> troca um elemento com seu pai 
 *                   (se necessário) -- para heap max e min

 * === FUNÇÃO IMPLEMENTADA PARA HEAP MAX E MIN ===
 *     descer_elemento_min -> troca um elemento com seu menor filho
 *     descer_elemento_max -> troca um elemento com seu maior filho

 * === OBS === 
 * Estou ciente do uso de variáveis desnecessárias, mas sem elas
 * o código estava denso e cheio de informação, o que dificulta
 * a leitura */

int pai (int i) {
	return (i - 1) / 2;
}

int filho_esq (int i) {
	return 2 * i + 1;
}

int filho_dir (int i) {
	return 2 * i + 2;
}

void trocar (Caixa * cx1, Caixa * cx2) {
	Caixa tmp = *cx1;
	*cx1 = *cx2;
	*cx2 = tmp;
}

void subir_elemento (php heap, int i) {
	int p = pai(i);
	int peso = heap->v[i].peso;
	int peso_p = heap->v[p].peso;

	if (i > 0 && peso_p > peso && !heap->max) {
		trocar(&heap->v[i], &heap->v[p]);
		subir_elemento(heap, p);
	}
	if (i > 0 && peso_p < peso &&  heap->max) {
		trocar(&heap->v[i], &heap->v[p]);
		subir_elemento(heap, p);
	}
}

void descer_elemento_min(php heap, int i) {
	/* Procedimento adotado na também função descer_elemento_max, com
	 * critérios deferentes.  Caso exista algum filho (primeiramente o
	 * esqerdo), assume-se que ele tem prioridade maior que seu pai. A
	 * prioridade do filho diretio é testada. Se a prioridade dos filhor
	 * for maior que a do pai, eles são trocados e a função é chamada
	 * para o novo filho. */
	int menor_f;
	int f_esq = filho_esq(i);
	int f_dir = filho_dir(i);

	if (f_esq < heap->n)
		menor_f = f_esq;
	else
		return;

	if (f_dir < heap->n &&
			heap->v[menor_f].peso > heap->v[f_dir].peso)
		menor_f = f_dir;

	if (heap->v[i].peso > heap->v[menor_f].peso) {
		trocar(&heap->v[i], &heap->v[menor_f]);
		descer_elemento_min(heap, menor_f);
	}
}

void descer_elemento_max(php heap, int i) {
	int maior_f;
	int f_esq = filho_esq(i);
	int f_dir = filho_dir(i);

	if ( f_esq < heap->n)
		maior_f = f_esq;
	else
		return;

	if (f_dir < heap->n &&
			heap->v[maior_f].peso < heap->v[f_dir].peso)
		maior_f = f_dir;

	if (heap->v[i].peso < heap->v[maior_f].peso) {
		trocar(&heap->v[i], &heap->v[maior_f]);
		descer_elemento_max(heap, maior_f);
	}
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DISPONIBILIZADAS */
Caixa criar_caixa (char * nome, int peso) {
	Caixa novo;
	novo.peso = peso;
	strcpy(novo.nome, nome);
	return novo;
}

php criar_heap(int tam, int max) {
	php novo;
	novo = malloc(sizeof(Heap));

	if (novo == NULL){
		printf("Não foi possível alocar o Heap.");
		exit(1);
	}

	novo->v = malloc(sizeof(Caixa) * tam);
	if (novo->v == NULL) {
		printf("Problemas para alocar um v de caixas.\n");
		exit(1);
	}

	novo->tam = tam;
	novo->n = 0;
	novo->max = max;

	return novo;
}

void inserir_caixa(php heap, Caixa caixa) {
	heap->v[heap->n] = caixa;
	heap->n++;

	subir_elemento(heap, heap->n -1);

}

void trocar_raiz(php heap_max, php heap_min) {
	/* Se ambos os heaps forem não-vazios, e a prioridade das suas
	 * raizes estiver invertida, elas são trocadas. Do contrário, nada
	 * acontece. */
	Caixa tmp = heap_max->v[0];

	if ((heap_max->n > 0 && heap_min->n > 0) &&
		heap_max->v[0].peso > heap_min->v[0].peso) {
			heap_max->v[0] = heap_min->v[0];
			heap_min->v[0] = tmp;
	}

	descer_elemento_max(heap_max, 0);
	descer_elemento_min(heap_min, 0);
}

Caixa remover_caixa(php heap) {
	/* Troca a caixa com maior prioridade com a última do heap. Decresce
	 * o número de elementos, possibilitando a sobrescrita do último
	 * elemento. Coloca o novo primeiro em sua posição adequada. */
	Caixa maior;

	maior = heap->v[0];
	trocar(&heap->v[0], &heap->v[heap->n-1]);
	heap->n--;


	if (heap->max)
		descer_elemento_max(heap, 0);
	else
		descer_elemento_min(heap, 0);

	return maior;

}

void imprimir_caixa (Caixa cx) {
	printf("%s: %d", cx.nome, cx.peso);
	printf("\n");
}

void destruir_heap(php heap) {
	free(heap->v);
	free(heap);
}
