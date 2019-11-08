// MAC0328 (2019) 
// Muitas funções discutidas nas minhas notas de aula e nos exercícios
// ainda não estão nesta biblioteca. Acrescente essas funções. Modifique
// as funções que já estão na biblioteca, se achar necessário. Sugiro
// marcar os trechos de código modificados/acrescentados com um
// comentário do tipo "// novo". Preserve meu bom layout (veja
// www.ime.usp.br/~pf/algoritmos/aulas/layout.html) e não use tabs. 

// Este arquivo: GRAPHlists.c (codificação UTF-8)
// Data: 2019-10-05
// Autor: Paulo Feofiloff
//
// Esta é a implementação de uma biblioteca de manipulação de grafos
// representados por listas de adjacência. Veja detalhes no arquivo-
// interface GRAPHlists.h.
//
// Tudo foi extraído de www.ime.usp.br/~pf/algoritmos_para_grafos/,
// que copiou muita coisa do livro "Algorithms", 3rd.ed., part 5, de
// Sedgewick.
////////////////////////////////////////////////////////////////////////


#define DEBUG false



// Estruturas de dados básicas
////////////////////////////////////////////////////////////////////////

#include "GRAPHlists.h"
// A interface GRAPHlists.h define a estrutura graph e o tipo-de-dados
// Graph. Também contém as interfaces STACK.h, QUEUE.h, PQ.h, UF.h e
// MYTOOLS.h. Também contém as interfaces padrão stdlib.h, stdio.h,
// string.h, limits.h e stdbool.h.



// Ferramentas para construção de grafos
////////////////////////////////////////////////////////////////////////

Graph 
GRAPHinit( int V) { 
   Graph G = mallocc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = mallocc( V * sizeof (link));
   for (vertex v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

// Função privada (= static) auxiliar usada para construir listas de
// adjacência. A função recebe um vértice w e o endereço next de um nó e
// devolve o endereço a de um novo nó tal que a->w == w e
// a->next == next. 
static link 
NEWnode( vertex w, link next) { 
   link a = mallocc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

// Função privada auxiliar usada para construir listas de adjacência.
// Esta é uma versão de NEWnode() apropriada para grafos com custos nos
// arcos.
static link 
NEWnode_c( vertex w, link next, int cst) { 
   link a = mallocc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   a->cst = cst;     
   return a;                         
}

void 
GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, G->adj[v]);
   G->A++;
}

void 
GRAPHinsertArc_c( Graph G, vertex v, vertex w, int cst) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      if (a->w == w) {
         a->cst = cst; // atualiza custo de arco existente
         return;
      }
   }
   G->adj[v] = NEWnode_c( w, G->adj[v], cst);
   G->A++;
}

void 
UGRAPHinsertEdge( UGraph G, vertex v, vertex w) { 
   GRAPHinsertArc( G, v, w);
   GRAPHinsertArc( G, w, v);
}

void 
UGRAPHinsertEdge_c( UGraph G, vertex v, vertex w, int cst) { 
   GRAPHinsertArc_c( G, v, w, cst);
   GRAPHinsertArc_c( G, w, v, cst);
}

void 
GRAPHremoveArc( Graph G, vertex v, vertex w) {
   link *aa = &(G->adj[v]); // A
   while (*aa != NULL && (*aa)->w != w)
      aa = &(*aa)->next; // B
   if (*aa != NULL) {
      link b = *aa;
      *aa = b->next;
      free( b);
      G->A--;
   }
}
// Observação A: &G->adj[v] significa &(G->adj[v])
// Observação B: &(*aa)->next significa &((*aa)->next)
//               e é diferente de *aa->next

void 
UGRAPHremoveEdge( UGraph G, vertex v, vertex w) {
   GRAPHremoveArc( G, v, w);
   GRAPHremoveArc( G, w, v);
}

void 
GRAPHshow( Graph G) { 
   for (vertex v = 0; v < G->V; ++v) {
      printf( "%2d:", v);
      for (link a = G->adj[v]; a != NULL; a = a->next)
         printf( " %2d", a->w);
      printf( "\n");
   }
}

void 
GRAPHshow_c( Graph G) { 
   for (vertex v = 0; v < G->V; ++v) {
      printf( "%2d:", v);
      for (link a = G->adj[v]; a != NULL; a = a->next)
         printf( " %2d (%2d)", a->w, a->cst);
      printf( "\n");
   }
}

void 
GRAPHshowArcs( Graph G) { 
   for (vertex v = 0; v < G->V; ++v)
      for (link a = G->adj[v]; a != NULL; a = a->next)
         printf( "%d %d\n", v, a->w);
}

void 
GRAPHshowArcs_c( Graph G) { 
   for (vertex v = 0; v < G->V; ++v)
      for (link a = G->adj[v]; a != NULL; a = a->next)
      printf( "%2d %2d %2d\n", v, a->w, a->cst);
}

Graph 
GRAPHcopy( Graph G) {
   Graph H = GRAPHinit( G->V);
   for (vertex v = 0; v < G->V; ++v) 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         GRAPHinsertArc( H, v, a->w); 
   return H;   
}

