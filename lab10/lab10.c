/* Tarefa de laborátorio 10 -- MC202 G
 * Alkindar Ferraz Rodrigues -- 154532 */
#include "arvore.h"

#define MAX_SIZE 32
#define MIN_SIZE 3

/* FUNÇÕES AUXILIARES AO PROGRAMA PRINCIPAL */

/* Retornam o papel de um valor de entrada */
int eh_numero(char teste[]) {
	return (teste[0] >= '0' && teste[0] <= '9')
		|| (teste[0] == '-'
				&& teste[1] >= '0' && teste[1] <= '9');
}

int eh_variavel (char teste[]) {
	return teste[0] >= 'a' && teste[0] <= 'z';
}

int eh_parentesis(char teste[]) {
	return teste[0] == '(';
}

/* Leitura dos daodos */
pno ler_valor() {
	/* VARIÁVEIS:
	 * strings:
	 *	 op -> leitura de operadores
	 *	 in -> leitura de ints ou varáveis
	 *	 par -> leitrua do parentesis final
	 * ints:
	 *	 x1 e x2 -> armazenam o valor dos inteiros, caso sejam,
	 *							passados a função criar_arv
	 * pnos:
	 *	 arv1 e arv2 -> armazenam os nós para as arvores de um
	 *									elemento (x1 e x2) ou subexpressao */

	char in[MAX_SIZE], op[MIN_SIZE], par[MIN_SIZE];
	int x1, x2;
	pno arv1 = NULL, arv2 = NULL;

	/* parentesis -> inicia uma subexpressao, na forma de uma subárvore
	 * numero ou var -> cria a subárvore (nó) e guarda-o */
	scanf("%s", in);
	if (eh_parentesis(in))
		arv1 = ler_valor();
	else if (eh_numero(in)) {
		x1 = atoi(in);
		arv1 = criar_arv(x1, 1, NULL, NULL);
	} else if (eh_variavel(in))
		arv1 = criar_arv(in[0], 0, NULL, NULL);

	scanf("%s", op);

	scanf("%s", in);
	if (eh_parentesis(in))
		arv2 = ler_valor();
	else if (eh_numero(in)){
		x2 = atoi(in);
		arv2 = criar_arv(x2, 1, NULL, NULL);
	} else if (eh_variavel(in))
		arv2 = criar_arv(in[0], 0, NULL, NULL);

	scanf("%s", par);

	return criar_arv(op[0], 0, arv1, arv2);
}


int main() {
	/* Lê, simplifica, imprime e destrói a árvore-expressao */
	char in[MIN_SIZE];
	pno expressao;

	scanf("%s", in);
	if (eh_parentesis(in)){
		expressao = ler_valor();
	}

	simplificar(expressao);

	imprimir_arvore(expressao);
	printf("\n");

	destruir_arv(expressao);

	return 0;
}
