// MAC0328 (2019) 
// Muitas funções discutidas nas minhas notas de aula e nos exercícios
// ainda não estão nesta biblioteca. Acrescente essas funções. Modifique
// as funções que já estão na biblioteca, se achar necessário. Sugiro
// marcar os trechos de código modificados/acrescentados com um
// comentário do tipo "// novo". Preserve meu bom layout (veja
// www.ime.usp.br/~pf/algoritmos/aulas/layout.html) e não use tabs. 

// Este arquivo: GRAPHlistsExperimental.c (codificação UTF-8)
// Data: 2019-10-05
// Autor: Paulo Feofiloff
//
// Esta é a implementação de um apêndice experimental da biblioteca 
// GRAPHlists de manipulação de grafos representados por listas de
// adjacência. Veja detalhes no arquivo-interface 
// GRAPHlistsExperimental.h.
//
// Este apêndice contém versões ingênuas e menos eficientes de várias
// das funções da biblioteca-mãe GRAPHlists.
//
// Tudo foi extraído de www.ime.usp.br/~pf/algoritmos_para_grafos/,
// que copiou muita coisa do livro "Algorithms", 3rd.ed., part 5, de
// Sedgewick.
////////////////////////////////////////////////////////////////////////


#define DEBUG false

// A interface GRAPHlists.h define a estrutura graph e o tipo-de-dados
// Graph. Também contém inclui as interfaces STACK.h, QUEUE.h, PQ.h,
// UF.h e MYTOOLS.h. Também contém as interfaces padrão stdlib.h,
// stdio.h, string.h, limits.h e stdbool.h.
#include "GRAPHlists.h"
#include "GRAPHlistsExperimental.h"



// Ferramentas para construção de grafos
////////////////////////////////////////////////////////////////////////

// Versão "pedestre" de GRAPHremoveArc() da bibioteca GRAPHlists.
void 
GRAPHremoveArc_v0( Graph G, vertex v, vertex w) {
   link a = G->adj[v];
   if (a != NULL && a->w == w) {
      G->adj[v] = a->next;
      free( a);
      G->A--;
   } else {
      link b = G->adj[v];
      while (b->next != NULL && b->next->w != w)
         b = b->next;
      if (b->next != NULL) {
         a = b->next;
         b->next = a->next;
         free( a);
         G->A--;
      }
   }
}



// Numerações e permutações de vértices
////////////////////////////////////////////////////////////////////////



// Grafos topológicos
////////////////////////////////////////////////////////////////////////



// Grafos aleatórios
////////////////////////////////////////////////////////////////////////



// Construtores de grafos
////////////////////////////////////////////////////////////////////////

// Supõe que m >= 1, n >= 1 e E <= m*n.
UGraph 
UGRAPHrand1bipartite_v0( int m, int n, int E) {
   UGraph G = UGRAPHinit( m+n);
   while (G->A < 2*E) {
      double r = rand( ) / (RAND_MAX + 1.0);
      vertex v = r*m;
      r = rand( ) / (RAND_MAX + 1.0);
      vertex w = m + r*n;
      UGRAPHinsertEdge( G, v, w);
   }
   return G;
}



// Caminhos e ciclos em grafos
////////////////////////////////////////////////////////////////////////



// Acessibilidade (caminho de um vértice a outro)
////////////////////////////////////////////////////////////////////////



// Busca em profundidade (= depth-first search = DFS)
////////////////////////////////////////////////////////////////////////

// Esta é uma versão simplificada da função privada dfsR() da biblioteca
// GRAPHlists. Ela será usada pelas funções GRAPHiStrong_v_0 e
// GRAPHiStrong_v_1.
static void 
dfsRsimple( Graph G, vertex v, int *pre, int *p) { 
   pre[v] = (*p)++; 
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (pre[a->w] == -1) {
         dfsRsimple( G, a->w, pre, p); 
      } 
}



// Ciclos e dags
////////////////////////////////////////////////////////////////////////

