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

    Transaction(int origem, int destino, int _valor, int _taxa): from(origem), to(destino), valor(_valor), taxa(_taxa), next(NULL) {}

    void imprime();

    private:

    int from;
    int to;
    int valor;
    int taxa;

    Transaction *next;
};

#endif