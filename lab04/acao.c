/* Tarefa de laborátorio 04 -- MC202 G
Alkindar Ferraz Rodrigues -- 154532
Implementação das funções de ação.h */

/*biblioteca necessaria para operações com nomes */
#include <string.h>

#include <stdio.h>
#include "acao.h"

acao criar_acao(char *nome, double investimento) {
	/* A var n_variacoes é iniciada com 0, ela sera incrementada
		 conforme a função adicionar_variacao for chamada. Seu valor é
		 consultado no progama principal, mas é alterado apenas pelas
		 funções fornecidas.  */
	acao nova;

	strcpy(nova.nome, nome);
	nova.investimento = investimento;
	nova.n_variacoes = 0;

	return nova;
}

acao adicionar_variacao(acao a, double variacao) {

	a.variacoes[a.n_variacoes] = variacao;
	a.n_variacoes++;

	return a;
}

void reportar_acao(acao a) {
	int i;
	double investimento_inicial;

	investimento_inicial = a.investimento;

	for (i = 0; i < a.n_variacoes; i++) {
		a.investimento += (a.investimento * a.variacoes[i]) / 100;
	}

	printf("%s ", a.nome);
	printf("%.2f ", a.investimento);
	if (a.investimento > investimento_inicial) {
		printf("GANHO\n");
	} else {
		printf("PERDA\n");
	}
}