// Faz uma busca DFS completa e depois procura um arco de retorno.
bool 
GRAPHhasCycle_v1( Graph G) {
   int *pre = mallocc( G->V * sizeof (int));
   int *post = mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   GRAPHdfs( G, pre, post, pa);
   free( pa);
   for (vertex v = 0; v < G->V; ++v) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (post[v] < post[w]) { // v-w é de retorno
            free( post);
            free( pre);
            return true;
         }
      }
   } 
   // post[v] > post[w] para todo arco v-w
   free( post);
   free( pre);
   return false;
}



// Componentes conexas (de grafos não-dirigidos)
////////////////////////////////////////////////////////////////////////



// Distâncias, potencial, e relaxação
////////////////////////////////////////////////////////////////////////



// Busca em largura (= breadth-first search = BFS)
////////////////////////////////////////////////////////////////////////



// Algoritmo de caminhos mínimos
////////////////////////////////////////////////////////////////////////



// Circuitos e florestas (não-radicadas)
////////////////////////////////////////////////////////////////////////

bool 
UGRAPHhasCircuit_v1( UGraph G) {
   int *pre = mallocc( G->V * sizeof (int));
   int *post =  mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   GRAPHdfs( G, pre, post, pa); // calcula pre[], post[] e pa[]
   free( post);
   for (vertex v = 0; v < G->V; ++v) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (pre[w] < pre[v]) // v-w é de retorno
            if (w != pa[v]) {
               free( pre); free( pa);
               return true;
            }
      }
   } 
   free( pre); free( pa);
   return false;
}



// Grafos aresta-biconexos (= edge-biconnected = eb)
////////////////////////////////////////////////////////////////////////

// Função privada auxiliar usada por UGRAPHisEbc_v3(), UGRAPHebcc_v1() e
// UGRAPHebcc_v3(). Faz uma busca DFS no grafo não-dirigido G e calcula
// os vetores pre[], post[], pa[] e lo[] (lowest preorder number). Os
// quatro vetores são indexados pelos vértices de G. O vetor lo[] tem a
// seguinte propriedade: um arco x-y faz parte de uma ponte se e somente
// se x == pa[y] e lo[y] == pre[y]. 
static void 
UGRAPHlo_v0( UGraph G, int *pre, int *post, vertex *pa, int *lo) { 
   GRAPHdfs( G, pre, post, pa); // calcula pre[], post[] e pa[]
   vertex *vv = mallocc( G->V * sizeof (vertex));
   for (vertex v = 0; v < G->V; ++v)
      vv[post[v]] = v; 
   // vv[0..V-1] é permutação dos vértices em pós-ordem
   for (int i = 0; i < G->V; ++i) {
      vertex v = vv[i];
      lo[v] = pre[v];
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (pre[w] < pre[v]) { // w é ancestral próprio de v
            if (w != pa[v])
               lo[v] = min( lo[v], pre[w]);
         } else { // w é descendente próprio de v
            if (pa[w] == v)
               lo[v] = min( lo[v], lo[w]);
         }
      }
   }
   free( vv);
}

// Função privada auxiliar usada por UGRAPHlo_v1().
static void 
dfsRlo( UGraph G, vertex v, int *pre, int *post, vertex *pa, int *lo,
int *p, int *pt) { 
   pre[v] = (*p)++;
   lo[v] = pre[v];
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pre[w] != -1) { // w é ancestral próprio de v
         if (w != pa[v])
            lo[v] = min( lo[v], pre[w]);
      } else {
         pa[w] = v;
         dfsRlo( G, w, pre, post, pa, lo, p, pt);
         lo[v] = min( lo[v], lo[w]);
      }
   }
   post[v] = (*pt)++;
}

// Versão recursiva de UGRAPHlo_v0(). Usa dfsRlo(). Usada por
// UGRAPHisEbc_v3(), UGRAPHebcc_v1() e UGRAPHebcc_v3().
static void 
UGRAPHlo_v1( UGraph G, int *pre, int *post, vertex *pa, int *lo) {
   for (vertex v = 0; v < G->V; ++v)
      pre[v] = -1, pa[v] = v;
   int cnt = 0, cntt = 0;
   for (vertex v = 0; v < G->V; ++v)
      if (pre[v] == -1) {
         pa[v] = v;
         dfsRlo( G, v, pre, post, pa, lo, &cnt, &cntt);
      }
}

