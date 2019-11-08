// MAC0328 (2019) 
// Muitas funções discutidas nas minhas notas de aula e nos exercícios
// ainda não estão nesta biblioteca. Acrescente essas funções. Modifique
// as funções que já estão na biblioteca, se achar necessário. Sugiro
// marcar os trechos de código modificados/acrescentados com um
// comentário do tipo "// novo". Preserve meu bom layout (veja
// www.ime.usp.br/~pf/algoritmos/aulas/layout.html) e não use tabs. 

// Este arquivo: GRAPHlistsExperimental.h (codificação UTF-8)
// Data: 2019-10-05
// Autor: Paulo Feofiloff
//
// Esta é a interface do apêndice experimental da biblioteca GRAPHlists
// de manipulação de grafos representados por listas de adjacência.
// Este apêndice contém versões ingênuas e menos eficientes de várias
// das funções da biblioteca-mãe GRAPHlists.
//
// Tudo foi extraído de www.ime.usp.br/~pf/algoritmos_para_grafos/,
// que copiou muita coisa do livro "Algorithms", 3rd.ed., part 5, de
// Sedgewick.
////////////////////////////////////////////////////////////////////////


#ifndef _GRAPHlistsExperimental_h
#define _GRAPHlistsExperimental_h



// Ferramentas para construção de grafos
////////////////////////////////////////////////////////////////////////

// A função GRAPHinsertArcQuick() insere um arco v-w no grafo G sem
// antes verificar se o arco v-w já existe. Esta função só deve ser
// usada se o cliente souber que G não tem arco v-w. A função supõe que
// v e w são distintos e menores que G->V.
void 
GRAPHinsertArcQuick( Graph G, vertex v, vertex w);

// A função GRAPHinsertArcQuick_c() insere um arco v-w com custo cst no
// grafo G sem antes verificar se o arco v-w já existe. Esta função só
// deve ser se o cliente souber que G não tem arco v-w.
void 
GRAPHinsertArcQuick_c( Graph G, vertex v, vertex w, int cst);

// Esta função insere uma aresta v-w no grafo não-dirigido G sem antes
// verificar se a aresta já existe. A função só deve ser usada se o
// usuário souber que G não tem a aresta v-w. A função supõe que v e w
// são distintos e menores que G->V.
void 
UGRAPHinsertEdgeQuick( UGraph G, vertex v, vertex w);

// Esta função insere uma aresta v-w com custo cst no grafo não-
// dirigido G sem antes verificar se a aresta já existe. A função supõe
// que v e w são distintos e menores que G->V.
void 
UGRAPHinsertEdgeQuick_c( UGraph G, vertex v, vertex w, int cst);

// A função GRAPHremoveArc_v0() remove o arco v-w do grafo G. Se não
// existe arco v-w, a função não faz nada. Esta é uma versão "pedestre"
// de GRAPHremoveArc().
void 
GRAPHremoveArc_v0( Graph G, vertex v, vertex w);



// Numerações e permutações de vértices
////////////////////////////////////////////////////////////////////////



// Grafos topológicos
////////////////////////////////////////////////////////////////////////



// Grafos aleatórios
////////////////////////////////////////////////////////////////////////



// Construtores de grafos
////////////////////////////////////////////////////////////////////////

// Constroi um grafo não-dirigido bipartido aleatório com m >= 1
// vértices "brancos", n >= 1 vértices "vermelhos" e E <= m*n arestas.
// Os vértices "brancos" são 0..m-1 e os "vermelhos" são m..m+n-1.
UGraph 
UGRAPHrand1bipartite_v0( int m, int n, int E);



// Caminhos e ciclos em grafos
////////////////////////////////////////////////////////////////////////



// Acessibilidade (caminho de um vértice a outro)
////////////////////////////////////////////////////////////////////////



// Busca em profundidade (= depth-first search = DFS)
////////////////////////////////////////////////////////////////////////



// Ciclos e dags
////////////////////////////////////////////////////////////////////////

// Decide se o grafo G tem ciclo. Esta é uma versão de GRAPHhasCycle()
// da biblioteca GRAPHlists.
bool 
GRAPHhasCycle_v1( Graph G);



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

