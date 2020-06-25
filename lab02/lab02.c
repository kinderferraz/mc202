/* Tarefa de laborátorio 02 -- MC202 G\n
Alkindar Ferraz Rodrigues -- 154532
Calcular a permutação de matrizes quadradas*/

#include <stdio.h>

/* Qantidade maxima de posições para as matrizes*/
#define MAX 312

/* Declarar funções que serão definidas */
void ler_vetor (int *vetor, int n);
void ler_matriz (double matriz[][MAX], int n);
void inicia_matriz (double matriz[][MAX], int ordem);
void imprime_matriz (double matriz[][MAX], int n);
void converter_vetor_p (int vetor_p[MAX], double matriz_p[][MAX], int ordem);

void multipica_matriz (double matriz[][MAX], double res[][MAX],
											 double matriz_p[][MAX], int ordem);

/* Definição das funções já mencionadas*/

void ler_vetor(int *vetor, int n){
	int i;
	for (i = 0; i < n; i++)
		scanf("%d\n", &vetor[i]);
}

void ler_matriz(double matriz[][MAX], int n){
	int lin, col;
	for (lin = 0; lin < n; lin++) 
		for (col = 0; col < n; col++) 
			scanf("%lf", &matriz[lin][col]);
}

void imprime_matriz(double matriz[][MAX], int n){
	int lin, col;
	for (lin = 0; lin < n; lin++) {
		for (col = 0; col < n; col++) {
			printf("%.1f", matriz[lin][col]);
			if (col < n - 1)
				printf(" ");
		}
		printf("\n");
	}
}

void inicia_matriz(double matriz[][MAX], int ordem) {
	/*Inicializa uma matriz com os valores zerados. */
	int i, j;

	for (i = 0; i < ordem; i++)
		for (j = 0; j < ordem; j++)
			matriz[i][j] = 0;
}

void converter_vetor_p(int *vetor, double matriz_p[][MAX], int ordem) {
	/*Coloca o valor 1 nas posições indicadas */
	int i, linha;

	for (i = 0; i < ordem; i++){
		linha = vetor[i]-1;
		matriz_p[linha][i] = 1;
	}
}


void multipica_matriz(double mat[][MAX], double mat_p[][MAX],
											double res[][MAX], int ordem) {
	int i, j, k;

	/*Calcula o valor a ser somado em uma dada posição e o adiciona.*/
	for (i = 0; i < ordem; i++) 
		for (j = 0; j < ordem; j++) 
			for (k = 0; k < ordem; k++) 
				res[i][j] += mat_p[i][k] * mat[k][j];
}

int main () {
	int ordem;
	int vetor_p[MAX];
	double matriz[MAX][MAX], matriz_p[MAX][MAX], resultado[MAX][MAX];

	scanf("%d\n", &ordem);

	/* Lê o vetor e a matriz de entrada, inicia as matrizes que serão usadas */
	ler_vetor(vetor_p, ordem);
	ler_matriz(matriz, ordem);
	inicia_matriz(matriz_p, ordem);
	inicia_matriz(resultado, ordem);

	/* Converte os valores fornecidos no vetor em uma matriz */
	converter_vetor_p(vetor_p, matriz_p, ordem);

	multipica_matriz(matriz, matriz_p, resultado, ordem);

	imprime_matriz(resultado, ordem);

	return 0;
}
