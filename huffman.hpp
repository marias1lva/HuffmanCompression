#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <cstring>
#include "avl.hpp"
using namespace std;

struct HuffmanNode{
    char caractere; //caractere que será codificado
    int frequencia; //quantas vezes esse caractere aparece no texto
    HuffmanNode* esq; //filho esquerdo (para 0)
    HuffmanNode* dir; //filho direito (para 1)
};


struct Lista{ //guarda os nós temporariamente
    HuffmanNode* elementos[256]; //array de ponteiros para nós
    int tamanho = 0; 

    void inserir(HuffmanNode* node){ //insere um novo nó na lista, mantendo a lista ordenada por frequência (crescente)
        int i = tamanho++; //aumenta o tamanho da lista
        while(i > 0 && elementos[i - 1]->frequencia > node->frequencia){ 
            elementos[i] = elementos[i - 1];
            i--;
        }
        elementos[i] = node;
    }

    HuffmanNode* removerMin(){ //remove e retorna o nó com menor frequência
        if (tamanho == 0) return nullptr; //se a lista estiver vazia, retorna nullptr
        HuffmanNode* minNode = elementos[0]; //primeiro elemento é o de menor frequência
        for(int k = 0; k < tamanho - 1; ++k){ 
            elementos[k] = elementos[k + 1]; 
        }
        tamanho--; //reduz o tamanho da lista
        return minNode; //retorna o nó removido
    }
};

void gerarTabelaCodigos(HuffmanNode* raiz, char tabela[256][256], char codigo[], int nivel){ //gera, para cada caractere, um código binário de acordo com o caminho na árvore ('0' -> esquerda, '1' -> direita)
    if(raiz == nullptr) return; //

    if(raiz->esq == nullptr && raiz->dir == nullptr){ //se for um nó folha, significa que chegamos a um caractere
        codigo[nivel] = '\0'; //finaliza a string de código
        strcpy(tabela[(unsigned char)raiz->caractere], codigo); //copia o código gerado para a tabela de códigos
        return;
    }

    codigo[nivel] = '0'; //adiciona '0' para o caminho esquerdo
    gerarTabelaCodigos(raiz->esq, tabela, codigo, nivel + 1); //chama recursivamente para o filho esquerdo
    codigo[nivel] = '1'; //adiciona '1' para o caminho direito
    gerarTabelaCodigos(raiz->dir, tabela, codigo, nivel + 1); //chama recursivamente para o filho direito
}

void codificarTexto(const string& texto, char tabela[256][256], char resultado[]){ //recebe o testo original a ser comprimido, a tabela de códigos de Huffman e um vetor 'resultado', onde será armazenado o texto codificado
    resultado[0] = '\0'; //inicializa o vetor resultado como uma string vazia
    for(char c : texto){ //percorre cada caractere do texto original
        strcat(resultado, tabela[(unsigned char)c]); //acessa o código binário correspondente ao caractere 'c' na tabela de códigos de Huffman e concatena no resultado
    } 
}

void decodificarTexto(const char* codificado, HuffmanNode* raiz, char resultado[]){ //recebe a sequência de bits codificada
    int resIndex = 0; //cria uma variável para marcar a posição onde vamos armazenar o caractere decodificado
    HuffmanNode* atual = raiz; //começa da raiz da Árvore de Huffman

    for(int i = 0; codificado[i] != '\0'; i++){ //percorre todos os bits da sequência comprimida (cada bit será '0' ou '1')
        if(codificado[i] == '0'){ //para cada bit
            atual = atual->esq; //vai para o filho esquerdo se for '0'
        }else{
            atual = atual->dir; //vai para o filho direito se for '1'
        }
        if(atual->esq == nullptr && atual->dir == nullptr){ //chegamos a um nó folha que é onde está guardado o caractere original
            resultado[resIndex++] = atual->caractere; //guarda o caractere no resultado decodificado e avança para a próxima posição
            atual = raiz; //volta para a raiz para começar a procurar o próximo caractere
        }
    }
    resultado[resIndex] = '\0'; //finaliza a string com o caractere nulo
}

void liberarHuffman(HuffmanNode* raiz){ //libera a memória alocada para a árvore de Huffman
    if(raiz == nullptr) return; 
    liberarHuffman(raiz->esq); //libera a subárvore esquerda
    liberarHuffman(raiz->dir); //libera a subárvore direita
    delete raiz; //libera o nó atual
}

void exportarParaLista(NoAvl* raiz, Lista& lista){ //exporta os caracteres e suas frequências da árvore AVL para a lista de Huffman
    if(raiz == nullptr) return;

    HuffmanNode* node = new HuffmanNode; //cria um novo nó de Huffman
    node->caractere = raiz->info; //atribui o caractere do nó AVL
    node->frequencia = raiz->qtdOcorrencias; //atribui a frequência do caractere
    node->esq = nullptr; // inicializa o filho esquerdo como nullptr
    node->dir = nullptr; // inicializa o filho direito como nullptr

    lista.inserir(node); //insere o nó de Huffman na lista, mantendo a ordem por frequência

    exportarParaLista(raiz->esq, lista); //chama recursivamente para o filho esquerdo
    exportarParaLista(raiz->dir, lista); //chama recursivamente para o filho direito
}

HuffmanNode* construirArvoreHuffman(Lista& lista){ //constrói a árvore de Huffman a partir da lista de nós
    while(lista.tamanho > 1){ //enquanto houver mais de um nó na lista
        HuffmanNode* no1 = lista.removerMin(); //remove o nó com menor frequência
        HuffmanNode* no2 = lista.removerMin(); //remove o próximo nó com menor frequência

        HuffmanNode* combinado = new HuffmanNode; //cria um novo nó combinado
        combinado->caractere = '\0'; //caractere não definido, pois é um nó interno
        combinado->frequencia = no1->frequencia + no2->frequencia; //soma as frequências dos dois nós removidos

        combinado->esq = no1; //define o filho esquerdo como o primeiro nó removido
        combinado->dir = no2; //define o filho direito como o segundo nó removido

        lista.inserir(combinado); //insere o nó combinado de volta na lista
    }
    if(lista.tamanho == 1){ //se restar apenas um nó na lista, esse é a raiz da árvore de Huffman
         return lista.elementos[0]; 
    }
    return nullptr; 
}

#endif