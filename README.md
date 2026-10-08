# Sistema New Cross Burger

Sistema desenvolvido em **C++** para gerenciamento de pedidos de uma hamburgueria, utilizando estruturas de dados lineares implementadas manualmente.

## Como executar

Compile todos os arquivos `.cpp`:
g++ *.cpp -o main.exe
./main.exe

## Estruturas utilizadas

O sistema utiliza três estruturas principais:

### 1. Lista Duplamente Encadeada — Histórico

Responsável por armazenar o **histórico dos pedidos**.

Cada nó possui:

* Um `Pedido`
* Um ponteiro para o nó anterior
* Um ponteiro para o próximo nó

```text
NULL ← [Pedido 1] ⇄ [Pedido 2] ⇄ [Pedido 3] → NULL
```

Permite:

* Percorrer o histórico para frente;
* Percorrer para trás;
* Buscar um pedido;
* Remover um pedido específico.

---

### 2. Fila — Preparação dos Pedidos

Responsável pelos pedidos que estão **aguardando a cozinha**.

Utiliza a regra **FIFO**:

> First In, First Out — primeiro que entra, primeiro que sai.

```text
Frente
  ↓
[Pedido 1] → [Pedido 2] → [Pedido 3]
                              ↑
                             Trás
```

Operações principais:

* `enfileirar()` → adiciona um pedido;
* `desenfileirar()` → remove o próximo pedido;
* `peek()` → consulta o primeiro pedido;
* `estaVazia()` → verifica se está vazia.

---

### 3. Pilha — Desfazer Ações

Responsável por armazenar as **ações realizadas no pedido**, permitindo desfazer a última alteração.

Utiliza a regra **LIFO**:

> Last In, First Out — último que entra, primeiro que sai.

Exemplo:

```text
        TOPO
          ↓
   [Remover item]
          ↓
   [Adicionar batata]
          ↓
   [Adicionar burger]
```

Ao utilizar `desempilhar()`, a última ação realizada é retirada primeiro.

Operações principais:

* `empilhar()` → adiciona uma ação;
* `desempilhar()` → remove a última ação;
* `peek()` → consulta o topo;
* `estaVazia()` → verifica se está vazia.

---

## Fluxo do sistema

O funcionamento básico pode ser representado assim:

```text
                 PEDIDO
                    │
                    ↓
             PILHA DE AÇÕES
                (LIFO)
                    │
             Fechar pedido
                    ↓
             FILA DA COZINHA
                (FIFO)
                    │
             Preparação
                    ↓
          HISTÓRICO DE PEDIDOS
        (Lista Duplamente Encadeada)
```

## 🎯 Resumo

| Estrutura                  | Função             | Regra                 |
| -------------------------- | ------------------ | --------------------- |
| Lista duplamente encadeada | Histórico          | Navegação frente/trás |
| Fila                       | Pedidos da cozinha | FIFO                  |
| Pilha                      | Desfazer ações     | LIFO                  |

O objetivo é demonstrar, na prática, o uso de **estruturas encadeadas** para resolver diferentes necessidades do sistema de pedidos.
