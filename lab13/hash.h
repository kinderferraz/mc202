#ifndef HASH_LAB
#define HASH_LAB

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Dois sobrenomes (15) +  duas iniciais + '\0' */
#define CHAVE_TAM 33


/* Tipo: */
typedef struct Item Item;
typedef struct Item * pit;
struct Item {
	char chave[CHAVE_TAM];
	int hash;
};


typedef struct Dict Dict;
typedef struct Dict * pdc;
struct Dict {
	pit * v;
	int n, tam;
};

void criar_chave(char * chave, char ini1, char snome1[], char ini2, char snome2[]);

void resetar_chave(char * chave);

int hash(pdc dict, char chave[]);

int hash2(pdc dict, char chave[]);

pit criar_item(pdc dict, char chave[]);

int itemcmp(pit item1, pit item2);

void destruir_item(pit item);

pdc criar_dict(int tam);

void inserir_item(pdc dict, char chave[]);

int buscar(pdc dict, pit item);

void imprimir_dict(pdc dict);

void destruir_dict(pdc dict);

#endif
