# Makefile para MAC0328 (2019).
# Codificação: UTF-8.
# Modifique à vontade!
########################################################################


# STD = -ansi
STD = -std=c99

OP1 = -Wall -Wextra -Wpedantic -Wshadow

OP2 = -Wno-unused-result -Wno-unused-function

## optimization
OPTM = -O0
# OPTM = -O2

# GDB = -g

# onde compilador deve procurar GRAPHlists.h, QUEUE.h, etc.
INC = -I./bib

LM = 
# LM = -lm
##  in case you use sqrt, sin, cos, etc.

# serão compilados junto com programa-cliente
BIB = \
bib/GRAPHlists.c \
bib/QUEUE.c \
bib/PQ.c \
bib/UF.c \
bib/MYTOOLS.c

VERBOSE = -v

.FORCE :

default : 
	@echo "Para compilar prog.c diga make prog"
	@echo ""

% : %.c .FORCE
	@echo "-------"
	gcc $(STD) $(OP1) $(OP2) $(OPTM) $(INC) $< $(BIB) -o $@ $(LM)
	@echo "-------"
	@echo ""

test:
	make aleatorios
	./aleatorios 10 20
	./aleatorios 100 5000
	./aleatorios 1000 50000

	rm -f aleatorios

tar:
	rm -rf 10258862
	rm -f 10258862.tar

	mkdir 10258862
	cp -r bib 10258862/bib
	cp -r aleatorios.c 10258862/aleatorios.c
	cp -r Makefile 10258862/Makefile
	tar -cvf 10258862.tar 10258862

ifneq ($$(basename "$(CURDIR)"), "10258862")
	echo $$(basename "$(CURDIR)")
	tar -xvf 10258862.tar
	cd 10258862; make test
endif

	rm -rf 10258862

.PHONY: test tar
