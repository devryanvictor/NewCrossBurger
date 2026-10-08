#ifndef ACAO_HPP
#define ACAO_HPP

#include <string>

using namespace std;

// Tipos de ação que podem ser desfeitas (enumeration do diagrama)
enum TipoAcao {
    ADICIONAR_ITEM,
    REMOVER_ITEM,
    APLICAR_DESCONTO
};

class Acao {
private:
    TipoAcao tipo;
    int numeroPedido;   // pedido que sofreu a ação
    string item;        // nome do item (ADICIONAR_ITEM / REMOVER_ITEM)
    float valor;        // preço do item, ou percentual de desconto ANTERIOR (APLICAR_DESCONTO)

public:
    Acao();
    Acao(TipoAcao tipo, int numeroPedido, string item, float valor);

    TipoAcao getTipo();
    string getTipoTexto();
    int getNumeroPedido();
    string getItem();
    float getValor();

    void setTipo(TipoAcao tipo);
    void setNumeroPedido(int numeroPedido);
    void setItem(string item);
    void setValor(float valor);

    void exibir();
};

#endif