// Função privada auxiliar usada por GRAPHdestroy(). Libera os nós da
// lista encadeada lst.
static void 
freelist( link lst) {
   if (lst != NULL) {
      freelist( lst->next);
      free( lst);
   }
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por freelist().
void 
GRAPHdestroy( Graph G) {
   for (vertex v = 0; v < G->V; ++v)
      freelist( G->adj[v]);
   free( G->adj);
   free( G);   
}

int
GRAPHindeg( Graph G, vertex v) {
   int *in = mallocc( G->V * sizeof (int));
   for (vertex w = 0; w < G->V; ++w) in[w] = 0;
   for (vertex u = 0; u < G->V; ++u) 
      for (link a = G->adj[u]; a != NULL; a = a->next) 
         in[a->w]++;
   int inv = in[v];
   free( in);
   return inv;
}

int
GRAPHoutdeg( Graph G, vertex v) {
   int outdeg = 0;
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      outdeg++;
   return outdeg;
}

Graph 
GRAPHreverse( Graph G) {
   Graph GR = GRAPHinit( G->V);
   for (vertex v = 0; v < G->V; ++v)
      for (link a = G->adj[v]; a != NULL; a = a->next) 
         GRAPHinsertArc( GR, a->w, v);
   return GR;
}

// Função privada auxiliar usada por GRAPHinvertLists(). A função
// inverte a lista de adjacência que começa em a e devolve o endereço do
// primeiro nó da nova lista.
static link 
invertR( link a) {
   if (a == NULL) return NULL;
   if (a->next == NULL) return a; // base da recursão
   link b = a->next;
   link aa = invertR( b);
   b->next = a;
   a->next = NULL;
   return aa;
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por invertR().
void 
GRAPHinvertLists( Graph G) {
   for (vertex v = 0; v < G->V; ++v) 
      G->adj[v] = invertR( G->adj[v]);
}

// Esta é uma versão não recursiva de GRAPHinvertLists().
void 
GRAPHinvertLists_i( Graph G) {
   for (vertex v = 0; v < G->V; ++v) {
      link a = NULL; // anterior
      link b = G->adj[v]; // corrente
      while (b != NULL) {
         link c = b->next; // seguinte
         b->next = a;
         a = b;
         b = c;
      }
      G->adj[v] = a;
   }
}

Graph 
GRAPHinputArcs( FILE *infile) {
   int V, A;
   fscanf( infile, "%d", &V);
   fscanf( infile, "%d", &A);
   Graph G = GRAPHinit( V);
   for (int i = 0; i < A; ++i) {
      vertex v, w;
      fscanf( infile, "%d %d", &v, &w);
      GRAPHinsertArc( G, v, w);
   }
   return G;
}

UGraph 
UGRAPHinputEdges_c( FILE *infile) {
   int V, E;
   fscanf( infile, "%d", &V);
   fscanf( infile, "%d", &E);
   UGraph G = UGRAPHinit( V);
   for (int i = 0; i < E; ++i) {
      vertex v, w; int cst;
      fscanf( infile, "%d %d %d", &v, &w, &cst);
      UGRAPHinsertEdge_c( G, v, w, cst);
   }
   return G;
}

// Usa fgets() and strtok().
Graph 
GRAPHinputLists( FILE *infile) {
   char line[LINE_MAX];
   fgets( line, LINE_MAX, infile); // A
   string token = strtok( line, " \n"); // token != NULL
   int V = strtol( token, NULL, 10);
   Graph G = GRAPHinit( V);
   for (int i = 0; i < V; i++) {
      fgets( line, LINE_MAX, infile); // A
      token = strtok( line, " \n"); // token != NULL
      vertex v = strtol( token, NULL, 10); // 0 <= v < V
      while ((token = strtok( NULL, " \n")) != NULL) {
         vertex w = strtol( token, NULL, 10); // 0 <= w < V
         GRAPHinsertArc( G, v, w);
      } // terminou processamento dos vizinhos de v
   }
   GRAPHinvertLists_i( G);
   return G;
}
// Observação A: line[] contém uma linha de infile;
//    se n = strlen( line) então
//    line[n] == '\0', n > 0 e line[n-1] != '\n'.

// Usa fgets() and strtok().
Graph 
GRAPHinputLists_c( FILE *infile) {
   char line[LINE_MAX];
   fgets( line, LINE_MAX, infile); // A
   string token = strtok( line, " \n"); // token != NULL
   int V = strtol( token, NULL, 10);
   Graph G = GRAPHinit( V);
   for (int i = 0; i < V; i++) {
      fgets( line, LINE_MAX, infile); // A
      token = strtok( line, " \n"); // token != NULL
      vertex v = strtol( token, NULL, 10); // 0 <= v < V
      while ((token = strtok( NULL, " \n")) != NULL) {
         vertex w = strtol( token, NULL, 10); // 0 <= w < V
         token = strtok( NULL, " \n");
         int cst = strtol( token, NULL, 10);
         GRAPHinsertArc_c( G, v, w, cst);
      } // terminou processamento dos vizinhos de v
   }
   GRAPHinvertLists_i( G);
   return G;
}
// Observação A: line[] contém uma linha de infile;
//    se n = strlen( line) então
//    n < LINE_MAX, line[n] == '\0', n > 0 e line[n-1] != '\n'.

void
UGRAPHedges( UGraph G, edge e[]) {
   int i = 0;
   for (vertex v = 0; v < G->V; ++v) 
      for (link a = G->adj[v]; a != NULL; a = a->next) 
         if (v < a->w) {
            e[i].v = v;
            e[i].w = a->w;
            e[i].cst = a->cst;
            ++i;
         }
}



// Numerações e permutações de vértices
////////////////////////////////////////////////////////////////////////

void
perm2num( int V, vertex perm[], int num[]) { 
   for (int i = 0; i < V; ++i) 
      num[perm[i]] = i; 
}

void
injnum2perm( int V, int num[], vertex perm[]) { 
   for (vertex v = 0; v < V; ++v) 
      perm[num[v]] = v; 
}



// Grafos topológicos
////////////////////////////////////////////////////////////////////////

// Eliminação iterada de fontes.
bool 
GRAPHisTopo( Graph G, int topo[]) { 
   int *indeg = mallocc( G->V * sizeof (int));
   for (vertex v = 0; v < G->V; ++v) indeg[v] = 0;
   for (vertex v = 0; v < G->V; ++v) 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         indeg[a->w] += 1;
   vertex *fila = mallocc( G->V * sizeof (vertex));
   int comeco = 0, fim = 0;
   for (vertex v = 0; v < G->V; ++v)
      if (indeg[v] == 0) 
         fila[fim++] = v;
   int k = 0;
   while (comeco < fim) { 
      // fila[comeco..fim-1] de fontes virtuais
      vertex v = fila[comeco++];
      topo[v] = k++;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         indeg[a->w] -= 1; // remoção virtual do arco v-w
         if (indeg[a->w] == 0) 
            fila[fim++] = a->w;
      }
   }
   free( indeg); free( fila);
   return k >= G->V;
}



// Grafos aleatórios
////////////////////////////////////////////////////////////////////////

// Esta função privada auxiliar devolve um vértice aleatório do grafo G.
// (Vamos supor que G->V <= RAND_MAX.) Ela é apenas um invólucro para a
// função rand() da biblioteca stdlib, que produz um número inteiro
// aleatório no intervalo fechado 0..RAND_MAX. 
static vertex 
randV( Graph G) { 
   double r = rand() / (RAND_MAX + 1.0); // 0 <= r < 1
   return r * G->V;
}

// Supõe que A <= V*(V-1). Código inspirado no Programa 17.7 de
// Sedgewick.
Graph 
GRAPHrand1( int V, int A) { 
   Graph G = GRAPHinit( V);
   while (G->A < A) {
      vertex v = randV( G);
      vertex w = randV( G);
      if (v != w) 
         GRAPHinsertArc( G, v, w);
   }
   return G;
}

// Supõe que E <= V*(V-1)/2. Código inspirado no Programa 17.7 de
// Sedgewick.
UGraph 
UGRAPHrand1( int V, int E) { 
   UGraph G = UGRAPHinit( V);
   int A = 2*E;
   while (G->A < A) {
      vertex v = randV( G);
      vertex w = randV( G);
      if (v != w)
         UGRAPHinsertEdge( G, v, w);
   }
   return G;
}

// Código inspirado no Programa 17.7 de Sedgewick.
Graph 
GRAPHrand1_c( int V, int A, int cmin, int cmax) { 
   Graph G = GRAPHinit( V);
   while (G->A < A) {
      vertex v = randV( G);
      vertex w = randV( G);
      int c = randInteger( cmin, cmax);
      if (v != w) 
         GRAPHinsertArc_c( G, v, w, c);
   }
   return G;
}

UGraph 
UGRAPHrand1_c( int V, int E, int cmin, int cmax) { 
   UGraph G = UGRAPHinit( V);
   int A = 2*E;
   while (G->A < A) {
      vertex v = randV( G);
      vertex w = randV( G);
      int c = randInteger( cmin, cmax);
      if (v != w) 
         UGRAPHinsertEdge_c( G, v, w, c);
   }
   return G;
}

Graph 
GRAPHrand2( int V, int A) { 
   double prob = (double) A / (V*(V-1));
   Graph G = GRAPHinit( V);
   for (vertex v = 0; v < V; ++v)
      for (vertex w = 0; w < V; ++w) 
         if (v != w)
            if (rand( ) < prob*(RAND_MAX+1.0))
               GRAPHinsertArc( G, v, w);
   return G;
}

Graph 
GRAPHrand2_c( int V, int A, int cmin, int cmax) { 
   double prob = (double) A / (V*(V-1));
   Graph G = GRAPHinit( V);
   for (vertex v = 0; v < V; ++v)
      for (vertex w = 0; w < V; ++w)
         if (v != w && rand( ) < prob*(RAND_MAX+1.0))
            GRAPHinsertArc_c( G, v, w, randInteger( cmin, cmax));
   return G;
}

UGraph 
UGRAPHrand2( int V, int E) { 
   double prob = (double) 2*E / (V*(V-1));
   UGraph G = GRAPHinit( V);
   for (vertex v = 0; v < V; ++v)
      for (vertex w = 0; w < V; ++w) 
         if (v != w)
            if (rand( ) < prob*(RAND_MAX+1.0))
               UGRAPHinsertEdge( G, v, w);
   return G;
}



// Construtores de grafos
////////////////////////////////////////////////////////////////////////

Graph 
GRAPHcomplete( int V) {
   Graph G = GRAPHinit( V);
   for (vertex v = 0; v < G->V; ++v)
      for (vertex w = 0; w < G->V; ++w)
         if (w != v)
            GRAPHinsertArc( G, v, w);
   return G;
}

Graph 
GRAPHrandPath( int V) {
   Graph G = GRAPHinit( V);
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   for (int i = 0; i < V-1; ++i)
      GRAPHinsertArc( G, vv[i], vv[i+1]);
   free( vv);
   return G;
}

UGraph 
UGRAPHrandPath( int V) {
   UGraph G = UGRAPHinit( V);
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   for (int i = 0; i < V-1; ++i)
      UGRAPHinsertEdge( G, vv[i], vv[i+1]);
   free( vv);
   return G;
}

// Supõe V >= 2.
Graph 
GRAPHrandCycle( int V) {
   Graph G = GRAPHinit( V);
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   for (int i = 0; i < V-1; ++i)
      GRAPHinsertArc( G, vv[i], vv[i+1]);
   GRAPHinsertArc( G, vv[V-1], vv[0]);
   free( vv);
   return G;
}

// Supõe V >= 3.
UGraph 
UGRAPHrandCircuit( int V) {
   UGraph G = UGRAPHinit( V);
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   for (int i = 0; i < V-1; ++i)
      UGRAPHinsertEdge( G, vv[i], vv[i+1]);
   UGRAPHinsertEdge( G, vv[V-1], vv[0]);
   free( vv);
   return G;
}

Graph 
GRAPHrandRootedTree( int V) {
   Graph G = GRAPHinit( V);
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   for (int i = 0; i < V-1; ++i) {
      int j = randInteger( i+1, V-1);
      GRAPHinsertArc( G, vv[j], vv[i]);
   }
   free( vv);
   return G;
}

UGraph 
UGRAPHrandTree( int V) {
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   UGraph G = UGRAPHinit( V);
   for (int j = 1; j < G->V; ++j) {
      int i = randInteger( 0, j-1);
      UGRAPHinsertEdge( G, vv[i], vv[j]);
   }
   free( vv);
   return G;
}

UGraph 
UGRAPHrand1connected( int V, int E) { 
   UGraph G = UGRAPHrandTree( V);
   while (G->A < 2*E) {
      vertex v = randV( G);
      vertex w = randV( G);
      if (v != w) 
         UGRAPHinsertEdge( G, v, w);
   }
   return G;
}

// Supõe que m >= 1, n >= 1 e E <= m*n.
UGraph 
UGRAPHrand1bipartite( int m, int n, int E) {
   UGraph G = UGRAPHinit( m+n);
   vertex *vv = mallocc( (m+n) * sizeof (vertex));
   for (int i = 0; i < m+n; ++i) vv[i] = i;
   randPermutation( vv, m+n);
   while (G->A < 2*E) {
      double r = rand( ) / (RAND_MAX + 1.0);
      int i = r*m;
      r = rand( ) / (RAND_MAX + 1.0);
      int j = m + r*n;
      UGRAPHinsertEdge( G, vv[i], vv[j]);
   }
   free( vv);
   return G;
}

Graph 
GRAPHrandDiGrid( int m, int n) { 
   int V = m * n;
   Graph G = GRAPHinit( V);
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   for (int i = 0; i < V-1; ++i) {
      if ((i+1) % n == 0) continue;
      GRAPHinsertArc( G, vv[i], vv[i+1]);
   }
   for (int i = 0; i < V-n; ++i) 
      GRAPHinsertArc( G, vv[i], vv[i+n]);
   free( vv);
   return G;
}

Graph 
GRAPHrandGrid( int m, int n) { 
   int V = m * n;
   Graph G = GRAPHinit( V);
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   for (int i = 0; i < V-1; ++i) {
      if ((i+1) % n == 0) continue;
      if (rand( ) < 0.5*(RAND_MAX+1.0))
         GRAPHinsertArc( G, vv[i], vv[i+1]);
      else 
         GRAPHinsertArc( G, vv[i+1], vv[i]);
   }
   for (int i = 0; i < V-n; ++i) 
      if (rand( ) < 0.5*(RAND_MAX+1.0))
         GRAPHinsertArc( G, vv[i], vv[i+n]);
      else 
         GRAPHinsertArc( G, vv[i+n], vv[i]);
   free( vv);
   return G;
}

UGraph 
UGRAPHrandGrid( int m, int n) { 
   int V = m * n;
   UGraph G = UGRAPHinit( V);
   vertex *vv = mallocc( V * sizeof (vertex));
   for (int i = 0; i < V; ++i) vv[i] = i;
   randPermutation( vv, V);
   for (int i = 0; i < V-1; ++i) {
      if ((i+1) % n == 0) continue;
      UGRAPHinsertEdge( G, vv[i], vv[i+1]);
   }
   for (int i = 0; i < V-n; ++i) 
      UGRAPHinsertEdge( G, vv[i], vv[i+n]);
   free( vv);
   return G;
}



// Caminhos e ciclos em grafos
////////////////////////////////////////////////////////////////////////



// Acessibilidade (caminho de um vértice a outro)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por GRAPHreach(). A função visita todos
// os vértices de G que podem ser alcançados a partir de v sem passar
// por vértices já visitados. 
static void 
reachR( Graph G, vertex v, bool *visited) { 
   visited[v] = true;
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (!visited[a->w])
         reachR( G, a->w, visited);
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por reachR().
bool 
GRAPHreach( Graph G, vertex s, vertex t) { 
   bool *visited = mallocc( G->V * sizeof (bool));
   for (vertex v = 0; v < G->V; ++v)
      visited[v] = false;
   reachR( G, s, visited);
   bool reachable = visited[t];
   free( visited);
   return reachable;
}



// Busca em profundidade (= depth-first search = DFS)
////////////////////////////////////////////////////////////////////////

// A função privada auxiliar dfsR() é o motor de GRAPHdfs(). Ela recebe
// um grafo G, um vértice v, uma numeração parcial pre[] dos vértices
// com valores no conjunto -1 0 1 ... *p-1, uma numeração parcial post[]
// dos vértices com valores no conjunto -1 0 1 ... *pt-1, e um vetor de
// pais parcial pa[]. A função faz uma busca DFS em G a partir de v. Se
// X é o conjunto dos vértices acessíveis a partir de v por caminhos que
// só usam vértices x tais que pre[x] vale -1, a função atribui um
// número pre[x] e um número post[x] a cada x em X. Se x é o k-ésimo
// vértice descoberto então pre[x] recebe o valor *p + k. Se x é o
// k-ésimo vértices a morrer então post[x] recebe o valor *pt + k. Além
// disso, a função armazena no vetor pa[] a parte da floresta DFS
// construída durante a busca.
static void 
dfsR( Graph G, vertex v, int *pre, int *post, vertex *pa, int *p,
int *pt) { 
   pre[v] = (*p)++; 
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (pre[a->w] == -1) {
         pa[a->w] = v; 
         dfsR( G, a->w, pre, post, pa, p, pt); 
      } 
   post[v] = (*pt)++;
}

// Esta função-invólucro (= wrapper function) invoca dfsR(). O código
// foi inspirado no programa 18.3 de Sedgewick.
void 
GRAPHdfs( Graph G, int *pre, int *post, vertex *pa) { 
   int cnt = 0, cntt = 0;
   for (vertex v = 0; v < G->V; ++v) 
      pre[v] = post[v] = -1; // A
   for (vertex v = 0; v < G->V; ++v)
      if (pre[v] == -1) {
         pa[v] = v;
         dfsR( G, v, pre, post, pa, &cnt, &cntt); // nova etapa
      }
}
// A: Inicializei post[] apenas porque a classificação on-the-fly dos
// arcos precisa disso.



// Ciclos e dags
////////////////////////////////////////////////////////////////////////

// Esta função privada auxiliar é usada por GRAPHhasCycle(). Ela devolve
// true se encontra um ciclo ao percorrer G a partir do vértice v e
// devolve false em caso contrário. O código é inspirado no de dfsR().
static bool 
dfsRhcy( Graph G, vertex v, int *pre, int *post, vertex *pa, int *p,
int *pt) { 
   pre[v] = (*p)++;
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pre[w] == -1) {
         if (dfsRhcy( G, w, pre, post, pa, p, pt)) return true;
      } else {
         if (post[w] == -1) return true;
      }
   }
   post[v] = (*pt)++;
   return false;
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por dfsRhcy(). Interrompe a busca DFS tão logo encontra
// um arco de retorno. (Esta é uma versão on-the-fly de 
// GRAPHhasCycle_v1() da biblioteca GRAPHlistsExperimental.)
bool 
GRAPHhasCycle( Graph G) { 
   int *pre = mallocc( G->V * sizeof (int));
   int *post = mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   int cnt = 0, cntt = 0;
   for (vertex v = 0; v < G->V; ++v)
      pre[v] = post[v] = -1;
   bool b = false;
   for (vertex v = 0; v < G->V; ++v)
      if (pre[v] == -1) {
         pa[v] = v;
         b = dfsRhcy( G, v, pre, post, pa, &cnt, &cntt);
         if (b) break; // temos um ciclo
         // (não necessariamente passando por v)
      }
   free( pa);
   free( post);
   free( pre);
   return b; 
}

bool 
GRAPHisDag( Graph G) {
   return !GRAPHhasCycle( G);
}



// Componentes conexas (de grafos não-dirigidos)
////////////////////////////////////////////////////////////////////////

// Esta função privada auxiliar é usada por UGRAPHcc(). Ela atribui o
// número id a todos os vértices que estão na componente conexa que
// contém v. O código é uma adaptação de dfsR().
static void 
dfsRcc( UGraph G, vertex v, int cc[], int id) { 
   cc[v] = id;
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (cc[a->w] == -1) 
         dfsRcc( G, a->w, cc, id); 
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por dfsRcc(). O código da função é uma adaptação da busca
// em profundidade GRAPHdfs(). O código foi copiado do programa 18.4,
// p.100, de Sedgewick.
int 
UGRAPHcc( UGraph G, int cc[]) { 
   int id = 0;
   for (vertex v = 0; v < G->V; ++v) 
      cc[v] = -1;
   for (vertex v = 0; v < G->V; ++v)
      if (cc[v] == -1) 
         dfsRcc( G, v, cc, id++);
   return id;
}

bool 
UGRAPHisConnected( UGraph G) {
   int *cc = mallocc( G->V * sizeof (int));
   int numcc = UGRAPHcc( G, cc);
   free( cc);
   if (numcc > 1) return false;
   return true;
}



// Distâncias, potencial, e relaxação
////////////////////////////////////////////////////////////////////////

// O código foi inspirado no programa 21.6 de Sedgewick.
void 
DAGshortestPaths( Dag G, vertex *vv, vertex s, vertex *pa, int *dist) { 
   const int INFINITY = G->V;
   for (vertex v = 0; v < G->V; ++v)
      pa[v] = -1, dist[v] = INFINITY;
   pa[s] = s, dist[s] = 0;

   for (int j = 0; j < G->V; ++j) {
      vertex v = vv[j];
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w; 
         if (dist[v] + 1 < dist[w]) {
            dist[w] = dist[v] + 1; // relaxação de v-w
            pa[w] = v;
         }
      }
   }
}



// Busca em largura (= breadth-first search = BFS)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar que implementa o algoritmo de busca em
// largura. Ela visita todos os vértices do grafo G que estão ao alcance
// do vértice s e armazena o vetor de pais da árvore de busca em
// pa[0..V-1]. A ordem em que os vértices são descobertos é registrada
// no vetor num[0..V-1]. Os vetores num[] e pa[] devem ser alocados
// pelo cliente. (Código inspirado no programa 18.9 de Sedgewick.) 
static void 
GRAPHbfs( Graph G, vertex s, int num[], vertex pa[]) { 
   for (vertex v = 0; v < G->V; ++v) 
      num[v] = -1;
   int c = 0;
   num[s] = c++;
   pa[s] = s;
   QUEUEinit( G->V);
   QUEUEput( s); 
   while (!QUEUEempty( )) {
      vertex v = QUEUEget( ); 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (num[a->w] == -1) {
            num[a->w] = c++; 
            pa[a->w] = v;
            QUEUEput( a->w); 
         }
   }
   QUEUEfree( ); 
}



// Algoritmo de caminhos mínimos
////////////////////////////////////////////////////////////////////////

// Variante da função GRAPHbfs() de busca em largura. O código é
// inspirado no programa 18.9 de Sedgewick.
void 
GRAPHshortestPaths( Graph G, vertex s, int dist[], vertex pa[]) { 
   const int INFINITY = G->V; 
   for (vertex v = 0; v < G->V; ++v) 
      dist[v] = INFINITY, pa[v] = -1;
   dist[s] = 0, pa[s] = s;
   QUEUEinit( G->V);
   QUEUEput( s); 
   while (!QUEUEempty( )) {
      vertex v = QUEUEget( ); 
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w; 
         if (dist[w] == INFINITY) { 
            dist[w] = dist[v] + 1;
            pa[w] = v;
            QUEUEput( w); 
         }
      }
   }
   QUEUEfree( ); 
}



