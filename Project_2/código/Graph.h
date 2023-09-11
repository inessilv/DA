//
// Created by inessilva_132 on 05/06/22.
//

#ifndef TP_2_GRAPH_H
#define TP_2_GRAPH_H
#include <limits>
#include <list>
#include <vector>
#include <functional>
#include "map"

using namespace std;
class Graph {
    int num_ver;

    // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed

    struct Edge {
        int dest;   // Destination node
        int capacity;
        int dur;
        bool changes;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;// As the node been visited on a search
        int m_cap;
        int parent;
        int path_flow;
        int eStrt;
        int lFih;
        int E_G; // grau de entrada
        int S_G; // grau de saída

    };
    vector<Node> nodes;
    struct node_cmp : public ::binary_function<pair<int,Node>,pair<int,Node> , bool> {
        bool operator()(pair<int,Node> &a, pair<int,Node> &b) {
            return a.second.m_cap < b.second.m_cap;
        }
    };

    /* vector<Node> t_graph;*/
public:

    Graph(int V);
    pair<int, vector<int>> bfs(int start,int end);
    void addEdge(int src, int dest, int cap, int dur);
    vector<Node> getNodes();
    Graph transposed_graph(Graph &g);
    void max_cap_Dijkstra(int start);
    int path_max_flow_dimension_given(int start, int end, int dimension);
    multimap<int, vector<int>> maxFlow(int start, int end);
    int bfs_maxflow(int start, int end, vector<vector<int>> flowPassed);
    vector<int> maximizeGroupSize(int start, int end);
    int min_dur(int start, int end);
    void cenario_1_1(int start,int end);
    void cenario_1_2(int start,int end);
    void cenario_2_1(int start,int end,int dim);
    void cenario_2_2(int start,int end,int dim);
    void cenario_2_3(int start,int end);
    void cenario_2_4(int start,int end );

};
#endif //TP_2_GRAPH_H
