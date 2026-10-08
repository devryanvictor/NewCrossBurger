#ifndef PILHARETIRADA_HPP
#define PILHARETIRADA_HPP

#include "NoPilhaPedido.hpp"

class PilhaRetirada {
private:
    NoPilhaPedido* topo;
    int tamanho;

public:
    PilhaRetirada();
    ~PilhaRetirada();

    void empilhar(Pedido pedido);
    Pedido desempilhar();

    bool estaVazia();
    Pedido* peek();

    int getTamanho();

    void limpar();
};

#endif
