MAIN = lab02

CC = gcc-9
CFLAGS = -ansi -Wall -pedantic-errors -Werror -g
OBJECTS = lab02.o

all: lab02

lab02: lab02.o
	$(CC) $(GFLAGS) $(OBJ) lab02.c -o lab02

lab02.o: lab02.c
	$(CC) $(CFLAGS) -c lab02.c


clean:
	rm -f $(MAIN) *.o

.PHONY: testar_tudo
testar_tudo: $(MAIN)
	@set -e ; \
	if [ ! -d testes_abertos ] ; then \
		echo "*****************************************************************" ; \
		echo "Copie o diretório 'testes_abertos' para a mesma pasta do Makefile" ; \
		echo "*****************************************************************" ; \
		exit 1 ; \
	fi ; \
	for entrada in testes_*/*.in ; do \
		saida=$$(echo "$$entrada" | sed -e 's/\.in$$/.out/' ) ; \
		resposta=$$(echo "$$entrada" | sed -e 's/\.in$$/.res/' ) ; \
		./$(MAIN) < "$$entrada" > "$$saida" ; \
		echo ; \
		echo "Testando $$entrada: " ; \
		if diff "$$resposta" "$$saida" ;  then \
			echo "OK" ; \
		else \
			echo "***********************************"; \
			echo "Falhou para $$entrada" ; \
			echo "***********************************"; \
			exit 1; \
		fi ; \
	done
