// MAC0328 (2019) 
// Muitas funções discutidas nas minhas notas de aula e nos exercícios
// ainda não estão nesta biblioteca. Acrescente essas funções. Modifique
// as funções que já estão na biblioteca, se achar necessário. Sugiro
// marcar os trechos de código modificados/acrescentados com um
// comentário do tipo "// novo". Preserve meu bom layout (veja
// www.ime.usp.br/~pf/algoritmos/aulas/layout.html) e não use tabs. 

// Este arquivo: GRAPHlists.h (codificação UTF-8)
// Data: 2019-10-05
// Autor: Paulo Feofiloff
//
// Esta é a interface de uma biblioteca de manipulação de grafos
// representados por listas de adjacência. Os grafos não têm arcos
// paralelos nem laços. Grafos não-dirigidos (= undirected) são um tipo
// especial de grafo: cada aresta de um grafo não-dirigido é um par
// (v-w, w-v) de arcos antipralelos.
//
// Os grafos têm custos (= costs = weights) nos arcos, mas muitas das
// funções ignoram os custos.
//
// Tudo foi extraído de www.ime.usp.br/~pf/algoritmos_para_grafos/,
// que copiou muita coisa do livro "Algorithms", 3rd.ed., part 5, de
// Sedgewick.
////////////////////////////////////////////////////////////////////////


#ifndef _GRAPHlists_h
#define _GRAPHlists_h

#include "STACK.h" // pilha
#include "QUEUE.h" // fila
#include "PQ.h" // fila priorizada (priority queue)
#include "UF.h" // union-find
#include "MYTOOLS.h" // string, mallocc(), randInteger(), ...
#include <stdlib.h> // strtol(), qsort(), etc.
#include <stdio.h>
#include <string.h> // strtok(), etc.
#include <limits.h> // INT_MAX, etc.
#include <stdbool.h>

#define min( A, B) (A) < (B) ? (A) : (B)
#define max( A, B) (A) > (B) ? (A) : (B)



// Estruturas de dados básicas
////////////////////////////////////////////////////////////////////////

// Vértices de grafos são representados por objetos do tipo vertex. Os
// vértices são inteiros não-negativos (0,1,2,...). Em raras ocasiões,
// uma variável do tipo vertex pode ter valor -1 com o significado de
// "não definido".
#define vertex int

// A lista de adjacência de um vértice v é composta por nós do tipo
// node. Cada nó da lista corresponde a um arco e contém um vizinho w de
// v e o endereço do nó seguinte da lista. Cada nó tem um campo cst para
// o custo do arco; o campo é ignorado pelas funções que manipulam
// grafos sem custos. Um link é um ponteiro para um node.
typedef struct node *link;
struct node { 
   vertex w; 
   int cst;
   link next; 
};

// A estrutura graph representa um grafo. O campo adj é um ponteiro para
// o vetor de listas de adjacência, o campo V é o número de vértices e o
// campo A é o número de arcos. Suporemos sempre que V >= 1.
struct graph {
   int V; 
   int A; 
   link *adj; 
};

// Um objeto do tipo Graph contém o endereço de um graph.
typedef struct graph *Graph;

// O tipo UGraph é um sinônimo de Graph. Esse tipo tem a missão de
// deixar claro, para o leitor humano, que o grafo é não-dirigido. (O
// "U" de "UGraph" é uma abreviatura de "undirected".) 
#define UGraph Graph

// O tipo Dag é um sinônimo de Graph. Esse tipo tem a missão de deixar
// claro, para o leitor humano, que o grafo é acíclico. 
#define Dag Graph

// O projeto de muitas das funções desta biblioteca, precisa enfrentar a
// seguinte decisão de projeto:
//  - ou o cliente (usuário da biblioteca) aloca um vetor onde a função 
//    depositará seus resultados
//  - ou a própria função aloca um vetor e devolve o seu endereço ao
//    cliente.
// Em qualquer caso, a desalocação do vetor deverá ser feita pelo
// cliente. A primeira alternativa parece mais limpa pois o cliente
// trata tanto da alocação (mallocc) quanto da desalocação (free).



// Ferramentas para construção de grafos
////////////////////////////////////////////////////////////////////////

// Algumas funções têm duas versões, uma para grafos sem custos nos
// arcos e outra para grafos com custos; o nome da segunda versão tem um
// sufixo "_c". Em alguns casos --- como o da árvore geradora de custo
// mínimo -- o sufixo "_c" é omitido porque a função só faz sentido para
// grafos com custos.

// A função GRAPHinit constrói e devolve um grafo com vértices
// 0 1 ... V-1 e nenhum arco.
Graph 
GRAPHinit( int V);

// Idem para grafo não-dirigido.
#define UGRAPHinit GRAPHinit

// A função GRAPHinsertArc() insere um arco v-w no grafo G. A função
// supõe que v e w são distintos e menores que G->V. Se o grafo já tem
// um arco v-w, a função não faz nada.
void 
GRAPHinsertArc( Graph G, vertex v, vertex w);

// A função GRAPHinsertArc_c() insere um arco v-w com custo cst no
// grafo G. A função supõe que v e w são distintos e menores que G->V.
// Se o grafo já tem um arco v-w, o novo custo cst substitui o antigo.
void 
GRAPHinsertArc_c( Graph G, vertex v, vertex w, int cst);

// A função UGRAPHinsertEdge() insere uma aresta v-w no grafo não-
// dirigido G. A função supõe que v e w são distintos e menores que
// G->V. Se o grafo já tem uma aresta v-w, a função não faz nada.
void 
UGRAPHinsertEdge( UGraph G, vertex v, vertex w);

