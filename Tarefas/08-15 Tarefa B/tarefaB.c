// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Andrew Ijano Lopes
// Número USP: 10297797
// Aluno:      Vitor Santa Rosa Gomes
// Número USP: 10258862
// Tarefa:     B
// Data:       2019-08-15
//
// EP feito em programação em pares por ambos os alunos.
//
// Baseado em:
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/index.html
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/enunciados.html#tB
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR
// TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// FACILITEI A DISTRIBUIÇÃO DE CÓPIAS.
//
////////////////////////////////////////////////////////////////////////

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "GRAPHlists.h"
#include "PQ.h"

// #region API

// Recebe um grafo e uma permutação perm[0..V-1] dos seus vértices e
// decide se a permutação é topológica.
int tperm(Graph graph, int perm[]);

// Decide se um grafo é topológico aplicando o seguinte algoritmo:
// remover vértices fonte do grafo indutivamente.
//
// Se todos os vértices forem removidos, o grafo é topológico: a ordem
// de remoção é uma ordenação topológica do grafo, visto que todos os
// vizinhos de um vértice são removidos depois dele.
//
// Se não, o grafo não é topológico: existe um subgrafo cujos (todos os)
// vértices possuem ao menos uma aresta incidente. Assim, neste subgrafo
// não existe um vértice capaz de ter o menor valor numa ordenação
// topológica qualquer.
// Como o subgrafo é induzido por remoção de vértices, o grafo original
// também não possui uma ordenação topológica, a qual implicaria numa
// topologia do subgrafo (contradição).
int top(Graph graph);

// #endregion

int tperm(Graph graph, vertex *perm) {
   vertex *topo = malloc(graph->V * sizeof(vertex));
   for (int i = 0; i < graph->V; i++) topo[perm[i]] = i;

   for (vertex v = 0; v < graph->V; v++)
      for (link a = graph->adj[v]; a != NULL; a = a->next)
         if (topo[v] >= topo[a->w]) {
            free(topo);
            return false;
         } 
   free(topo);
   return true;
}

int top(Graph graph) {
   int *indeg = malloc(graph->V * sizeof(vertex));
   memcpy(indeg, graph->indeg, graph->V * sizeof(vertex));

   PQinit(graph->V);

   for (vertex v = 0; v < graph->V; v++) PQinsert(v, indeg);

   while (!PQempty()) {
      vertex v = PQdelmin(indeg);

      if (indeg[v]) {
         free(indeg);
         return false;
      }

      for (link node = graph->adj[v]; node != NULL; node = node->next) {
         indeg[node->w]--;
         PQdec(node->w, indeg);
      }
   }

   free(indeg);
   return true;
}

// Árvore de recursão do grafo em https://www.ime.usp.br/~pf/\
// algoritmos_para_grafos/aulas/figs/Sedgewick-Wayne/\
// TinyNetworkOnly.png

// Grafo:
// 0: 2 4
// 1: 3
// 2: 7
// 3: 6
// 4: 5 7
// 5: 1 4 7
// 6: 0 2 4
// 7: 3 5

// Stack trace:
// v-w dfsR(G,w)              pre[w]   pa[w]
// -----------------------------------------
// 0 dfsR(G,0)                0        0
// 0-2 dfsR(G,2)              1        0
//   2-7 dfsR(G,7)            2        2
//     7-3 dfsR(G,3)          3        7
//       3-6 dfsR(G,6)        4        3
//         6-0
//         6-2
//         6-4 dfsR(G,4)      5        6
//           4-5 dfsR(G,5)    6        4
//             5-1 dfsR(G,1)  7        5
//               1-3
//               1
//             5-4
//             5-7
//             5
//           4-7
//           4
//         6
//       3
//     7-5
//     7
//   2
// 0-4
// 0

// Final state:
// w  |  pre   pa
// ---+-----------
// 0  |  0     0
// 1  |  7     5
// 2  |  1     0
// 3  |  3     7
// 4  |  5     6
// 5  |  6     4
// 6  |  4     3
// 7  |  2     2
