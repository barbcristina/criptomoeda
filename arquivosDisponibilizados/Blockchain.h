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
    friend class TIterator;
    
    public:

    typedef TIterator TransactionIterator;

    Blockchain();

    void imprimeBlockchain();

    void alteraTransacao(int posBloco, int posTransaction, int novaOrigem, int novoDestino, int novoValor, int novaTaxa);

    void imprimeSaldo(int bloco);

    //void mergeTransactions(transacoes *t, int p, int q, int r);

    void criaBloco(transacoes *t, int n, int mx, int min);

    Blockchain(const Blockchain &);

	Blockchain & operator=(const Blockchain &other);

    Block * copyBlock(const Block *ptr);

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
	TIterator(Transaction *ptr_, Block *b_): ptr(ptr_), b(b_) {}
	Transaction &operator*() {return *ptr;}
	const Transaction &operator*() const {return *ptr;} 

	bool operator==(const TIterator &other) const;
	bool operator!=(const TIterator &other) const;

    TIterator operator++(int);

	
private:
	Transaction *ptr;
    Block *b;
};

#endif