// Esta função insere uma aresta v-w com custo cst no grafo não-
// dirigido G. A função supõe que v e w são distintos e menores que
// G->V. Se o grafo já tem uma aresta v-w, a função não faz nada.
void 
UGRAPHinsertEdge_c( UGraph G, vertex v, vertex w, int cst);

// A função GRAPHremoveArc() remove o arco v-w do grafo G. Se não existe
// arco v-w, a função não faz nada.
void 
GRAPHremoveArc( Graph G, vertex v, vertex w);

// A função UGRAPHremoveEdge() remove aresta v-w do grafo não-dirigido
// G. Se não existe aresta v-w, a função não faz nada.
void 
UGRAPHremoveEdge( UGraph G, vertex v, vertex w);

// Para cada vértice v do grafo G, esta função imprime, em uma linha da
// saída padrão, todos os vértices adjacentes a v.
void 
GRAPHshow( Graph G);

#define UGRAPHshow GRAPHshow

// Para cada vértice v do grafo G, esta função imprime, em uma linha da
// saída padrão, todos os vértices adjacentes a v e os respectivos
// custos.
void 
GRAPHshow_c( Graph G);

#define UGRAPHshow_c GRAPHshow_c

// Esta função imprime, na saída padrão, todos os arcos de G. Cada linha
// da saída tem a forma v w, sendo v a ponta inicial e w a ponta final
// de um arco.
void 
GRAPHshowArcs( Graph G);

// Esta função imprime, na saída padrão, todos os arcos de G. Cada linha
// da saída tem a forma v w (cst), sendo v a ponta inicial, w aponta
// final e cst o custo de um arco.
void 
GRAPHshowArcs_c( Graph G);

// Esta função devolve uma cópia do grafo G.
Graph 
GRAPHcopy( Graph G);

#define UGRAPHcopy GRAPHcopy

// Decide se os grafos G e H são iguais.
bool 
GRAPHisEqual( Graph G, Graph H);

// Esta função desaloca toda a memória usada pela estrutura de dados que
// representa o grafo G.
void 
GRAPHdestroy( Graph G);

#define UGRAPHdestroy GRAPHdestroy

// Esta função decide se o grafo G é não-dirigido.
bool 
GRAPHisUndirected( Graph G);

// Esta função devolve o grau de entrada do vértice v no grafo G. A
// função é cara: consome tempo proporcional ao tamanho do grafo.
int
GRAPHindeg( Graph G, vertex v);

// Esta função devolve o grau de saída do vértice v no grafo G.
int
GRAPHoutdeg( Graph G, vertex v);

// Constrói o reverso do grafo G. (O reverso tem um arco w-v para cada
// arco v-w de G.) 
Graph 
GRAPHreverse( Graph G);

// Esta função inverte as listas de adjacência de todos os vértices do
// grafo G. Por exemplo, se os 4 vizinhos de um certo vértice u aparecem
// na ordem v w x y na lista G->adj[u], então depois da aplicação da
// função os vizinhos aparecem na ordem y x w v.
void 
GRAPHinvertLists( Graph G);

// Versão iterativa (ou seja, não-recursiva) de GRAPHinvertLists().
void 
GRAPHinvertLists_i( Graph G);

// Esta função devolve a soma dos custos dos arcos do grafo G. Se o 
// cálculo da soma causar overflow aritmético, imprime mensagem e para.
int 
GRAPHcost_c( Graph G);

// Esta função devolve a soma dos custos das arestas do grafo não-
// dirigido G. (A função supõe que cada um dos dois arcos que formam
// uma aresta tem custo igual ao da aresta.) Se o cálculo da soma causar
// overflow aritmético, imprime mensagem e para.
int 
UGRAPHcost_c( UGraph G);

// Esta função constrói o grafo descrito no arquivo infile, que deve ter
// o seguinte formato: primeiro o número de vértices, depois o número de
// arcos, depois os pares de vértices que definem os arcos. As demais
// linhas do arquivo são ignoradas (podendo ser usadas para
// comentários). Exemplo:
//      6
//      10
//      0 4
//      0 1
//      2 4
//      2 3
//      2 0
//      3 5
//      3 4
//      4 5
//      4 1
//      5 1
// A função devolve NULL se, por qualquer motivo, o grafo não puder ser
// construído.
Graph 
GRAPHinputArcs( FILE *infile);

// Idem para grafos não-dirigidos, trocando "arco" por "aresta".
UGraph 
UGRAPHinputEdges( FILE *infile);

// Esta função constrói o grafo com custos nos arcos descrito no arquivo
// infile. Formato do arquivo: primeiro o número de vértices, depois o
// número de arcos, depois os pares de vértices que definem os arcos
// seguidos dos respectivos custos. As demais linhas do arquivo são
// ignoradas (podendo ser usadas para comentários). Exemplo:
//      6
//      10
//      0 4   91
//      0 1   92
//      2 4   88
//      2 3   99
//      2 0   99
//      3 5   88
//      3 4   77
//      4 5   66
//      4 1   55
//      5 1   44
// A função devolve NULL se, por qualquer motivo, o grafo não puder ser
// construído.
Graph 
GRAPHinputArcs_c( FILE *infile);

// Idem para grafos não-dirigidos, trocando "arco" por "aresta".
UGraph 
UGRAPHinputEdges_c( FILE *infile);

#define LINE_MAX 1000

