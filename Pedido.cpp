#include "Pedido.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

Pedido::Pedido() {
    numero = 0;
    cliente = "";
    quantidadeItens = 0;
    percentualDesconto = 0.0f;
    total = 0.0f;
    status = ABERTO;
    for (int i = 0; i < 20; i++) {
        valores[i] = 0.0f;
    }
}

Pedido::Pedido(int numero, std::string cliente) : Pedido() {
    this->numero = numero;
    this->cliente = cliente;
}

void Pedido::recalcularTotal() {
    float subtotal = 0.0f;
    for (int i = 0; i < quantidadeItens; i++) {
        subtotal += valores[i];
    }
    total = subtotal * (1.0f - percentualDesconto / 100.0f);
}

int Pedido::getNumero() {
    return numero;
}

std::string Pedido::getCliente() {
    return cliente;
}

int Pedido::getQuantidadeItens() {
    return quantidadeItens;
}

float Pedido::getTotal() {
    return total;
}

float Pedido::getDesconto() {
    return percentualDesconto;
}

StatusPedido Pedido::getStatus() {
    return status;
}

std::string Pedido::getStatusTexto() {
    switch (status) {
        case ABERTO:     return "aberto";
        case NA_COZINHA: return "na cozinha";
        case PRONTO:     return "pronto";
        case ENTREGUE:   return "entregue";
        case CANCELADO:  return "cancelado";
    }
    return "desconhecido";
}

std::string Pedido::getItem(int posicao) {
    if (posicao < 0 || posicao >= quantidadeItens) {
        return "";
    }
    return itens[posicao];
}

float Pedido::getValorItem(int posicao) {
    if (posicao < 0 || posicao >= quantidadeItens) {
        return 0.0f;
    }
    return valores[posicao];
}

void Pedido::setNumero(int numero) {
    this->numero = numero;
}

void Pedido::setCliente(std::string cliente) {
    this->cliente = cliente;
}

void Pedido::setStatus(StatusPedido status) {
    this->status = status;
}

int Pedido::buscarItem(std::string item, float valor) {
    for (int i = 0; i < quantidadeItens; i++) {
        if (itens[i] != item) {
            continue;
        }
        if (valor >= 0.0f && std::fabs(valores[i] - valor) > 0.001f) {
            continue;
        }
        return i;
    }
    return -1;
}

bool Pedido::adicionarItem(std::string item, float valor) {
    if (quantidadeItens >= 20) {
        return false; // limite atingido
    }
    itens[quantidadeItens] = item;
    valores[quantidadeItens] = valor;
    quantidadeItens++;
    recalcularTotal();
    return true;
}

bool Pedido::removerItem(std::string item, float valor) {
    int posicao = buscarItem(item, valor);
    if (posicao == -1) {
        return false; // item não encontrado
    }
    for (int i = posicao; i < quantidadeItens - 1; i++) {
        itens[i] = itens[i + 1];
        valores[i] = valores[i + 1];
    }
    quantidadeItens--;
    recalcularTotal();
    return true;
}

void Pedido::aplicarDesconto(float percentual) {
    if (percentual < 0.0f) percentual = 0.0f;
    if (percentual > 100.0f) percentual = 100.0f;
    percentualDesconto = percentual;
    recalcularTotal();
}

void Pedido::exibir() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Numero do Pedido: " << numero << " [" << getStatusTexto() << "]" << std::endl;
    std::cout << "Cliente: " << cliente << std::endl;
    std::cout << "Itens do Pedido:" << std::endl;
    if (quantidadeItens == 0) {
        std::cout << "  (nenhum item)" << std::endl;
    }
    for (int i = 0; i < quantidadeItens; i++) {
        std::cout << "- " << itens[i] << " - R$" << valores[i] << std::endl;
    }
    if (percentualDesconto > 0.0f) {
        std::cout << "Desconto: " << percentualDesconto << "%" << std::endl;
    }
    std::cout << "Total: R$" << total << std::endl;
    std::cout << "-----------------------------" << std::endl;
}
