#include "NoPilhaPedido.hpp"

NoPilhaPedido::NoPilhaPedido(Pedido pedido) {
    dado = pedido;
    proximo = nullptr;
}