// Esta função constrói o grafo descrito no arquivo infile. Formato: A
// primeira linha do arquivo contém o número V de vértices do grafo
// (devemos ter V >= 1). Cada uma das V linhas seguintes contém a lista
// de adjacência de um dos vértices do grafo; cada uma dessas linhas tem
// a forma 
//       v w1 w2 ... wk 
// sendo w1 w2 ... wk os vizinhos do vértice v. As demais linhas de
// infile são ignoradas (podendo ser usadas para comentários). Exemplo:
//     7
//     0   6 1
//     1   0 6 3
//     2   4
//     3   1
//     4   2
//     5
//     6   0 1
// Cada linha do arquivo infile deve ter < LINE_MAX caracteres (contando
// o \n final). Devemos ter LINE_MAX >= 2. Todos os caracteres das V+1
// primeiras linhas devem ser dígitos decimais, espaços, e '\n'. Cada
// uma das V+1 primeiras linhas tem pelo menos um dígito decimal.
//    No grafo construído, a ordem dos vértices em cada lista de
// adjacência é igual à ordem em que os vértices aparecem na linha 
// correspondente de infile.
Graph 
GRAPHinputLists(  FILE *infile);

#define UGRAPHinputLists GRAPHinputLists

// Esta função constrói o grafo descrito no arquivo infile. Formato: A
// primeira linha do arquivo contém o número V de vértices do grafo
// (devemos ter V >= 1). Cada uma das V linhas seguintes contém a lista
// de adjacência de um dos vértices do grafo; cada uma dessas linhas tem
// a forma 
//       v w1 c1 w2 c2 ... wk ck 
// sendo w1 w2 ... wk os vizinhos do vértice v e c1 c2 ... ck os custos
// dos arcos v-w1 v-w2 ... v-wk respectivamente. As demais linhas de
// infile são ignoradas (podendo ser usadas para comentários). Exemplo:
//     7
//     0   6  90   1  91
//     1   0  92   6  93   3  94
//     2   4  95  
//     3   1  96  
//     4   2  97  
//     5         
//     6   0  98   1  99
// Cada linha do arquivo infile deve ter < LINE_MAX caracteres (contando
// o \n final). Devemos ter LINE_MAX >= 2. Todos os caracteres das V+1
// primeiras linhas devem ser dígitos decimais, espaços, e '\n'. Cada
// uma das V+1 primeiras linhas tem pelo menos um dígito decimal.
//    No grafo construído, a ordem dos vértices em cada lista de
// adjacência é igual à ordem em que os vértices aparecem na linha 
// correspondente de infile.
Graph 
GRAPHinputLists_c(  FILE *infile);

#define UGRAPHinputLists_c GRAPHinputLists_c

// O tipo edge representa uma aresta. As pontas de uma aresta e são e.v
// e e.w. (Isso é usado apenas na implementação do algoritmo de Kruskal
// para árvore geradora de custo mínimo.)
typedef struct {vertex v, w; int cst;} edge;

// Armazena as arestas do grafo não-dirigido G no vetor e[0..E-1], sendo
// E = G->A/2.
void 
UGRAPHedges( UGraph G, edge *e);



// Numerações e permutações de vértices
////////////////////////////////////////////////////////////////////////

// Converte a permutação perm[0..V-1] dos vértices 0..V-1 de um grafo na
// correspondente numeração num[0..V-1] dos vértices. (Teremos
// num[perm[i]] == i.)
void
perm2num( int V, vertex *perm, int *num);

// Converte a numeração injetiva num[0..V-1] dos vértices de um grafo na
// correspondente permutação perm[0..V-1] dos vértices. O vetor num[]
// deve ser uma bijeção entre o conjunto dos vértices e o conjunto de
// números 0..V-1.
void
injnum2perm( int V, int *num, vertex *perm);

// Converte a numeração num[0..V-1] dos vértices de um grafo na
// correspondente permutação perm[0..V-1] dos vértices. A numeração
// num[] pode não ser injetiva; basta que atribua um número inteiro não
// negativo a cada vértice.
void
num2perm( int V, int *num, vertex *perm);



// Grafos topológicos
////////////////////////////////////////////////////////////////////////

// Uma numeração num[] dos vértices é topológica se num[v] < num[w] para
// cada arco v-w. Uma numeração num[] é anti-topológica se num[v] >
// num[w] para cada arco v-w. Uma permutação vv[] dos vértices é
// topológica se i < j para cada arco vv[i]-vv[j] do grafo. Uma
// permutação vv[] dos vértices é anti-topológica se i > j para cada
// arco vv[i]-vv[j] do grafo.
 
// Decide se o grafo G é topológico. Em caso afirmativo, armazena no
// vetor topo[0..V-1] uma numeração topológica dos vértices de G. 
// (A função implementa o algoritmo de eliminação iterada de fontes.)
// (Veja também a função GRAPHisDag() que é mais completa e tão
// eficiente quanto esta.)
bool 
GRAPHisTopo( Graph G, int *topo);



// Grafos aleatórios
////////////////////////////////////////////////////////////////////////

// Constrói grafo aleatório com vértices 0..V-1 e exatamente A arcos. A
// função supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função
// consume muuuito tempo. Por isso, a função não deve ser usada para
// gerar grafos muito densos.
Graph 
GRAPHrand1( int V, int A);

// Constrói grafo não-dirigido aleatório com vértices 0..V-1 e
// exatamente E arestas. A função supõe que E <= V*(V-1)/2. Se E for
// proximo de V*(V-1)/2, a função consume muuuito tempo. Por isso, a
// função não deve ser usada para gerar grafos muito densos.
UGraph 
UGRAPHrand1( int V, int E);

