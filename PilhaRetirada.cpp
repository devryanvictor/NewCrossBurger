#include "PilhaRetirada.hpp"
#include <iostream>

PilhaRetirada::PilhaRetirada() {
    topo = nullptr;
    tamanho = 0;
}

void PilhaRetirada::empilhar(Pedido pedido) {
    NoPilhaPedido* novoNo = new NoPilhaPedido(pedido);
    novoNo->proximo = topo;
    topo = novoNo;
    tamanho++;
}

Pedido PilhaRetirada::desempilhar() {
    if (estaVazia()) {
        std::cout << "A pilha de retirada esta vazia. Nao é possivel desempilhar." << std::endl;
        return Pedido(); // Retorna um pedido vazio
    }
    NoPilhaPedido* noRemovido = topo;
    Pedido pedidoRemovido = noRemovido->dado;
    topo = topo->proximo;
    delete noRemovido;
    tamanho--;
    return pedidoRemovido;
}

bool PilhaRetirada::estaVazia() {
    return topo == nullptr;
}

Pedido* PilhaRetirada::peek() {
    if (
        estaVazia()) {

        std::cout << "A pilha de retirada esta vazia. Nao ha elemento no topo." << std::endl;
        return nullptr;
    }
    return &(topo->dado);
}

int PilhaRetirada::getTamanho() {
    return tamanho;
}

void PilhaRetirada::limpar() {
    NoPilhaPedido* atual = topo;

    while (atual != nullptr) {
        NoPilhaPedido* proximoNo = atual->proximo;
        delete atual;
        atual = proximoNo;
    }

    topo = nullptr;
    tamanho = 0;
}

PilhaRetirada::~PilhaRetirada() {
    limpar();
}
