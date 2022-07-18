#include "Blockchain.h"
#include "Block.h"
#include <iostream>
#include "algorithm"

Blockchain::Blockchain() {}

void Blockchain::criaBloco(int n, int mx, int min, transacoes *t){
	transacoes melhores[mx];

    for(int i = 0; i < mx; i++){
		int maior = 0;
		int pos = 0;

		for(int j = 0; j < n; j++){
			if(t[j].taxas > maior){
				maior = t[j].taxas;
				pos = j;
				}
			}
	
			melhores[i] = t[pos];
			t[pos].taxas = -1;
		}

////////////////////////////////////////////////////////////
    int posicao = 1;
    int hashant;
    if(first == NULL){
        posicao = 1;
        hashant = 0;
    }else{
        Block *b = first;
        while(b){
            posicao++;
            if(b->prox == NULL){
                hashant = b->getHash();
            }
            b = b->prox;
        }

    }

    if(first == NULL){
        Block *bloco = new Block(posicao, hashant , min);
        for(int i = 0; i>mx ; i++)
        bloco->addTransaction(0, 0, 0, 0);

        bloco->minerar("quiet");

        first = last = bloco;
        
    }else{
        Block *bloco = new Block(posicao, hashant , min);
        for(int i = 0; i<mx ; i++){
        bloco->addTransaction(melhores[i].origem, melhores[i].destino, melhores[i].valores, melhores[i].taxas);
        }

        bloco->minerar("quiet");

        last->prox = bloco;
		last->prox->ant = last;
        last = last->prox;
    }
}

void Blockchain::imprimeBlockchain(){
        if(first == NULL){
            std::cout << "=====================" << std::endl;
            std::cout << std::endl;
            std::cout << "=====================" << std::endl;
        }
        else if(first != NULL){
            Block *ptr = first;
            std::cout << "=====================" << std::endl;
            while(ptr){
                std::cout << "---------------------" << std::endl;
                std::cout << "Pos: " << ptr->pos << std::endl;
                std::cout << "Prev hash: " << ptr->prevHash << std::endl;
                std::cout << "Criador: " << ptr->criador << std::endl;
                std::cout << "Transacoes: " << std::endl;
                if(ptr->inicio != NULL){
                    Transaction *t = ptr->inicio;
                    if(first != NULL){
                        while(t){
                            std::cout << t->a << " -> " << t->b << " (valor: " << t->valor << " , taxa: " << t->taxa << ")" << std::endl;
                            t = t->next;
                        }
                    }
                }
                std::cout << "Proof of work: " << ptr->getProofWork() << std::endl;
                std::cout << "Hash: " << ptr->getHash() << std::endl;
                std::cout << "---------------------" << std::endl;
                ptr = ptr->prox;
                if(ptr != NULL){
                std::cout << "          ^" << std::endl;
                std::cout << "          |" << std::endl;
                std::cout << "          v" << std::endl;
                }else{
                    std::cout << std::endl;
                    std::cout << "=====================" << std::endl;
                }
            }
        }
    }

void Blockchain::destroy(const Block *ptr){
    if(ptr==NULL) return;
    destroy(ptr->prox);
    delete ptr;
}

void Blockchain::destroy(){
    destroy(first);
}

Blockchain::~Blockchain(){
    destroy();
}

TIterator TIterator::operator++(int) {
    TIterator old = *this;
	ptr = ptr->next;
	return old;
}

bool TIterator::operator==(const TIterator &other) const{
    return ptr==other.ptr;
    }

bool TIterator::operator!=(const TIterator &other) const {
    return ptr!=other.ptr;
    }

Blockchain::TransactionIterator Blockchain::transactionBegin() const {
    return TransactionIterator(first->inicio);
}

Blockchain::TransactionIterator Blockchain::transactionEnd() const {
    return TransactionIterator(NULL);
}