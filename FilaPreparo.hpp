#ifndef FILAPREPARO_HPP
#define FILAPREPARO_HPP

#include "NoFila.hpp"

class FilaPreparo {
private:
    NoFila* inicio;
    NoFila* fim;
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
