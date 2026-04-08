#* Compilador a usar
CC = gcc

#* Flags de compilação:
#* -Wall → ativa warnings importantes
#* -Wextra → warnings adicionais
#* -g → permite debug (usar com gdb)
CFLAGS = -Wall -Wextra -g

#* Diretório onde estão os headers (.h)
#* -Iinclude diz ao compilador onde procurar stack.h
INCLUDES = -Iinclude

#* Ficheiros fonte (.c) do projeto
SRC = src/stack.c test/main.c

#* Nome do executável final
OUT = func_stack

#* Regra principal (executada quando escreves "make")
all:
	# Compila tudo e cria o executável
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(OUT)

#* Regra para compilar e executar diretamente
run: all
	#* Executa o programa depois de compilar
	./$(OUT)

#* Regra para limpar ficheiros gerados
clean:
	#* Remove o executável
	rm -f $(OUT)
