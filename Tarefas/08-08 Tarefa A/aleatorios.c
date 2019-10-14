// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Vitor Santa Rosa Gomes
// Número USP: 10258862
// Tarefa:     A
// Data:       2019-08-08
//
// Baseado em:
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/index.html
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/enunciados.html#tA
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR
// TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// FACILITEI A DISTRIBUIÇÃO DE CÓPIAS. 
//
////////////////////////////////////////////////////////////////////////

// Gera um grafo aleatório com V vértices e A arestas. Em seguida, 
// escreve na entrada padrão os vértices cujo grau de saída esteja em 
// (0, 1, 2, 3, M-3, M-2, M-1, M), em que M é o grau máximo do grafo 
// gerado. Se V <= 30, também é escrita uma representação da lista de 
// adjacências.
// Uso:
//      $ ./aleatorios.bin <V> <A>
// Exemplos:
//      $ ./aleatorios.bin 10 20
//      $ ./aleatorios.bin 100 5000
////////////////////////////////////////////////////////////////////////


#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include "GRAPHlists.h"


void 
die(int code) {
   errno = code;
   fprintf(stderr, "%s\n", strerror(errno));
   exit(code);
}

void 
raise(string message) {
   errno = EXIT_FAILURE;
   fprintf(stderr, "%s\n", message);
   exit(EXIT_FAILURE);
}

void
print_deg(Graph graph, int* degs, string title, int lo, int hi) {
   for (int deg = lo; deg <= hi; deg++) {
      printf("%6s[v]==%-3d:", title, deg);

      for (vertex v = 0; v < graph->V; v++)
         if (degs[v] == deg)
            printf(" %3d", v);

      printf("\n");
   }
}

void 
report_graphrand(Graph (*GRAPHrand)(int, int), 
                 int vertices_count, 
                 int edges_count, 
                 string title) {
   
   clock_t start = clock();
   Graph graph = GRAPHrand(vertices_count, edges_count);
   clock_t end = clock();

   printf("%s(V=%d, A=%d) in %fs\n", 
          title, 
          graph->V, graph->A,
          (float)(end-start)/CLOCKS_PER_SEC);

   int maxindeg  = -1,
       maxoutdeg = -1;
   for (vertex v = 0; v < graph->V; v++) {
      if (graph->indeg[v] > maxindeg)
         maxindeg  = graph->indeg[v];
      if (graph->outdeg[v] > maxoutdeg)
         maxoutdeg = graph->outdeg[v];
   }
   
   print_deg(graph, graph->indeg, "indeg", 0, 3);
   printf("   ...\n");
   print_deg(graph, graph->indeg, "indeg", maxindeg-3, maxindeg);
   printf("\n");

   print_deg(graph, graph->outdeg, "outdeg", 0, 3);
   printf("   ...\n");
   print_deg(graph, graph->outdeg, "outdeg", maxoutdeg-3, maxoutdeg);
   printf("\n");

   if (graph->V < 30)
      GRAPHshow(graph);
   printf("\n");

   GRAPHdestroy(graph);
}

int
main(int argc, char **argv) {
   if (argc != 3)
      raise("Usage: ./aleatorios.bin <V> <A>");

   int vertices_count, edges_count;
   vertices_count = strtol(argv[1], NULL, 10);
   edges_count    = strtol(argv[2], NULL, 10);

   if (errno)
      die(errno);


   report_graphrand(GRAPHrand1,
                    vertices_count, edges_count, 
                    "GRAPHrand1");
   report_graphrand(GRAPHrand2,
                    vertices_count, edges_count, 
                    "GRAPHrand2");

   
   return EXIT_SUCCESS;
}
