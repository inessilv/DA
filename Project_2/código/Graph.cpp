//
// Created by inessilva_132 on 05/06/22.
//

#include "Graph.h"
#include <climits>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <iostream>

#define INF 2147483647

using namespace  std;

Graph::Graph(int V) : num_ver(V), hasDir(true), nodes(V+1) {
num_ver = V;
hasDir = true;

}
void Graph::addEdge(int start, int dest,int cap, int dur){
    nodes[start].adj.push_back({dest,cap,dur});
    /*t_graph[dest].adj.push_back({start,cap,dur});*/
}


vector<Graph::Node> Graph::getNodes() {
    return nodes;
}


Graph Graph::transposed_graph(Graph &g){
    Graph t_graph(num_ver);

    for(int v = 1; v <= num_ver; v++){
        for(auto &itr : nodes[v].adj){
        t_graph.addEdge(itr.dest,v,itr.capacity,itr.dur);
            // insere no novo grafo
        }
    }
    return t_graph;
}
void Graph::max_cap_Dijkstra(int start){
    for (int i = 1;i<=num_ver;i++){
        nodes[i].parent = -1;
        nodes[i].m_cap = 0;
    }

    priority_queue<pair<int,Node>, std::vector<pair<int,Node>>, node_cmp> q;
    nodes[start].m_cap = INF;
    q.push({start,nodes[start]});

    while(!q.empty()) {
        pair<int, Node> temp = q.top();
        int ind = temp.first;
        Node v = temp.second;
        q.pop();
        for (auto itr = v.adj.begin(); itr != v.adj.end(); itr++) {
            if ((min(v.m_cap, itr->capacity)) > nodes[itr->dest].m_cap) {
                nodes[itr->dest].m_cap = min(v.m_cap, itr->capacity);
                nodes[itr->dest].parent = ind;
                q.push ({itr->dest, nodes[itr->dest]});

            }
        }
    }
}
 pair<int, vector<int>> Graph::bfs(int start,int end) {
    for (int i = 0; i < num_ver; i++) {
        nodes[i].visited = false;
        nodes[i].parent = -1;
    }
    queue<int> q;
    q.push(start);
    nodes[start].visited = true;
    nodes[start].parent = start;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto &edge: nodes[v].adj) {
            int w = edge.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].parent = v;
            }
        }
    }

    int stop = end;
    vector<int> ve;
    int cap = INF;
    while (stop != start) {
        ve.push_back(stop);
        for (auto &x: nodes[nodes[stop].parent].adj) {
            if (x.dest == stop)
                cap = min(cap, x.capacity);
        }
        stop = nodes[stop].parent;
    }
    ve.push_back(start);
    reverse(ve.begin(), ve.end());
    pair<int, vector<int>> res;
    res.first = cap;
    res.second = ve;

    return res;
}

