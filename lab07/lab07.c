/* Tarefa de laborátorio 06 -- MC202 G
 * Alkindar Ferraz Rodrigues -- 154532
 * Backtrace -- escape a maze*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOV 4

typedef struct {
	int lin;
	int col;
} ponto;


/* Funções relacionadas a entrada, saida e alocação das matrizes de caracteres */

char ** alocar_labirinto(int lin, int col);
void desalocar_labirinto(char ** labirinto, int lin);

void ler_labirinto(char **labirinto, int lin, int col);
void imprimir_labirinto(char **labirinto,  int lin, int col);

ponto seguinte(ponto atual, char dir, int lin, int col);
int pode_mover(char **labirinto, ponto teste, ponto anterior);
int achar_saida(char **labirinto, int lin, int col, ponto anterior, ponto entrada, ponto saida);


int main () {
	/* Constantes de tamanho maximo do labirinto.
	 * Os mesmos nomes são usados nas demais funções com este mesmo sentido.
	 * A variável livres contém o número de O's na entrada, e este é o maior
	 * valor possível para o caminho de saida. */
	int lin, col;

	/* Matrizes que armazenam o labirinto dado, o caminho de saida e uma lista
	 * dos pontos já percorridos. */
	char **labirinto;

	/* Registros para os pontos de entrada e saida.
	 * Invalido é o valor passado na primeira chamada da funçao achar_saida */
	ponto entrada, saida;
	ponto invalido;

	invalido.lin = -1;
	invalido.col = -1;

	scanf("%d %d ", &lin, &col);
	scanf("%d %d ", &entrada.lin, &entrada.col);
	scanf("%d %d ", &saida.lin, &saida.col);

	labirinto = alocar_labirinto(lin, col);
	ler_labirinto(labirinto, lin, col);
	achar_saida (labirinto, lin, col, invalido, entrada, saida);

	imprimir_labirinto(labirinto, lin, col);
	desalocar_labirinto(labirinto, lin);

	return 0;
}

char ** alocar_labirinto(int lin, int col) {
	/* Aloca a memoria necessária para as matrizes labirintos, com base nos
	 * valores de lin e col fornecidos. */

	char ** labirinto;
	int i;

	labirinto = malloc(lin * sizeof(char*));
	for (i = 0; i < lin; i++) {
		labirinto[i] = malloc(col * sizeof(char*));
	}
	return labirinto;
}

void desalocar_labirinto(char ** labirinto, int lin) {
	int i;
	for (i = 0; i < lin; i++){
		free(labirinto[i]);
	}
	free(labirinto);
}

void ler_labirinto(char **labirinto, int lin, int col) {
	/* Lê os valores de entrada e armazena-os na posição correspondente da
	 * matriz */

	int i, j;
	char lixo;

	for (i = 0; i < lin; i++){
		for (j = 0; j < col; j++) {
			scanf("%c", &labirinto[i][j]);
		}
	scanf("%c", &lixo);
	}
}

void imprimir_labirinto(char **labirinto,  int lin, int col){
	/* Dado um ponteiro para a matriz, imprime asteriscos onde estão
	 * marcados e espaços onde estão marcados 'X', para possições
	 * impossíveis, ou 'Z' para caminhos que não levam à saida. */
	int i, j;
	for (i = 0; i < lin; i++){
		for (j = 0; j < col; j++) {
			if (labirinto[i][j] == '*') {
				printf("%c", labirinto[i][j]);
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

int achar_saida(char **labirinto, int lin, int col, ponto anterior, ponto entrada, ponto saida) {
	/* Função recursiva para encontrar a saida do labirnto.
	 * Dado o ponto em questão, sob o nome de entrada, testa os quatro pontos
	 * possiveis na seguinte ordem: acima, abaixo, a direita e a esquerda.
	 * Estas informações são passadas no laço, com o seguinte procedimento:
	 * 1) a função seguinte retorna os valores do proximo ponto a ser testado
	 * 2) a função pode mover retorna a viabilidade desta posição
	 * 3) caso seja um movimento viavel, a função é chamada novamente para o
	 * ponto proximo.
	 * 4) caso nenhuma posição viavel seja encontrada, é retornado 0 e o
	 * caminho inviável é marcado com 'Z' na matriz labirnto
	 * 5) caso contrário, ao se encontrar a posição de saida, é retornado 1
	 * e o caminho viavel é marcado com '*' */
	ponto proximo;
	char mov[MOV] = {'c', 'b', 'd', 'e'};
	int prossegue;  /* bool */
	int i;


	if (entrada.lin == saida.lin && entrada.col == saida.col){
		labirinto[saida.lin][saida.col] = '*';
		return 1;
	}

	for (i = 0; i < MOV; i++) {
		proximo = seguinte(entrada, mov[i], lin, col);
		if (pode_mover(labirinto,  proximo, anterior)) {
			prossegue = achar_saida (labirinto, lin, col, entrada, proximo, saida);
			if (prossegue) {
				labirinto[entrada.lin][entrada.col] = '*';
				return 1;
			} else {
				labirinto[entrada.lin][entrada.col] = 'Z';
			}
		}
	}
	return 0;
}

int pode_mover(char **labirinto, ponto teste, ponto anterior){
	/* Testa a viabilidade de um ponto vizinho ao ponto em questão.  Se
	 * o ponto for identido ao ponto anterior, a função retorna 0, para
	 * que nao se caia num loop. */

	if (teste.lin == -1
			|| (teste.lin == anterior.lin && teste.col == anterior.col))
		return 0;
	else if (labirinto[teste.lin][teste.col] == 'O')
		return 1;
	else 
		return 0;
}


ponto seguinte(ponto atual, char dir, int lin, int col) {
	/* Retorna o proximo ponto a ser testado.
	 * Caso os indices estejam fora da matriz, o valor sentinela -1 é devolvido */

	ponto proximo;

	if (dir == 'c') {
		proximo.lin = atual.lin - 1;
		proximo.col = atual.col;
	} else if (dir == 'b') {
		proximo.lin = atual.lin + 1;
		proximo.col = atual.col;
	} else if (dir == 'd') {
		proximo.lin = atual.lin;
		proximo.col = atual.col + 1;
	} else if (dir == 'e') {
		proximo.lin = atual.lin;
		proximo.col = atual.col - 1;
	}

	if ((0 <= proximo.lin && proximo.lin < lin )
			&& (0 <= proximo.col && proximo.col < col )) {
		return proximo;
	} else {
		proximo.lin = -1;
		proximo.col = -1;
		return proximo;
	}
}
