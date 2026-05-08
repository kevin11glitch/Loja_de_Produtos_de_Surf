# 🏄‍♂️ Tati Surf Co. - Sistema de Gerenciamento de Estoque

Desenvolvido como parte dos meus estudos em Estruturas de Dados no curso de graduação em Engenharia de Software na Universidade Federal do Ceará (UFC), Campus Russas, este sistema foca na implementação de estruturas de dados dinâmicas e algoritmos de alta eficiência. Trata-se de uma aplicação de console escrita em C voltada para a gestão de estoque de uma loja de surf, utilizando uma Lista Duplamente Encadeada para organizar o inventário de forma automática e crescente pelo preço.

## 🚀 Funcionalidades

O sistema oferece uma interface interativa com as seguintes operações:

1.  **Visualização Total do Estoque**: Lista todos os produtos cadastrados, do mais barato ao mais caro.
2.  **Filtro por Categoria**: Procura e exibe produtos de categorias específicas (Parafina, Leash, Quilha, Deck) utilizando comparação de strings robusta.
3.  **Filtro por Faixa de Preço**: Exibe produtos dentro de um intervalo de valores definido pelo utilizador (ex: entre R$ 50,00 e R$ 200,00).
4.  **Compra de Produtos (Remoção)**: Permite a "compra" de um item através do seu código único, reorganizando automaticamente os ponteiros da lista e libertando a memória (`free`).
5.  **Ordenação Automática em Tempo Real**: Cada novo produto é inserido na posição correta da lista, eliminando a necessidade de algoritmos de ordenação externos.

## 🛠️ Tecnologias e Conceitos Aplicados

-   **Linguagem C**: Implementação de lógica de baixo nível e manipulação de memória.
-   **Alocação Dinâmica de Memória**: Uso de `malloc` e `free` para gerir o ciclo de vida dos nós da lista.
-   **Lista Duplamente Encadeada**: Estrutura de dados que permite a navegação bidirecional (`prox` e `ant`), facilitando remoções e inserções.
-   **Ponteiros**: Manipulação direta de endereços de memória para criar a união entre os nós.
-   **Modularização**: Código estruturado em funções especialistas para garantir fácil manutenção.

## 📋 Como Executar

1.  Certifique-se de que tem um compilador C instalado (GCC, Clang ou MinGW).
2.  Clone o repositório:
    ```bash
    git clone [https://github.com/kevin11glitch/Loja_de_Produtos_de_Surf.git]
    ```
3.  Compile o programa:
    ```bash
    gcc Loja_Surf.c -o programa.exe
    ```
4.  Execute a aplicação:
    ```bash
    programa.exe
    ```

## 📂 Estrutura do Nó (Struct)

```c
typedef struct NO {
    int codigo;
    char* tipo_prod;
    char* descricao;
    float preco;
    struct NO *prox;
    struct NO *ant;
} NO;
```
