// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Andrew Ijano Lopes
// Número USP: 10297797
// Aluno:      Vitor Santa Rosa Gomes
// Número USP: 10258862
// Tarefa:     G
// Data:       2019-09-29
//
// EP feito em programação em pares por ambos os alunos.
//
// Baseado em:
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/index.html
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/enunciados.html#tG
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR
// TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// FACILITEI A DISTRIBUIÇÃO DE CÓPIAS.
//
////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "GRAPHlists.h"

// Escreva um programa que tente resolver o problema da coloração
// vértices. Faça o que puder para que o seu programa use o menor número
// possível de cores. O ponto de partida do seu programa deve ser o
// algoritmo de coloração sequencial. Acrescente a esse ponto de partida
// todas as heurísticas que puder. Por exemplo, a heurística de Brelaz,
// a heurística da troca de cores em componentes bicoloridas, a
// aleatorização, e qualquer outra heurística que você conhecer ou
// inventar. Talvez seja uma boa ideia escrever (e testar) várias
// versões da função de coloração, começando com a mais simples, e
// acrescentando mais heurísticas a cada versão subsequente. Assim será
// fácil ver o valor das heurísticas nos testes. Digite o seu programa
// num arquivo NNN.c, sendo NNN os 3 últimos dígitos do número USP de
// algum dos membros do grupo. O arquivo NNN.c deve ter o cabeçalho de
// identificação usual.  Envie o arquivo ao Paca. O seu programa será
// testado com a versão mais recente das bibliotecas que ficam em
// SANDBOX/bib/. Teste o seu programa com grafos aleatórios. Escreva um
// pequeno relatório sobre o que você aprendeu com os testes. Esse
// relatório deve constar no fim do aquivo-fonte do seu programa. Seu
// programa deve receber argumentos V, E e s, nessa ordem, pela linha de
// comando.
// ./123 1000 200000 77
// Em seguida, deve usar UGRAPHrand1() para construir um grafo aleatório
// com V vértices e E arestas tendo s como semente do gerador de números
// aleatórios. O grafo aleatório deve então ser submetido às funções de
// coloração. O programa deve medir o consumo de tempo de cada função de
// coloração.

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-pedantic"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#pragma region prototypes
// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa na
// ordem natural dos vértices.
// Consumo de tempo: O(V + A)
int UGRAPHvertexColoring_v0(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa numa
// ordem aleatória dos vértices.
// Consumo de tempo: O(V + A)
int UGRAPHvertexColoring_v1(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa dos
// vértices ordenados pela quantidade de cores adjacentes (Variação da
// Heurística de Brelaz).
// Consumo de tempo: O(V*(V + A) + A)
int UGRAPHvertexColoring_v2(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa dos
// vértices ordenados pela quantidade de cores adjacentes considerando
// o pior caso para vértices ainda não coloridos.
// Consumo de tempo: O(V*(logV + V*logV + A) + A)
int UGRAPHvertexColoring_v3(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa dos
// vértices ordenados pela pré-ordem de uma DFS.
// Consumo de tempo: O(V + A)
int UGRAPHvertexColoring_v4(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa dos
// vértices ordenados pela pós-ordem de uma DFS.
// Consumo de tempo: O(V + A)
int UGRAPHvertexColoring_v5(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa dos
// vértices ordenados pela descoberta de uma BFS.
// Consumo de tempo: O(V + A)
int UGRAPHvertexColoring_v6(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa dos
// vértices ordenados pela quantidade de vértices não coloridos em sua
// adjacência.
// Consumo de tempo: O((V + A)*logV)
int UGRAPHvertexColoring_v7(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. Implementa uma coloração gulosa dos
// vértices ordenados pela quantidade de cores adjacentes e escolhe
// vértices de maior grau em caso de empate (Heurística de Brelaz).
// Consumo de tempo: O(V * (V + A))
int UGRAPHvertexColoring_v8(UGraph G, int* color);

// Fornece uma coloração válida dos vértices do grafo não-dirigido G e
// devolve o número de cores efetivamente usadas. A coloração é
// armazenada no vetor color[]. A coloração obtida é a que utilizou o
// menor número de cores dentre diversas heurísticas.
// Consumo de tempo: polinomial em (V + A)
int UGRAPHvertexColoringMin(UGraph G, int* color);
#pragma endregion

#pragma region static functions
static int checkUsedColors(UGraph G, int* colors) {
   int maxColor = -1;
   for (vertex v = 0; v < G->V; v++)
      maxColor = maxColor < colors[v] ? colors[v] : maxColor;

   if (maxColor > G->V) return G->V + 1;

   bool *isColorUsed = mallocc((maxColor + 1) * sizeof(bool));

   for (vertex v = 0; v < maxColor; v++)
      isColorUsed[v] = false;

   for (vertex v = 0; v < G->V; v++)
      isColorUsed[colors[v]] = true;

   int usedColorsCount = 0;

   for (int i = 0; i <= maxColor; i++)
      if (isColorUsed[i]) usedColorsCount++;

   return usedColorsCount;
}

static bool checkGraphColoring(UGraph G, int* color) {
   for (vertex v = 0; v < G->V; v++)
      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (color[v] == color[a->w]) {
            printf("%d %d\n", v, a->w);
            return false;
         }
   return true;
}
#pragma endregion

#pragma region coloring functions
int UGRAPHvertexColoring_v0(UGraph G, int* color) {
   int k = 0;
   bool* available = mallocc(G->V * sizeof(bool));

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   for (vertex v = 0; v < G->V; v++) {
      int i;

      for (i = 0; i < k; i++) available[i] = true;

      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (color[a->w] != -1) available[color[a->w]] = false;

      for (i = 0; i < k; i++)
         if (available[i]) break;

      if (i < k)
         color[v] = i;
      else
         color[v] = k++;
   }

   free(available);
   return k;
}

int UGRAPHvertexColoring_v1(UGraph G, int* color) {
   int k = 0;
   bool* available = mallocc(G->V * sizeof(bool));

   vertex* vv = mallocc(G->V * sizeof(vertex));
   for (int j = 0; j < G->V; j++) vv[j] = j;
   randPermutation(vv, G->V);

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   for (int j = 0; j < G->V; j++) {
      vertex v = vv[j];
      int i;

      for (i = 0; i < k; i++) available[i] = true;

      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (color[a->w] != -1) available[color[a->w]] = false;

      for (i = 0; i < k; i++)
         if (available[i]) break;

      if (i < k)
         color[v] = i;
      else
         color[v] = k++;
   }

   free(available);
   free(vv);
   return k;
}

int UGRAPHvertexColoring_v2(UGraph G, int* color) {
   int k = 0;

   PQinit(G->V);
   int* adjColors = mallocc(G->V * sizeof(int));
   for (vertex v = 0; v < G->V; v++) {
      adjColors[v] = 0;
      PQinsert(v, adjColors);
   }

   bool* available = mallocc(G->V * sizeof(bool));

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   while (!PQempty()) {
      vertex v = PQdelmin(adjColors);
      int i;

      for (i = 0; i < k; i++) available[i] = true;

      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (color[a->w] != -1) available[color[a->w]] = false;

      for (i = 0; i < k; i++)
         if (available[i]) break;

      if (i < k)
         color[v] = i;
      else
         color[v] = k++;

      for (link a = G->adj[v]; a != NULL; a = a->next) {
         bool newColor = true;

         if (color[a->w] != -1)
            continue;

         for (link b = G->adj[a->w]; b != NULL; b = b->next)
            if (b->w != v && color[b->w] == color[v]) newColor = false;

         if (newColor) {
            adjColors[a->w]--;
            PQdec(a->w, adjColors);
         }
      }
   }

   free(adjColors);
   free(available);
   PQfree();
   return k;
}

int UGRAPHvertexColoring_v3(UGraph G, int* color) {
   int k = 0;
   bool* available = mallocc(G->V * sizeof(bool));

   PQinit(G->V);

   int* coloredAdj = mallocc(G->V * sizeof(int));
   for (vertex v = 0; v < G->V; v++) {
      coloredAdj[v] = 0;

      for (link a = G->adj[v]; a != NULL; a = a->next) coloredAdj[v]--;

      PQinsert(v, coloredAdj);
   }

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   while (!PQempty()) {
      vertex v = PQdelmin(coloredAdj);
      int i;

      for (i = 0; i < k; i++) available[i] = true;

      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (color[a->w] != -1) available[color[a->w]] = false;

      for (i = 0; i < k; i++)
         if (available[i]) break;

      if (i < k)
         color[v] = i;
      else
         color[v] = k++;

      for (link a = G->adj[v]; a != NULL; a = a->next) {
         if (color[a->w] != -1) continue;

         coloredAdj[a->w] = 0;

         for (int j = 0; j < k; j++) available[j] = true;

         for (link b = G->adj[a->w]; b != NULL; b = b->next)
            if (color[b->w] != -1)
               available[color[b->w]] = false;
            else
               coloredAdj[a->w]--;

         for (int j = 0; j < k; j++) coloredAdj[a->w] -= !available[j];

         PQdec(a->w, coloredAdj);
      }
   }

   PQfree();
   free(available);
   free(coloredAdj);
   return k;
}

int UGRAPHvertexColoring_v4(UGraph G, int* color) {
   int k = 0;
   bool* available = mallocc(G->V * sizeof(bool));

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   int* pre = mallocc(G->V * sizeof(int));
   int* post = mallocc(G->V * sizeof(int));
   vertex* pa = mallocc(G->V * sizeof(vertex));
   GRAPHdfs(G, pre, post, pa);

   vertex* vv = mallocc(G->V * sizeof(vertex));
   for (vertex v = 0; v < G->V; v++) vv[pre[v]] = v;

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   for (int j = 0; j < G->V; j++) {
      vertex v = vv[j];
      int i;

      for (i = 0; i < k; i++) available[i] = true;

      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (color[a->w] != -1) available[color[a->w]] = false;

      for (i = 0; i < k; i++)
         if (available[i]) break;

      if (i < k)
         color[v] = i;
      else
         color[v] = k++;
   }

   free(available);
   free(pre);
   free(post);
   free(pa);
   free(vv);
   return k;
}

int UGRAPHvertexColoring_v5(UGraph G, int* color) {
   int k = 0;
   bool* available = (bool*)mallocc(G->V * sizeof(bool));

   int* pre = mallocc(G->V * sizeof(int));
   int* post = mallocc(G->V * sizeof(int));
   vertex* pa = mallocc(G->V * sizeof(vertex));
   GRAPHdfs(G, pre, post, pa);

   vertex* vv = mallocc(G->V * sizeof(vertex));
   for (vertex v = 0; v < G->V; v++) vv[post[v]] = v;

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   for (int j = 0; j < G->V; j++) {
      vertex v = vv[j];
      int i;

      for (i = 0; i < k; i++) available[i] = true;

      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (color[a->w] != -1) available[color[a->w]] = false;

      for (i = 0; i < k; i++)
         if (available[i]) break;

      if (i < k)
         color[v] = i;
      else
         color[v] = k++;
   }

   free(available);
   free(pre);
   free(post);
   free(pa);
   free(vv);
   return k;
}

int UGRAPHvertexColoring_v6(UGraph G, int* color) {
   int k = 0;
   bool* available = mallocc(G->V * sizeof(bool));
   bool* visited = mallocc(G->V * sizeof(bool));

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   for (vertex v = 0; v < G->V; v++) visited[v] = false;

   QUEUEinit(G->V);
   int w = 0;
   while (w < G->V) {
      QUEUEput(w);
      visited[w] = true;

      while (!QUEUEempty()) {
         vertex v = QUEUEget();
         int i;

         for (i = 0; i < k; i++) available[i] = true;

         for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (color[a->w] != -1) available[color[a->w]] = false;

            if (!visited[a->w]) {
               QUEUEput(a->w);
               visited[a->w] = true;
            }
         }

         for (i = 0; i < k; i++)
            if (available[i]) break;

         if (i < k)
            color[v] = i;
         else
            color[v] = k++;
      }

      while (w < G->V && color[w] != -1) w++;
   }

   QUEUEfree();
   free(available);
   free(visited);
   return k;
}

int UGRAPHvertexColoring_v7(UGraph G, int* color) {
   int k = 0;
   bool* available = mallocc(G->V * sizeof(bool));

   PQinit(G->V);

   int* coloredAdj = mallocc(G->V * sizeof(int));
   for (vertex v = 0; v < G->V; v++) {
      coloredAdj[v] = 0;

      for (link a = G->adj[v]; a != NULL; a = a->next) coloredAdj[v]--;

      PQinsert(v, coloredAdj);
   }

   for (vertex v = 0; v < G->V; v++) color[v] = -1;

   while (!PQempty()) {
      vertex v = PQdelmin(coloredAdj);
      int i;

      for (i = 0; i < k; i++) available[i] = true;

      for (link a = G->adj[v]; a != NULL; a = a->next) {
         if (color[a->w] != -1) {
            available[color[a->w]] = false;
         } else {
            coloredAdj[a->w]++;
            PQdec(a->w, coloredAdj);
         }
      }

      for (i = 0; i < k; i++)
         if (available[i]) break;

      if (i < k)
         color[v] = i;
      else
         color[v] = k++;
   }

   PQfree();
   free(available);
   free(coloredAdj);
   return k;
}

int UGRAPHvertexColoring_v8(UGraph G, int* color) {
   int k = 0;

   int* degrees = mallocc(G->V * sizeof(int));
   int* adjColors = mallocc(G->V * sizeof(int));
   bool* available = mallocc(G->V * sizeof(bool));

   for (vertex v = 0; v < G->V; v++) {
     degrees[v] = GRAPHindeg(G, v);
     adjColors[v] = 0;
     color[v] = -1;
   }

   for (int c = 0; c < G->V; c++) {
      vertex v = 0;
      for (vertex w = 1; w < G->V; w++) {
         bool vIsColored = color[v] != -1;
         bool wIsNotColored = color[w] == -1;
         bool moreAdjColors = adjColors[v] < adjColors[w];
         bool higherDegree =
             adjColors[v] == adjColors[w] && degrees[v] <= degrees[w];
         bool wIsBetter =
             wIsNotColored && (moreAdjColors || higherDegree);

         if (vIsColored || wIsBetter) v = w;
      }

      int i;

      for (i = 0; i < k; i++) available[i] = true;

      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (color[a->w] != -1) available[color[a->w]] = false;

      for (i = 0; i < k; i++)
         if (available[i]) break;

      if (i < k)
         color[v] = i;
      else
         color[v] = k++;

      for (link a = G->adj[v]; a != NULL; a = a->next) {
         bool newColor = true;

         for (link b = G->adj[a->w]; b != NULL; b = b->next)
            if (b->w != v && color[b->w] == color[v]) newColor = false;

         if (newColor) {
            adjColors[a->w]++;
         }
      }
   }

   free(degrees);
   free(adjColors);
   free(available);
   return k;
}

int UGRAPHvertexColoringMin(UGraph G, int* color) {
   int (*colorers[])(UGraph, int*) = {
       UGRAPHvertexColoring_v0, UGRAPHvertexColoring_v1,
       UGRAPHvertexColoring_v2, UGRAPHvertexColoring_v3,
       UGRAPHvertexColoring_v4, UGRAPHvertexColoring_v5,
       UGRAPHvertexColoring_v6, UGRAPHvertexColoring_v7,
       UGRAPHvertexColoring_v8};
   int count = sizeof(colorers) / sizeof(colorers[0]);

   int* tmpColor = mallocc(G->V * sizeof(int));
   int minColors = INT_MAX;

   for (int i = 0; i < count; i++) {
      int k = colorers[i](G, tmpColor);

      if (k < minColors) {
         minColors = k;
         memcpy(color, tmpColor, G->V * sizeof(int));
      }
   }

   return minColors;
}
#pragma endregion

#pragma region main
int main(int argc, char** argv) {
   char buffer[(int)10E5];
   setbuf(stdout, buffer);
   // setbuf(stdout, NULL);

   int (*colorers[])(UGraph, int*) = {
       UGRAPHvertexColoring_v0, UGRAPHvertexColoring_v1,
       UGRAPHvertexColoring_v2, UGRAPHvertexColoring_v3,
       UGRAPHvertexColoring_v4, UGRAPHvertexColoring_v5,
       UGRAPHvertexColoring_v6, UGRAPHvertexColoring_v7,
       UGRAPHvertexColoring_v8, UGRAPHvertexColoringMin};
   int count = sizeof(colorers) / sizeof(colorers[0]);
   const char* names[] = {"v0", "v1", "v2", "v3", "v4",
                          "v5", "v6", "v7", "v8", "Min"};

   int V, A, s;
   V = strtol(argv[1], NULL, 10);
   A = strtol(argv[2], NULL, 10);
   s = strtol(argv[3], NULL, 10);

   UGraph G = UGRAPHrand1(V, A);
   printf("G(V=%d, A=%d)\n", G->V, G->A);
   printf("----------------------\n");
   printf("versão cores  segundos\n");
   printf("----------------------\n");

   int* color = mallocc(G->V * sizeof(int));
   int colorsCount;
   clock_t start, end;
   float seconds;

   for (int i = 0; i < count; i++) {
      srand(s);

      start = clock();
      colorsCount = colorers[i](G, color);
      end = clock();

      assert(checkGraphColoring(G, color) && "Valid Coloring");
      assert(colorsCount == checkUsedColors(G, color));
      
      seconds = (float)(end - start) / CLOCKS_PER_SEC;
      printf("%6s %6d %8f\n", names[i], colorsCount, seconds);
   }

   return EXIT_SUCCESS;
   // return EXIT_FAILURE;
}
#pragma endregion

#pragma region report
// Considere o seguinte batch de testes para este programa (código em 
// bash script):
//
// for (( v=0; v<=300; v++ )); do
//    for (( a=0; a<v*(v-1)/2; a+=2*v )); do
//       ./862.bin $v $a 0
//    done
// done
//
// Sejam
//    1) T=11325 a quantidade de instâncias geradas pelo batch,
//    2) V e A o resultado de UGRAPHrand1 para cada uma das instâncias
//       do programa,
//    3) Ci a função UGRAPHvertexColoring_v{i},
//    4) Cmin a função UGRAPHvertexColoringMin,
//    5) c(Ci) a quantidade de cores usada pela função Ci, e
//    6) t(Ci) o tempo usado pela função Ci.
//
// Sinopse dos métodos:
//
//    Ci    |  Primeira cor válida dos vértices em ordem
// ---------+----------------------------------------------------------
//    v0    |  natural 0..V-1
//    v1    |  aleatória
//    v2    |  decrescente de cores adjacentes
//    v3    |  decrescente de cores adjacentes mais vizinhos sem cor
//    v4    |  da pré-ordem de uma DFS
//    v5    |  da pós-ordem de uma DFS
//    v6    |  da descoberta de uma BFS
//    v7    |  decrescente de vizinhos não coloridos
//    v8    |  decrescente de <cores adjacentes, grau> (H. de Brelaz)
// ---------+----------------------------------------------------------
//    Min   |  Melhor coloração resultante dos C0..C8
//
// A média de cores que cada Ci usou acima de Cmin e a média de tempo
// usado por Ci são
//
//          |  Paucas cores?           Tempo viável?
// ---------+-----------------------------------------------
//    Ci    |  (c(Ci)-c(Cmin))/V/T     t(Ci)/(V+A)/T  
// ---------+-----------------------------------------------
//    v0    |  0.0193188111208324      0.0000000259108549
//    v1    |  0.0190192108372629      0.0000000237734473
//    v2    |  0.0187942994831212      0.0000023220802077
//    v3    |  0.0023870056126589      0.0000014086968265
//    v4    |  0.0184214561993705      0.0000000396639296
//    v5    |  0.0202626158215407      0.0000000372441115
//    v6    |  0.0194391730412765      0.0000000229622349
//    v7    |  0.0031143700837454      0.0000000515163883
//    v8    |  0.0069814536418083      0.0000059485375623
// ---------+-----------------------------------------------
//    Min   |  0.0000000000000000      0.0000098441128435
//
////////////////////////////////////////////////////////////////////////
//
//          |  Paucas cores?           Tempo viável?
// ---------+-----------------------------------------------
//    Ci    |  (c(Ci)-c(Cmin))/V/T     t(Ci)/(V+A)/T  
// ---------+-----------------------------------------------
//    v0    |  4.8022958057395142      0.0000000322622366
//    v1    |  4.7248565121412804      0.0000000292609658
//    v2    |  0.8852097130242825      0.0000013672771137
//    v3    |  1.6003532008830021      0.0000017040411164
//    v4    |  4.6458278145695369      0.0000000486832170
//    v5    |  4.9579690949227375      0.0000000459355224
//    v6    |  4.8403532008830021      0.0000000282175398
//    v7    |  1.6939514348785871      0.0000000807870574
//    v8    |  0.3117880794701987      0.0000070773829524
// ---------+-----------------------------------------------
//    Min   |  0.0000000000000000      0.0000103935030442
//
////////////////////////////////////////////////////////////////////////
//
// É possível perceber que v3, v7 e v8 produzem os melhores resultados,
// enquanto v2, v3 e v8 levam mais tempo por sua natureza pelo menos 
// quadrática em V+E.
//
// Interessantemente, v3 e v7 performaram melhor que a Heurística de 
// Brelaz (~v2 e v8); em particular, v7 possui tempo de execução viável 
// no tamanho do grafo.
//
// Embora não estejamos imediatamente interessados no tempo de execução 
// --- porém na quantida de cores ---, v2, v3 e v8 impediram testes com 
// grafos maiores.
//
// Como todas as heurísticas testadas tentam usar a primeira cor 
// disponível considerando uma ordem natural das cores, fazer troca de
// cores de componentes bicoloridas necessariamente não diminuirá a 
// quantidade de cores usadas.
// Tentativa de prova: as componentes bicoloridas não podem ter cores de
// valor menor pois já estão adjacentes a elas (pela forma como suas 
// cores foram escolhidas). Assim, só será possível trocar as cores das 
// componentes por cores de valor maior, não diminuindo (e possivelmente
// aumentando) a quantidade de cores.
#pragma endregion

#pragma GCC diagnostic pop
