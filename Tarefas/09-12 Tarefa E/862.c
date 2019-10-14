// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Vitor Santa Rosa Gomes
// Número USP: 10258862
// Tarefa:     B
// Data:       2019-09-12
//
// EP feito em programação em pares por ambos os alunos.
//
// Baseado em:
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/index.html
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/enunciados.html#tE
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR
// TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// FACILITEI A DISTRIBUIÇÃO DE CÓPIAS.
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "GRAPHlists.h"


// #region API

// Algoritmo ingênuo para aresta-biconexão.
// Primeiro, verifica-se que o grafo é conexo com UGRAPHisConnected(). 
// Se sim, usa-se UGRAPHreach() para verificar se alguma aresta numa 
// árvore DFS do grafo é ponte.
// Cúbico em V: V(V+A)
bool
UGRAPHisBiconnected(UGraph G);

// #endregion API


bool
UGRAPHisBiconnected(UGraph G) {
   if (!UGRAPHisConnected(G))
      return false;

   vertex* stack = malloc(G->V*sizeof(vertex));
   bool* visited = mallocc(G->V*sizeof(bool));
   int top = 0;

   for (vertex v = 0; v < G->V; v++)
      visited[v] = false;

   stack[top++] = (vertex) 0;
   visited[0]   = true;

   while (top) {
      vertex v = stack[--top];

      for (link a = G->adj[v]; a != NULL; a = a->next) {
         if (!visited[a->w]) {
            vertex w = a->w;
            bool isBridge;

            visited[w] = true;
            stack[top++] = w;

            a->w = (vertex) v; // risky arc removal
            isBridge = !UGRAPHreach(G, v, w);
            a->w = w;

            if (isBridge)
               return false;
         }
      }
   }

   return true;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-pedantic"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
int main(int argc, char **argv) {
   setbuf(stdout, NULL);

   int V, A, s;
   V = strtol(argv[1], NULL, 10);
   A = strtol(argv[2], NULL, 10);
   s = strtol(argv[3], NULL, 10);

   srand(s);

   UGraph G = UGRAPHrand1(V, A);
   bool testUGRAPHisEbc_v3, testUGRAPHisBiconnected;
   clock_t start, end;
   float seconds;
   printf("G(V=%d, A=%d)\n", G->V, G->A);


   start = clock();
   testUGRAPHisEbc_v3 = UGRAPHisEbc_v3(G);
   end = clock();
   seconds = (float) (end-start)/CLOCKS_PER_SEC;
   printf("UGRAPHisEbc_v3           %1d %fs\n", 
          testUGRAPHisEbc_v3, 
          seconds);


   start = clock();
   testUGRAPHisBiconnected = UGRAPHisBiconnected(G);
   end = clock();
   seconds = (float) (end-start)/CLOCKS_PER_SEC;
   printf("UGRAPHisBiconnected      %1d %fs\n", 
          testUGRAPHisBiconnected, 
          seconds);


   return !(testUGRAPHisEbc_v3 == testUGRAPHisBiconnected);
}
#pragma GCC diagnostic pop
