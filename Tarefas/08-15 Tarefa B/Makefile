# Makefile para MAC0328 (2019).
# Codificação: UTF-8.
# Modifique à vontade!
########################################################################

STD = -std=c99
OP1 = -Wall -Wextra -Wpedantic -Wshadow
OP2 = -Wno-unused-result -Wno-unused-function -Wno-unused-parameter
OPT = -O0
GDB = -g
INC = -I./bib
LM  = # -lm
BIB = bib/*.c

VERBOSE = -v

.FORCE :

default : 
	make tarefaB
	./tarefaB.bin

% : %.c .FORCE
	@echo "-------"
	gcc $(STD) $(OP1) $(OP2) $(OPT) $(INC) $< $(BIB) -o $@.bin $(LM)
	@echo "-------"
	@echo ""
