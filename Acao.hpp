#ifndef ACAO_HPP
#define ACAO_HPP

#include <string>

using namespace std;

class Acao {
private:
    string tipo;
    string descricao;

public:
    Acao();
    Acao(string tipo, string descricao);

    string getTipo();
    string getDescricao();

    void setTipo(string tipo);
    void setDescricao(string descricao);

    void exibir();
};

#endif