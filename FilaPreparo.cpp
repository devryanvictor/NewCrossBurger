#include "FilaPreparo.hpp"
#include <iostream>

FilaPreparo::FilaPreparo() {
    frente = nullptr;
    tras = nullptr;
    tamanho = 0;
}

void FilaPreparo::enfileirar(Pedido pedido) {
    NoFila* novoNo = new NoFila(pedido);
    if (estaVazia()) {
        frente = novoNo;
        tras = novoNo;
    } else {
        tras->proximo = novoNo;
        tras = novoNo;
    }
    tamanho++;
}

Pedido FilaPreparo::desenfileirar() {
    NoFila* noRemovido = frente;
    Pedido pedidoRemovido = noRemovido->dado;

    frente = frente->proximo;

    if (frente == nullptr) {
        tras = nullptr;
    }

    delete noRemovido;
    tamanho--;
    return pedidoRemovido;
}

bool FilaPreparo::estaVazia() {
    return frente == nullptr;
}

Pedido* FilaPreparo::peek() {
    if (estaVazia()) {
        std::cout << "A fila está vazia. Não há elemento na frente." << std::endl;
        return nullptr;
    }
    return &(frente->dado);
}

int FilaPreparo::getTamanho() {
    return tamanho;
}

void FilaPreparo::limpar() {
    NoFila* atual = frente;

    while (atual != nullptr) {
        NoFila* proximoNo = atual->proximo;
        delete atual;
        atual = proximoNo;
    }

    frente = nullptr;
    tras = nullptr;
    tamanho = 0;
}

FilaPreparo::~FilaPreparo() {
    limpar();
}