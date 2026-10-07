#include "Pedido.hpp"
#include <iostream>

Pedido::Pedido() {
    numero = 0;
    cliente = "";
    quantidadeItens = 0;
    total = 0.0f;
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

void Pedido::setNumero(int numero) {
    this->numero = numero;
}

void Pedido::setCliente(std::string cliente) {
    this->cliente = cliente;
}

void Pedido::setTotal(float total) {
    this->total = total;
}

void Pedido::adicionarItem(std::string item, float valor) {
    if (quantidadeItens < 20) {
        itens[quantidadeItens] = item;
        quantidadeItens++;
        total += valor;
    } else {
        std::cout << "Não é possível adicionar mais itens. Limite atingido." << std::endl;
    }
}

void Pedido::removerItem(int posicao) {
    if (posicao >= 0 && posicao < quantidadeItens) {
        total -= 0; // Subtrair o valor do item removido do total
        for (int i = posicao; i < quantidadeItens - 1; i++) {
            itens[i] = itens[i + 1];
        }
        quantidadeItens--;
    } else {
        std::cout << "Posição inválida. Não é possível remover o item." << std::endl;
    }
}

void Pedido::exibir() {
    std::cout << "Número do Pedido: " << numero << std::endl;
    std::cout << "Cliente: " << cliente << std::endl;
    std::cout << "Itens do Pedido:" << std::endl;
    for (int i = 0; i < quantidadeItens; i++) {
        std::cout << "- " << itens[i] << std::endl;
    }
    std::cout << "Total: R$" << total << std::endl;
}  
