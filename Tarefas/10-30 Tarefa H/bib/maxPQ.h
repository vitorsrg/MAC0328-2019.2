// MAC0328 (2019) 
// Altere, modifique, e acrescente à vontade. Sugiro marcar os trechos 
// de código modificados/acrescentados com um comentário do tipo
// "// novo". Preserve o meu bom layout (veja www.ime.usp.br/~pf/
// algoritmos/aulas/layout.html) e não use tabs. 

// Este arquivo: maxPQ.h
// Data: 2019-10-14
// Autor: Paulo Feofiloff
//
// Esta é a interface da implementação de uma fila priorizada
// "decrescente" (= max-oriented priority queue) de vértices de um grafo
// (veja GRAPHlists.h e GRAPHlists.c).
//
// O código é uma adaptação do programa 9.11, p.390, do livro
// "Algorithms", 3rd.ed., part 1, de Sedgewick.
////////////////////////////////////////////////////////////////////////


#ifndef _maxPQ_h
#define _maxPQ_h

#include "MYTOOLS.h" // mallocc()

// Os vértices (de grafos) são inteiros não-negativos (veja
// GRAPHlists.h).
#define vertex int

// As prioridades da fila são dadas em um vetor prty[] indexado por
// vértices. (O vetor é fornecido pelo usuário.) Se prty[v] > prty[w]
// então o vértice v tem prioridade maior que o vértice w. O primeiro 
// vértice da fila tem prioridade máxima.

void 
maxPQinit( int V);
// Supõe-se que a fila tem no máximo V vértices.

int 
maxPQempty( void);

void 
maxPQinsert( vertex v, int prty[]);

// Devolve um vértice v da fila que maximiza prty[v]. Esse vértice é
// retirado da fila.
vertex 
maxPQdelmax( int prty[]);

// Rearranja a fila depois que prty[w] aumentou (portanto move w em
// direção ao início da fila).
void 
maxPQaug( vertex w, int prty[]);

void 
maxPQfree( );

#endif