// Circuitos e florestas (não-radicadas)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por UGRAPHhasCircuit(). Recebe um grafo
// G e devolve true se encontrar um circuito ao percorrer G a partir do
// vértice v. Inspirada em dfsR().
static bool 
dfsRhci( UGraph G, vertex v, int *pre, vertex *pa, int *p) { 
   pre[v] = (*p)++;
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pre[w] == -1) {
         pa[w] = v; 
         if (dfsRhci( G, w, pre, pa, p)) return true;
      } else { // pre[w] < pre[v]
         if (w != pa[v]) return true; 
      }
   }
   return false;
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado pela função privada hasCircuit(). (Esta função é uma versão
// on-the-fly da função UGRAPHhasCircuit_v1() da biblioteca
// GRAPHlistsExperimental.)
bool 
UGRAPHhasCircuit( UGraph G) {
   int *pre = mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   int cnt = 0;
   for (vertex v = 0; v < G->V; ++v)
      pre[v] = -1;
   for (vertex v = 0; v < G->V; ++v) {
      if (pre[v] == -1) {
         pa[v] = v;
         if (dfsRhci( G, v, pre, pa, &cnt)) {
            free( pre); free( pa);
            return true;
         }
      }
   }
   free( pre); free( pa);
   return false;
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por UGRAPHhasCircuit().
bool
UGRAPHisForest( UGraph G) {
   return !UGRAPHhasCircuit( G);
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por UGRAPHisForest() e UGRAPHisConnected().
bool
UGRAPHisTree( UGraph G) {
   return UGRAPHisForest( G) && UGRAPHisConnected( G);
}



// Grafos aresta-biconexos (= edge-biconnected = eb)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por UGRAPHisEbc(). Calcula lo[v]. 
// Devolve true se encontrar uma ponte na subfloresta DFS que tem v como
// raiz e devolve false em caso contrário.
static bool 
dfsRbridge( UGraph G, vertex v, int *pre, vertex *pa, int *lo, int *p) {
   vertex w; link a;
   pre[v] = (*p)++;
   lo[v] = pre[v];
   for (a = G->adj[v]; a != NULL; a = a->next) {
      w = a->w;
      if (pre[w] != -1) { // v-w é arco de avanço ou de retorno
         if (w != pa[v]) // w é ancestral de pa[v]
            lo[v] = min( lo[v], pre[w]);
      } else { 
         pa[w] = v;
         if (dfsRbridge( G, w, pre, pa, lo, p)) // calcula lo[w]
            return true;
         if (lo[w] == pre[w]) // v-w é ponte
            return true;       
         lo[v] = min( lo[v], lo[w]) ;
      }
   }
   return false;
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por dfsRbridge(). Esta é uma versão on-the-fly de 
// UGRAPHisEbc_v3(), que está na biblioteca GRAPHlistsExperimental.
// Algoritmo linear sofisticado: faz uma busca DFS que calcula o lowest
// preorder number de cada vértice. (Código inspirado no programa 18.7,
// p.108, de Sedgewick.)
bool 
UGRAPHisEbc( UGraph G) {
   int *pre = mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   int *lo = mallocc( G->V * sizeof (int));
   // muitos escrevem "low" no lugar do meu "lo"
   bool b = true;
   for (vertex v = 0; v < G->V; ++v)
      pre[v] = -1;
   int cnt = 0;
   pa[0] = 0;
   if (dfsRbridge( G, 0, pre, pa, lo, &cnt))
      b = false;
   for (vertex v = 1; v < G->V; ++v)
      if (pre[v] == -1) 
         b = false; // G é desconexo
   free( pa);
   free( pre);
   free( lo);
   return b;
}



// Componentes aresta-biconexas (= edge-biconnected components = ebcc)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por UGRAPHebcc(). (Muitos livros
// escrevem "low" no lugar do meu "lo".)
static void 
dfsRebcc( UGraph G, vertex v, int *ebcc, int *pre, vertex *pa, int *lo, 
int *p, int *pid) {
   pre[v] = (*p)++;
   STACKpush( v);
   lo[v] = pre[v];
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pre[w] == -1) {
         pa[w] = v;
         dfsRebcc( G, w, ebcc, pre, pa, lo, p, pid);
         lo[v] = min( lo[v], lo[w]) ;
      } else { // w á ancestral próprio de v
         if (w != pa[v]) 
            lo[v] = min( lo[v], pre[w]);
      }
   } 
   if (lo[v] == pre[v]) { // v é cabeça
      vertex u;
      do {
         u = STACKpop( );
         ebcc[u] = *pid;
      } while (u != v);
      (*pid)++;
   }
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por dfsRebcc(). Esta é uma implementação on-the-fly do
// algoritmo de Tarjan para componentes aresta-biconexas.
int UGRAPHebcc( UGraph G, int *ebcc) {
   int *pre = mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   int *lo = mallocc( G->V * sizeof (int));
   STACKinit( G->V);
   for (vertex v = 0; v < G->V; ++v)
      pre[v] = ebcc[v] = -1;
   int cnt = 0;
   int id = 0;
   for (vertex v = 0; v < G->V; ++v)
      if (pre[v] == -1) {
         pa[v] = v;
         dfsRebcc( G, v, ebcc, pre, pa, lo, &cnt, &id); // nova etapa
      }
   free( pre); 
   free( lo); 
   free( pa);
   STACKfree( );
   return id;
}



// Grafos fortemente conexos (= strongly connected)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por GRAPHisStrong(). Faz uma busca
// em profundidade a partir do vértice v e decide se a parte do grafo
// visitada é fortemente conexa.
static bool 
dfsRiss( Graph G, vertex v, int *pre, vertex *pa, int *lo, int *p) {
   pre[v] = (*p)++;
   lo[v] = pre[v];
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pre[w] == -1) {
         if (!dfsRiss( G, w, pre, pa, lo, p)) // calcula lo[w]
            return false;
         lo[v] = min( lo[v], lo[w]);
      } else if (pre[w] < pre[v]) // v-w é de retorno ou cruzada 
         lo[v] = min( lo[v], pre[w]);
   }
   if (lo[v] == pre[v] && pa[v] != v) 
      return false; 
   return true;
}

// Versão on-the-fly de GRAPHisStrong_v3(), que está na biblioteca
// GRAPHlistsExperimental.
bool 
GRAPHisStrong( Graph G) {
   int *pre = mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   int *lo = mallocc( G->V * sizeof (int));
   for (vertex v = 0; v < G->V; ++v) 
      pre[v] = -1;
   int cnt = 0;
   vertex s = 0;
   if (!dfsRiss( G, s, pre, pa, lo, &cnt)) {
      free( pre); free( pa); free( lo);
      return false;
   }
   for (vertex v = 0; v < G->V; ++v) {
      if (pre[v] == -1) {
         free( pre); free( pa); free( lo);
         return false;
      }
   }
   free( pre); free( pa); free( lo);
   return true;
}



// Componentes fortes (= strong components = sc)
////////////////////////////////////////////////////////////////////////



// Algoritmo de Tarjan para componentes fortes
////////////////////////////////////////////////////////////////////////



// Algoritmo de Kosaraju para componentes fortes
////////////////////////////////////////////////////////////////////////



// Coloração de vértices
////////////////////////////////////////////////////////////////////////

int 
UGRAPHseqColoring( UGraph G, int color[]) { 
   int k = 0;
   for (vertex v = 0; v < G->V; ++v) color[v] = -1;
   bool *disponivel = mallocc( G->V * sizeof (int));
   for (vertex v = 0; v < G->V; ++v) {
      int i;
      for (i = 0; i < k; ++i) 
         disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) disponivel[i] = false;
      } // disponivel[0..k-1] dá as cores disponíveis para v
      for (i = 0; i < k; ++i) 
         if (disponivel[i]) break;
      if (i < k) color[v] = i;
      else color[v] = k++;
   }
   free( disponivel);
   return k;
}



