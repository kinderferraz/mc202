/* Tarefa de laborátorio 04 -- MC202 G
   Alkindar Ferraz Rodrigues -- 154532 
   Relátorio de portifólio de ações */

#include <stdio.h>
#include "acao.h"
#include "portfolio.h"


int main () {
	char nome[MAX_SIZE_NAME], sobrenome[MAX_SIZE_NAME];
	int i;
	int n_var;
	double investimento;
	double var;
	acao acao;
	portfolio cliente;

	scanf("%s", nome);
	scanf("%s", sobrenome);
	cliente = criar_portfolio(nome, sobrenome);

	/* O valor de duas das variáveis internas é consultado neste trecho,
		 mas nao é alterado diretamente. O numero de ações que o cliente
		 possui é acessado como parametro do laço externo. Já o laço
		 interno compara o valor de n_variacoes com o valor de entrada, e
		 enquanto todas elas não forem lidas repetir o laço. O valor de
		 n_variacoes é incrementado dentro da funçnao
		 adicionar_variacao. */
	for (i= 0; i < cliente.n_acoes; i++){
		scanf("%s", nome);
		scanf("%lf ", &investimento);
		scanf("%d ", &n_var);

		acao = criar_acao(nome, investimento);

		while (acao.n_variacoes < n_var) {
			scanf("%lf\n", &var);
			acao = adicionar_variacao(acao, var);
		}

		cliente = adicionar_acao(cliente, acao);
	}

	criar_relatorio(cliente);

	return 0;
}
