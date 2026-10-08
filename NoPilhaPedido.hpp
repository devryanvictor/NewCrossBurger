#ifndef NOPILHAPEDIDO_HPP
#define NOPILHAPEDIDO_HPP

#include "Pedido.hpp"

class NoPilhaPedido {
public:
    Pedido dado;
    NoPilhaPedido* proximo;

    NoPilhaPedido(Pedido pedido);
};

#endif
