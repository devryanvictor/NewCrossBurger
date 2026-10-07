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
    tamanho ++;
}

void ListaHistoricoPedidos::inserirPosicao(Pedido pedido, int posicao) {
    if (posicao < 0 || posicao > tamanho) {
        std::cout << "Posição inválida." << std::endl;
        return;
    }

    if (posicao == 0) {
        inserirInicio(pedido);
        return;
    }

    if (posicao == tamanho) {
        inserirFim(pedido);
        return;
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
}

bool ListaHistoricoPedidos::remover(int numero) {
    NoLista* atual = inicio;

    while (atual != nullptr) {
        if (atual->dado.getNumero() == numero) {
            if (atual == inicio) {
                inicio = atual->proximo;
                if (inicio != nullptr) {
                    inicio->anterior = nullptr;
                }
            } else if (atual == fim) {
                fim = atual->anterior;
                if (fim != nullptr) {
                    fim->proximo = nullptr;
                }
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

Pedido* ListaHistoricoPedidos::buscar(int numero) {
    NoLista* atual = inicio;

    while (atual != nullptr) {
        if (atual->dado.getNumero() == numero) {
            return &(atual->dado);
        }
        atual = atual->proximo;
    }

    return nullptr; // Pedido não encontrado
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