#ifndef Transaction_H
#define Transaction_H

#include "Block.h"
#include "Blockchain.h"

//class Block;
//class Blockchain;
class TIterator;

class Transaction{
    friend class Block;
    friend class Blockchain;
    friend class TIterator;

    
    public:

    Transaction(const int origem, const int destino, const int _valor, const int _taxa): a(origem), b(destino), valor(_valor), taxa(_taxa), next(NULL) {}

    void imprime();

    private:

    int a;
    int b;
    int valor;
    int taxa;

    Transaction *next;
};

#endif