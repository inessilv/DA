#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Cenarios/cenarios.h"
#include "Cenarios/Cenario_1.cpp"
#include "Cenarios/Cenario_2.cpp"
#include "Cenarios/Cenario_3.cpp"


using namespace std;
int main(int argc, char *argv[]) {
    vector<struct Estafeta> estafetas;
    vector<struct Encomenda> encomendas;

    if (argc == 2 || argc == 3) {
        ifstream file_encomendas(argv[1]);
        if (!file_encomendas.is_open()) {
            cerr << "Could not open the file - 'encomendas.txt' " << endl;
            return EXIT_FAILURE;
        }
        while (!file_encomendas.eof()) {
            struct Encomenda encomenda;
            file_encomendas >> encomenda.volume;
            file_encomendas >> encomenda.peso;
            file_encomendas >> encomenda.recompensa;
            file_encomendas >> encomenda.duracao;
            encomendas.push_back(encomenda);
        }

        ifstream file_estafetas(argv[2]);
        if (!file_estafetas.is_open()) {
            cerr << "Could not open the file - 'carrinhas.txt' " << endl;
            return EXIT_FAILURE;
        }

        while (!file_estafetas.eof()) {
            struct Estafeta estafeta;
            file_estafetas >> estafeta.volMax;
            file_estafetas >> estafeta.pesoMax;
            file_estafetas >> estafeta.custo;
            estafetas.push_back(estafeta);
        }
    }
    int n;

    cout << "Selecione o cenário que pretende testar - 1/2/3" << endl;
    cin >> n;


    if(n == 1){
        sort(encomendas.begin(), encomendas.end(), volCompare);
        sort(estafetas.begin(), estafetas.end(), vol_MaxCompare);
        std::cout << encontrar_min_estafetas(encomendas,estafetas) << std::endl;
    }
    else if(n == 2){
        sort(encomendas.begin(), encomendas.end(), rec_Compare);
        sort(estafetas.begin(), estafetas.end(), custo_Compare);
        std::cout << maximizar_lucro(encomendas,estafetas) << std::endl;
    }
    else if( n == 3){
        sort(encomendas.begin(),encomendas.end(),dur_Compare);
        std::cout << min_media_duracao(encomendas) << std::endl;
    }

    return 0;

}
