#include "FilaPreparo.hpp"
#include <iostream>

FilaPreparo::FilaPreparo() {
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

void FilaPreparo::enfileirar(Pedido pedido) {
    NoFila* novoNo = new NoFila(pedido);
    if (estaVazia()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}

Pedido FilaPreparo::desenfileirar() {
    if (estaVazia()) {
        std::cout << "A fila esta vazia. Nao e possivel desenfileirar." << std::endl;
        return Pedido(); // Retorna um pedido vazio
    }

    NoFila* noRemovido = inicio;
    Pedido pedidoRemovido = noRemovido->dado;

    inicio = inicio->proximo;

    if (inicio == nullptr) {
        fim = nullptr;
    }

    delete noRemovido;
    tamanho--;
    return pedidoRemovido;
}

bool FilaPreparo::estaVazia() {
    return inicio == nullptr;
}

Pedido* FilaPreparo::peek() {
    if (estaVazia()) {
        std::cout << "A fila esta vazia. Nao ha elemento na frente." << std::endl;
        return nullptr;
    }
    return &(inicio->dado);
}

int FilaPreparo::getTamanho() {
    return tamanho;
}

void FilaPreparo::limpar() {
    NoFila* atual = inicio;

    while (atual != nullptr) {
        NoFila* proximoNo = atual->proximo;
        delete atual;
        atual = proximoNo;
    }

    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

FilaPreparo::~FilaPreparo() {
    limpar();
}