// Esta função decide se o grafo não-dirigido G tem um circuito. Em
// caso de resposta negativa, G é uma floresta.
bool 
UGRAPHhasCircuit_v1( UGraph G);



// Grafos aresta-biconexos (= edge-biconnected = eb)
////////////////////////////////////////////////////////////////////////

// Decide se o grafo não-dirigido G é aresta-biconexo. (Algoritmo
// quadrático: consome (V+E)*V unidades de tempo.)
bool 
UGRAPHisEbc_v0( UGraph G);

// Decide se o grafo não-dirigido G é aresta-biconexo. (Algoritmo
// quadrático: consome (V+E)*V unidades de tempo. Mais rápido que
// UGRAPHisEbc_v0().)
bool 
UGRAPHisEbc_v1( UGraph G);
 
// Decide se o grafo não-dirigido G é aresta-biconexo. (Implementa o
// algoritmo de Tarjan. A função é linear: consome V+E unidades de
// tempo.)
bool 
UGRAPHisEbc_v3( UGraph G);



// Componentes aresta-biconexas (= edge-biconnected components = ebcc)
////////////////////////////////////////////////////////////////////////

// Esta função devolve o número (quantidade) de componentes aresta-
// biconexas do grafo não-dirigido G. Também atribui um rótulo ebcc[v] 
// (os rótulos são 0,1,2,...) a cada vértice v de G de modo que dois 
// vértices tenham o mesmo rótulo se e somente se os dois pertencem à 
// mesma componente aresta-biconexa. A função é ingênua e quadrática:
// consome tempo poporcional a V*(V+E).
int 
UGRAPHebcc_v0( UGraph G, int *ebcc);

// Versão melhorada de UGRAPHebcc_v0.
int 
UGRAPHebcc_v1( UGraph G, int *ebcc);

// Esta função devolve o número (quantidade) de componentes aresta-
// biconexas do grafo não-dirigido G. Também atribui um rótulo ebcc[v] 
// (os rótulos são 0,1,2,...) a cada vértice v de G de modo que dois 
// vértices tenham o mesmo rótulo se e somente se os dois pertencem à 
// mesma componente aresta-biconexa. (A função é linear. Implementa uma
// versão simplificada do algoritmo de Tarjan.)
int 
UGRAPHebcc_v3( UGraph G, int *ebcc);



// Grafos fortemente conexos (= strongly connected)
////////////////////////////////////////////////////////////////////////

// Decide se grafo G é fortemente conexo. (Algoritmo ingênuo,
// quadrático.)
bool
GRAPHisStrong_v0( Graph G);

// Decide se grafo G é fortemente conexo. (Algoritmo linear simples.)
bool
GRAPHisStrong_v1( Graph G);

// Decide se o grafo G é fortemente conexo. (A função implementa o
// algoritmo de Tarjan.)
bool 
GRAPHisStrong_v3( Graph G); 



// Componentes fortes (= strong components = sc)
////////////////////////////////////////////////////////////////////////

// Esta função devolve o número (quantidade) de componentes fortes do
// grafo G. Também atribui um rótulo sc[v] (os rótulos são 0,1,2,...) 
// a cada vértice v de G de modo que dois vértices tenham o mesmo rótulo
// se e somente se os dois pertencem à mesma componente forte. A função
// consome tempo linear (tempo proporcional a V+A). (A função implementa
// um algoritmo ingênuo: faz uma cópia do grafo, remove os arcos que não
// pertencem a ciclos, e calcula as "componentes conexas" do grafo
// resultante.)
int 
GRAPHsc_v0( Graph G, int *sc);

// Variante de GRAPHsc_v0().
int 
GRAPHsc_v1( Graph G, int *sc);



// Algoritmo de Tarjan para componentes fortes
////////////////////////////////////////////////////////////////////////



// Algoritmo de Kosaraju para componentes fortes
////////////////////////////////////////////////////////////////////////



// Coloração de vértices
////////////////////////////////////////////////////////////////////////

// Devolve o grafo de Mycielski G_k.
UGraph 
UGRAPHmycielski( int k);



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




#endif

