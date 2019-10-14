// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Andrew Ijano Lopes
// Número USP: 10297797
// Aluno:      Vitor Santa Rosa Gomes
// Número USP: 10258862
// Tarefa:     B
// Data:       2019-08-29
//
// EP feito em programação em pares por ambos os alunos.
//
// Baseado em:
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/index.html
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/enunciados.html#tC
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

// Recebe um grafo G e imprima (1) a sequência de vértices de um ciclo 
// de G ou (2) uma permutação topológica dos vértices de G. No caso (1), 
// imprima a sequência em uma linha do terminal com um - entre cada 
// vértice e o seguinte. (Lembre-se de que o último vértice deve ser 
// igual ao primeiro.) No caso (2), imprima a permutação em uma linha 
// do terminal com um entre cada vértice e o seguinte. 
bool
CouT1(Graph G);

// Variante de CouT1() que seja baseada na versão on-the-fly de 
// GRAPHhasCycle().
bool
CouT2(Graph G);

// Variante de CouT1() que seja baseada na função top() da tarefa B.
bool
CouT3(Graph G);

// Teste do módulo.
int
main(int argc, char **argv);
// #endregion

void 
_reverse(int* arr, int lo, int hi) {
   int tmp;
   for (int i = lo; i < (hi+lo)/2; i++) {
      tmp = arr[i];
      arr[i] = arr[hi-1-i+lo];
      arr[hi-1-i+lo] = tmp;
   }
}

void
_printtopo(Graph G, int* post) {
   vertex *perm = malloc(G->V * sizeof(vertex));

   for (vertex i = 0; i < G->V; i++) 
      perm[post[i]] = i;

   for (int i = G->V - 1; i >= 0; i--) 
      printf("%d ", post[i]);
   printf("\n");

   free(perm);
}

void
_printcycle(vertex* cycle, int size) {
   for (vertex v = 0; v < size-1; v++)
      printf("%d-", cycle[v]);
   printf("%d\n", cycle[size-1]);
}

bool
CouT1(Graph G) {
   int* pre = mallocc(G->V*sizeof(int));
   int* post = mallocc(G->V*sizeof(int));
   vertex* parent = mallocc(G->V*sizeof(vertex));

   GRAPHdfs(G, pre, post, parent);

   for (vertex v = 0; v < G->V; v++) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;

         if (post[v] < post[a->w]) {
            vertex *cycle = mallocc(G->V*sizeof(vertex));
            int top = 0;

            cycle[top++] = v;
            for (vertex u = v; u != w; u = parent[u])
               cycle[top++] = parent[u];
            cycle[top++] = v;

            _reverse(cycle, 1, top-1);

             _printcycle(cycle, top);

            free(pre);
            free(post);
            free(parent);
            free(cycle);
            return true;
         }
      }
   }


   _printtopo(G, post);

   free(pre);
   free(post);
   free(parent);
   return false;
}

bool 
_dfsRcycle(Graph G, vertex v, 
           int *pre, int *post, vertex *pa,
           int* cnt, int* cntt, 
           vertex *cycle, int *cycle_size) { 
   pre[v] = (*cnt)++;

   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;

      if (pre[w] == -1) {
         if (_dfsRcycle(G, w, 
                        pre, post, pa, 
                        cnt, cntt, cycle, cycle_size)) {
            if (cycle[*cycle_size] != -1) {
               cycle[(*cycle_size)++] = v;
               if (v == cycle[0])
                  cycle[(*cycle_size)] = -1;
            }

           return true; 
         } 
      } else {
         if (post[w] == -1) {
            cycle[(*cycle_size)++] = w;
            cycle[(*cycle_size)++] = v;

            return true;
         }
      }
   }
   post[v] = (*cntt)++;
   return false;
}

bool
CouT2(Graph G) {
   int* pre = mallocc(G->V*sizeof(int));
   int* post = mallocc(G->V*sizeof(int));
   int* parent = mallocc(G->V*sizeof(vertex));
   int cnt = 0,
       cntt = 0;

   for (vertex v = 0; v < G->V; v++)
      pre[v] = post[v] = -1;


   vertex *cycle = malloc(G->V*sizeof(vertex));
   int cycle_size = 0;

   for (int i = 0; i < G->V; i++)
      cycle[i] = 0;

   for (vertex v = 0; v < G->V; v++)
      if (pre[v] == -1) {
         parent[v] = v;
         if (_dfsRcycle(G, v, 
                        pre, post, parent, 
                        &cnt, &cntt, 
                        cycle, &cycle_size)) {

            _printcycle(cycle, cycle_size);

            free(pre);
            free(parent);
            free(post);
            free(cycle);
            return true;
         }
      }   

   _printtopo(G, post);

   free(pre);
   free(parent);
   free(post);
   free(cycle);
   return false;
}

