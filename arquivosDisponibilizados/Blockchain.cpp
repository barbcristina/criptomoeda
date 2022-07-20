#include "Blockchain.h"
#include "Block.h"
#include <iostream>
#include "algorithm"
#include "vector"

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
    
        bloco->minerar("quiet");

        first = last = bloco;
        
    }else{
        Block *bloco = new Block(posicao, hashant , min);
        if(n>=mx){
            for(int i = 0; i<mx ; i++){
            bloco->addTransaction(melhores[i].origem, melhores[i].destino, melhores[i].valores, melhores[i].taxas);
            }
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
                    std::cout << std::endl;
                }
            }
        }
    }

void Blockchain::alteraTransacao(int posBloco, int posTransaction, int novaOrigem, int novoDestino, int novoValor, int novaTaxa){
    Block *b = first;
    while(b->pos != posBloco){
        b = b->prox;
    }
    int posTransacao = 1;

    Transaction *t = b->inicio;
    while(posTransacao != posTransaction){
        t = t->next;
        posTransacao++;
    }

    t->a = novaOrigem;
    t->b = novoDestino;
    t->valor = novoValor;
    t->taxa = novaTaxa;
    b->proofWork = 0;

    b->minerar("quiet");
}

void Blockchain::imprimeSaldo(int bloco){
    std::vector<int> maiorU;
    std::vector<int> saldo;

    std::cout << "=====================" << std::endl;
    std::cout << "Saldo apos bloco " << bloco << std::endl;

    Block *b = first;
    Transaction *t = b->inicio;
    
    for(int i = 1; i <= bloco; i++){
        maiorU.push_back(b->criador);
        
        while(b->pos != bloco){
            if(!b->inicio){
	            while(b && !b->inicio && (b->pos != bloco)) 
                    b = b->prox;
                if(b)
                    t = b->inicio;
                else 
                    t = NULL;
            }   
                while(t){
                maiorU.push_back(t->a);
                maiorU.push_back(t->b);
                t = t->next;
            }
        }
    }

    int maior = 0;

    for(int i = 0; i < maiorU.size(); i++){
        std::cout << maiorU[i] << std::endl;
        if(maiorU[i] > maior)
        maior = maiorU[i];
    }

    saldo.resize(maior+1);

    b = first;

    int j = 1;

    while(b->pos <= bloco){

        int recompensa = 256;

        for(int i = 1; i < j; i++)
        recompensa /= 2;
        j++;

        saldo[b->criador] += recompensa;

        Transaction *ptr = b->inicio;
        if(ptr){
            while(ptr){
                saldo[ptr->a] -= ptr->valor;
                saldo[ptr->b] += ptr->valor;
                saldo[b->criador] += ptr->taxa;
                saldo[ptr->a] -= ptr->taxa;
                ptr = ptr->next;
            }
        }

        if(b->prox)
        b = b->prox;
        else break;
    }


    for(int i = 0; i < saldo.size(); i++){
        std::cout << i << " : " << saldo[i] << std::endl;
    }
    std::cout << "=====================" << std::endl;

}

Block * Blockchain::copyBlock(const Block *ptr){
    if(ptr==NULL) {
		return NULL;
	}
    Block *bloco = new Block(ptr->pos, ptr->prevHash, ptr->criador, ptr->proofWork);
    Transaction *ptr2 = ptr->inicio;
    while(ptr2){
      bloco->addTransaction(ptr2->a, ptr2->b, ptr2->valor, ptr2->taxa);
      ptr2 = ptr2->next;
   }


   bloco->prox = copyBlock(ptr->prox);

   return bloco;
}

Blockchain & Blockchain::operator=(const Blockchain &other) {
	if(this==&other) 
    return *this; 
    destroy();

    first = copyBlock(other.first);
    last = other.last;
   
    return *this;
}

Blockchain::Blockchain(const Blockchain &other) {
	*this = other;
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
    if(!ptr->next){
        if(b && !b->prox->inicio){
            b = b->prox;
	        while(b && !b->inicio)
                b = b->prox;
                if(b)
                ptr = b->inicio;
                else 
                ptr = NULL;
        }
        else{
            b = b->prox;
            ptr = b->inicio;
        }
    }
    else{
        ptr = ptr->next;
        }
	    return old;
}

bool TIterator::operator==(const TIterator &other) const{
    return ptr==other.ptr;
    }

bool TIterator::operator!=(const TIterator &other) const {
    return ptr!=other.ptr;
    }

Blockchain::TransactionIterator Blockchain::transactionBegin() const {
    Block *b = first;
    Transaction *ptr = first->inicio;
    if(!b->inicio){
	    while(b && !b->inicio) 
        b = b->prox;
        if(b)
        ptr = b->inicio;
        else 
        ptr = NULL;
    }
    return TransactionIterator(ptr, b);
}

Blockchain::TransactionIterator Blockchain::transactionEnd() const {
    return TransactionIterator(NULL, first);
}