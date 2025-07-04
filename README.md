# Compactador de Texto com Huffman e AVL

## Sobre o Projeto
Este repositório contém a implementação de um programa em C++ que realiza a **compressão e descompressão** de textos utilizando o **Algoritmo de Huffman**, com o auxílio de uma **árvore AVL** para contagem eficiente e balanceada da frequência dos caracteres presentes no texto. O sistema implementa um **compactador de texto** que codifica os dados para uma representação binária compacta e, posteriormente, realiza a descompressão dos dados codificados, reconstruindo fielmente o texto original inserido pelo usuário.

O objetivo principal é aplicar conceitos fundamentais de **estruturas de dados** (árvores balanceadas e árvores binárias) para criar uma ferramenta funcional de compressão que exibe o resultado em formato binário (sequência de 0s e 1s) e posteriormente recupera o texto original.

## Funcionalidades
- Leitura do texto de entrada via teclado.
- Construção de uma árvore **AVL** para armazenar a frequência de cada caractere.
- Geração de uma **árvore de Huffman** com base nas frequências.
- Criação de uma **tabela de códigos binários** para os caracteres.
- Compressão do texto original para uma sequência de bits.
- Descompressão da sequência para reconstrução do texto original.
- Liberação adequada de memória dinâmica.

## Organização dos Arquivos
- `main.cpp` – Lógica principal do programa: entrada, compressão, descompressão e exibição.
- `avl.hpp` – Implementação da árvore AVL com controle de altura e balanceamento.
- `huffman.hpp` – Implementação do algoritmo de Huffman, incluindo codificação e decodificação.

## Como Funciona
1. **Entrada do Texto**: Usuário insere um texto via `cin`.
2. **Contagem de Frequências**: Cada caractere é inserido na árvore AVL, que contabiliza suas ocorrências e mantém o balanceamento.
3. **Conversão AVL → Lista de Huffman**: A árvore AVL é percorrida e os dados são exportados para uma lista ordenada por frequência.
4. **Construção da Árvore de Huffman**: A lista é usada para construir uma árvore binária onde o caminho até cada caractere representa seu código binário.
5. **Codificação**: Cada caractere do texto original é substituído por seu código binário (em forma de `char`).
6. **Exibição do Texto Codificado**: Mostra o vetor de caracteres com `0`s e `1`s representando os bits.
7. **Decodificação**: O vetor codificado é percorrido e a árvore de Huffman é usada para reconstruir o texto original.
8. **Exibição do Texto Decodificado**.

## Exemplo de execução

```bash
Digite o texto para compressao: hello world

---------------------------------------

Tabela de codigos de Huffman:
Letra | Codigo
----- | -----
  ' ' | 00
  'd' | 010
  'e' | 011
  'h' | 100
  'l' | 101
  'o' | 110
  'r' | 1110
  'w' | 1111

Texto codificado: 10001110101110101100011111111010

Texto decodificado: hello world
```

## Tecnologias
- Linguagem: **C++**
- Estruturas utilizadas:
  - Árvore AVL: Uma árvore binária de busca balanceada utilizada para armazenar os caracteres do texto junto com a contagem de suas frequências, garantindo operações eficientes de inserção e busca com complexidade O(log n).
  - Árvore de Huffman: Uma árvore binária construída a partir das frequências dos caracteres, que gera códigos binários prefixados para cada caractere. Esta estrutura é utilizada para realizar a compressão e descompressão do texto, possibilitando a representação compacta dos dados.
    - Essas estruturas permitem que o programa faça a contagem de frequências de forma eficiente e crie um código de compressão ótimo, garantindo a funcionalidade principal do compactador de texto.
  - Vetores de caracteres (`char[]`)

## Gerenciamento de Memória
Todo o espaço alocado dinamicamente para as árvores (AVL e Huffman) é devidamente liberado ao final da execução.

## Referências
- Algoritmo de Huffman – Compressão de dados baseada em frequências.
- Árvores AVL – Estrutura de dados balanceada para manter acesso eficiente aos dados.

## Como usar
1. Clone o repositório em seu computador com o comando abaixo:
```bash
git clone https://github.com/marias1lva/HuffmanCompression.git
cd HuffmanCompression
```
2. Compile o código usando um compilador de C++, como o g++:
```bash
g++ -o HuffmanCompression main.cpp
```
3. Execute o programa:
```bash
./HuffmanCompression
```
4. Digite o texto que deseja comprimir e acompanhe a saída no terminal.