// Versão default de UGRAPHlo().
#define UGRAPHlo UGRAPHlo_v1
 
// Muito ingênua e lenta. Verifica se a remoção de uma aresta desconecta
// o grafo. Algoritmo quadrático: consome (V+E)*V unidades de tempo.
bool 
UGRAPHisEbc_v0( UGraph G) {
   if (!UGRAPHisConnected( G)) 
      return false;
   UGraph GG = GRAPHcopy( G);
   for (vertex v = 0; v < G->V; ++v) { // yes, G
      for (link a = G->adj[v]; a != NULL; a = a->next) { // yes, G
         vertex w = a->w;
         if (w < v) continue;
         GRAPHremoveArc( GG, v, w);
         if (!GRAPHreach( GG, v, w)) {
            GRAPHdestroy( GG);
            return false;
         }
         GRAPHinsertArc( GG, v, w);
      }
   }
   GRAPHdestroy( GG);
   return true;
}
 
// Usa UGRAPHlo() para calcular lo[] (um arco x-y faz parte de uma ponte
// se e somente se x == pa[y] e lo[y] == pre[y]. Depois examina todos os
// vértices à procura de pontes. Linear: consome V+E unidades de tempo. 
bool 
UGRAPHisEbc_v3( UGraph G) {
   int *pre = mallocc( G->V * sizeof (int));
   int *post =  mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   int *lo = mallocc( G->V * sizeof (int));
   // muitos escrevem "low" no lugar do meu "lo"
   UGRAPHlo( G, pre, post, pa, lo); // calcula pre[], post[], pa[], lo[]
   free( post);
   bool b = true;
   for (vertex v = 0; v < G->V; ++v) {
      if (lo[v] == pre[v] && pa[v] != v) {
         b = false; // pa[v]-v é ponte
         break;
      }
   }
   int roots = 0;
   for (vertex v = 0; v < G->V; ++v) {
      if (pa[v] == v) ++roots;
      if (roots > 1) { 
         b = false; // G é desconexo;
         break;
      }
   }
   free( lo);
   free( pa);
   free( pre);
   return b;
}



// Componentes aresta-biconexas (= edge-biconnected components = ebcc)
////////////////////////////////////////////////////////////////////////

// Implementação ingênua. Remove todas as pontes e calcula as 
// componentes conexas do que sobrou.
int 
UGRAPHebcc_v0( UGraph G, int *ebcc) { 
   Graph GG = GRAPHcopy( G);
   int *pre = mallocc( GG->V * sizeof (int));
   int *post =  mallocc( GG->V * sizeof (int));
   vertex *pa = mallocc( GG->V * sizeof (vertex));
   GRAPHdfs( GG, pre, post, pa); // preenche pre[], post[], pa[]
   free( pre);
   free( post);
   for (vertex v = 0; v < GG->V; ++v) {
      vertex u = pa[v];
      if (u == v) continue;
      UGRAPHremoveEdge( GG, v, u);
      if (GRAPHreach( GG, v, u))
         UGRAPHinsertEdge( GG, v, u);
   }
   // GG não tem pontes
   int id = UGRAPHcc( GG, ebcc);
   // GG tem id componentes conexas
   UGRAPHdestroy( GG);
   free( pa);
   return id;
}

// Implementação menos ingênua. Usa UGRAPHlo() para encontrar as pontes.
// Remove as pontes e calcula as componentes conexas do que sobrou.
int 
UGRAPHebcc_v1( UGraph G, int *ebcc) { 
   Graph GG = GRAPHcopy( G);
   int *pre = mallocc( GG->V * sizeof (int));
   int *post =  mallocc( GG->V * sizeof (int));
   int *lo =  mallocc( GG->V * sizeof (int));
   vertex *pa = mallocc( GG->V * sizeof (vertex));
   UGRAPHlo( GG, pre, post, pa, lo); 
   // preenche pre[], post[], pa[] e lo[]
   free( post);
   for (vertex v = 0; v < GG->V; ++v) {
      if (lo[v] == pre[v]) {
         if (pa[v] == v) continue;
         UGRAPHremoveEdge( GG, pa[v], v);
      }
   }
   // GG não tem pontes
   int id = UGRAPHcc( GG, ebcc);
   // GG tem id componentes conexas
   UGRAPHdestroy( GG);
   free( pa);
   free( pre);
   free( lo);
   return id;
}