// Esta é a versão de GRAPHrand1() para grafos com custos nos arcos. Os
// custos dos arcos são escolhidos aleatoriamente no intervalo semi-
// aberto [cmin,cmax).
Graph 
GRAPHrand1_c( int V, int A, int cmin, int cmax);

// Esta é a versão de UGRAPHrand1() para grafos não-dirigidos com custos
// nas arestas. Os custos são escolhidos aleatoriamente no intervalo
// semi-aberto [cmin,cmax).
UGraph 
UGRAPHrand1_c( int V, int E, int cmin, int cmax);

// Constrói um grafo aleatório com vértices 0..V-1. Cada um dos V*(V-1)
// possíveis arcos é inserido com probabilidade p, sendo p calculado de
// modo que o número esperado de arcos seja A. A função supõe que 
// V >= 2 e A <= V*(V-1). A função é mais usada para gerar grafos
// densos.
Graph 
GRAPHrand2( int V, int A);

// Esta é a versão de GRAPHrand2() para grafos com custos nos arcos. Os
// custos dos arcos são escolhidos aleatoriamente no intervalo
// semi-aberto [cmin,cmax).
Graph 
GRAPHrand2_c( int V, int A, int cmin, int cmax);

// Constrói um grafo não-dirigido aleatório com vértices 0..V-1. Cada
// uma das V*(V-1)/2 possíveis arestas é inserida com probabilidade p,
// sendo p calculado de modo que o número esperado de arestas seja E.
// A função supõe que V >= 2 e E <= V*(V-1)/2. A função é mais usada
// para gerar grafos não-dirigidos densos.
UGraph 
UGRAPHrand2( int V, int E);

// Esta é a versão de UGRAPHrand2() para grafos não-dirigidos com custos
// nas arestas. Os custos das arestas são escolhidos aleatoriamente no
// intervalo semi-aberto [cmin,cmax).
UGraph 
UGRAPHrand2_c( int V, int E, int cmin, int cmax);



// Construtores de grafos
////////////////////////////////////////////////////////////////////////

// Constroi um grafo não-dirigido bipartido aleatório com m >= 1
// vértices "brancos", n >= 1 vértices "vermelhos" e E <= m*n arestas.
UGraph 
UGRAPHrand1bipartite( int m, int n, int E);

// Constroi um grafo não-dirigido bipartido aleatório com m >= 1
// vértices "brancos", n >= 1 vértices "vermelhos" e E <= m*n arestas.
// Os custos das arestas são escolhidos aleatoriamente no intervalo
// semi-aberto [cmin,cmax).
UGraph 
UGRAPHrand1bipartite_c( int m, int n, int E, int cmin, int cmax);

// Constroi uma árvore (não-dirigida, não-radicada) aleatória com V
// vértices.
UGraph 
UGRAPHrandTree( int V);

// Constroi uma árvore (não-dirigida, não-radicada) aleatória com V
// vértices. Os custos das arestas são escolhidos aleatoriamente no
// intervalo semi-aberto [cmin,cmax).
UGraph 
UGRAPHrandTree_c( int V, int cmin, int cmax);

// Constroi um grafo não-dirigido aleatório conexo com V vértices e E
// arestas. A função supõe que V-1 <= E <= V*(V-1).
UGraph 
UGRAPHrand1connected( int V, int E);

// Constroi um grafo não-dirigido aleatório conexo com V vértices e E
// arestas. Os custos das arestas são escolhidos aleatoriamente no
// intervalo semi-aberto [cmin,cmax). A função supõe que V-1 <= E <=
// V*(V-1).
UGraph 
UGRAPHrand1connected_c( int V, int E, int cmin, int cmax);

// Constrói um grafo completo com V vértices.
Graph 
GRAPHcomplete( int V);

// Constrói um torneio aleatório (as direções dos arcos são aleatórias)
// com V vértices.
Graph 
GRAPHrandTournament( int V);

// Constrói um grafo-caminho com V vértices.
Graph 
GRAPHrandPath( int V);

// Constrói um grafo-caminho não-dirigido com V vértices.
UGraph 
UGRAPHrandPath( int V);

// Constrói um grafo-ciclo com V >= 2 vértices.
Graph 
GRAPHrandCycle( int V);

// Constrói um grafo-circuito (não-dirigido) com V >= 3 vértices.
UGraph 
UGRAPHrandCircuit( int V);

// Constrói uma árvore radicada aleatória com V vértices.
Graph 
GRAPHrandRootedTree( int V);

// Constrói uma escada de Möbius com vértices 0..2n-1.
UGraph 
UGRAPHmoebius( int n);

// Constrói um cubo de dimensão n.
UGraph 
UGRAPHcube( int n);

// Constrói um grafo da dama (do jogo de xadrez) t-por-t.
UGraph 
UGRAPHchessQueen( int t);

// Constrói uma grade (dirigida) m-por-n. Quando percorremos a grade "da
// esquerda para a direita" e "de cima para baixo", a sequência de
// vértices é uma permutação aleatória de 0 1 ... m*n-1. Veja um exemplo
// 3-por-3 em que a permutação dos vértices é trivial:
//
//          0--1--2
//          |  |  |
//          3--4--5
//          |  |  |
//          6--7--8
//
// No caso de uma permutação trivial, os vértices são disposto assim:
//
//          0        1        2        3  ...        n-1
//          n      n+1      n+2      n+3  ...      n+n-1
//         2n     2n+1     2n+2     2n+3  ...     2n+n-1
//          .        .        .        .    .          .
//          .        .        .        .    .          .
//     (m-1)n (m-1)n+1 (m-1)n+2 (m-1)n+3  ... (m-1)n+n-1
//
// Todos os arcos são dirigidos "para a direita" e "para baixo". A
// função supõe que m*n < INT_MAX.
Graph 
GRAPHrandDiGrid( int n, int m);

