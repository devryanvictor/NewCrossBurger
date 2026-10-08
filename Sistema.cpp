#include "Sistema.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cmath>

// ---------------------------------------------------------------
// Funções auxiliares de leitura (sempre leem a linha inteira, então
// não sobra lixo no buffer e não é preciso usar cin.ignore())
// ---------------------------------------------------------------
static std::string lerLinha(const std::string& mensagem) {
    std::string linha;
    std::cout << mensagem;
    if (!std::getline(std::cin, linha)) {
        std::cout << std::endl << "Entrada encerrada. Saindo..." << std::endl;
        std::exit(0);
    }
    // remove espaços no início e no fim
    size_t ini = linha.find_first_not_of(" \t\r");
    if (ini == std::string::npos) {
        return "";
    }
    size_t fim = linha.find_last_not_of(" \t\r");
    return linha.substr(ini, fim - ini + 1);
}

static int lerInt(const std::string& mensagem) {
    while (true) {
        std::string s = lerLinha(mensagem);
        try {
            size_t pos = 0;
            int v = std::stoi(s, &pos);
            if (pos == s.size()) {
                return v;
            }
        } catch (...) {
        }
        std::cout << "Valor invalido. Digite um numero inteiro." << std::endl;
    }
}

static float lerFloat(const std::string& mensagem) {
    while (true) {
        std::string s = lerLinha(mensagem);
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == ',') s[i] = '.'; // aceita vírgula decimal
        }
        try {
            size_t pos = 0;
            float v = std::stof(s, &pos);
            if (pos == s.size() && std::isfinite(v)) {
                return v;
            }
        } catch (...) {
        }
        std::cout << "Valor invalido. Digite um numero (ex.: 12.50)." << std::endl;
    }
}

// ---------------------------------------------------------------
// Construtor e auxiliares privados
// ---------------------------------------------------------------
Sistema::Sistema() {
    proximoNumero = 1; // o primeiro pedido será o número 1
    std::cout << std::fixed << std::setprecision(2);
}

// O histórico guarda a versão "oficial" de cada pedido.
Pedido* Sistema::obterPedido(int numero) {
    NoLista* no = historico.buscarPorNumero(numero);
    if (no == nullptr) {
        return nullptr;
    }
    return &(no->dado);
}

// Pergunta o número do pedido e valida. Retorna nullptr (com mensagem) se não der.
Pedido* Sistema::selecionarPedido(bool apenasAberto) {
    int numero = lerInt("Digite o numero do pedido: ");
    Pedido* pedido = obterPedido(numero);

    if (pedido == nullptr) {
        std::cout << "Pedido nao encontrado." << std::endl;
        return nullptr;
    }

    if (apenasAberto && pedido->getStatus() != ABERTO) {
        std::cout << "O pedido #" << numero << " esta " << pedido->getStatusTexto()
                  << " e nao pode mais ser alterado." << std::endl;
        return nullptr;
    }

    return pedido;
}

// Tira um pedido do meio da fila mantendo a ordem dos demais.
void Sistema::removerDaFila(int numero) {
    int n = filaCozinha.getTamanho();
    for (int i = 0; i < n; i++) {
        Pedido p = filaCozinha.desenfileirar();
        if (p.getNumero() != numero) {
            filaCozinha.enfileirar(p);
        }
    }
}

// Tira um pedido do meio da pilha mantendo a ordem dos demais (usa pilha auxiliar).
void Sistema::removerDaPilhaRetirada(int numero) {
    PilhaRetirada aux;

    while (!pilhaRetirada.estaVazia()) {
        Pedido p = pilhaRetirada.desempilhar();
        if (p.getNumero() != numero) {
            aux.empilhar(p);
        }
    }

    while (!aux.estaVazia()) {
        pilhaRetirada.empilhar(aux.desempilhar());
    }
}

// ---------------------------------------------------------------
// RF01 - Cadastrar novo pedido
// ---------------------------------------------------------------
void Sistema::cadastrarPedido() {
    std::string cliente = lerLinha("Digite o nome do cliente: ");
    if (cliente.empty()) {
        std::cout << "O nome do cliente nao pode ser vazio." << std::endl;
        return;
    }

    Pedido pedido(proximoNumero, cliente);
    historico.inserirFim(pedido);

    std::cout << "Pedido cadastrado com sucesso! Numero do pedido: " << proximoNumero << std::endl;
    proximoNumero++;
}