// Grafos bipartidos e circuitos ímpares
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por UGRAPHtwoColor().
static bool 
dfsR2color( UGraph G, vertex v, int *color, int c) { 
   color[v] = 1-c;
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w; 
      if (color[w] == -1) {
         if (dfsR2color( G, w, color, 1-c) == false) 
            return false; 
      }
      else { // v-w é de avanço ou de retorno
         if (color[w] == 1-c) // base da recursão
            return false;
      }
   }
   return true;
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por dfsR2color(). Código inspirado no programa 18.6 de
// Sedgewick.
bool 
UGRAPHtwoColor( UGraph G, int *color) { 
   for (vertex v = 0; v < G->V; ++v) 
      color[v] = -1; // incolor
   for (vertex v = 0; v < G->V; ++v)
      if (color[v] == -1) 
         if (!dfsR2color( G, v, color, 0)) 
            return false;
   return true;
}



// Emparelhamentos (= matchings)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por augmentMatch_bfs(). Esta função
// executa a operação M(+)P sobre um emparelhamento M e um caminho
// aumentador P. O emparelhamento M é representado pelo vetor
// match[0..V-1]. O caminho P é representado por um vetor pa[]. O
// término de P é t. A origem de P não é dada explicitamente mas
// caracterizada pela propriedade pa[s] == s. (Esta função vale para
// qualquer grafo não-dirigido, bipartido ou não.)
static void 
newMatching( vertex *match, vertex t, vertex *pa) { 
   vertex x;
   do {
      x = pa[t];
      match[t] = x;
      match[x] = t; // A
      t = pa[x]; 
   } while (t != x);
}
/* No ponto A: a aresta t-x entrou no emparelhamento e a aresta x-pa[x]
// saiu do emparelhamento:
//
//     antes:   .     .     x      depois:   .     x     .
//               \   //\   //\                \   //\   /\\
//                \ //  \ //  \                \ //  \ /  \\
//                 .     .     t                .     t    .
*/



