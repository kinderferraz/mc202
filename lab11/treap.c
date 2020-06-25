#include "treap.h"

pno criar_no(int dado, pno pai) {
	/* Cria e devolve um novo nó.  Uma prioridade aleatória é associada
	 * a ele e seu valor é ilimitado visto que isso melhora o desempenho
	 * do algoritmo.  (se ela fosse limitada a 50, como eu havia
	 * testado, executava o teste 15 em 1,9s. Sem a limitação, todos os
	 * testes tomam +- 0.4s) */
	pno novo;
	novo = malloc(sizeof(No));

	if (novo == NULL) {
		printf("Problema para criar a Treap.\n");
		exit(1);
	}

	novo->dado = dado;
	novo->pri = rand();

	novo->esq = novo->dir = NULL;
	novo->pai = pai;
	return novo;
}

pno buscar(pno raiz, int dado) {
	if (raiz == NULL || raiz->dado == dado)
		return raiz;

	if (dado < raiz->dado)
		return buscar(raiz->esq, dado);

	return buscar(raiz->dir, dado);
}

pno inserir_no(pno raiz, int dado, pno pai) {
	/* Insere um nó em uma treap, que pode ser vazia. A posição do nó é
	 * encontrada e ele é devidamente criado, e a prioridade é então
	 * conferida. Se a treap for vazia, ele é retornado como raiz.  Para
	 * manter o TAD, o ponteiro raiz de cada chamada é passado como pai
	 * à seguinte, até que a função criar_no faça o novo nó apontar
	 * corretamente para seu pai. */
	pno novo;

	if (raiz == NULL) {
		novo = criar_no(dado, pai);
		return novo;
	}

	if (dado <= raiz->dado) {
		raiz->esq = inserir_no(raiz->esq, dado, raiz);

		if (raiz->esq->pri > raiz->pri)
			raiz = girar_dir(raiz);
	} else {
		raiz->dir = inserir_no(raiz->dir, dado, raiz);

		if (raiz->dir->pri > raiz->pri)
			raiz = girar_esq(raiz);
	}

	return raiz;
}

/* Implementando com a terminlogia usada nas imagens do exercicio. */
pno girar_esq(pno x) {
	/* x  -> raiz
	 * y  -> filho direito
	 * t2 -> neto à esquerda de x, filho de y
	 * imediatamente após performar uma mudança,
	 * o pai de cada nó é atualizado,
	 * à exceção de t2 que pode ser NULL. */
	pno y, t2;

	y = x->dir;
	t2 = y->esq;
	y->pai = x->pai;

	y->esq = x;
	x->pai = y;

	x->dir = t2;
	if (t2 != NULL)
		t2->pai = x;

	return y;
}

pno girar_dir(pno y) {
	/* Procedimento inverso ao da função girar_esq.
	 * Mantém o TAD e confere se t2 existe antes de modificá-lo */
	pno x, t2;

	x = y->esq;
	t2 = x->dir;
	x->pai = y->pai;

	x->dir = y;
	y->pai = x;

	y->esq = t2;
	if(t2 != NULL)
		t2->pai = y;

	return x;
}

/* Funções retiradas dos slides de aula:
 * minimo()
 * ancestral_direita()
 * sucessor() */
pno minimo(pno treap) {
	/* Retorna o menor valor de uma treap: o descendente mais a
	 * esquerda */
	while (treap->esq != NULL)
		treap = treap->esq;

	return treap;
}

pno ancestral_direita(pno x) {
	/* Retorna o ancestral de um nó, com menor valor maior que o dele.
	 * Ele será, se existir, o pai (pela esquerda) mais próximo de x */
	if (x == NULL)
		return NULL;
	if (x->pai == NULL || x->pai->esq == x)
		return x->pai;
	else
		return ancestral_direita(x->pai);
}

pno sucessor(pno x) {
	/* Retorna o menor entre os filhos a direita de x, ou o ancestral a
	 * direita dele */
	if (x->dir != NULL)
		return minimo(x->dir);
	else
		return ancestral_direita(x);
}

/* Fim das funções retiradas dos slides de aula */

pno diferenca(pno cjto1, pno cjto2) {
	/* Constrói o conjunto diferença entre dois conjuntos dados. Para
	 * tanto, os dois conjuntos são percorridos em paralelo, através dos
	 * ponteiros de teste(1 e 2): enquanto um deles não terminar, os
	 * dados referidos pelos ponteiros teste são comparados: se um
	 * elemento for menor que outro, ele é inserido em diff e o sucessor
	 * dele é encontrado.  quando os dois elementos forem iguais, eles
	 * são passados.  Ao fim do processo, os dois conjuntos são
	 * destruidos, para evitar o vazamento de memória: o conjunto diff
	 * retornado pode ser chamado como cjto1 numa chamada posterior, e a
	 * referência a ele será perdida quando um novo conjunto for
	 * devolvido. */
	pno diff = NULL;
	pno teste1, teste2;
	teste1 = minimo(cjto1);
	teste2 = minimo(cjto2);

	while (teste1 != NULL && teste2 != NULL) {
		if (teste1->dado < teste2->dado) {
			diff = inserir_no(diff, teste1->dado, NULL);
			teste1 = sucessor(teste1);
		}
		else if (teste1->dado > teste2->dado) {
			diff = inserir_no(diff, teste2->dado, NULL);
			teste2 = sucessor(teste2);
		}
		else if (teste1->dado == teste2->dado){
			teste1 = sucessor(teste1);
			teste2 = sucessor(teste2);
		}
	}

	if (teste1 == NULL)
		while (teste2 != NULL){
			diff = inserir_no(diff, teste2->dado, NULL);
			teste2 = sucessor(teste2);
		}

	if (teste2 == NULL)
		while (teste1 != NULL){
			diff = inserir_no(diff, teste1->dado, NULL);
			teste1 = sucessor(teste1);
		}

	destruir_treap(cjto1);
	destruir_treap(cjto2);
	return diff;
}

void imprimir_treap(pno raiz) {
	/* Imprime o conjunto de forma decrescente:
	 * primeiro o lado mais a direita da subárvore primeiro. */
	if (raiz != NULL) {
		imprimir_treap(raiz->dir);
		printf("%d ", raiz->dado);
		imprimir_treap(raiz->esq);
	}
}

void destruir_treap(pno raiz){
	if (raiz != NULL) {
		destruir_treap(raiz->esq);
		destruir_treap(raiz->dir);
		free(raiz);
	}
}
