#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "Pedido.hpp"
#include "ListaHistoricoPedidos.hpp"
#include "FilaPreparo.hpp"
#include "PilhaAcoes.hpp"
#include "PilhaRetirada.hpp"

class Sistema {
private:
    PilhaAcoes pilhaDesfazer;
    FilaPreparo filaCozinha;
    PilhaRetirada pilhaRetirada;
    ListaHistoricoPedidos historico;
    int proximoNumero; // gera números de pedido únicos

    // Auxiliares
    Pedido* obterPedido(int numero);
    Pedido* selecionarPedido(bool apenasAberto);
    void removerDaFila(int numero);
    void removerDaPilhaRetirada(int numero);

public:
    Sistema();

    // RF01 - Cadastrar novo pedido
    void cadastrarPedido();

    // RF02 - Adicionar/remover item (e aplicar desconto)
    void adicionarItem();
    void removerItem();
    void aplicarDesconto();

    // RF03 - Desfazer última ação
    void desfazer();

    // RF04 - Fechar pedido (ainda não implementado)
    void fecharPedido();

    // RF05 - Chamar cozinha
    void chamarCozinha();

    // RF06 - Marcar pedido como pronto
    void marcarPronto();

    // RF07 - Retirar pedido pronto
    void retirarPedido();

    // RF08 - Consultar histórico
    void consultarHistorico();

    // RF09 - Buscar pedido
    void buscarPedido();

    // RF10 - Cancelar pedido
    void cancelarPedido();

    // RF11 - Relatório do dia
    void relatorioDoDia();

    // Menu principal
    void menu();
};

#endif