// Emparelhamentos em grafos bipartidos (= bipartite matching)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por UGRAPHbipMatch_bfs(). Esta função
// recebe um grafo não-dirigido bipartido G, com bicoloração
// color[0..V-1], e um emparelhamento M representado por match[0..V-1].
// A função procura calcular um emparelhamento maior que M. Se tiver
// sucesso, devolve true e modifica match[] de acordo. Se fracassar,
// devolve false sem alterar match[]. A função usa a estratégia de
// busca em largura (BFS). O vetor visited[] é usado para marcar os
// os vértices visitados durante a busca; poderia ter sido alocado e
// desalocado internamente, mas é alocado externamente para permitir
// o cálculo subsequente de uma cobertura mínima. (Esse código não está
// no livro de Sedgewick.) 
static bool 
augmentMatch_bfs( UGraph G, int *color, vertex *match, bool *visited) {
   vertex *pa = mallocc( G->V * sizeof (vertex)); 
   for (vertex v = 0; v < G->V; ++v) visited[v] = false;
   QUEUEinit( G->V);
   for (vertex s = 0; s < G->V; ++s) {
      if (color[s] == 0 && match[s] == -1) { 
         visited[s] = true; 
         pa[s] = s;
         QUEUEput( s); 
      }
   }
   // a fila contém todos os vértices solteiros de cor 0
   while (!QUEUEempty( )) { 
      // color[v] == 0 para todo v na fila
      vertex v = QUEUEget( ); 
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w; // color[w] == 1
         if (!visited[w]) {
            // v-w não está no emparelhamento
            visited[w] = true; 
            pa[w] = v; 
            if (match[w] == -1) { // caminho aumentador!
               newMatching( match, w, pa);
               QUEUEfree( ); free( pa);
               return true;
            }
            vertex x = match[w]; // color[x] == 0 e visited[x] == false
            visited[x] = true;
            pa[x] = w; // caminho ganhou segmento v-w-x
            QUEUEput( x); 
         }
      }
   }
   QUEUEfree( ); free( pa);
   return false;
}
// O processo iterativo é uma busca em largura que procura por um
// caminho alternante simples, de comprimento maior que 0, que comece
// num vértice solteiro de cor 0 e termine num vértice solteiro de
// cor 1. Em caso de sucesso, o caminho é armazenado no vetor de pais
// pa[].

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é
// executado por augmentMatch_bfs(). A função usa busca BFS para
// procurar caminhos aumentadores. (Esta função não está no livro de
// Sedgewick.)
int 
UGRAPHbipMatch_bfs( UGraph G, int *color, vertex *match, bool *cover) {
   bool *visited = mallocc( G->V * sizeof (bool));
   for (vertex v = 0; v < G->V; ++v) match[v] = -1;
   int size = 0;
   while (augmentMatch_bfs( G, color, match, visited))
      size++;
   for (vertex v = 0; v < G->V; ++v) {
      if ((color[v] == 1 && visited[v]) || 
          (color[v] == 0 && !visited[v]))
         // superfluous parentheses make compiler happy
         cover[v] = true;
      else cover[v] = false;
   }
   free( visited);
   return size;
}

