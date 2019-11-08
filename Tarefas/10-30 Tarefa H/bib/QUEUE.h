// MAC0328 (2019) 
// Altere, modifique, e acrescente � vontade. Sugiro marcar os trechos 
// de c�digo modificados/acrescentados com um coment�rio do tipo
// "// novo". Preserve o meu bom layout (veja www.ime.usp.br/~pf/
// algoritmos/aulas/layout.html) e n�o use tabs. 

// Este arquivo: QUEUE.h (codifica��o UTF-8)
// Data: 2019-07-17
// Autor: Paulo Feofiloff
//
// Esta � a interface da implementa��o de uma fila de v�rtices de um
// grafo (veja GRAPHlists.h e GRAPHlists.c).
//
// Este interface � uma adapta��o do programa 4.9, p.154, do livro
// "Algorithms", 3rd.ed., part 1, de Sedgewick.
////////////////////////////////////////////////////////////////////////


#ifndef _QUEUE_h
#define _QUEUE_h

#include "MYTOOLS.h" // mallocc()

// V�rtice de grafo (veja GRAPHlists.h).
#define vertex int

void 
QUEUEinit( int N);

bool 
QUEUEempty( void);

void 
QUEUEput( vertex v);

vertex 
QUEUEget( void);

void 
QUEUEfree( void);

#endif
