#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
using namespace std;

struct NoAvl{
    char info; //caractere armazenado
    int altura; //altura do nó
    int qtdOcorrencias; //frequência do caractere
    NoAvl *esq = nullptr, *dir = nullptr; //ponteiros para os filhos esquerdo e direito
};

void prefixado(NoAvl *raiz){ //árvore em pré-ordem
    if(raiz == nullptr) return;
    cout << raiz->info << "(" << raiz->qtdOcorrencias << ") "; 
    prefixado(raiz->esq);   
    prefixado(raiz->dir);
}

void infixado(NoAvl *raiz){ //árvore em ordem (alfabética)
    if(raiz == nullptr) return;
    infixado(raiz->esq);
    cout << raiz->info << "(" << raiz->qtdOcorrencias << ") ";
    infixado(raiz->dir);
}

void posfixado(NoAvl *raiz){ //árvore em pós-ordem
    if(raiz == nullptr) return;
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    cout << raiz->info << "(" << raiz->qtdOcorrencias << ") ";
}

void liberar(NoAvl *raiz){ //libera a memória alocada para a árvore
    if(raiz == nullptr) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    delete raiz;
}

int getAltura(NoAvl *raiz){ //retorna a altura do nó
    return(raiz == nullptr) ? 0 : raiz->altura; //se o nó for nulo, a altura é 0
}

int calcularAltura(NoAvl *raiz){ //calcula a altura do nó
    int altE = getAltura(raiz->esq); //altura do filho esquerdo
    int altD = getAltura(raiz->dir); //altura do filho direito
    return(altE > altD) ? altE + 1 : altD + 1; //retorna a altura máxima entre os filhos + 1
}

NoAvl *rotacaoSimplesDireita(NoAvl *k){ //rotaciona o nó k para a direita
    NoAvl *x = k->esq; 
    NoAvl *t2 = x->dir;

    k->esq = t2;
    x->dir = k;
    k->altura = calcularAltura(k);
    x->altura = calcularAltura(x);
    return x;
}

NoAvl *rotacaoSimplesEsquerda(NoAvl *k){ //rotaciona o nó k para a esquerda
    NoAvl *y = k->dir;
    NoAvl *t2 = y->esq;

    k->dir = t2;
    y->esq = k;
    k->altura = calcularAltura(k);
    y->altura = calcularAltura(y);
    return y;
}

NoAvl *rotacaoDuplaDireita(NoAvl *k){ //usada quando o filho da esquerda está desbalanceado para a direita
    k->esq = rotacaoSimplesEsquerda(k->esq);
    return rotacaoSimplesDireita(k);
}

NoAvl *rotacaoDuplaEsquerda(NoAvl *k){ //usada quando o filho da direita está desbalanceado para a esquerda
    k->dir = rotacaoSimplesDireita(k->dir);
    return rotacaoSimplesEsquerda(k);
}

NoAvl *rotacaoAVL(NoAvl *k){ //decide automaticamente qual rotação aplicar
    if(getAltura(k->esq) > getAltura(k->dir)){ 
        NoAvl *x = k->esq;
        if(getAltura(x->esq) >= getAltura(x->dir))
            return rotacaoSimplesDireita(k);
        else
            return rotacaoDuplaDireita(k);
    }else{
        NoAvl *y = k->dir;
        if(getAltura(y->dir) >= getAltura(y->esq))
            return rotacaoSimplesEsquerda(k);
        else
            return rotacaoDuplaEsquerda(k);
    }
}

NoAvl *inserir(NoAvl *raiz, char valor){ //insere um novo nó na árvore AVL
    if(raiz == nullptr){
        raiz = new NoAvl;
        raiz->info = valor;
        raiz->altura = 1;
        raiz->qtdOcorrencias = 1;
        return raiz;
    }
    if(valor == raiz->info){
        raiz->qtdOcorrencias++;
    }else if(valor < raiz->info){
        raiz->esq = inserir(raiz->esq, valor);
    }else{
        raiz->dir = inserir(raiz->dir, valor);
    }

    raiz->altura = calcularAltura(raiz);
    int altE = getAltura(raiz->esq);
    int altD = getAltura(raiz->dir);
    if(abs(altE - altD) == 2)
        raiz = rotacaoAVL(raiz);
    return raiz;
}

void mostrar_arvore(NoAvl *raiz, int tab){
    cout << endl;
    for(int i = 0; i < tab; i++) cout << " ";
    if(raiz == nullptr){
        cout << "*";
        return;
    }
    cout << raiz->info << "(" << raiz->qtdOcorrencias << ")";
    mostrar_arvore(raiz->esq, tab + 3);
    mostrar_arvore(raiz->dir, tab + 3);
}

#endif
