#include "NoLista.hpp"
#include <iostream>

NoLista::NoLista(Pedido pedido) {
    dado = pedido;
    anterior = nullptr;
    proximo = nullptr;
}