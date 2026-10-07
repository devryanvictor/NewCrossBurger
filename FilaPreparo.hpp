#ifndef FILAPREPARO_HPP
#define FILAPREPARO_HPP

#include "NoFila.hpp"

class FilaPreparo {
private:
    NoFila* frente;
    NoFila* tras;
    int tamanho;

public:
    FilaPreparo();
    ~FilaPreparo();

    void enfileirar(Pedido pedido);
    Pedido desenfileirar();

    bool estaVazia();
    Pedido* peek();

    int getTamanho();

    void limpar();
};

#endif