/* Tarefa de laborátorio 13 -- MC202 G
 * Alkindar Ferraz Rodrigues -- 154532
 * hash */

#include "hash.h"

#define MAX_AUT 6
#define MAX_SNOME 16
#define HSH_TAM 2048

int ler_artigos(char ini[], char snome[][MAX_SNOME]);
	/* Lê autores de artigos e armazena-os em um vetor (de inicias) e
	 * uma matiz (de sobrenomes) Retorna a quantidade de autores lidos*/

void inserir(pdc dict, int n, char ini[], char snome[][MAX_SNOME]);
	/* Insere os autores de uma dado artigo, dois a dois, na hash table,
	 * a partir dos resultados da função ler_artigos */

int ler_buscar(pdc dict);
	/* Lê um par de autores e procura-os na tabela */

int main () {
	/* TESTE FC CHAVE */
	char inicial[MAX_AUT], sobrenome[MAX_AUT][MAX_SNOME];
	int achado;
	int n, m;
	int i, j;
	pdc dict;

	dict = criar_dict(HSH_TAM);
	scanf("%d %d", &n, &m);

	for (i = 0; i < n; i++){
		j = ler_artigos(inicial, sobrenome);
		inserir(dict, j, inicial, sobrenome);
	}

	for (i = 0; i < m; i++){
		achado = ler_buscar(dict);
		if (achado)
			printf("S\n");
		else
			printf("N\n");
	}

	return 0;
}

int ler_artigos(char inicial[], char sobrenome[][MAX_SNOME]) {
	int i;
	char separador;

	i = 0;
	separador = '\0';
	while (separador != '.'){
		scanf(" %c. %[^.,]%c", &inicial[i], sobrenome[i], &separador);
		i++;
	}
	return i;
}

void inserir(pdc dict, int n, char ini[], char snome[][MAX_SNOME]) {
	char chave[CHAVE_TAM];
	int i, j;

	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++){
			criar_chave(chave, ini[i], snome[i], ini[j], snome[j]);
			inserir_item(dict, chave);
		}
}

int ler_buscar(pdc dict) {
	char ini[2], snome[2][16], separador;
	char chave[CHAVE_TAM];
	int achado;
	pit item;

	scanf(" %c. %[^.,]%c", &ini[0], snome[0], &separador);
	scanf(" %c. %[^.,]%c", &ini[1], snome[1], &separador);

	criar_chave(chave, ini[0], snome[0], ini[1], snome[1]);
	item = criar_item(dict, chave);
	achado = buscar(dict, item);
	free(item);
	return achado;
}