// Constrói uma grade (dirigida) m-por-n em que as direções dos arcos
// são aleatórios: "para a direita" e "para baixo" com probabilidade 0.5
// e "para a esquerda" e "para cima" com probabilidade 0.5.
Graph 
GRAPHrandGrid( int n, int m);

// Constrói uma grade não-dirigida m-por-n.
UGraph 
UGRAPHrandGrid( int m, int n);

// Constrói um subgrafo gerador não-dirigido aleatório de uma grade
// não-dirigida m-por-n. Cada uma das arestas da grade deve ser incluída
// no subgrafo com probabilidade p, sendo p calculado de modo que o
// número esperado de arestas seja E. Supõe que E <= 2*m*n - m - n.
UGraph 
UGRAPHrandSubGrid( int m, int n, int E);



// Caminhos e ciclos em grafos
////////////////////////////////////////////////////////////////////////

// O comprimento de um caminho ou ciclo é o número de arcos do caminho. 

// A propósito, um número x é dito positivo de x >= 0 e negativo se
// x <= 0.



// Acessibilidade (caminho de um vértice a outro)
////////////////////////////////////////////////////////////////////////

// Recebe vértices s e t de um grafo G e decide se t está alcance de s
// (ou seja, se existe um caminho de s a t).
bool 
GRAPHreach( Graph G, vertex s, vertex t);

#define UGRAPHreach GRAPHreach

// Imprime (a sequência de vértices do) caminho de s a t armazenado no
// vetor de pais pa[0..G->V-1].
void 
GRAPHprintPath( Graph G, vertex s, vertex t, vertex *pa);



// Busca em profundidade (= depth-first search = DFS)
////////////////////////////////////////////////////////////////////////

// A função GRAPHdfs() faz uma busca em profundidade no grafo G, numera
// os vértices em pré-ordem e pós-ordem, e constrói a floresta DFS da
// busca. Os resultados são armazenados nos vetores pre[], post[] e pa[]
// respectivamente, todos indexados pelos vértices (e alocados pelo
// cliente da biblioteca). A numeração em pré- e pós-ordem e o vetor de
// pais são definidos assim:
//   - se x é o k-ésimo vértice descoberto então pre[x] = k,
//   - se x é o k-ésimo vértice a morrer então post[x] = k,
//   - se v é o pai de um vértice w na floresta DFS então pa[w] = v,
//   - se w é uma raiz da floresta então pa[w] = w.
void 
GRAPHdfs( Graph G, int *pre, int *post, vertex *pa);

// Esta função é uma versão iterativa (não-recursiva) de GRAPHdfs().
void 
GRAPHdfs_i( Graph G, int *pre, int *post, vertex *pa);



// Ciclos e dags
////////////////////////////////////////////////////////////////////////

// Um passeio (= walk) é uma sequência de vértices dotada da seguinte
// propriedade: se v e w são vértices consecutivos na sequência então
// v-w é um arco do grafo. Um passeio é fechado se tem pelo menos dois
// arcos e seu primeiro vértice coincide com o último. Um caminho
// (= path) é um passeio sem arcos repetidos. Um ciclo (= cycle) é um
// caminho fechado. 

// Decide se o grafo G tem ciclo.
bool 
GRAPHhasCycle( Graph G);

// Decide se o grafo G é um dag.
bool 
GRAPHisDag( Graph G);

// Recebe um grafo G e devolve um vértice z de um ciclo ou -1 se G é um
// dag. No primeiro caso, z pa[z] pa[pa[z]] ... z é o reverso de um
// ciclo. No segundo caso, post[] é uma numeração anti-topológica.
// (A função é uma extensão de GRAPHhasCycle().)
int 
GRAPHcycle( Graph G, int *post, vertex *pa);



// Componentes conexas (de grafos não-dirigidos)
////////////////////////////////////////////////////////////////////////

// Calcula as componentes conexas do grafo não-dirigido G. Devolve o
// número de componentes conexas de G e armazena no vetor cc[0..V-1]
// (alocado pelo cliente da biblioteca) uma numeração dos vértices tal
// que dois vértices v e w pertencem à mesma componente conexa se e
// somente se cc[v] == cc[w]. (O sufixo "cc" é uma abreviatura de
// "connected component".)
int
UGRAPHcc( UGraph G, int *cc);

// Decide se o grafo não-dirigido G é conexo.
bool 
UGRAPHisConnected( UGraph G);



// Distâncias, potencial, e relaxação
////////////////////////////////////////////////////////////////////////

// Esta função recebe um dag G com V vértices, uma permutação topológica
// vv[0..V-1] de G, e um vértice s de G. A função armazena em pa[] o
// vetor de pais de uma árvore de caminhos mínimos com raiz s. (Se um
// vértice v não está ao alcance de s, teremos pa[v] == -1.) As 
// distâncias (contadas em número de arcos) a partir de s são
// armazenadas no vetor dist[]. O espaço para os vetores pa[0..V-1] e
// dist[0..V-1] deve ser alocado pelo cliente.
void 
DAGshortestPaths( Dag G, vertex *vv, vertex s, vertex *pa, int *dist); 



