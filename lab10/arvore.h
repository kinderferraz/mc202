#ifndef ARVORE
#define ARVORE

#include <stdlib.h>
#include <stdio.h>


typedef struct No No;
typedef No * pno;

struct No {
	int num;         /* Bool: o dado armazenado é int (1), ou char (0)*/
	int dado;
	pno esq, dir;
};

pno criar_arv(int dado, int num, pno esq, pno dir);
	/* Retorna uma arvore, cuja raiz é passada por dado, as subárovres
	 * esq e dir dever ser fornecidas, mesmo que NULL */

int calcular(char op, int op1, int op2);
	/* Calcula de uma dada expressao:
	 *   op -> operador
	 *   op1 e op2 -> operandos */

void simplificar(pno arv);
	/* A partir da arvore forncecida, retorna a mesma árvore,
	 * devidamente podada quando possível */

void imprimir_arvore(pno raiz);
	/* Imprime uma árvore, acrescentando parêntesis para delimitar uma
	 * subexpressao */

pno destruir_arv(pno folha);
	/* Destrói completamente a árvore */

#endif
