#ifndef NOLISTA_HPP
#define NOLISTA_HPP

#include "Pedido.hpp"

class NoLista {
public:
    Pedido dado;
    NoLista* anterior;
    NoLista* proximo;

    NoLista(Pedido pedido);
};

#endif