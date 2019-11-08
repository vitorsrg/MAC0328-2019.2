// MAC0328 (2019) 
// Altere, modifique, e acrescente à vontade. Sugiro marcar os trechos 
// de código modificados/acrescentados com um comentário do tipo
// "// novo". Preserve o meu bom layout (veja www.ime.usp.br/~pf/
// algoritmos/aulas/layout.html) e não use tabs. 

// Este arquivo: STACK.h (codificação UTF-8)
// Data: 2019-10-04
// Autor: Paulo Feofiloff
//
// Esta é a interface da implementação de uma pilha de vértices de um
// grafo (veja GRAPHlists.h e GRAPHlists.c).
//
// Este interface foi adaptada do programa 4.1, p.137, do livro
// "Algorithms", 3rd.ed., part 1, de Sedgewick.
////////////////////////////////////////////////////////////////////////


#ifndef _STACK_h
#define _STACK_h

#include "MYTOOLS.h" // mallocc()

// Vértice de grafo (veja GRAPHlists.h).
#define vertex int

// Cria uma pilha vazia com espaço para N vértices.
void 
STACKinit( int N);

// Decide se a pilha está vazia.
bool 
STACKempty( void);

// Coloca v no topo da pilha.
void 
STACKpush( vertex v);

// Retira um vértice do topo da pilha.
vertex 
STACKpop( void);

// Devolve o vértice que está no topo da pilha, sem retirá-lo da pilha.
vertex 
STACKpeek( void);

// Libera a memória ocupada pela pilha.
void 
STACKfree( void);

#endif