// Busca em largura (= breadth-first search = BFS)
////////////////////////////////////////////////////////////////////////



// Algoritmo de caminhos mínimos
////////////////////////////////////////////////////////////////////////

// Esta função recebe um grafo G e um vértice s de G e armazena em
// pa[0..V-1] o vetor de pais de uma árvore de caminhos mínimos com raiz
// s. (Se um vértice v não está ao alcance de s, teremos pa[v] == -1 e
// dist[v] == G->V.) As distâncias a partir de s (contadas em número de
// arcos) são armazenadas no vetor dist[0..V-1]. O espaço para os
// vetores dist[] e pa[] deve ser alocado pelo cliente.
void 
GRAPHshortestPaths( Graph G, vertex s, int *dist, vertex *pa);



// Circuitos e florestas (não-radicadas)
////////////////////////////////////////////////////////////////////////

// Um circuito (= circuit) num grafo não-dirigido é um ciclo dotado da
// seguinte propriedade: se um arco v-w pertence ao ciclo então o arco
// antiparalelo w-v não pertence ao ciclo.

// Esta função decide se o grafo não-dirigido G tem um circuito. Em
// caso de resposta negativa, G é uma floresta.
bool 
UGRAPHhasCircuit( UGraph G);

// Recebe um grafo não-dirigido G e devolve um inteiro w. Se w == -1,
// o grafo é uma floresta, senão o grafo tem um circuito. No segundo
// caso, w é um vértice e w-p[w]-pa[pa[w]]-... é um circuito.
int 
UGRAPHcicuit( UGraph G, vertex *pa);

// Decide se o grafo não-dirigido G é uma floresta.
bool
UGRAPHisForest( UGraph G);

// Decide se o grafo não-dirigido G é uma árvore.
bool
UGRAPHisTree( UGraph G);



// Grafos aresta-biconexos (= edge-biconnected = eb)
////////////////////////////////////////////////////////////////////////

// Um grafo não-dirigido é aresta-biconexo se for conexo e não tiver
// pontes (ou seja, se cada uma de suas arestas estiver em um circuito).

// Decide se o grafo não-dirigido G é aresta-biconexo. (Implementa o
// algoritmo de Tarjan on-the-fly. O algoritmo é linear: consome V+E
// unidades de tempo. 
bool 
UGRAPHisEbc( UGraph G);



// Componentes aresta-biconexas (= edge-biconnected components = ebcc)
////////////////////////////////////////////////////////////////////////

// Esta função devolve o número (quantidade) de componentes aresta-
// biconexas do grafo não-dirigido G. Também atribui um rótulo ebcc[v] 
// (os rótulos são 0,1,2,...) a cada vértice v de G de modo que dois 
// vértices tenham o mesmo rótulo se e somente se os dois pertencem à 
// mesma componente aresta-biconexa. (A função é linear: consome tempo 
// proporcional ao tamanho do grafo. Implementa o algoritmo de Tarjan.)
int 
UGRAPHebcc( UGraph G, int *ebcc);



// Grafos fortemente conexos (= strongly connected)
////////////////////////////////////////////////////////////////////////

// Decide se o grafo G é fortemente conexo. (A função implementa o
// versão on-the-fly do algoritmo de Tarjan.)
bool 
GRAPHisStrong( Graph G); 



// Componentes fortes (= strong components = sc)
////////////////////////////////////////////////////////////////////////



// Algoritmo de Tarjan para componentes fortes
////////////////////////////////////////////////////////////////////////

// Esta função devolve o número (quantidade) de componentes fortes do
// grafo G. Também atribui um rótulo sc[v] a cada vértice v de G de modo
// que dois vértices tenham o mesmo rótulo se e somente se os dois
// pertencem à mesma componente forte. (Os rótulos pertencem ao
// intervalo 0..V-1, mas nem todo inteiro nesse intervalo é rótulo de
// alguma componente forte.) A função é linear: consume tempo
// proporcional a V+A.
int 
GRAPHscTarjan_v4( Graph G, int *sc);

// Versão default das funções de cálculo de componentes fortes.
#define GRAPHscTarjan GRAPHscTarjan_v4



// Algoritmo de Kosaraju para componentes fortes
////////////////////////////////////////////////////////////////////////

// Esta função devolve o número (quantidade) de componentes fortes do
// grafo G. Também atribui um rótulo sc[v] (os rótulos são 0,1,2,...) 
// a cada vértice v de G de modo que dois vértices tenham o mesmo 
// rótulo se e somente se os dois pertencem à mesma componente forte.  
// A função é linear: consome tempo proporcional a V+A.
int 
GRAPHscKosaraju( Graph G, int *sc);



// Coloração de vértices
////////////////////////////////////////////////////////////////////////

// Esta função decide se o grafo não-dirigido G admite k-coloração
// válida dos vértices. (Supõe k > 0.) Em caso afirmativo, armazena uma
// k-coloração no vetor color[0..V-1]. (Usa um algoritmo força-bruta de
// backtracking e portanto consome tempo exponencial.)
bool 
UGRAPHbruteColoring( UGraph G, int *color, int k);

// Esta função calcula uma coloração válida dos vértices do grafo não-
// dirigido G e devolve o número de cores efetivamente usadas. A
// coloração é armazenada no vetor color[]. A função procura usar poucas
// cores, mas em geral usa mais cores que o mínimo necessário. (A função
// implementa a heurística da "coloração sequencial".)
int 
UGRAPHseqColoring( UGraph G, int *color);



