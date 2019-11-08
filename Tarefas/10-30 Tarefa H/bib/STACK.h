// MAC0328 (2019) 
// Altere, modifique, e acrescente � vontade. Sugiro marcar os trechos 
// de c�digo modificados/acrescentados com um coment�rio do tipo
// "// novo". Preserve o meu bom layout (veja www.ime.usp.br/~pf/
// algoritmos/aulas/layout.html) e n�o use tabs. 

// Este arquivo: STACK.h (codifica��o UTF-8)
// Data: 2019-10-04
// Autor: Paulo Feofiloff
//
// Esta � a interface da implementa��o de uma pilha de v�rtices de um
// grafo (veja GRAPHlists.h e GRAPHlists.c).
//
// Este interface foi adaptada do programa 4.1, p.137, do livro
// "Algorithms", 3rd.ed., part 1, de Sedgewick.
////////////////////////////////////////////////////////////////////////


#ifndef _STACK_h
#define _STACK_h

#include "MYTOOLS.h" // mallocc()

// V�rtice de grafo (veja GRAPHlists.h).
#define vertex int

// Cria uma pilha vazia com espa�o para N v�rtices.
void 
STACKinit( int N);

// Decide se a pilha est� vazia.
bool 
STACKempty( void);

// Coloca v no topo da pilha.
void 
STACKpush( vertex v);

// Retira um v�rtice do topo da pilha.
vertex 
STACKpop( void);

// Devolve o v�rtice que est� no topo da pilha, sem retir�-lo da pilha.
vertex 
STACKpeek( void);

// Libera a mem�ria ocupada pela pilha.
void 
STACKfree( void);

#endif




