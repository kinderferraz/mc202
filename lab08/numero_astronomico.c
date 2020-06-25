#include <stdlib.h>
#include "numero_astronomico.h"

/* Para uso interno a implementação. Não são estritamente necessárias
 * para o uso proposto */

void add_casa(p_no ini);
int remove_zeros(p_no ini, p_no fim);
void remove_casa(p_no casa);
int copiar_lista(p_no ini1, p_no fim1, p_no ini2, p_no fim2);

void add_casa(p_no ini) {
	/* Adiciona uma casa de valor 0 ao início do numero. */
	p_no novo, aux;
	aux = ini->prox;

	novo = malloc(sizeof(No));
	if (novo == NULL) {
		printf("Não foi possivel alocar um novo algarismo. \n");
		exit(1);
	}

	novo->valor = 0;
	novo->prox = aux;
	novo->ant = ini;

	aux->ant = novo;
	ini->prox = novo;
}

int remove_zeros(p_no pri, p_no fim) {
	/* Remove os zeros ao início da lista.
	 * p_no pri é o primeiro algarismo no numero (ini->prox)
	 * do contrário (pri == ini), não se entra na recursão. */

	int zeros;                            /* bool */

	if (pri->valor != 0)
		return 1;
	else if (pri == fim)
		return 0;
	else {
		zeros = remove_zeros(pri->prox, fim);

		if (zeros)
			remove_casa(pri);
		
		return 1;
	}
}

void remove_casa(p_no casa) {
	/* Remove uma dada casa do numero, ajustando seus vizinhos */
	casa->prox->ant = casa->ant;
	casa->ant->prox = casa->prox;
	free(casa);
}


/* Funções para uso do cliente */
void criar_numero(p_no *ini, p_no *fim) {
	/* Dado o endereço de dois p_no, inicia uma lista vazia. */
	*ini = malloc(sizeof(No));
	*fim = malloc(sizeof(No));

	if (*ini == NULL || *fim == NULL) {
		printf("Não foi possivel alocar as cabeças da lista \n");
		exit(1);
	}

	/* Valores sentinelas: para esta representação de um int, apenas algarismos de
	 * 0 a 9 são necessários. Não são estritamete necessários. */
	(*ini)->valor = -1;
	(*fim)->valor = -1;

	(*ini)->prox = *fim;
	(*fim)->ant = *ini;

	(*ini)->ant = NULL;
	(*fim)->prox = NULL;
}

void add_algarismo(p_no fim, int x) {
	/* Adiciona um algarismo a partir da cabeça fim.
	 * Assim, o algarismo de maior peso estará ligado à cabeça inicio. */
	p_no novo, aux;
	aux = fim->ant;

	novo = malloc(sizeof(No));
	if (novo == NULL) {
		printf("Não foi possivel alocar um novo algarismo. \n");
		exit(1);
	}

	novo->valor = x;
	novo->prox = fim;
	novo->ant = aux;

	aux->prox = novo;
	fim->ant = novo;
}

void imprime_numero(p_no ini, p_no fim) {
	/* Imprime um numero a partir da cabeça início, em ordem inversa à de
	 * leitura. */
	p_no i;

	remove_zeros(ini->prox, fim);

	i = ini->prox;
	while (i != fim) {
		printf("%d", i->valor);
		i = i->prox;
	}

	printf("\n");
}

void destroi_numero(p_no ini, p_no fim) {
	/* Destrói o numero a partir do fim, liberando os nós. */
	p_no aux;

	aux = fim->ant;
	while (aux != ini){
		aux = aux->ant;
		free(aux->prox);
	}
	free(ini);
	free(fim);
}

void somar(p_no ini1, p_no fim1, p_no ini2, p_no fim2) {
	/* Altera o numero 1 (p_no ini1 e fim1), somando os valores do numero 2
	 * à cada casa do primeiro. */

	p_no n1, n2;

	remove_zeros(ini2->prox, fim2);

	n1 = fim1->ant;

	/* Percorre o numero auxiliar, efetuando a soma */
	for(n2 = fim2->ant; n2 != ini2; n2 = n2->ant){
		/* Adiciona casas se necessário */
		if (n1->ant == ini1)
			add_casa(ini1);

		n1->valor += n2->valor;

		n1 = n1->ant;
	}

	/* Percorre o numero principal, corrigindo as casas decimais */
	for(n1 = fim1->ant; n1 != ini1; n1 = n1->ant)
		if (n1->valor >= 10){
			n1->valor -= 10;
			(n1->ant)->valor++;
		}
}