bool
CouT3(Graph G) {
   int* indeg = malloc(G->V*sizeof(int));

   for (vertex v = 0; v < G->V; v++)
      indeg[v] = 0;

   for (vertex v = 0; v < G->V; v++) 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         indeg[a->w]++;


   vertex* topo = mallocc(G->V*sizeof(int));
   int cnt = G->V;

   vertex* queue = malloc(G->V*sizeof(vertex));
   int lo = 0, 
       hi = 0;

   for (vertex v = 0; v < G->V; v++)
      if (!indeg[v])
         queue[hi++] = v;

   while (lo < hi) {
      vertex v = queue[lo++];
      topo[v] = --cnt;

      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (!--indeg[a->w])
            queue[hi++] = a->w;
   }


   if (cnt == 0) {
      _printtopo(G, topo);

      free(indeg);
      free(topo);
      free(queue);
      return false;
   }

   vertex* stack = malloc(G->V*sizeof(vertex));
   vertex* parent = malloc(G->V*sizeof(vertex));
   bool* visited = mallocc(G->V*sizeof(bool));
   bool* alive = mallocc(G->V*sizeof(bool));
   int top = 0;

   for (vertex v = 0; v < G->V; v++) {
      visited[v] = !indeg[v];
      alive[v] = false;
      parent[v] = -1;
   }

   for (vertex v = 0; v < G->V; v++)
      if (!visited[v]) {
         stack[top++] = v;
         visited[v] = true;

         while (top) {
            vertex u = stack[top-1];

            if (alive[u]) {
               alive[u] = false;
               top--;
               continue;
            }

            alive[u] = true;

            for (link a = G->adj[u]; a != NULL; a = a->next) {
               if (alive[a->w]) {
                  vertex *cycle = mallocc(G->V*sizeof(vertex));
                  int size = 0;

                  cycle[size++] = u;
                  for (vertex w = u; w != a->w; w = parent[w])
                     cycle[size++] = parent[w];
                  cycle[size++] = u;

                  _reverse(cycle, 1, size-1);

                  _printcycle(cycle, size);

                  free(indeg);
                  free(topo);
                  free(queue);
                  free(stack);
                  free(parent);
                  free(visited);
                  free(alive);
                  free(cycle);
                  return true;
               }
               if (!visited[a->w]) {
                  visited[a->w] = true;
                  stack[top++] = a->w;
                  parent[a->w] = u;
               }
            }
         }
      }

   exit(EXIT_FAILURE);
   return -1;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-pedantic"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
int main(int argc, char **argv) {
   setbuf(stdout, NULL);


   #pragma region init
   int V, A, s;
   V = strtol(argv[1], NULL, 10);
   A = strtol(argv[2], NULL, 10);
   s = strtol(argv[3], NULL, 10);

   srand(s);

   printf("algrth\tcycle?\ttime\n");

   Graph G = GRAPHrand1(V, A);
   clock_t start, end;
   float seconds;

   bool test0, test1, test2, test3;
   #pragma endregion

   #pragma region true
   start = clock();
   test0 = GRAPHhasCycle_v1(G);
   end = clock();

   seconds = (float) (end-start)/CLOCKS_PER_SEC;
   
   printf("true\t%d\t%f\n", test0, seconds);
   #pragma endregion

   #pragma region count1
   start = clock();
   test1 = CouT1(G);
   end = clock();

   seconds = (float) (end-start)/CLOCKS_PER_SEC;
   
   printf("cout1\t%d\t%f\n", test1, seconds);
   #pragma endregion

   #pragma region count2
   start = clock();
   test2 = CouT2(G);
   end = clock();

   seconds = (float) (end-start)/CLOCKS_PER_SEC;
   
   printf("cout2\t%d\t%f\n", test2, seconds);
   #pragma endregion

   #pragma region count3
   start = clock();
   test3 = CouT3(G);
   end = clock();
   seconds = (float) (end-start)/CLOCKS_PER_SEC;
   
   printf("cout3\t%d\t%f\n", test3, seconds);
   #pragma endregion


   printf("\n");

   return !(   test0 == test1
            && test0 == test2
            && test0 == test3);
}
#pragma GCC diagnostic pop

