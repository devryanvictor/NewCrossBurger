#include "Acao.hpp"
#include <iostream>
#include <iomanip>

Acao::Acao() {
    tipo = ADICIONAR_ITEM;
    numeroPedido = 0;
    item = "";
    valor = 0.0f;
}

Acao::Acao(TipoAcao tipo, int numeroPedido, std::string item, float valor) {
    this->tipo = tipo;
    this->numeroPedido = numeroPedido;
    this->item = item;
    this->valor = valor;
}

TipoAcao Acao::getTipo() {
    return tipo;
}

std::string Acao::getTipoTexto() {
    switch (tipo) {
        case ADICIONAR_ITEM:   return "Adicionar item";
        case REMOVER_ITEM:     return "Remover item";
        case APLICAR_DESCONTO: return "Aplicar desconto";
    }
    return "Desconhecida";
}

int Acao::getNumeroPedido() {
    return numeroPedido;
}

std::string Acao::getItem() {
    return item;
}

float Acao::getValor() {
    return valor;
}

void Acao::setTipo(TipoAcao tipo) {
    this->tipo = tipo;
}

void Acao::setNumeroPedido(int numeroPedido) {
    this->numeroPedido = numeroPedido;
}

void Acao::setItem(std::string item) {
    this->item = item;
}

void Acao::setValor(float valor) {
    this->valor = valor;
}

void Acao::exibir() {
    std::cout << "Acao: " << getTipoTexto() << " (pedido #" << numeroPedido << ")" << std::endl;
    if (tipo == APLICAR_DESCONTO) {
        std::cout << "Desconto anterior: " << std::fixed << std::setprecision(2) << valor << "%" << std::endl;
    } else {
        std::cout << "Item: " << item << " - R$" << std::fixed << std::setprecision(2) << valor << std::endl;
    }
}
