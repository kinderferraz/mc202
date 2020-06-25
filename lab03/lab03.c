/* Tarefa de laboratório 03
 * Alkindar Rodrigues -- 154532 
 * operações em strings */

#include <stdio.h>

#define BUFFER 100
#define CMD 3

int comando (char cmd[], char teste[]);
int tamanho (char buffer[]);
int cat (char buffer[], char str[], int t_buffer);
void cmp (char buffer[], char str[], int t_buffer);
int sub (char buffer[], int ini, int fim);

int main () {
	char buffer[BUFFER], str[BUFFER];
	char cmd[CMD];
	int tam_b = 0;
	int x, tam;

	while (1) {
		scanf("%s", cmd);

		if (comando(cmd, "CAT")) {
			scanf ("%s", str);
			tam_b = cat(buffer, str, tam_b);
		} else if (comando(cmd, "CMP")) {
			scanf ("%s", str);
			cmp (buffer, str, tam_b);
		} else if (comando(cmd, "SUB")) {
			scanf("%d ", &x);
			scanf("%d ", &tam);
			tam_b = sub(buffer, x, tam);
		} else if (comando(cmd, "END")) {
			break;
		}
	}
	return 0;
}

int comando (char cmd[], char teste[]) {
	/*Função para identificar o comando dado*/
	int i;
	for (i = 0; i < CMD; i++){
		if (cmd[i] != teste [i]){
			return 0;
		}
	}
	return 1;
}

int tamanho (char buffer[]) {
	/*Função para retornar o tamanho de uma dada string*/
	int i = 0;
	while (buffer[i] != '\0'){
		i++;
	}
	return i;
}

int cat (char buffer[], char str[], int t_buffer) {
	/* Função que concatena uma string a outra.  A variavel i percorre
	 * as variaves ao fim do buffer e lhes da o valor dado por str[j] */
	int t_str;
	int i;
	int j = 0;

	t_str = tamanho(str);

	for (i = t_buffer; i < (t_buffer + t_str); i++) {
		buffer[i] = str[j];
		j++;
	}
	buffer[i] = '\0';
	printf("%s\n", buffer);
	return i;
}

void cmp (char buffer[], char str[], int t_buffer){
	/* Função que compara duas strings
	 * As duas são percorridas pelo mesmo indice e é avisada a primeira
	 * desigualdade */
	int i, t_str;
	t_str = tamanho(str);
	if (t_str != t_buffer) {
		printf("DIFERENTE\n");
		return;
	}

	for (i = 0; i < t_buffer; i++) {
		if (buffer[i] != str[i]) {
			printf("DIFERENTE\n");
			return;
		}
	}
	printf("IGUAL\n");
}

int sub (char buffer[], int ini, int tam) {
	/* Função que dá uma substring de um determinado vetor Assumo que a
	 * o tamanho, a partir do inicio, não excederá o fim da string, isto
	 * é, que a variavel i não será maior que o tamanho da string */
	int i, j;
	j = 0;

	for (i = ini; i < (ini + tam); i++) {
		buffer[j] = buffer[i];
		j++;
	}

	buffer[j] = '\0';
	printf("%s\n", buffer);

	return j;
}