// ---------------------------------------------------------------
// RF02 - Adicionar/remover item e aplicar desconto
// ---------------------------------------------------------------
void Sistema::adicionarItem() {
    Pedido* pedido = selecionarPedido(true);
    if (pedido == nullptr) {
        return;
    }

    std::string item = lerLinha("Digite o nome do item: ");
    if (item.empty()) {
        std::cout << "O nome do item nao pode ser vazio." << std::endl;
        return;
    }

    float valor = lerFloat("Digite o valor do item: ");
    if (valor <= 0.0f) {
        std::cout << "O valor do item deve ser maior que zero." << std::endl;
        return;
    }

    if (!pedido->adicionarItem(item, valor)) {
        std::cout << "Nao e possivel adicionar mais itens. Limite de 20 atingido." << std::endl;
        return;
    }

    pilhaDesfazer.empilhar(Acao(ADICIONAR_ITEM, pedido->getNumero(), item, valor));
    std::cout << "Item adicionado com sucesso! Total: R$" << pedido->getTotal() << std::endl;
}

void Sistema::removerItem() {
    Pedido* pedido = selecionarPedido(true);
    if (pedido == nullptr) {
        return;
    }

    if (pedido->getQuantidadeItens() == 0) {
        std::cout << "O pedido nao tem itens para remover." << std::endl;
        return;
    }

    pedido->exibir();
    std::string item = lerLinha("Digite o nome do item a remover: ");

    int posicao = pedido->buscarItem(item);
    if (posicao == -1) {
        std::cout << "Item nao encontrado no pedido." << std::endl;
        return;
    }

    float valor = pedido->getValorItem(posicao);
    pedido->removerItem(item, valor);

    pilhaDesfazer.empilhar(Acao(REMOVER_ITEM, pedido->getNumero(), item, valor));
    std::cout << "Item removido com sucesso! Total: R$" << pedido->getTotal() << std::endl;
}

void Sistema::aplicarDesconto() {
    Pedido* pedido = selecionarPedido(true);
    if (pedido == nullptr) {
        return;
    }

    if (pedido->getQuantidadeItens() == 0) {
        std::cout << "Adicione itens ao pedido antes de aplicar desconto." << std::endl;
        return;
    }

    float percentual = lerFloat("Digite o percentual de desconto (0 a 100): ");
    if (percentual < 0.0f || percentual > 100.0f) {
        std::cout << "Percentual invalido." << std::endl;
        return;
    }

    float anterior = pedido->getDesconto();
    pedido->aplicarDesconto(percentual);

    // guarda o percentual ANTERIOR para poder desfazer
    pilhaDesfazer.empilhar(Acao(APLICAR_DESCONTO, pedido->getNumero(), "desconto", anterior));
    std::cout << "Desconto aplicado! Novo total: R$" << pedido->getTotal() << std::endl;
}

// ---------------------------------------------------------------
// RF03 - Desfazer última ação
// ---------------------------------------------------------------
void Sistema::desfazer() {
    if (pilhaDesfazer.estaVazia()) {
        std::cout << "Nao ha açoes para desfazer." << std::endl;
        return;
    }

    Acao acao = pilhaDesfazer.desempilhar();
    Pedido* pedido = obterPedido(acao.getNumeroPedido());

    if (pedido == nullptr || pedido->getStatus() != ABERTO) {
        std::cout << "Acao descartada: o pedido #" << acao.getNumeroPedido()
                  << " nao esta mais aberto." << std::endl;
        return;
    }

    switch (acao.getTipo()) {
        case ADICIONAR_ITEM:
            pedido->removerItem(acao.getItem(), acao.getValor());
            break;
        case REMOVER_ITEM:
            pedido->adicionarItem(acao.getItem(), acao.getValor());
            break;
        case APLICAR_DESCONTO:
            pedido->aplicarDesconto(acao.getValor()); // volta ao percentual anterior
            break;
    }

    std::cout << "Acao desfeita:" << std::endl;
    acao.exibir();
    std::cout << "Total atual do pedido #" << pedido->getNumero() << ": R$" << pedido->getTotal() << std::endl;
}

// ---------------------------------------------------------------
// RF04 - Fechar pedido (a implementar depois)
// ---------------------------------------------------------------
void Sistema::fecharPedido() {
    std::cout << "Fechar pedido ainda nao foi implementado." << std::endl;
}

