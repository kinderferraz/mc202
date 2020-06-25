#ifndef UNIVERSIDADE_H
#define UNIVERSIDADE_H

#define MAX_NOME 30
#define MAX_CODIGO 6
#define MAX_DISCIPLINAS 5

typedef struct {
    char nome[MAX_NOME];
    char sobrenome[MAX_NOME];
    double salario;
    char disciplina[MAX_CODIGO];
} Professor;
typedef Professor * p_professor;

typedef struct {
    char nome[MAX_NOME];
    char sobrenome[MAX_NOME];
    int qtd_disciplinas;
    char disciplinas[MAX_DISCIPLINAS][MAX_CODIGO];
    double notas[MAX_DISCIPLINAS];
} Aluno;

typedef Aluno * p_aluno;

p_professor criarProfessor(char nome[], char sobrenome[],
													 double salario, char disciplina[]);

void destruirProfessor(p_professor professor);
p_aluno criarAluno(char nome[], char sobrenome[]);

void adicionarDisciplina(p_aluno aluno,
												 char disciplina[],
												 double nota);
void destruirAluno(p_aluno aluno);
void obterNotasExtremas(p_aluno alunos[], int qtd_alunos,
												char disciplina[], double *nota_min,
												double *nota_max);

void reajusteSalario(p_professor professor, double media_notas);
void imprimirProfessor(p_professor professor);

#endif /* UNIVERSIDADE_H */
