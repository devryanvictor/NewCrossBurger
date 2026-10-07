#ifndef LISTAHISTORICOPEDIDOS_HPP
#define LISTAHISTORICOPEDIDOS_HPP

#include "NoLista.hpp"

class ListaHistoricoPedidos {
private:
    NoLista* inicio;
    NoLista* fim;
    int tamanho;

public:
    ListaHistoricoPedidos();
    ~ListaHistoricoPedidos();

    void inserirInicio(Pedido pedido);
    void inserirFim(Pedido pedido);
    void inserirPosicao(Pedido pedido, int posicao);

    bool remover(int numero);
    Pedido* buscar(int numero);

    void percorrerFrente();
    void percorrerTras();

    bool estaVazia();
    int getTamanho();

    void limpar();
};

#endif