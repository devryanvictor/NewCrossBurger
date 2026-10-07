#ifndef NOPILHA_HPP
#define NOPILHA_HPP

#include "Acao.hpp"

class NoPilha {
public:
    Acao dado;
    NoPilha* proximo;

    NoPilha(Acao acao);
};

#endif