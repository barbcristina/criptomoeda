#ifndef Blockchain_H
#define Blockchain_H

#include "Block.h"
//#include "imprimeTransacoes.h"
#include "Transaction.h"

class Block;
class Transaction;

struct transacoes{
	int origem;
	int destino;
	int valores;
	int taxas;
};


class Blockchain{
    friend class Transaction;
    private:

    int pos = 1;
    int prevhash = 0;
    int minerador;

    public:

    Blockchain();

    void imprime();

    void criaBloco(int n, int mx, int min, transacoes *t);


    Block *first = NULL;
    Block *last = NULL;
};

#endif