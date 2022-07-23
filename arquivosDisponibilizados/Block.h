#ifndef Block_H
#define Block_H

#include "SHA256.h"
#include <string>
#include "Transaction.h"
#include "Blockchain.h"

class Block{
    friend class Transaction;
    friend class Blockchain;

    private:

    int pos;
    int prevHash ;
    int criador;
    int proofWork;

    void create();
    void destroy(const Transaction *ptr);
    void destroy();


    public:

    Transaction *inicio = NULL;
    Transaction *fim = NULL;

    Block *prox;
    Block *ant;
    
    Block(int _pos, int _prevHash, int _criador): pos(_pos), prevHash(_prevHash), criador(_criador), proofWork(0), prox(NULL), ant(NULL) {}

    Block(int _pos, int _prevHash, int _criador, int _proofWork): pos(_pos), prevHash(_prevHash), criador(_criador), proofWork(_proofWork), prox(NULL), ant(NULL) {}

    void addTransaction(int _a, int _b, int valor1, int taxa1);

    void minerar(std::string tipo);

    bool validaBloco();

    std::string hashBinario();

    int getHash() const;

    int size() const;

    void clear();

    int getProofWork() const;

    void verbose();

	Block(const Block &);

	Block & operator=(const Block &other);

    ~Block();

};

#endif