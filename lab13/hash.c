#include "hash.h"

#define BASE 256
#define PRIMO 461

void criar_chave(char * chave, char ini1, char snome1[], char ini2, char snome2[]) {
	/* Cria uma chave a partir de uma dupla de autores, em ordem
	 * alfabética A função strncat é usada para copiar apenas o 1
	 * caractere das iniciais, que não é seguida de '\0' A ordem
	 * alfabética é dada pela comparação da primeira letra do sobrenome,
	 * seguida pelas iniciais e pelas duas etras seguintes do
	 * sobrenome */
	resetar_chave(chave);
	if ((snome1[0] < snome2[0])
	 || ((snome1[0] == snome2[0]) && (ini1 < ini2))
	 || ((snome1[0] == snome2[0]) && (ini1 == ini2)
			 && (snome1[1] < snome2[1]))
	 || ((snome1[0] == snome2[0]) && (ini1 == ini2)
			 && (snome1[1] == snome2[1])
			 && (snome1[2] < snome2[2])))
	{
		strncat(chave, &ini1, 1);
		strcat(chave, snome1);
		strncat(chave, &ini2, 1);
		strcat(chave, snome2);
	}
	else
	{
		strncat(chave, &ini2, 1);
		strcat(chave, snome2);
		strncat(chave, &ini1, 1);
		strcat(chave, snome1);
	}
}

void resetar_chave(char * chave) {
	/* Esvazia a string para as funções strcat */
	chave[0] = '\0';
}

int hash(pdc dict, char chave[]) {
	/* Função de hash apresentada em aula */
	int i;
	int hash = 0;

	for (i = 0; chave[i] != '\0'; i++)
		hash = (hash + chave[i] * BASE) % dict->tam;

	return hash;
}

int hash2(pdc dict, char chave[]) {
	/* Hash aux: retorna um número ímpar */
	int i;
	int hash = 0;

	for (i = 0; chave[i] != '\0'; i++){
		hash = PRIMO - (chave[i] % PRIMO);
		hash = hash % dict->tam;
	}
	if (hash % 2 == 0)
		hash += 1;
	return hash;
}

pit criar_item(pdc dict, char chave[]) {
	/* Cria um novo item, copia a chave e salava o valor de hash para a
	 * chave */
	pit novo;

	novo = malloc(sizeof(Item));
	if (novo == NULL)
		exit(1);

	novo->hash = hash(dict, chave);
	strncpy(novo->chave, chave, CHAVE_TAM);

	return novo;
}

int itemcmp(pit item1, pit item2) {
	/* compara duas chaves */
	if (strcmp(item1->chave, item2->chave) == 0)
		return 1;
	return 0;
}

void destruir_item(pit item) {
	free(item);
}

pdc criar_dict(int tam) {
	/* Aloca uma hash table, seu vetor de chaves, inicializado com NULL
	 * Posiciona os valores de tam e n */
	pdc novo;
	int i;

	novo = malloc(sizeof(Dict));
	if (novo == NULL)
		exit(1);

	novo->v = malloc(sizeof(pit) * tam);
	if (novo->v == NULL)
		exit(1);

	for (i = 0; i < tam; i++)
		novo->v[i] = NULL;

	novo->tam = tam;
	novo->n = 0;

	return novo;
}

void inserir_item(pdc dict, char chave[]) {
	/* Cria um item a partir da chave fornecida.
   * Se o item já tiver sido inserido, a função retorna 
   * Se a posição estiver vazia, o item é inserido 
   * So contrario, o valor de h2 é calculado, e o valor de i 
   * é incrementado até encontrar a próxima posição livre */
	pit item;
	int h2;
	int i = 1;
	int inserido;

	item = criar_item(dict, chave);

	inserido = buscar(dict, item);
	if (inserido)
		return;

	if (dict->v[item->hash] == NULL)
		dict->v[item->hash] = item;
	else {
		h2 = hash2(dict, chave);
		while(dict->v[(item->hash + i * h2) % dict->tam] != NULL)
			i++;
		dict->v[(item->hash + i * h2) % dict->tam] = item;
	}
	dict->n++;
}

int buscar(pdc dict, pit item) {
	/* Processo análogo ao de inserção:
	 * procura-se o item na posição de sua hash.
	 * caso ele não esteja lá, o valor de h2 é calculado e i incrementado
	 * até que uma posição livre ou o item seja encontrado */
	int h2;
	pit aux;
	int i = 0;

	h2 = hash2(dict, item->chave);
	aux = dict->v[(item->hash + i * h2) % dict->tam];
	while (aux != NULL){
		if (itemcmp(item, aux))
			return 1;
		i++;
		aux = dict->v[(item->hash + i * h2) % dict->tam];
	}
	return 0;
}

void imprimir_dict(pdc dict) {
	/* Função auxiliar: imprime o indice de um item, seguido de sua
		 chave */
	int i;
	for (i = 0; i < dict->tam; i++)
		if (dict->v[i] != NULL)
			printf("%d -> %s\n", i, dict->v[i]->chave);
}

void destruir_dict(pdc dict) {
	/* Destroi os itens alocados, seguido do vetor de ponteiros e por
	 * fim o próprio dicionário */
	int i;
	for (i = 0; i < dict->tam; i++)
		if (dict->v[i] != NULL)
			destruir_item(dict->v[i]);
	free(dict->v);
	free(dict);
}
