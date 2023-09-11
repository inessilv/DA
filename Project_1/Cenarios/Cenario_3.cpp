//
// Created by inessilva_132 on 15/04/22.
//

#include "cenarios.h"
bool dur_Compare(struct Encomenda e1 ,struct Encomenda e2){
    return (e1.duracao < e2.duracao);

}
int min_media_duracao(std::vector<struct Encomenda> enc) {
    int num = 0;
    int duracao = 0;
    int limite = 28800;
    int i=0;
    int duracao2 = 0;

    while (duracao < limite && i<enc.size()) {
        if(duracao + enc.at(i).duracao > limite)break;
        duracao += enc.at(i).duracao;
        duracao2 += duracao;
        num++;
        i++;
    }
    return (double)duracao2/num;
}

