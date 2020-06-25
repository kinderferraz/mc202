#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "universidade.h"

p_professor criarProfessor(char nome[], char sobrenome[],
													 double salario, char disciplina[]){
	/* A partir das informações lidas em main, aloca um espaço para um
	 * novo professor, armazena as informações nos respectivos campos e
	 * retorna um ponteiro para este novo registro.  */

	p_professor novo;
	novo = malloc(sizeof(Professor));

	strcpy(novo->nome, nome);
	strcpy(novo->sobrenome, sobrenome);
	novo->salario = salario;
	strcpy(novo->disciplina, disciplina);

	return novo;
}


void destruirProfessor(p_professor professor) {
	/* Desaloca o espaço ocupado por um registro de professor. */
	free(professor);
}


p_aluno criarAluno(char nome[], char sobrenome[]) {
	/* Cria um ponteiro para registro de aluno e aloca espaço para ele
	 * em seguida copia os parâmetro passados para os devidos campos e
	 * inicia a variável qtd_disciplinas com 0. */

	p_aluno novo;
	novo = malloc(sizeof(Aluno));

	strcpy(novo->nome, nome);
	strcpy(novo->sobrenome, sobrenome);
	novo->qtd_disciplinas = 0;

	return novo;
}


void adicionarDisciplina(p_aluno aluno, char disciplina[],
												 double nota) {
	/* Para cada informação de disciplina lida por main, coloca o codigo
	 * e a nota da disciplina em posições identicas da matriz (vetor de
	 * strings) disciplinas e do vetor notas associadas ao aluno.  A
	 * variável dis é apenas para encurtar as linhas seguintes.*/

	int dis;
	dis = aluno->qtd_disciplinas;

	strcpy(aluno->disciplinas[dis], disciplina);
	aluno->notas[dis] = nota;

	aluno->qtd_disciplinas++;
}

void destruirAluno(p_aluno aluno) {
	/* Desaloca o espaço ocupado por um registro de professor. */
	free(aluno);
}

void obterNotasExtremas(p_aluno alunos[], int qtd_alunos,
												char disciplina[], double *nota_min,
												double *nota_max) {
	/* Para obter a maior a menor nota que os alunos obtiveram em cada
	 * matéria, começamos com duas sentinelas. Para cada aluno,
	 * percorremos a matriz com os codigos de disciplinas cursadas e
	 * comparamos com a disciplina desejada, isto é, passada por
	 * parâmetro. Caso ela esteja presente, procuramos a nota obtida,
	 * armazenada na posição idêntica do vetor notas.  Comparamos esta
	 * com as notas já encontradas (ou sentinelas) e caso seja a
	 * informação desejada, armamos nos endereços recebidos por
	 * parâmetro. */
	int i, j;

	nota_min[0] = 11.0;
	nota_max[0] = -1.0;

	for (i = 0; i < qtd_alunos; i++) 
		for (j = 0; j < alunos[i]->qtd_disciplinas; j++)
			if (strcmp(alunos[i]->disciplinas[j], disciplina) == 0) {
				if (alunos[i]->notas[j] > nota_max[0])
					nota_max[0] = alunos[i]->notas[j];
				
				if (alunos[i]->notas[j] < nota_min[0]) 
					nota_min[0] = alunos[i]->notas[j];

	}
}


void reajusteSalario(p_professor professor, double media_notas) {
	/* Para calcular o novo valor recebido pelo professor, a variável
	 * salário é usada apenas para encurtar as linhas. Ela recebe o
	 * valor atual que o professor recebe, e calcula o novo valor com
	 * base na média recebida. Em seguida o valor atualizado é colocado
	 * no no devido campo do registro. */

	double salario;

	salario = professor->salario;
	if (media_notas == 10)
		salario += salario * 0.15;
	else if (media_notas >= 9)
		salario += salario * 0.1;
	else if (media_notas >= 8.5) 
		salario += salario * 0.05;

	professor->salario = salario;
}


void imprimirProfessor(p_professor professor) {
	/* Imprime a saída conforme especificado: nome e sobrenome do
	 * professor, o salário atualizado e um caractere de nova linha. */
	printf("%s %s ", professor->nome, professor->sobrenome);
	printf("%.2f\n", professor->salario);
}
