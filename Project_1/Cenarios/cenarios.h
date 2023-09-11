//
// Created by inessilva_132 on 15/04/22.
//

#ifndef DA_T1_CENARIOS_H
#define DA_T1_CENARIOS_H


#include <vector>
//!Struct para guardar dados informações relacionadas com o estafeta.
struct Estafeta {
    //! Volume máximo.
    int volMax;
    //! Peso máximo.
    int pesoMax;
    //! Custo.
    int custo;
    //! Bool para indicar se o estafeta foi utilizado.
    bool used;
};
//!Struct para guardar dados informações relacionadas com as encomendas.
struct Encomenda {
    //! Volume.
    int volume;
    //! Peso.
    int peso;
    //! Recompensa.
    int recompensa;
    //! Duração da entrega.
    int duracao;
    //! Inteiro identificador do estafeta a que a encomenda ficou associada.
    int estaf;
};
// funções para encomendas

//! Compara os volumes das encomendas.
//! @param e1 Encomenda .
//! @param e2 Encomenda.
//! @return Retorna um Bool que indica se o parâmetro da esquerda é menor do que o da direita em termos de volume.
 bool volCompare(struct Encomenda e1, struct Encomenda e2);
//! Compara as durações das encomendas.
//! @param e1 Encomenda .
//! @param e2 Encomenda.
//! @return Retorna um Bool que indica se o parâmetro da esquerda é menor do que o da direita em termos de duração.
bool dur_Compare(struct Encomenda e1 ,struct Encomenda e2);
//! Compara os valores das recompensas das encomendas.
//! @param e1 Encomenda .
//! @param e2 Encomenda.
//! @return Retorna um Bool que indica se a recompensa relacionada com o parâmetro da esquerda é menor do que a da direita.
bool rec_Compare(struct Encomenda e1, struct Encomenda e2);

//funções para estafetas
//! Compara a capacidade máxima de tranporte de cada estafeta em termos de volume.
//! @param e1 Estafeta .
//! @param e2 Estafeta.
//! @return Retorna um Bool que indica se o volume máximo do estafeta 1 é menor que o volume máximo do estafeta 2.
bool vol_MaxCompare(struct Estafeta e1, struct Estafeta e2);
//! Compara o custo de cada estafeta no transporte de cada encomenda.
//! @param e1 Estafeta .
//! @param e2 Estafeta.
//! @return Retorna um Bool que indica se o custo do estafeta 1 é menor que o custo do estafeta 2.
bool custo_Compare(struct Estafeta e1, struct Estafeta e2);

//Cenário 1(0-1 Knapsack - Greedy)
//! Encontra  o número mínimo de estafetas necessários para serem realizadas todas as entregas.
//! @param enc Vetor com todas as encomendas a entregar .
//! @param est Vetor com todos os estafetas disponíveis.
//! @return Retorna o número mínimo de estafetas.
int encontrar_min_estafetas (std::vector<struct Encomenda> enc, std::vector<struct Estafeta> est);

//Cenário 2
//! Maximiza o lucro da empresa.
//! @param enc Vetor com todas as encomendas a entregar .
//! @param est Vetor com todos os estafetas disponíveis.
//! @return Retorna um inteiro que indica o lucro máximo.
int maximizar_lucro (std::vector<struct Encomenda> enc, std::vector<struct Estafeta> est);

//Cenário 3(Job Scheduling)
//! Obtém a duração média mínima possível para na entrega de encomendas.
//! @param enc Vetor com todas as encomendas a entregar .
//! @return Retorna um inteiro que representa a mínima duração media que se pode obter.
int min_media_duracao(std::vector<struct Encomenda> enc);

#endif //DA_T1_CENARIOS_H