// Função privada auxiliar usada por UGRAPHebcc_v3(). Faz ebcc[x] = id
// para todo vértice x que tenha ebcc[x] == -1 e seja descendente de v
// na floresta radicada representada por pa[].
static void 
compR( UGraph G, vertex v, int *ebcc, vertex *pa, int id) { 
   ebcc[v] = id; 
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pa[w] == v && ebcc[w] == -1)
         compR( G, w, ebcc, pa, id); 
   }
}

// Usa UGRAPHlo() para calcular lo[]. Depois examina os vértices em pos-
// ordem à procura de cabeças de componentes.
int 
UGRAPHebcc_v3( UGraph G, int *ebcc) {
   int *pre = mallocc( G->V * sizeof (int));
   int *post =  mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   int *lo = mallocc( G->V * sizeof (int));
   // muitos livros escrevem "low" no lugar do meu "lo"
   // calcula pre[], post[], pa[] e lo[]:
   UGRAPHlo( G, pre, post, pa, lo); 
   // v é cabeça de componente aresta-biconexa sse lo[v] == pre[v]
   // x-y é ponte sse x = pa[y] e lo[y] == pre[y] 
   vertex *vv = mallocc( G->V * sizeof (vertex));
   for (vertex v = 0; v < G->V; ++v)
      vv[post[v]] = v;
   // vv[0..V-1] é permutação dos vértices em pós-ordem
   for (vertex v = 0; v < G->V; ++v)
      ebcc[v] = -1;
   int id = 0;
   for (int i = 0; i < G->V; ++i) {
      vertex v = vv[i];
      if (lo[v] == pre[v]) // ebcc[v] == -1
         // v é cabeça decomponente aresta-biconexa
         compR( G, v, ebcc, pa, id++); 
   } 
   free( pre);
   free( post);
   free( pa);
   free( lo);
   free( vv);
   return id;
}



// Grafos fortemente conexos (= strongly connected)
////////////////////////////////////////////////////////////////////////

bool
GRAPHisStrong_v0( Graph G) {
   int *pre = mallocc( G->V * sizeof (int));
   for (vertex v = 0; v < G->V; ++v) 
      pre[v] = -1; 
   int cnt = 0;
   dfsRsimple( G, 0, pre, &cnt); // preenche o vetore pre[] 
   for (vertex v = 0; v < G->V; ++v) {
      if (pre[v] == -1) {
         free( pre);
         return false;
      }
   }
   for (vertex s = 1; s < G->V; ++s) { 
      if (!GRAPHreach( G, s, 0)) {
         free( pre);
         return false;
      }
   }
   free( pre);
   return true;
}

// Faz uma busca DFS no grafo G e calcula os vetores pre[], post[], pa[]
// e lo[] (lowest preorder number). Os quatro vetores são indexados
// pelos vértices de G. O vetor lo[] tem a seguinte propriedade: um arco
// x-y abraça um vértice v (ou seja, x é descendente de v mas y não é
// descendente de v) se e somente se lo[y] == pre[y]. (O código só 
// difere do de UGRAHlo_v0() em uma linha.)
static void 
GRAPHlo( Graph G, int *pre, int *post, vertex *pa, int *lo) { 
   GRAPHdfs( G, pre, post, pa); // calcula pre[], post[] e pa[]
   vertex *vv = mallocc( G->V * sizeof (vertex));
   for (vertex v = 0; v < G->V; ++v)
      vv[post[v]] = v; 
   // vv[0..V-1] é permutação dos vértices em pós-ordem
   for (int i = 0; i < G->V; ++i) {
      vertex v = vv[i];
      lo[v] = pre[v];
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (pre[w] < pre[v]) // A
            lo[v] = min( lo[v], pre[w]);
         else // B
            lo[v] = min( lo[v], lo[w]);
      }
   }
   free( vv);
}
// Observação A: w é ancestral próprio ou primo esquerdo de v.
// Observação B: w é descendente próprio de v. Mesmo que não seja filho
// de v, se lo[w] < lo[v] então lo[w] ≡ pre[y] para algum arco x-y que
// abraça w e nesse caso x-y também abraça v.

