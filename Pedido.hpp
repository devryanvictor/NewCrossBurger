#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <string>

using namespace std;

class Pedido {
private:
    int numero;
    string cliente;
    string itens[20];
    int quantidadeItens;
    float total;

public:
    Pedido();
    Pedido(int numero, string cliente);

    int getNumero();
    string getCliente();
    float getTotal();
    int getQuantidadeItens();

    void setNumero(int numero);
    void setCliente(string cliente);
    void setTotal(float total);

    void adicionarItem(string item, float valor);
    void removerItem(int posicao);

    void exibir();
};

#endif