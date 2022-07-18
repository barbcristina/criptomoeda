#ifndef Blockchain_H
#define Blockchain_H

#include "Block.h"
#include "Transaction.h"

class Block;
class Transaction;
class TIterator;

struct transacoes{
	int origem;
	int destino;
	int valores;
	int taxas;
};


class Blockchain{
    friend class Transaction;
    
    public:

    typedef TIterator TransactionIterator;

    Blockchain();

    void imprimeBlockchain();

    void criaBloco(int n, int mx, int min, transacoes *t);

    void destroy(const Block *ptr);
    void destroy();

    ~Blockchain();

    TransactionIterator transactionBegin() const;
    TransactionIterator transactionEnd() const;


    Block *first = NULL;
    Block *last = NULL;
};

class TIterator {
	friend class Blockchain;
public:
	TIterator(Transaction *ptr_): ptr(ptr_){}
	Transaction &operator*() {return *ptr;}
	const Transaction &operator*() const {return *ptr;} 

	bool operator==(const TIterator &other) const;
	bool operator!=(const TIterator &other) const;

    TIterator operator++(int);

	
private:

	Transaction *ptr;
};

#endif