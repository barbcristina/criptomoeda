#ifndef Block_H
#define Block_H

#include "SHA256.h"
#include <string>

class Transaction{
    public:

    Transaction(const int origem, const int destino, const int _valor, const int _taxa): a(origem), b(destino), valor(_valor), taxa(_taxa), next(NULL) {}
    int a;
    int b;
    int valor;
    int taxa;

    Transaction *next;
};

class Block{
    private:
    int pos;
    int prevHash;
    int criador;
    int proofWork;

    public:

    Transaction *inicio = NULL;
    Transaction *fim = NULL;
    
    Block(int _pos, int _prevHash, int _criador): pos(_pos), prevHash(_prevHash), criador(_criador), proofWork(0) {}

    Block(int _pos, int _prevHash, int _criador, int _proofWork): pos(_pos), prevHash(_prevHash), criador(_criador), proofWork(_proofWork) {}

    void addTransaction(int _a, int _b, int valor1, int taxa1);

    void minerar(std::string tipo);

    bool validaBloco();

    std::string hashBinario();

    int getHash();

    int getProofWork();

    void create();

    //Construtor de copia
	Block(const Block &);
	Block & operator=(const Block &other);

    void clear();

    void verbose();

    void destroy(const Transaction *ptr);

    void destroy();

    ~Block();

    Block *anterior = NULL;
    Block *next = NULL;
};

#endif