// ---------------------------------------------------------------
// RF05 - Chamar cozinha (envia o pedido aberto para a fila de preparo)
// ---------------------------------------------------------------
void Sistema::chamarCozinha() {
    Pedido* pedido = selecionarPedido(true);
    if (pedido == nullptr) {
        return;
    }

    if (pedido->getQuantidadeItens() == 0) {
        std::cout << "Nao e possível enviar um pedido sem itens para a cozinha." << std::endl;
        return;
    }

    pedido->setStatus(NA_COZINHA);
    filaCozinha.enfileirar(*pedido);
    std::cout << "Pedido #" << pedido->getNumero() << " enviado para a cozinha. "
              << "Posicao na fila: " << filaCozinha.getTamanho() << std::endl;
}

// ---------------------------------------------------------------
// RF06 - Marcar pedido como pronto (primeiro da fila)
// ---------------------------------------------------------------
void Sistema::marcarPronto() {
    if (filaCozinha.estaVazia()) {
        std::cout << "Nao ha pedidos na fila da cozinha." << std::endl;
        return;
    }

    Pedido emPreparo = filaCozinha.desenfileirar();
    Pedido* pedido = obterPedido(emPreparo.getNumero());

    if (pedido == nullptr) {
        std::cout << "Erro: pedido nao encontrado no historico." << std::endl;
        return;
    }

    pedido->setStatus(PRONTO);
    pilhaRetirada.empilhar(*pedido);
    std::cout << "Pedido #" << pedido->getNumero() << " (" << pedido->getCliente()
              << ") esta pronto para retirada." << std::endl;
}

// ---------------------------------------------------------------
// RF07 - Retirar pedido pronto (topo da pilha de retirada)
// ---------------------------------------------------------------
void Sistema::retirarPedido() {
    if (pilhaRetirada.estaVazia()) {
        std::cout << "Nao ha pedidos prontos para retirada." << std::endl;
        return;
    }

    Pedido pronto = pilhaRetirada.desempilhar();
    Pedido* pedido = obterPedido(pronto.getNumero());

    if (pedido == nullptr) {
        std::cout << "Erro: pedido nao encontrado no historico." << std::endl;
        return;
    }

    pedido->setStatus(ENTREGUE);
    std::cout << "Pedido entregue!" << std::endl;
    pedido->exibir();
}

// ---------------------------------------------------------------
// RF08 - Consultar histórico
// ---------------------------------------------------------------
void Sistema::consultarHistorico() {
    if (historico.estaVazia()) {
        std::cout << "O historico esta vazio." << std::endl;
        return;
    }

    std::cout << "1 - Do mais antigo para o mais recente" << std::endl;
    std::cout << "2 - Do mais recente para o mais antigo" << std::endl;
    int opcao = lerInt("Escolha: ");

    std::cout << std::endl;
    if (opcao == 1) {
        historico.percorrerFrente();
    } else if (opcao == 2) {
        historico.percorrerTras();
    } else {
        std::cout << "Opcao invalida." << std::endl;
    }
}

// ---------------------------------------------------------------
// RF09 - Buscar pedido
// ---------------------------------------------------------------
void Sistema::buscarPedido() {
    std::cout << "1 - Buscar por numero" << std::endl;
    std::cout << "2 - Buscar por cliente" << std::endl;
    int opcao = lerInt("Escolha: ");

    if (opcao == 1) {
        int numero = lerInt("Digite o numero do pedido: ");
        NoLista* no = historico.buscarPorNumero(numero);
        if (no == nullptr) {
            std::cout << "Pedido nao encontrado." << std::endl;
        } else {
            no->dado.exibir();
        }
    } else if (opcao == 2) {
        std::string cliente = lerLinha("Digite o nome do cliente (exato): ");
        NoLista* no = historico.buscarPorCliente(cliente);
        if (no == nullptr) {
            std::cout << "Nenhum pedido encontrado para esse cliente." << std::endl;
            return;
        }
        // mostra o primeiro e depois os demais pedidos do mesmo cliente
        while (no != nullptr) {
            no->dado.exibir();
            no = no->proximo;
            while (no != nullptr && no->dado.getCliente() != cliente) {
                no = no->proximo;
            }
        }
    } else {
        std::cout << "Opçao invalida." << std::endl;
    }
}

