#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "Pedido.hpp"
#include "ListaHistoricoPedidos.hpp"
#include "FilaPreparo.hpp"
#include "PilhaAcoes.hpp"

class Sistema {
private:
    ListaHistoricoPedidos historico;
    FilaPreparo filaPreparo;
    PilhaAcoes pilhaAcoes;
    int proximoNumeroPedido; // Variável para gerar números de pedido únicos
public:
    Sistema();

    // RF01 - Cadastrar novo pedido
    void novoPedido();

    // RF02 - Adicionar/remover item
    void adicionarItem();
    void removerItem();

    // RF03 - Desfazer última ação
    void desfazer();

    // RF04 - Fechar pedido
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
    void relatorioDia();

    // Menu principal
    void menu();
};

#endif