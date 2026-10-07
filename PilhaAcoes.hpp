#ifndef PILHAACOES_HPP
#define PILHAACOES_HPP

#include "NoPilha.hpp"

class PilhaAcoes {
private:
    NoPilha* topo;
    int tamanho;

public:
    PilhaAcoes();
    ~PilhaAcoes();

    void empilhar(Acao acao);
    Acao desempilhar();

    bool estaVazia();
    Acao* peek();

    int getTamanho();

    void limpar();
};

#endif