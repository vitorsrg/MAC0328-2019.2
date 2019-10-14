# Exemplo muito simples de arquivo Makefile
# (veja a pagina "Como organizar, compilar e depurar 
# um programa C")


STD = -std=c99
# -std=c99: padrao C99 da linguagem C
# -ansi:    padrao C90 da linguagem C

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
# -O0: nao otimiza o codigo ao compilar
# -g:  prepara o terreno para que o gdb possa encontrar bugs

LIBRARIES = -lm
# necessario no caso de usar math.h


# para produzir o arquivo executavel xxx, 
# basta dizer "make xxx"

xxx : ppp.c qqq.c rrrr.h
	gcc $(STD) $(OPTIONS) ppp.c qqq.c -o xxx $(LIBRARIES)

# o que parecem ser espacos no comeco da linha anterior
# sao, na verdade, um unico caractere de tabulacao (\t) 
