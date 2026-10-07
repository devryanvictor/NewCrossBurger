#include "NoFila.hpp"
#include <iostream>

NoFila::NoFila(Pedido pedido) {
    dado = pedido;
    proximo = nullptr;
}