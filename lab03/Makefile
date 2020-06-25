MAIN = lab03
CC = gcc-9
CFLAGS = -ansi -Wall -pedantic-errors -Werror -g
OBJECTS = lab03.o

all: lab03

lab03: lab03.o
	$(CC) $(GFLAGS) $(OBJ) lab03.c -o lab03

lab03.o: lab03.c
	$(CC) $(CFLAGS) -c lab03.c

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
		resultado=$$(echo "$$entrada" | sed -e 's/\.in$$/.res/' ) ; \
		saida=$$(echo "$$entrada" | sed -e 's/\.in$$/.out/' ) ; \
		./$(MAIN) < $$entrada > $$saida ; \
		echo ; \
		echo "Testando $$entrada: " ; \
		if diff $$resultado $$saida ;  then \
			echo "OK" ; \
		else \
			echo "***********************************"; \
			echo "Falhou para $$entrada" ; \
			echo "***********************************"; \
			exit 1; \
		fi ; \
	done
