#ifndef Transaction_H
#define Transaction_H
#include "Block.h"
#include "Blockchain.h"
//#include "imprimeTransacoes.h"

class Block;

class Transaction{
    friend class Block;
    friend class Blockchain;

    
    public:

    Transaction(const int origem, const int destino, const int _valor, const int _taxa): a(origem), b(destino), valor(_valor), taxa(_taxa), next(NULL) {}

    private:

    int a;
    int b;
    int valor;
    int taxa;

    Transaction *next;
};

#endif