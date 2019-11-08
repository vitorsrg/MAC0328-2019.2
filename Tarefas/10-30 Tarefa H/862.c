// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Vitor Santa Rosa Gomes
// Número USP: 10258862
// Tarefa:     G
// Data:       2019-09-29
//
// EP feito em programação em pares por ambos os alunos.
//
// Baseado em:
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/index.html
// https://www.ime.usp.br/~pf/mac0328-2019/tarefas/enunciados.html#tH
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR
// TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// FACILITEI A DISTRIBUIÇÃO DE CÓPIAS.
//
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Tarefa H: emparelhamentos, altura, etc. (para 2019-10-30)
//
// 1. Esta tarefa consiste em três itens que não têm relação entre si.
//
//    * [SIMPLIFIQUEI O ENUNCIADO!] Altura de árvore radicada. Escreva 
//    uma função que receba uma árvore radicada T e a raiz r da árvore e
//    devolva a altura da árvore. O protótipo da função deve ser
//       int altura( Graph T, vertex r);
//
//    * Emparelhamento maximal. Escreva uma função que calcule um 
//    emparelhamento maximal num grafo não-dirigido arbitrário. O 
//    emparelhamento deve ser representado por um vetor match[]. A 
//    função deve devolver o tamanho do emparelhamento.
//
//    * Fim do algoritmo húngaro. No fim da última iteração do 
//    algoritmo húngaro para emparelhamento máximo em grafo bipartido, 
//    é possível que o conjunto X seja vazio? É possível que X seja o 
//    conjunto de todos os vértices? Discuta essas duas possibilidades.
//
// 2. Não é obrigatório compilar nem testar as duas função. (Mas você 
// pode querer fazer isso para ter certeza de que a função está 
// correta.)
//
// 3. Digite os códigos das duas funções. Digite sua resposta ao 
// terceiro item acima como se fosse um /* comentário */ de um programa.
// Coloque tudo num arquivo NNN.c, sendo NNN os 3 últimos dígitos do seu
// número USP. O arquivo NNN.c deve ter o cabeçalho de identificação 
// usual. Envie o arquivo ao Paca.
//
// 4. Esta tarefa é individual: cada aluno deve fazer a sua.
//
// 5. Prazo de entrega no Paca: dia 30/10, quarta-feira, até as 23h59m.
////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmacro-redefined"
#include "GRAPHlists.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-pedantic"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#pragma region prototypes
int
altura(Graph T, vertex r);

void
UGRAPHmaximalMaching(UGraph G, vertex* match);
#pragma endregion

#pragma region static functions
bool
checkHeight(Graph T, vertex r, int height) {
   if (height < 0)
      return false;

   for (link a = T->adj[r]; a != NULL; a = a->next)
      if (!checkHeight(T, a->w, height-1))
         return false;
   
   return true;
}

bool
checkMaximalMaching(UGraph G, vertex* match) {
   for (vertex v = 0; v < G->V; v++)
      if (match[v] != -1 && v != match[match[v]])
         return false;

   for (vertex v = 0; v < G->V; v++)
      if (match[v] == -1)
         for (link a = G->adj[v]; a != NULL; a = a->next)
            if (match[v] == match[a->w])
               return false;

   return true;
}
#pragma endregion

#pragma region functions
int
altura(Graph T, vertex r) {
   int maxHeight = 0;

   for (link a = T->adj[r]; a != NULL; a = a->next) {
      int height = altura(T, a->w) + 1;

      if (maxHeight < height)
         maxHeight = height;
   }

   return maxHeight;
}

void
UGRAPHmaximalMaching(UGraph G, vertex* match) {
   bool* discovered = mallocc(G->V*sizeof(bool));
   vertex* stack    = mallocc(G->V*sizeof(vertex));
   int top = 0;

   for (vertex v = 0; v < G->V; v++) {
      match[v]      = -1;
      discovered[v] = false;
   }

   for (vertex u = 0; u < G->V; u++) {
      if (discovered[u])
         continue;

      discovered[u] = true;
      stack[top++]  = u;

      while (top) {
         vertex v = stack[--top];

         for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (match[v] == -1 && match[v] == match[a->w]) {
               match[v]    = a->w;
               match[a->w] = v;
            }
            if (!discovered[a->w]) {
               discovered[a->w] = true;
               stack[top++]     = a->w;
            }
         }
      }
   }

   free(discovered);
   free(stack);
}
#pragma endregion

#pragma region main
int 
main(int argc, char** argv) {
   setbuf(stdout, NULL);

   int V, E, s;
   V = strtol(argv[1], NULL, 10);
   E = strtol(argv[2], NULL, 10);
   s = strtol(argv[3], NULL, 10);


   Graph T    = GRAPHrandRootedTree(V);
   printf("T(V=%d)\n", T->V);
   int height = altura(T, 0);
   assert(checkHeight(T, 0, height) && "Valid height");

   UGraph G = UGRAPHrand1(V, E);
   printf("G(V=%d, E=%d)\n", G->V, G->A/2);
   vertex* match = mallocc(G->V*sizeof(vertex));
   UGRAPHmaximalMaching(G, match);
   assert(checkMaximalMaching(G, match) && "Valid maximal maching");

   free(match);
   return EXIT_SUCCESS;
}
#pragma endregion

#pragma region report
////////////////////////////////////////////////////////////////////////
// Fim do algoritmo húngaro. Algoritmo disponícel em:
// [0] https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/\
//                                matching-bipartite.html
//
// No fim da última iteração do algoritmo húngaro para emparelhamento 
// máximo em grafo bipartido, é possível que o conjunto X seja vazio? É 
// possível que X seja o conjunto de todos os vértices? Discuta essas 
// duas possibilidades.
//
// Assumindo a seguinte definição do conjunto X dada em [0]: 
//    "Seja X é o conjunto dos vértices visitados na tentativa frustrada
//    de encontrar um caminho aumentador. Em outras palavras, X é o 
//    conjunto dos términos de todos os caminhos alternantes que começam
//    em vértices solteiros de C0, sendo C0 o conjunto dos vértices s 
//    tais que color[s] ≡ 0."
//
// Assim, X = {v in 0..G->V-1: visited[v]} quando augmentMatch acaba.
//
// Parte 1. Pelo segundo "for" de augmentMatch, X será vazio somente se 
// não hover vértices solteiros em C0. Isso pode acontecer se todos os 
// vértices em C0 possuírem uma aresta e um par; ou, trivialmente, se C0
// é vazio.
//
// Parte 2. Se C1 for vazio ou se o grafo tiver nenhuma aresta, mas 
// houver pelo menos um vértice em C0, todos os vértices de C0 serão 
// visitados e nunca ocorrerá augmentMatch. Ou, por exemplo, X pode ser 
// o conjunto de todos os vértices:
//             a  c
//             | /
//             b
//
// Rastro:
//                               visited[a b c]    pa[a b c]
//    UGRAPHbipMatch
//       augmentMatch
//          QUEUEput(a)                  *            a    
//          QUEUEput(c)                  *   *        a   c
//          newMatching com a->b
//       augmentMatch
//          QUEUEput(c)                      *            c
//          QUEUEput(b)                    * *          c c
//          QUEUEput(a)                  * * *        b c c
//          return
////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma GCC diagnostic pop

////////////////////////////////////////////////////////////////////////
// I walked all night long in the dark just to be standing here
// Only to feel like nobody, I'm Miss Y am I here?