// Grafos bipartidos e circuitos ímpares
////////////////////////////////////////////////////////////////////////

// Decide se o grafo não-dirigido G admite bipartição. Em caso
// afirmativo, atribui uma "cor", 0 ou 1, a cada vértice de G de tal
// forma que toda aresta tenha pontas de cores diferentes. As cores dos
// vértices são armazenadas no vetor color[] indexado pelos vértices.
bool 
UGRAPHtwoColor( UGraph G, int *color);

// Recebe um grafo não-dirigido G e devolve true ou false. No primeiro
// caso, armazena uma bicoloração dos vértices de G (as duas cores são
// 0 e 1) no vetor color[0..V-1]. No segundo caso, armazena (a sequência
// de vértices de) um circuito ímpar no vetor oddc[0..k], sendo k >= 1 o
// menor índice tal que v[k] == v[0]. 
bool
UGRAPHtwoColorOrOddCircuit( UGraph G, int *color, int *oddc);



// Emparelhamentos (= matchings)
////////////////////////////////////////////////////////////////////////

// Um emparelhamento é representado por um vetor match[0..V-1] de
// vértices indexado por vértices. Se o emparelhamento casa um vértice v
// com um vértice w, temos match[v] == w e match[w] == v. Se v é
// solteiro (ou seja, não incide em aresta alguma do empaelhamento),
// então match[v] == -1. É claro que vale a seguinte propriedade: se
// match[v] != -1 então match[match[v]] == v.

// Um emparelhamento é máximo se não existe outro maior. Um
// emparelhamento M é maximal se não existe outro maior que contenha M.

// Calcula um emparelhamento maximal no grafo G. Armazena o
// emparelhamento no vetor match[] e devolve o tamanho do
// emparelhamento.
int 
UGRAPHmaximalMatching( UGraph G, vertex *match);

// Um caminho é alternante (= alternating) em relação a um
// emparelhamento M se for simples e se suas arestas estiverem
// alternadamente em M e fora de M.  Um caminho alternante é aumentador
// (= augmenting) se começa e termina num vértice solteiro e tem
// comprimento maior que 0. 



// Emparelhamentos em grafos bipartidos (= bipartite matching)
////////////////////////////////////////////////////////////////////////

// Esta função calcula um emparelhamento máximo M e uma cobertura mínima
// K no grafo não-dirigido bipartido G. A bipartição de G é dada pelo
// vetor color[0..V-1], que tem valores 0 e 1. A função devolve o
// tamanho comum de M e K. Também armazena uma representação de M no
// vetor match[0..V-1] e o vetor característico de K no vetor cover[].
// (A função usa busca BFS para procurar caminhos aumentadores. A função
// não está no livro de Sedgewick.) 
int 
UGRAPHbipMatch_bfs( UGraph G, int *color, vertex *match, bool *cover);

// (Função análoga a UGRAPHbipMatch_bfs(), mas usa busca DFS
// para procurar caminhos aumentadores.)
int 
UGRAPHbipMatch_dfs( UGraph G, int *color, vertex *match, bool *cover);

// Versão default da função de emparelhamento bipartido máximo e
// cobertura mínima.
#define UGRAPHbipMatch UGRAPHbipMatch_bfs



// Algoritmo de Prim para árvores geradoras de custo mínimo 
// (= MST = minimal spanning tree)
////////////////////////////////////////////////////////////////////////

// Recebe um grafo não-dirigido conexo G com custos arbitrários nas
// arestas e devolve o custo de uma MST de G. (Se G não for conexo,
// calcula uma MST da componente conexa de G que contém o vértice 0.)
// Também armazena no vetor pa[0..V-1], alocado pelo cliente, o vetor
// de pais que representa uma MST. Esta é uma implementação ingênua do
// algoritmo de Prim. A função é quadrática: consome V*E unidades de
// tempo no pior caso. 
int
UGRAPHmstP0( UGraph G, vertex *pa);

// Recebe um grafo não-dirigido conexo G com custos arbitrários nas
// arestas e devolve o custo de uma MST de G. (Se G não for conexo,
// calcula uma MST da componente conexa de G que contém o vértice 0.)
// Também armazena no vetor pa[0..V-1], alocado pelo cliente, o vetor
// de pais que representa uma MST. Esta é uma implementação eficiente do
// algoritmo de Prim apropriada para grafos densos. A função consome
// V^2 unidades de tempo no pior caso.
int
UGRAPHmstP1( UGraph G, vertex *pa);

// Recebe um grafo não-dirigido conexo G com custos arbitrários nas
// arestas e devolve o custo de uma MST de G. (Se G não for conexo,
// calcula uma MST da componente conexa de G que contém o vértice 0.)
// Também armazena no vetor pa[0..V-1], alocado pelo cliente, o vetor
// de pais que representa uma MST. Esta é uma implementação eficiente 
// do algoritmo de Prim apropriada para grafos esparsos. Consome
// E log V unidades de tempo no
// pior caso. O código é uma versão melhorada do Programa 21.1 de
// Sedgewick. 
int
UGRAPHmstP2( UGraph G, vertex *pa);

// Recebe um grafo não-dirigido conexo G com custos arbitrários nas
// arestas e devolve o custo de uma MST de G. (Se G não for conexo,
// calcula uma MST da componente conexa de G que contém o vértice 0.)
// Também armazena no vetor pa[0..V-1], alocado pelo cliente, o vetor
// de pais que representa uma MST. Esta é uma implementação eficiente
// do algoritmo de Prim apropriada para grafos esparsos. Consome
// E log V unidades de tempo no pior caso.
int
UGRAPHmstP3( UGraph G, vertex *pa);



