#include "ListaHistoricoPedidos.hpp"
#include <iostream>

ListaHistoricoPedidos::ListaHistoricoPedidos() {
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

void ListaHistoricoPedidos::inserirInicio(Pedido pedido) {
    NoLista* novoNo = new NoLista(pedido);
    if (estaVazia()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        NoLista* antigoInicio = inicio;
        antigoInicio->anterior = novoNo;
        novoNo->proximo = antigoInicio;
        inicio = novoNo;
    }
    tamanho++;
}

void ListaHistoricoPedidos::inserirFim(Pedido pedido) {
    NoLista* novoNo = new NoLista(pedido);
    if (estaVazia()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        NoLista* antigoFim = fim;
        antigoFim->proximo = novoNo;
        novoNo->anterior = antigoFim;
        fim = novoNo;
    }
    tamanho++;
}

bool ListaHistoricoPedidos::inserirPosicao(Pedido pedido, int posicao) {
    if (posicao < 0 || posicao > tamanho) {
        return false; // posição inválida
    }

    if (posicao == 0) {
        inserirInicio(pedido);
        return true;
    }

    if (posicao == tamanho) {
        inserirFim(pedido);
        return true;
    }

    NoLista* novoNo = new NoLista(pedido);
    NoLista* atual = inicio;

    for (int i = 0; i < posicao; i++) {
        atual = atual->proximo;
    }

    NoLista* anterior = atual->anterior;
    anterior->proximo = novoNo;
    novoNo->anterior = anterior;
    novoNo->proximo = atual;
    atual->anterior = novoNo;

    tamanho++;
    return true;
}

bool ListaHistoricoPedidos::removerPorNumero(int numero) {
    NoLista* atual = inicio;

    while (atual != nullptr) {
        if (atual->dado.getNumero() == numero) {
            if (atual == inicio) {
                inicio = atual->proximo;
                if (inicio != nullptr) {
                    inicio->anterior = nullptr;
                } else {
                    fim = nullptr; // a lista ficou vazia
                }
            } else if (atual == fim) {
                fim = atual->anterior;
                fim->proximo = nullptr;
            } else {
                NoLista* anterior = atual->anterior;
                NoLista* proximo = atual->proximo;
                anterior->proximo = proximo;
                proximo->anterior = anterior;
            }

            delete atual;
            tamanho--;
            return true;
        }
        atual = atual->proximo;
    }

    return false; // Pedido não encontrado
}

NoLista* ListaHistoricoPedidos::buscarPorNumero(int numero) {
    NoLista* atual = inicio;

    while (atual != nullptr) {
        if (atual->dado.getNumero() == numero) {
            return atual;
        }
        atual = atual->proximo;
    }

    return nullptr; // Pedido não encontrado
}

NoLista* ListaHistoricoPedidos::buscarPorCliente(string cliente) {
    NoLista* atual = inicio;

    while (atual != nullptr) {
        if (atual->dado.getCliente() == cliente) {
            return atual; // primeiro pedido do cliente
        }
        atual = atual->proximo;
    }

    return nullptr; // Cliente não encontrado
}

void ListaHistoricoPedidos::percorrerFrente() {
    NoLista* atual = inicio;

    while (atual != nullptr) {
        atual->dado.exibir();
        atual = atual->proximo;
    }
}

void ListaHistoricoPedidos::percorrerTras() {
    NoLista* atual = fim;

    while (atual != nullptr) {
        atual->dado.exibir();
        atual = atual->anterior;
    }
}

NoLista* ListaHistoricoPedidos::getInicio() {
    return inicio;
}

bool ListaHistoricoPedidos::estaVazia() {
    return inicio == nullptr;
}

int ListaHistoricoPedidos::getTamanho() {
    return tamanho;
}

void ListaHistoricoPedidos::limpar() {
    NoLista* atual = inicio;

    while (atual != nullptr) {
        NoLista* proximoNo = atual->proximo;
        delete atual;
        atual = proximoNo;
    }

    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

ListaHistoricoPedidos::~ListaHistoricoPedidos() {
    limpar();
}
