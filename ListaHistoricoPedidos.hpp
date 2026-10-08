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
    bool inserirPosicao(Pedido pedido, int posicao);

    bool removerPorNumero(int numero);
    NoLista* buscarPorNumero(int numero);
    NoLista* buscarPorCliente(string cliente);

    void percorrerFrente();
    void percorrerTras();

    NoLista* getInicio();
    bool estaVazia();
    int getTamanho();

    void limpar();
};

#endif
