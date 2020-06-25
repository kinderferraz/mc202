#include "arvore.h"

/* FUNÇÕES AUXILIARES À IMPLEMENTAÇÃO DE ÁRVORE BINRÁRIA
 * Conferem o papel de um determinado nó */

int eh_var(int dado) {
	return dado >= 'a' && dado <= 'z';
}

int eh_op(int dado) {
	return dado == '+' || dado == '-' ||
		dado == '*' || dado == '/';
}

/* IMPLEMENTAÇÃO DA ARVORE BINÁRIA */

pno criar_arv(int dado, int num, pno esq, pno dir) {
	pno novo;
	novo = malloc(sizeof(No));

	if (novo == NULL) {
		printf("Problemas para alocar memoria.\n");
		exit(1);
	}

	novo->dado = dado;
	novo->num = num;

	novo->esq = esq;
	novo->dir = dir;

	return novo;
}

int calcular(char op, int op1, int op2){
	switch(op) {
		case '+':
			return op1 + op2;

		case '-':
			return op1 - op2;

		case '*':
			return op1 * op2;

		case '/':
			return op1 / op2;
	}
		return -1;
}

void simplificar(pno raiz) {
	/* Precorre a árvore e simplifica os nós quando possível.
	 * Os nós descendentes do nó simplificado são removidos. */

		int resultado;

	/* Verificar se é uma folha (numero ou variável) -> não faz nada */
	if (raiz->num)
		return;
	else if (eh_var(raiz->dado))
		return;

	/* Subárvore esq: se for var não faz nada,
	 * se for operador, simplifica-o */
	if (eh_var(raiz->esq->dado))
		;
	else if (eh_op(raiz->esq->dado))
		simplificar(raiz->esq);

	/* Subárvore direita */
	if (eh_var(raiz->dir->dado))
		;
	else if (eh_op (raiz->dir->dado))
		simplificar(raiz->dir);

	if (raiz->esq->num && raiz->dir->num) {
		resultado = calcular(raiz->dado, raiz->esq->dado, raiz->dir->dado);
		raiz->dado = resultado;
		raiz->num = 1;
		raiz->esq = destruir_arv(raiz->esq);
		raiz->dir = destruir_arv(raiz->dir);
	}
}

void imprimir_arvore(pno raiz) {
	/* Inordem
	 * confere se a raiz é uma folha -> não faz nada
	 * se for operador -> imprime os filhos.
	 * se o filho for operador -> chama a função para a subexpressao. */
	if (raiz->num)
		return;
	else if (eh_var(raiz->dado))
		return;

	printf("( ");

	if (raiz->esq->num)
		printf("%d ", raiz->esq->dado);
	else if (eh_var(raiz->esq->dado))
		printf("%c ", raiz->esq->dado);
	else if (eh_op(raiz->esq->dado))
		imprimir_arvore(raiz->esq);

	printf ("%c ", raiz->dado);

	if (raiz->dir->num)
		printf("%d ", raiz->dir->dado);
	else if (eh_var(raiz->dir->dado))
		printf("%c ", raiz->dir->dado);
	else if (eh_op(raiz->dir->dado))
		imprimir_arvore(raiz->dir);

	printf(") ");
}

pno destruir_arv(pno folha) {
	/* Destrói completamente a árvore.
	 * O retorno NULL mantém o TAD da árvore na simplificação,
	 * já que ele é assinalado aos filhos do nó que o chamou */

	if (folha != NULL) {
		destruir_arv(folha->esq);
		destruir_arv(folha->dir);
		free(folha);
	}
	return NULL;
}
