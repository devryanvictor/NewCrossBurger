#include "Acao.hpp"
#include <iostream>

Acao::Acao() {
    tipo = "";
    descricao = "";
}

Acao::Acao(std::string tipo, std::string descricao) {
    this->tipo = tipo;
    this->descricao = descricao;
}

std::string Acao::getTipo() {
    return tipo;
}

std::string Acao::getDescricao() {
    return descricao;
}

void Acao::setTipo(std::string tipo) {
    this->tipo = tipo;
}

void Acao::setDescricao(std::string descricao) {
    this->descricao = descricao;
}   

void Acao::exibir() {
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Descrição: " << descricao << std::endl;
}