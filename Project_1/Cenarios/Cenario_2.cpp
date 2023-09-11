//
// Created by inessilva_132 on 15/04/22.
//

#include <iostream>
#include "cenarios.h"

bool rec_Compare(struct Encomenda e1, struct Encomenda e2){
    return ((e1.recompensa/(e1.volume+e1.peso)) > (e2.recompensa/(e2.volume+e2.peso)));
}
bool custo_Compare(struct Estafeta e1, struct Estafeta e2){
    return (e1.custo < e2.custo);
}
int maximizar_lucro (std::vector<struct Encomenda> enc, std::vector<struct Estafeta> est){

    int lucro = 0;
    int lucro_enc = 0;
    int maxlucro = 0;
    int j=0;
    int pesototal = 0;
    int volTotal = 0;

    for (int i = 0; i < est.size(); i++) {

        while (est.at(i).volMax >= 0 && est.at(i).pesoMax >= 0 && j < enc.size()) {

            if (enc.at(j).volume <= est.at(i).volMax && enc.at(j).peso <= est.at(i).pesoMax) {

                est.at(i).volMax -= enc.at(j).volume;
                est.at(i).pesoMax -= enc.at(j).peso;
                lucro_enc += enc.at(j).recompensa;

            } else if (enc.at(j).volume > est.at(i).volMax || enc.at(j).peso > est.at(i).pesoMax) {
                est.at(i).used = false;

                break;
            }

            j++;

        }

        lucro += lucro_enc - est.at(i).custo;
        if (lucro < 0) {
            lucro = 0;
            maxlucro = maxlucro;
        }
        else {

            maxlucro += lucro;
        }
        lucro_enc = 0;

            lucro = 0;

    }

    return maxlucro;

}