// ---------------------------------------------------------------
// RF10 - Cancelar pedido (qualquer pedido ainda não entregue)
// ---------------------------------------------------------------
void Sistema::cancelarPedido() {
    Pedido* pedido = selecionarPedido(false);
    if (pedido == nullptr) {
        return;
    }

    switch (pedido->getStatus()) {
        case ENTREGUE:
            std::cout << "Nao e possivel cancelar: o pedido ja foi entregue." << std::endl;
            return;
        case CANCELADO:
            std::cout << "O pedido ja esta cancelado." << std::endl;
            return;
        case NA_COZINHA:
            removerDaFila(pedido->getNumero());
            break;
        case PRONTO:
            removerDaPilhaRetirada(pedido->getNumero());
            break;
        case ABERTO:
            break; // ainda não saiu do balcão, não está em nenhuma estrutura
    }

    pedido->setStatus(CANCELADO);
    std::cout << "Pedido #" << pedido->getNumero() << " cancelado com sucesso." << std::endl;
}

// ---------------------------------------------------------------
// RF11 - Relatório do dia
// ---------------------------------------------------------------
void Sistema::relatorioDoDia() {
    if (historico.estaVazia()) {
        std::cout << "Nenhum pedido registrado hoje." << std::endl;
        return;
    }

    int abertos = 0, naCozinha = 0, prontos = 0, entregues = 0, cancelados = 0;
    int itensVendidos = 0;
    float faturamento = 0.0f;

    NoLista* atual = historico.getInicio();
    while (atual != nullptr) {
        Pedido& p = atual->dado;
        switch (p.getStatus()) {
            case ABERTO:     abertos++;    break;
            case NA_COZINHA: naCozinha++;  break;
            case PRONTO:     prontos++;    break;
            case CANCELADO:  cancelados++; break;
            case ENTREGUE:
                entregues++;
                faturamento += p.getTotal();
                itensVendidos += p.getQuantidadeItens();
                break;
        }
        atual = atual->proximo;
    }

    std::cout << "===== RELATORIO DO DIA =====" << std::endl;
    std::cout << "Total de pedidos: " << historico.getTamanho() << std::endl;
    std::cout << "  Abertos:     " << abertos << std::endl;
    std::cout << "  Na cozinha:  " << naCozinha << std::endl;
    std::cout << "  Prontos:     " << prontos << std::endl;
    std::cout << "  Entregues:   " << entregues << std::endl;
    std::cout << "  Cancelados:  " << cancelados << std::endl;
    std::cout << "Itens vendidos (entregues): " << itensVendidos << std::endl;
    std::cout << "Faturamento (entregues): R$" << faturamento << std::endl;
    if (entregues > 0) {
        std::cout << "Ticket medio: R$" << faturamento / entregues << std::endl;
    }
    std::cout << "============================" << std::endl;
}

// ---------------------------------------------------------------
// Menu principal
// ---------------------------------------------------------------
void Sistema::menu() {
    int opcao;

    do {
        std::cout << std::endl;
        std::cout << "====== NEW CROSS BURGER ======" << std::endl;
        std::cout << " 1 - Cadastrar pedido" << std::endl;
        std::cout << " 2 - Adicionar item" << std::endl;
        std::cout << " 3 - Remover item" << std::endl;
        std::cout << " 4 - Aplicar desconto" << std::endl;
        std::cout << " 5 - Desfazer ultima acao" << std::endl;
        std::cout << " 6 - Chamar cozinha" << std::endl;
        std::cout << " 7 - Marcar pedido como pronto" << std::endl;
        std::cout << " 8 - Retirar pedido pronto" << std::endl;
        std::cout << " 9 - Consultar historico" << std::endl;
        std::cout << "10 - Buscar pedido" << std::endl;
        std::cout << "11 - Cancelar pedido" << std::endl;
        std::cout << "12 - Relatorio do dia" << std::endl;
        std::cout << " 0 - Sair" << std::endl;

        opcao = lerInt("Escolha uma opcao: ");
        std::cout << std::endl;

        switch (opcao) {
            case 1:  cadastrarPedido();    break;
            case 2:  adicionarItem();      break;
            case 3:  removerItem();        break;
            case 4:  aplicarDesconto();    break;
            case 5:  desfazer();           break;
            case 6:  chamarCozinha();      break;
            case 7:  marcarPronto();       break;
            case 8:  retirarPedido();      break;
            case 9:  consultarHistorico(); break;
            case 10: buscarPedido();       break;
            case 11: cancelarPedido();     break;
            case 12: relatorioDoDia();     break;
            case 0:  std::cout << "Encerrando o sistema. Ate logo!" << std::endl; break;
            default: std::cout << "Opcao invalida." << std::endl; break;
        }
    } while (opcao != 0);
}
