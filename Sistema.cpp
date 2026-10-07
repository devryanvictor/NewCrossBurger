#include "Sistema.hpp"
#include <iostream>

Sistema::Sistema() {
    proximoNumeroPedido = 1; // Inicializa o número do próximo pedido como 1
}

void Sistema::novoPedido() {
    Pedido pedido;
    pedido.setNumero(proximoNumeroPedido);
    std::string cliente;
    std::cout << "Digite o nome do cliente: ";
    std::cin.ignore(); // Limpa o buffer do teclado
    std::getline(std::cin, cliente);
    pedido.setCliente(cliente);

    historico.inserirFim(pedido);
    proximoNumeroPedido++; // Incrementa o número do próximo pedido

    std::cout << "Pedido cadastrado com sucesso! Número do pedido: " << pedido.getNumero() << std::endl;
}

void Sistema::adicionarItem() {
    std::cout << "Digite o número do pedido para adicionar item: ";
    int numeroPedido;
    std::cin >> numeroPedido;
    Pedido* pedido = historico.buscar(numeroPedido);
    if (pedido != nullptr) {
        std::string item;
        float valor;
        std::cout << "Digite o nome do item: ";
        std::cin.ignore(); // Limpa o buffer do teclado
        std::getline(std::cin, item);
        std::cout << "Digite o valor do item: ";
        std::cin >> valor;
        pedido->adicionarItem(item, valor);
        std::cout << "Item adicionado com sucesso!" << std::endl;
    } else {
        std::cout << "Pedido não encontrado." << std::endl;
    }
}

void Sistema::removerItem() {

    int numeroPedido;
    std::cout << "Digite o número do pedido para remover item: ";
    std::cin >> numeroPedido;
    Pedido* pedido = historico.buscar(numeroPedido);
    if (pedido != nullptr) {
        int posicao;
        std::cout << "Digite a posição do item a ser removido (0 a " << pedido->getQuantidadeItens() - 1 << "): ";
        std::cin >> posicao;
        pedido->removerItem(posicao);
        std::cout << "Item removido com sucesso!" << std::endl;
    } else {
        std::cout << "Pedido não encontrado." << std::endl;
    }
}