static bool 
dfsRaugment( UGraph G, vertex v, vertex *match, bool *visited) {
   visited[v] = true; // color[v] == 0
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w; // color[w] == 1
      if (!visited[w]) {
         // v-w não está no emparelhamento
         visited[w] = true;
         if (match[w] == -1) {
            // base da recursão
            match[w] = v;
            match[v] = w;
            return true; 
         }
         vertex ww = match[w];   
         if (dfsRaugment( G, ww, match, visited)) {
            match[w] = v;
            match[v] = w;
            return true;
         }
      }
   }
   return false; // base da recursão
}



// Algoritmo de Prim para árvores geradoras de custo mínimo 
// (= MST = minimal spanning tree)
////////////////////////////////////////////////////////////////////////

// O código é uma versão melhorada do Programa 20.3 de Sedgewick.
int
UGRAPHmstP1( UGraph G, vertex pa[]) {  
   const int INFINITY = INT_MAX;
   bool *tree = mallocc( G->V * sizeof (bool));
   vertex *preco = mallocc( G->V * sizeof (int)); // price
   // inicialização:
   for (vertex v = 0; v < G->V; ++v) 
      pa[v] = -1, tree[v] = false, preco[v] = INFINITY; 
   pa[0] = 0, tree[0] = true;
   for (link a = G->adj[0]; a != NULL; a = a->next) {
      pa[a->w] = 0, preco[a->w] = a->cst; 
   }
   int mstcost = 0;
   while (true) { 
      int min = INFINITY;
      vertex y = 0; // y is initialized just to make compiler happy 
      for (vertex w = 0; w < G->V; ++w) {
         if (tree[w]) continue;
         if (preco[w] < min) 
            min = preco[w], y = w; 
      }
      if (min == INFINITY) break;
      // aresta pa[y]-y é a mais barata da franja
      tree[y] = true; 
      mstcost += preco[y];
      // atualização de preco[]:
      for (link a = G->adj[y]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (tree[w]) continue;
         int cst = a->cst;
         if (cst < preco[w]) {
            preco[w] = cst; 
            pa[w] = y; 
         }
      }
   }
   free( tree); free( preco);
   return mstcost;
}

