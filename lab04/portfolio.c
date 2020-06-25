/* Tarefa de laborátorio 04 -- MC202 G
Alkindar Ferraz Rodrigues -- 154532
Implementação das funções de portfolio.h */

/*biblioteca necessaria para operações com nomes*/
#include <string.h>  

#include <stdio.h>
#include "portfolio.h"
#include "acao.h"

portfolio criar_portfolio(char *nome, char *sobrenome) {
	portfolio criando;

	strcpy(criando.nome, nome);
	strcpy(criando.sobrenome, sobrenome);
	scanf("%d", &criando.n_acoes);

	return criando;
}

portfolio adicionar_acao(portfolio p, acao a){
	static int i = 0;

	p.acoes[i] = a;
	i++;

	return p;
}

void criar_relatorio(portfolio p) {
	int i;
	printf("Relatorio de %s %s\n", p.nome, p.sobrenome);
	for (i = 0; i < p.n_acoes; i++) {
		reportar_acao(p.acoes[i]);
	}
}
