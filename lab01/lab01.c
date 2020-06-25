#include <stdio.h>

void ler_vetor(int *vetor, int n);
int diferenca(int *vetor_a, int m, int *vetor_b, int n, int *vetor_diff, int counter);
void imprime_vetor(int *vetor, int elementos);


int main () {
	int m, n, unicos;
	int vetor_a[40], vetor_b[40], diff[80];

	scanf ("%d %d\n", &m, &n);
	ler_vetor(vetor_a, m);
	ler_vetor(vetor_b, n);

	unicos = diferenca(vetor_a, m, vetor_b, n, diff, 0);
	unicos = diferenca(vetor_b, n, vetor_a, m, diff, unicos);

	imprime_vetor (diff, unicos);

	return 0;
}

void ler_vetor (int *vetor, int n) {
	/* Função para ler um vetor, considerando um valor fornecido. */
	int i;
	for (i = 0; i < n; i++)
		scanf("%d", &vetor[i]);
}

int diferenca (int *vetor_a, int m,
							 int *vetor_b, int n,
							 int *vetor_diff, int counter) {
	/*Função para constatar os elementos que não se repetem em dois
	vetores, considerando a ordem em que são passados. Desta forma, a
	função precisa ser chamada duas vezes.  Para cada elemento do
	primeiro vetor, se for encontrado um igual no segundo vetor, uma
	variavel marcadora é assinalada. Aqueles que não forem assinalados
	serão copiados ao vetor final, e uma variavel contadora recorda o
	tamanho deste e é devolvida */
	int el1, el2, repete, i, j;
	repete = 0;
	for (i = 0; i < m; i++) {
		el1 = vetor_a[i];
		for (j = 0; j < n; j++) {
			el2 = vetor_b[j];
			if (el1 == el2){
				repete = 1;
				break;
			}
		}
		if (!repete) {
			vetor_diff[counter] = el1;
			counter += 1;
		} else {
			repete = 0;
		}
	}
	return counter;
}

void imprime_vetor(int *vetor, int elementos) {
	int i;
	for (i = 0; i < elementos; i++){
		printf("%d ", vetor[i]);
	}
	printf("\n");
}