// Código inspirado no Programa 21.1 de Sedgewick.
int
UGRAPHmstP2( UGraph G, vertex pa[]) { 
   const int INFINITY = INT_MAX;
   bool *tree = mallocc( G->V * sizeof (bool));
   vertex *preco = mallocc( G->V * sizeof (int)); // price
   // inicialização:
   for (vertex v = 1; v < G->V; ++v) 
      pa[v] = -1, tree[v] = false, preco[v] = INFINITY; 
   pa[0] = 0, tree[0] = true;
   for (link a = G->adj[0]; a != NULL; a = a->next) {
      pa[a->w] = 0; 
      preco[a->w] = a->cst; 
   } 
   PQinit( G->V); 
   for (vertex v = 1; v < G->V; ++v)
      PQinsert( v, preco); 

   int mstcost = 0;
   while (!PQempty( )) {
      vertex y = PQdelmin( preco);
      if (preco[y] == INFINITY) break; // supérfluo se G conexo
      tree[y] = true;
      mstcost += preco[y];
      // atualização de preco[]:
      for (link a = G->adj[y]; a != NULL; a = a->next) {
         vertex w = a->w; 
         if (tree[w]) continue;
         int cst = a->cst;
         if (cst < preco[w]) { 
            preco[w] = cst; 
            PQdec( w, preco); 
            pa[w] = y;
         }
      }
   }
   PQfree( ); free( tree); free( preco);
   return mstcost;
}



