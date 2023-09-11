#include <iostream>
#include <limits>
#include <fstream>
#include "Graph.h"
#include "Graph.cpp"

using namespace std;


int main(int argc, char *argv[]) {

    ifstream file_tests(argv[1]);
    if (!file_tests.is_open()) {
        cerr << "Could not open the file - 'tests.txt' " << endl;
        return EXIT_FAILURE;
    }
    int num, t;
    file_tests >> num;
    file_tests >> t;

    Graph graph(num);
    while (!file_tests.eof()) {
        int start_ver, end_ver, cap, dur;

        file_tests >> start_ver;
        file_tests >> end_ver;
        file_tests >> cap;
        file_tests >> dur;
        graph.addEdge(start_ver, end_ver, cap, dur);

    }
    cout << "Selecione se pretende que o grupo se separe ou permaceça junto:" << endl;
    cout << " - 1 : Grupos não se separam " << endl;
    cout << " - 2 : Grupos podem separar-se " << endl;

    int type;
    cin >> type;

    cout << "Selecione o cénário que pretende testar:" << endl;
    cout << " - 1.1 : Grupos não se separam : Maximizar a dimensão do grupo " << endl;
    cout << " - 1.2 : Grupos não se separam : Maximizar a dimensão do grupo e minimizar o nº de transbordos " << endl;
    cout << " - 2.1 : Grupos podem separar-se : Determinar um encaminhamento para o grupo dada a sua dimensão " << endl;
    cout << " - 2.2 : Grupos podem separar-se : Corrigir um encaminhamento " << endl;
    cout << " - 2.3 : Grupos podem separar-se : Determinar a dimensão máxima do grupo e um encaminhamento" << endl;
    cout << " - 2.4 : Grupos podem separar-se : Determinar quando é que um grupo se reuniria novamente no destino"
         << endl;

    int ex;
    cin >> ex;

    if (type == 1) {
        int start, end;
        cin >> start >> end;
        if (ex == 1) {
            graph.cenario_1_1(start, end);
        } else if (ex == 2) {
            graph.cenario_1_2(start, end);
        }

    } else if (type == 2) {
        int s, e;
        cin >> s >> e;
        int dim;
        if (ex == 1) {
            cin >> dim;
            graph.cenario_2_1( s, e, dim);
        } else if (ex == 2) {
            cin >> dim;
            graph.cenario_2_2( s, e, dim);
        } else if (ex == 3) {
            graph.cenario_2_3( s, e);
        } else if (ex == 4) {
            graph.cenario_2_4(s, e);
        }

    }
    return 0;
}