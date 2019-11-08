// MAC0328 (2019) 
// Altere, modifique, e acrescente � vontade. Sugiro marcar os trechos 
// de c�digo modificados/acrescentados com um coment�rio do tipo
// "// novo". Preserve o meu bom layout (veja www.ime.usp.br/~pf/
// algoritmos/aulas/layout.html) e n�o use tabs. 

// Este arquivo: STACK.c (codifica��o UTF-8)
// Data: 2019-10-04
// Autor: Paulo Feofiloff
//
// Esta � uma implementa��o de uma pilha de v�rtices de um grafo (veja
// GRAPHlists.h e GRAPHlists.c).
//
// O c�digo � uma adapta��o do programa 4.4, p.146, do livro
// "Algorithms", 3rd.ed., part 1, de Sedgewick.
////////////////////////////////////////////////////////////////////////


#include "STACK.h"
// inclui MYTOOLS.h (que cont�m a defini��o de mallocc())

// A pilha � implementada no vetor stack[0..N-1].
static vertex *stack;
static int top;

void 
STACKinit( int N) { 
   stack = mallocc( N * sizeof (vertex)); 
   top = 0; 
}

bool 
STACKempty( ) { 
   return top == 0; 
}

void 
STACKpush( vertex v) { 
   stack[top++] = v; 
}

int 
STACKpop( ) { 
   return stack[--top]; 
}

int 
STACKpeek( ) { 
   return stack[top-1]; 
}

void 
STACKfree( ) { 
   free( stack);
}

