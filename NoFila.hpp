#ifndef NOFILA_HPP
#define NOFILA_HPP

#include "Pedido.hpp"

class NoFila {
public:
    Pedido dado;
    NoFila* proximo;

    NoFila(Pedido pedido);
};

#endif