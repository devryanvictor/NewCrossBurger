#include "NoPilha.hpp"
#include <iostream>

NoPilha::NoPilha(Acao acao) {
    dado = acao;
    proximo = nullptr;
}