// Algoritmo de Kruskal para árvores geradoras de custo mínimo 
// (= MST = minimal spanning tree)
////////////////////////////////////////////////////////////////////////

// Esta função privada auxiliar compara o campo cst de dois objetos *aa
// e *bb do tipo edge. A função é usada como 3-o argumento da função
// qsort() da biblioteca stdlib. Para ordenar um vetor arr[0..N-1] de
// objetos do tipo edge, diga qsort( arr, N, sizeof (edge), comp_edge).
static int 
comp_edge( const void *aa, const void *bb) {
    edge *a = (edge *) aa;
    edge *b = (edge *) bb;
    if (a->cst < b->cst) return -1;
    if (a->cst > b->cst) return  1;
    return 0;
}

// Implementação eficiente do algoritmo de Kruskal. Usa union-find.
// Consome V*(E+V) log^* V unidades de tempo no pior caso. Usa a função
// auxiliar comp_edge(). (O código foi copiado, com ligeiras
// modificações, do Programa 20.5, p.249, de Sedgewick.) 
int 
UGRAPHmstK1( UGraph G, edge mst[]) { 
   // o tipo edge foi definido em GRAPHlist.h:
   // typedef struct {vertex v, w;} edge;
   int V = G->V;
   edge *e = mallocc( (V*(V-1)/2) * sizeof (edge));  
   UGRAPHedges( G, e);
   int E = G->A/2; 
   // quickSort( e, 0, E-1); 
   qsort( e, E, sizeof (edge), comp_edge);
   UFinit( V);
   int mstcost = 0;
   int k = 0;
   for (int i = 0; k < V-1; ++i) {
      vertex v0 = UFfind( e[i].v);
      vertex w0 = UFfind( e[i].w);
      if (v0 != w0) {
         UFunion( v0, w0);
         mst[k++] = e[i];
         mstcost += e[i].cst;
      }
   }
   // mst[0..V-2] é o conjunto de arestas de uma MST
   UFfree( ); free( e);
   return mstcost;
} 



// Distâncias e potenciais sob custos positivos (= SPT)
////////////////////////////////////////////////////////////////////////



// Caminhos de custo mínimo em dags (custos arbitrários)
////////////////////////////////////////////////////////////////////////



// Algoritmo de Dijkstra para caminhos mínimos sob custos positivos
////////////////////////////////////////////////////////////////////////

// Código inspirado no Programa 20.3 de Sedgewick. Não usa fila
// priorizada.
void 
GRAPHsptD1( Graph G, vertex s, vertex *pa, int *dist) {
   const int INFINITY = INT_MAX;
   bool *tree = mallocc( G->V * sizeof (bool));
   // inicialização:
   for (vertex v = 0; v < G->V; ++v)
      pa[v] = -1, tree[v] = false, dist[v] = INFINITY;
   pa[s] = s, tree[s] = true, dist[s] = 0;
   for (link a = G->adj[s]; a != NULL; a = a->next) 
      pa[a->w] = s, dist[a->w] = a->cst;
   while (true) {
      // cálculo de y:
      int min = INFINITY;
      vertex y = 0; // y initialized to make compiler happy
      for (vertex z = 0; z < G->V; ++z) {
         if (tree[z]) continue;
         if (dist[z] < min) // dist[z] é o preço de z
            min = dist[z], y = z;
      }
      if (min == INFINITY) break;
      tree[y] = true;
      // atualização de dist[]:
      for (link a = G->adj[y]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (tree[w]) continue;
         int cst = a->cst;
         if (dist[y] + cst < dist[w]) {
            dist[w] = dist[y] + cst; // relaxação de y-w
            pa[w] = y;
         }
      }
   }
   free( tree);
}

// Código inspirado no Programa 21.1 de Sedgewick. Usa uma fila
// priorizada.
void 
GRAPHsptD2( Graph G, vertex s, vertex *pa, int *dist) {
   const int INFINITY = INT_MAX;
   bool *tree = mallocc( G->V * sizeof (bool));
   // inicialização:
   for (vertex v = 0; v < G->V; ++v)
      pa[v] = -1, tree[v] = false, dist[v] = INFINITY; 
   pa[s] = s, tree[s] = true, dist[s] = 0;
   for (link a = G->adj[s]; a != NULL; a = a->next) {
      pa[a->w] = s;
      dist[a->w] = a->cst; // preço de a->w
   }
   PQinit( G->V);
   for (vertex v = 0; v < G->V; ++v)
      if (v != s) PQinsert( v, dist);
   while (!PQempty( )) {
      vertex y = PQdelmin( dist);
      if (dist[y] == INFINITY) break;
      tree[y] = true;
      // atualização de dist[]:
      for (link a = G->adj[y]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (tree[w]) continue; // redundant
         int cst = a->cst;
         if (dist[y] + cst < dist[w]) {
            dist[w] = dist[y] + cst; // relaxa y-w
            PQdec( w, dist);
            pa[w] = y;
         }
      }
   }
   PQfree( ); free( tree);
}



// Caminhos de comprimento máximo e de custo máximo
////////////////////////////////////////////////////////////////////////



// Fluxo máximo
////////////////////////////////////////////////////////////////////////



