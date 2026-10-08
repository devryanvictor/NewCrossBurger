#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <string>

using namespace std;

enum StatusPedido {
    ABERTO,
    NA_COZINHA,
    PRONTO,
    ENTREGUE,
    CANCELADO
};

class Pedido {
private:
    int numero;
    string cliente;
    string itens[20];
    float valores[20];          // preço de cada item (mesma posição de itens[])
    int quantidadeItens;
    float percentualDesconto;   // 0 a 100
    float total;                // soma dos valores com o desconto aplicado
    StatusPedido status;

    void recalcularTotal();

public:
    Pedido();
    Pedido(int numero, string cliente);

    int getNumero();
    string getCliente();
    float getTotal();
    int getQuantidadeItens();
    float getDesconto();
    StatusPedido getStatus();
    string getStatusTexto();
    string getItem(int posicao);
    float getValorItem(int posicao);

    void setNumero(int numero);
    void setCliente(string cliente);
    void setStatus(StatusPedido status);

    // Retorna a posição do item (ou -1). Se valor >= 0, também confere o preço.
    int buscarItem(string item, float valor = -1.0f);

    bool adicionarItem(string item, float valor);
    // Remove a primeira ocorrência do item (se valor >= 0, só se o preço também bater).
    bool removerItem(string item, float valor = -1.0f);
    // Define o percentual de desconto do pedido (substitui o desconto anterior).
    void aplicarDesconto(float percentual);

    void exibir();
};

#endif
