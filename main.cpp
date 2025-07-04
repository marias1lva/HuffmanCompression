#include <iostream>
#include <string>
#include "avl.hpp"
#include "huffman.hpp"
using namespace std;

#define MAX_TEXT 1000

int main(){
    string texto;
    cout << "Digite o texto para compressao: ";
    getline(cin, texto); //para permitir espaços e linhas inteiras

    NoAvl* raiz = nullptr; //cria a raiz da árvore AVL(nula inicialmente)

    for(char c : texto){ //para cada caractere do texto
        raiz = inserir(raiz, c); //insere o caractere na árvore AVL
    } //se o caractere já existir, aumenta a contagem (qtdOcorrencias) e mantém a AVL balanceada automaticamente

    Lista lista; //exporta os nós da AVL para uma Lista ordenada por frequência e prepara a lista para contruir a árvore de Huffman
    exportarParaLista(raiz, lista);

    HuffmanNode* huffmanRaiz = construirArvoreHuffman(lista); //constrói a Árvore de Huffman usando a lista: combina os dois nós de menor frequência até restar apenas a raiz

    //cria uma tabela para armazenar os códigos binários gerados
    char tabela[256][256] = {""}; 
    char codigo[256];
    gerarTabelaCodigos(huffmanRaiz, tabela, codigo, 0);
    cout << "\n---------------------------------------\n";
    cout << "\nTabela de codigos de Huffman:\n";
    cout << "Letra | Codigo\n";
    cout << "----- | ----- \n";
    for(int i = 0; i < 256; i++){
        if(strlen(tabela[i]) > 0){
            if(isprint(i)){
                cout << "  '" << (char)i << "' | " << tabela[i] << endl;
            }else{
                cout << " (ASCII " << i << ") | " << tabela[i] << endl;
            }
        }
    }

    //coloca o texto original em uma sequência de bits com base na tabela e mostra o texto codificado na tela
    char codificado[MAX_TEXT * 8];
    codificarTexto(texto, tabela, codificado);

    cout << "\nTexto codificado: " << codificado << endl;

    //decodifica a sequência de bits de volta para o texto original e mostra o texto decodificado na tela
    char decodificado[MAX_TEXT];
    decodificarTexto(codificado, huffmanRaiz, decodificado);

    cout << "\nTexto decodificado: " << decodificado << endl;

    //libera a memória alocada para a árvore AVL e a árvore de Huffman
    liberar(raiz);
    liberarHuffman(huffmanRaiz);

    return 0;
}
