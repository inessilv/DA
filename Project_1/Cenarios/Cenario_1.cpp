//
// Created by inessilva_132 on 15/04/22.
//
#include "cenarios.h"

bool volCompare(struct Encomenda e1, struct Encomenda e2){
    return (e1.peso+e1.volume > e2.peso+e2.volume);
}

bool vol_MaxCompare(struct Estafeta e1, struct Estafeta e2){
    return (e1.pesoMax+e1.volMax > e2.pesoMax+e2.volMax);

}

int encontrar_min_estafetas (std::vector<struct Encomenda> enc, std::vector<struct Estafeta> est) {

    int j = 0;
    int cont = 0;
    for (int i = 0; i < est.size(); i++) {

        while (est.at(i).volMax >= 0 && est.at(i).pesoMax >= 0 && j < enc.size()) {

            if (enc.at(j).volume <= est.at(i).volMax && enc.at(j).peso <= est.at(i).pesoMax) {
                est.at(i).volMax -= enc.at(j).volume;
                est.at(i).pesoMax -= enc.at(j).peso;
            } else if (enc.at(j).volume > est.at(i).volMax || enc.at(j).peso > est.at(i).pesoMax) {
                est.at(i).used = false;
                cont++;
                break;
            }

            j++;
        }
    }

    return cont;
}








