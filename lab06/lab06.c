/* Tarefa de laborátorio 06 -- MC202 G
Alkindar Ferraz Rodrigues -- 154532 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "universidade.h"

/* As constantes usadas já foram definidas em universidade.h */

int main () {
	/* vetores de ponteiros para professores e alunos */
	p_professor *professores;
	p_aluno *alunos;

	/* números de professores e alunos. o índice i é generico para os
	 * loops, j é para o loop aninhado ao adicionar as disciplinas de
	 * cada aluno */
	int i, n_profs, n_alunos;
	int j, n_disciplinas;

	/* variáveis relativas às informações a serem computadas */
	char nome[MAX_NOME];
	char sobrenome[MAX_NOME];
	char codigo[MAX_CODIGO];
	double salario, nota;

	/* ponteiros para as notas extremas e variável que recebe a media
		 dos professores */
	double *nota_max, *nota_min, media;


	/* ler a quantidade de professores e alocar memória para os
		 ponteiros necessários */
	scanf(" %d", &n_profs);
	professores = malloc(sizeof(p_professor) * n_profs);

	/* ler e armazenar as informações de cada professor */
	for (i=0; i < n_profs; i++) {
		scanf("%s %s", nome, sobrenome);
		scanf(" %lf", &salario);
		scanf(" %s", codigo);
		professores[i] = criarProfessor(nome, sobrenome, salario, codigo);
	}

	/* ler a quantidade de alunos e alocar memória para os ponteiros
		 necessários */
	scanf(" %d", &n_alunos);
	alunos = malloc(sizeof(p_aluno) * n_alunos);

	/* ler e armazenar as informações de cada aluno, usando loops
		 aninhados */
	for (i = 0; i < n_alunos; i++) {
		scanf("%s %s", nome, sobrenome);
		alunos[i] = criarAluno(nome, sobrenome);
		scanf(" %d", &n_disciplinas);

		for (j = 0; j < n_disciplinas; j++) {
			scanf(" %s", codigo);
			scanf(" %lf", &nota);
			adicionarDisciplina(alunos[i], codigo, nota);
		}
	}

	/* alocar os espaços de memória que recebem os valores extremos para
	 * cada professor */
	nota_max = malloc(sizeof(double));
	nota_min = malloc(sizeof(double));


	/* segundo uso do vetor código, como parâmetro em
	 * 'obterNotasExtremas'. As funções reajusteSalario e
	 * imprimirProfessor são chamadas para cada professor, atingindo o
	 * objetivo do programa */
	for (i = 0; i < n_profs; i++) {
		strcpy(codigo, professores[i]->disciplina);
		obterNotasExtremas(alunos, n_alunos, codigo, nota_min, nota_max);
		media = (*nota_max + *nota_min) / 2;
		reajusteSalario(professores[i], media);
		imprimirProfessor(professores[i]);
	}

	/* desalocar os espaços de memória, na ordem inversa a que foram
	 * alocados */
	free(nota_min);
	free(nota_max);


	/* os dois trechos seguintes desalocam os espaços ocupados pelos
	 * registros e em seguida o espaço do vetor de ponteiros que permite
	 * o acesso a elas */
	for (i = 0; i < n_alunos; i++) {
		free(alunos[i]);
	}
	free(alunos);

	for (i = 0; i < n_profs; i++) {
		free(professores[i]);
	}
	free(professores);

	return 0;
}
