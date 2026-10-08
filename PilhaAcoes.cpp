#include "PilhaAcoes.hpp"
#include <iostream>

PilhaAcoes::PilhaAcoes(){
    topo = nullptr;
    tamanho = 0;
}

void PilhaAcoes::empilhar(Acao acao) {
    NoPilha* novoNo = new NoPilha(acao);
    novoNo->proximo = topo;
    topo = novoNo;
    tamanho++;
}

Acao PilhaAcoes::desempilhar() {
    if (estaVazia()){
        std::cout << "A pilha está vazia. Não é possível desempilhar." << std::endl;
        return Acao(); // Retorna um objeto Acao vazio
    }
    NoPilha* noRemovido = topo;
    Acao acaoRemovida = noRemovido->dado;
    topo = topo->proximo;
    delete noRemovido;
    tamanho--;
    return acaoRemovida;
}

bool PilhaAcoes::estaVazia() {
    return topo == nullptr;
}

Acao* PilhaAcoes::peek() {

    if (estaVazia()) {
        std::cout << "A pilha esta vazia. Nao ha elemento no topo." << std::endl;
        return nullptr;
    }

    return &topo->dado;
}

int PilhaAcoes::getTamanho() {
    return tamanho;
}

void PilhaAcoes::limpar() {
    NoPilha* atual = topo;

    while (atual != nullptr) {
        NoPilha* proximoNo = atual->proximo;
        delete atual;
        atual = proximoNo;
    }

    topo = nullptr;
    tamanho = 0;
}

PilhaAcoes::~PilhaAcoes() {
    limpar();
}