// Duas vezes mais rápido que GRAPHisStrong_v1() quando grafo aleatório
// é muito grande
bool 
GRAPHisStrong_v3( Graph G) { 
   int *pre = mallocc( G->V * sizeof (int));
   int *post =  mallocc( G->V * sizeof (int));
   vertex *pa = mallocc( G->V * sizeof (vertex));
   int *lo = mallocc( G->V * sizeof (int));
   // muitos escrevem "low" no lugar do meu "lo"
   GRAPHlo( G, pre, post, pa, lo); // calcula pre[], pa[] e lo[]
   free( post);
   for (vertex v = 0; v < G->V; ++v) {
      if (lo[v] == pre[v] && pa[v] != v) {
         free( lo); free( pa); free( pre);
         return false;
      }
   }
   int roots = 0;
   for (vertex v = 0; v < G->V; ++v) {
      if (pa[v] == v) ++roots;
      if (roots > 1) {
         free( lo); free( pa); free( pre);
         return false;
      }
   }
   free( lo); free( pa); free( pre);
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

// Recebe o grafo de Mycielski G_k e devolve o grafo de Mycielski 
// G_{k+1}. Supõe que k >= 2.
static UGraph 
nextMycielski( UGraph G) {
   int V = G->V;
   UGraph GG = GRAPHinit( 2*V+1); // this will become G_{k+1}
   for (vertex v = 0; v < V; ++v) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;
         UGRAPHinsertEdge( GG, v, w);
         UGRAPHinsertEdge( GG, v+V, w); // could use inserEdgeQuick
      }
      UGRAPHinsertEdge( GG, v+V, 2*V); // could use inserEdgeQuick
   }
   return GG;
   // if G_k has n vertices and m edges 
   // then G_{k+1} will have 2n+1 vertices and 3m+n edges
}

// Devolve o grafo de Mycielski G_k.
UGraph 
UGRAPHmycielski( int k) {
   UGraph G = GRAPHinit( 2);
   UGRAPHinsertEdge( G, 0, 1); // G_2
   if (k == 2) return G;
   UGraph GG;
   for (int i = 2; i < k; ++i) { 
      // build G_{i+1} from G_i
      GG = nextMycielski( G);
      GRAPHdestroy( G);
      G = GG;
   }
   return GG;
}



// Grafos bipartidos e circuitos ímpares
////////////////////////////////////////////////////////////////////////



// Emparelhamentos (= matchings)
////////////////////////////////////////////////////////////////////////



// Emparelhamentos em grafos bipartidos (= bipartite matching)
////////////////////////////////////////////////////////////////////////



// Algoritmo de Prim para árvores geradoras de custo mínimo 
// (= MST = minimal spanning tree)
////////////////////////////////////////////////////////////////////////



// Algoritmo de Kruskal para árvores geradoras de custo mínimo 
// (= MST = minimal spanning tree)
////////////////////////////////////////////////////////////////////////



// Distâncias e potenciais sob custos positivos (= SPT)
////////////////////////////////////////////////////////////////////////



// Caminhos de custo mínimo em dags (custos arbirários)
////////////////////////////////////////////////////////////////////////



// Algoritmo de Dijkstra para caminhos mínimos sob custos positivos
////////////////////////////////////////////////////////////////////////



// Caminhos de comprimento máximo e de custo máximo
////////////////////////////////////////////////////////////////////////



// Fluxo máximo
////////////////////////////////////////////////////////////////////////