// Algoritmo de Kruskal para árvores geradoras de custo mínimo 
// (= MST = minimal spanning tree)
////////////////////////////////////////////////////////////////////////

// Recebe um grafo não-dirigido conexo G com custos arbitrários nas
// arestas e devolve o custo de uma MST de G. Também armazena no vetor
// mst[0..V-2] (alocado pelo cliente) as arestas de uma MST. Esta é uma
// implementação ingênua do algoritmo de Kruskal. A função consome
// V*(E+V) unidades de tempo no pior caso.
int
UGRAPHmstK0( UGraph G, edge mst[]);

// Recebe um grafo não-dirigido conexo G com custos arbitrários nas
// arestas e devolve o custo de uma MST de G. Também armazena no vetor
// mst[0..V-2] (alocado pelo cliente) as arestas de uma MST. Esta é uma
// implementação eficiente do algoritmo de Kruskal. Consome
// V*(E+V) log^* V unidades de tempo no pior caso.
int
UGRAPHmstK1( UGraph G, edge mst[]);



// Distâncias e potenciais sob custos positivos (= SPT)
////////////////////////////////////////////////////////////////////////



// Caminhos de custo mínimo em dags (custos arbirários)
////////////////////////////////////////////////////////////////////////

// Esta função recebe um dag G com custos arbitrários nos arcos, uma
// permutação topológica vv[] de G, e um vértice s de G. A função
// armazena uma SPT com raiz s no vetor de pais pa[]. Se um vértice v
// não está ao alcance de s, teremos pa[v] == -1. As distâncias a partir
// de s são armazenadas no vetor dist[]. Os vetores pa[0..V-1] e
// dist[0..V-1] devem ser alocados pelo cliente.
void 
DAGspt( Dag G, vertex *vv, vertex s, vertex *pa, int *dist);



// Algoritmo de Dijkstra para caminhos mínimos sob custos positivos
////////////////////////////////////////////////////////////////////////

// Recebe um grafo G com custos positivos nos arcos e um vértice s.
// Armazena uma SPT de G com raiz s no vetor de pais pa[]. Se um vértice
// v não estiver ao alcance de s, pa[v] valerá -1. As distâncias a
// partir de s são armazenadas no vetor dist[]. Os vetores pa[] e dist[]
// devem ser alocados pelo cliente. Esta é uma implementação ingênua do
// algoritmo de Dijkstra. Ela consome V*A unidades de tempo.
void 
GRAPHsptD0( Graph G, vertex s, vertex *pa, int *dist);

// Recebe um grafo G com custos positivos nos arcos e um vértice s.
// Armazena uma SPT de G com raiz s no vetor de pais pa[]. Se um vértice
// v não estiver ao alcance de s, pa[v] valerá -1. As distâncias a
// partir de s são armazenadas no vetor dist[]. Os vetores pa[] e dist[]
// devem ser alocados pelo cliente. Esta é uma implementação do
// algoritmo de Dijkstra. Ela consome V^2 unidades de tempo.
void 
GRAPHsptD1( Graph G, vertex s, vertex *pa, int *dist);

// Recebe um grafo G com custos positivos nos arcos e um vértice s.
// Armazena uma SPT de G com raiz s no vetor de pais pa[]. Se um vértice
// v não estiver ao alcance de s, pa[v] valerá -1. As distâncias a
// partir de s são armazenadas no vetor dist[]. Os vetores pa[] e dist[]
// devem ser alocados pelo cliente. Esta é uma implementação do
// algoritmo de Dijkstra. Ela consome A log V unidades de tempo.
void 
GRAPHsptD2( Graph G, vertex s, vertex *pa, int *dist);

// Recebe um grafo G com custos positivos nos arcos e um vértice s.
// Armazena uma SPT de G com raiz s no vetor de pais pa[]. Se um vértice
// v não estiver ao alcance de s, pa[v] valerá -1. As distâncias a
// partir de s são armazenadas no vetor dist[]. Os vetores pa[] e dist[]
// devem ser alocados pelo cliente. Esta é uma implementação do
// algoritmo de Dijkstra. Ela consome A log V unidades de tempo.
void 
GRAPHsptD3( Graph G, vertex s, vertex *pa, int *dist);

// Implementação default do algoritmo de Dijkstra.
#define GRAPHsptD GRAPHsptD2



// Caminhos de comprimento máximo e de custo máximo
////////////////////////////////////////////////////////////////////////

// Recebe um grafo G e vértices s e t. Devolve o comprimento de um
// caminho simples de comprimento máximo de s a t. (Em particular,
// devolve 0 se s == t.) Se não existe caminho algum de s a t, devolve
// -1 (que representa infinito negativo). Cuidado! Esta função só é
// razoável para grafos MUITO PEQUENOS.
int 
GRAPHmaxSimplePath( Graph G, vertex s, vertex t);

// Recebe um grafo G com custos positivos nos arcos e vértices s e t. 
// Devolve o custo de um caminho simples de custo máximo de s a t. (Em
// particular, devolve 0 se s == t.) Se não existe caminho algum de s a
// t, devolve -1 (que representa infinito negativo). Cuidado! Esta
// função só é razoável para grafos MUITO PEQUENOS.
int 
GRAPHmaxSimplePath_c( Graph G, vertex s, vertex t);



// Fluxo máximo
////////////////////////////////////////////////////////////////////////


#endif

