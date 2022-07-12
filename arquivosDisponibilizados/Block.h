#ifndef Block_H
#define Block_H

#include "SHA256.h"
#include <string>
#include "Transaction.h"
#include "Blockchain.h"
//#include "imprimeTransacoes.h"

class Transaction;

class Block{
    friend class Transaction;
    friend class Blockchain;

    private:
    int pos;
    int prevHash ;
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

    void verbose();

    void create();

	Block(const Block &);

	Block & operator=(const Block &other);

    void clear();

    void destroy(const Transaction *ptr);

    void destroy();

    ~Block();

    Block *prox;
    Block *ant;

};

#endif