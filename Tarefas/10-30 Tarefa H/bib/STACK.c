// MAC0328 (2019) 
// Altere, modifique, e acrescente à vontade. Sugiro marcar os trechos 
// de código modificados/acrescentados com um comentário do tipo
// "// novo". Preserve o meu bom layout (veja www.ime.usp.br/~pf/
// algoritmos/aulas/layout.html) e não use tabs. 

// Este arquivo: STACK.c (codificação UTF-8)
// Data: 2019-10-04
// Autor: Paulo Feofiloff
//
// Esta é uma implementação de uma pilha de vértices de um grafo (veja
// GRAPHlists.h e GRAPHlists.c).
//
// O código é uma adaptação do programa 4.4, p.146, do livro
// "Algorithms", 3rd.ed., part 1, de Sedgewick.
////////////////////////////////////////////////////////////////////////


#include "STACK.h"
// inclui MYTOOLS.h (que contém a definição de mallocc())

// A pilha é implementada no vetor stack[0..N-1].
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

