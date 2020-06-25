/* Tarefa de laborátorio 08 -- MC202 G
Alkindar Ferraz Rodrigues -- 154532 */

#include <stdio.h>
#include "numero_astronomico.h"

void reinicia_numero(p_no *ini, p_no *fim) {
	/* Função auxiliar: através do endereço de dois p_no, destroi o numero já
	 * armazenado e inicia outro numero com estes ponteiros */
	destroi_numero(*ini, *fim);
	criar_numero(ini, fim);
}


int main () {
	/* p_no para dois numeros a serem manipulados */
	p_no i, f;
	p_no i_outro, f_outro;

	/* Caracteres de entrada */
	int alg;
	char entrada;

	/* Criar numeros, o primeiro é inicializado com 0 */
	criar_numero(&i, &f);
	criar_numero(&i_outro, &f_outro);
	add_algarismo(f, 0);

	scanf("%c", &entrada);

	while (entrada != '#') {
		/* Ao entrar '\n' a leitura do numero auxiliar é interrompida, a soma é
		 * efetuada, o numero principal impresso e o numero auxiliar é
		 * reiniciado */
		if (entrada == '\n') {
			somar(i, f, i_outro, f_outro);
			imprime_numero(i, f);
			reinicia_numero(&i_outro, &f_outro);
		} else if (entrada != '+' && entrada != ' '){
			alg = entrada - '0';
			add_algarismo(f_outro, alg);
		} else{
			;
		}
		scanf("%c", &entrada);
	}

	destroi_numero(i_outro, f_outro);
	destroi_numero(i, f);

	return 0;
}