vector<int> Graph::maximizeGroupSize(int start,int end) {
    max_cap_Dijkstra(start);
    int i = end;
    vector<int> path;
    path.push_back(end);
    while(i != start) {
        path.push_back(getNodes()[i].parent);
        i = getNodes()[i].parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

int Graph::bfs_maxflow(int start, int end, vector<vector<int>> flowPassed){
    queue<int> q;
    q.push(start);
    int n=1;

    while( n <= num_ver){
        nodes[n].parent = -1;
        nodes[n].path_flow = 0;
        n++;
    }
    nodes[start].parent = -2;
    nodes[start].path_flow = INF;

    while(!q.empty()){
        int v = q.front();
        q.pop();
        for (auto edge: nodes[v].adj){
            int w = edge.dest;
            if(nodes[w].parent == -1){
                if(edge.capacity - flowPassed[v][w] > 0){
                    nodes[w].parent = v;
                    nodes[w].path_flow = min(nodes[v].path_flow, edge.capacity - flowPassed[v][w]);
                    if(w == end) return nodes[w].path_flow;
                    q.push(w);
                }
            }
        }
    }
    return 0;
}

multimap<int, vector<int>> Graph::maxFlow(int start, int end) {
    int tam = num_ver + 1;
    vector<vector<int>> flowPassed(tam, vector<int>(tam,0));
    multimap<int, vector<int>> reso;
    int maxFlow = 0;
    while(true) {
        list<int> cam; //path
        int flow = bfs_maxflow(start, end,flowPassed);
        if (flow == 0) {
            break;
        }
        int v = end;
        cam.push_back(v);
        maxFlow += flow;

        while(v != start){
            int w = nodes[v].parent;
            flowPassed[w][v] += flow;  //symetric flow f(v,w) = - f(w,v)
            flowPassed[v][w] -= flow;
            v = w;
            cam.push_back(v);
        }
        reverse(cam.begin(), cam.end());
        pair<int, vector<int>> aux;
        aux.first = flow;
        for (auto &x:cam)
            aux.second.push_back(x);
        reso.insert(aux);
    }
    return reso;
}



int Graph::min_dur(int start, int end) {
    int n = 1;
    while (n <= num_ver) {
        nodes[n].E_G = 0;
        nodes[n].parent = -1;
        nodes[n].eStrt = 0;
        for (auto &itr : nodes[n].adj) {
            nodes[itr.dest].E_G++;
        }
        n++;
    }
    queue<int> l;
    for (int j = 1; j <= num_ver; j++) {
        if (nodes[j].E_G == 0) l.push(j);
    }
    int min_dur = -1;
    int node;
    while (!l.empty()) {
        int tmp = l.front();
        l.pop();
        if (min_dur <nodes[tmp].eStrt ) {
            min_dur = nodes[tmp].eStrt;
            node = tmp;
        }

        for (auto &it: nodes[tmp].adj) {
            if (it.dur + nodes[tmp].eStrt > nodes[it.dest].eStrt  ) {
                nodes[it.dest].parent = tmp;
                nodes[it.dest].eStrt = it.dur + nodes[tmp].eStrt;
            }
            nodes[it.dest].E_G--;
            if (nodes[it.dest].E_G == 0) {
                l.push(it.dest);
            }
        }
    }
    return nodes[end].eStrt - nodes[start].eStrt;

}

int Graph::path_max_flow_dimension_given(int start,int end,int dim) {
    int maxFl= 0;
    multimap<int, vector<int>> res = maxFlow(start, end);
    for (const auto& it : res){
        maxFl += it.first;
    }
    if (dim > maxFl) {
        cout << "Group dimension (" << dim
             << ") the total capacity is greater than all the possible trips from the start to that end ("
             << maxFl << ")"
             << endl;
        return EXIT_SUCCESS;
    }
    int number = 1;
    if(dim == maxFl){
        cout << "The group should be divided by their following trips:" << endl;
        for (const auto& it : res){
            cout << "Path " << number << ": ";
            for (auto &x: it.second){
                cout << x << " , ";
            }
            cout <<" with capacity " << it.first << endl;
            number++;
        }
        cout << endl;
        return EXIT_SUCCESS;
    }
    else{
        int aux = dim;
        vector<int> final;
        while (aux > 0) {
            int max = INT_MIN;
            for (auto &x: res){
                if (x.first > max){
                    max = x.first;
                    final = x.second;
                }
            }
            map<int, vector<int>>::iterator it;
            for (it = res.begin(); it != res.end(); it++){
                if (it->second == final)
                    break;
            }
            res.erase(it);

            if (aux <= max){
                cout << aux << " elements of the group should attend the trip: " << endl;
                for (auto &x: final){
                    cout << x << " , ";
                }
                cout << "with capacity " << max << endl;
                return max - aux;
            }
            else {
                cout << max << " elements of the group should attend the trip: " << endl;
                for (auto &x: final) {
                    cout << x << " , ";
                }
                cout << "with capacity " << max << endl;
            }
            aux -= max;
        }
    }
    return 0;
}


void Graph::cenario_1_1(int start,int end){
    vector<int> path = maximizeGroupSize(start,end);
    for(auto &it : path) {
        cout << it << " -> ";
    }
    cout << "The maximum capacity of this path is " << getNodes()[end].m_cap << endl;
}

void Graph::cenario_1_2(int start,int end){
    vector<int> pathMaxSize = maximizeGroupSize(start,end);
    cout << "Path maximum capacity : ";
    for(auto &it : pathMaxSize) {
        cout << it << " , ";
    }
    cout << "Capacity: " << getNodes()[end].m_cap << endl;

    vector<int> pathmin = bfs(start, end).second;
    cout << "Path minimum overflow : ";
    for(auto &it : pathmin) {
        cout << it << " , ";
    }
    cout << "Capacity: " << bfs(start, end).first << endl;
}

void Graph::cenario_2_1(int start,int end,int dim){
    path_max_flow_dimension_given(start, end, dim);
}
void Graph::cenario_2_2(int start,int end,int dim){
    cout << "Este/s é/são o/os caminho/s adequado/s para essa dimensão do grupo: " << endl << endl;
    int r = path_max_flow_dimension_given(start, end,dim);

    cout << "Insira agora a nova dimensão do grupo, de modo a corrigir o/os encaminhamento/s anterior/s: " << endl << endl;
    int old_dim = dim;
    int n_dim;
    cin >> n_dim;

    if (n_dim - old_dim <= r)
    {
        cout << "Com a nova dimensão de grupo, não é necessário alterar o encaminhamento porque as "
             << n_dim - old_dim
             << " pessoas novas conseguem entrar na última viagem listada que tem como espaço restante "
             << r << "." << endl;
    }
    else{
        path_max_flow_dimension_given(start, end,n_dim);
    }

}

void Graph::cenario_2_3(int start,int end){
    int max = 0;
    multimap<int, vector<int>> resultado = maxFlow(start,end);
    for (const auto& it : resultado){
        max += it.first;
    }
    cout << "Dimensão máxima : " << max<< endl;
    int d = max;
    path_max_flow_dimension_given(start, end,d);
}

void Graph::cenario_2_4 ( int start, int end) {
    int t = min_dur(start, end);
    cout << "O grupo reunir-se-à no destino após " << t << " horas" << endl;
}

