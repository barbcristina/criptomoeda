#include "Blockchain.h"
#include "Block.h"
#include <iostream>

void Blockchain::criaBloco(int n, int mx, int min, transacoes *t){
    transacoes aux[n];
	transacoes melhores[mx];

    for(int i = 0; i<n; i++){
		aux[i].origem = t[i].origem;
		aux[i].destino = t[i].destino;
		aux[i].valores = t[i].valores;
		aux[i].taxas = t[i].taxas;
	}

    for(int i = 0; i < mx; i++){
		int maior = 0;
		int pos = 0;

		for(int j = 0; j < n; j++){
			if(aux[j].taxas > maior){
				maior = aux[j].taxas;
				pos = j;
				}
			}
	
			melhores[i] = aux[pos];
			aux[pos].taxas = -1;
		}

////////////////////////////////////////////////////////////

    if(pos = 1){
        Block *bloco = new Block(pos, prevhash , min);
        for(int i = 0; i>mx ; i++)
        bloco->addTransaction(0, 0, 0, 0);

        bloco->minerar("quiet");
        prevhash = bloco->getHash();

        if(first == last)
        first = last = bloco;
        else{
        last->prox = bloco;
		last->prox->ant = last;
        last = last->prox;
        }
    }else{
        Block *bloco = new Block(pos, prevhash , min);
        for(int i = 0; i>mx ; i++)
        bloco->addTransaction(melhores[i].origem, melhores[i].destino, melhores[i].valores, melhores[i].taxas);

        bloco->minerar("quiet");
        prevhash = bloco->getHash();

        if(first == last)
        first = last = bloco;
        else{
        last->prox = bloco;
		last->prox->ant = last;
        last = last->prox;
        }
    }

////////////////////////////////////////////////////////////
        minerador = min;
        pos++;

    }

void Blockchain::imprime(){
        Block *ptr = first;
        Transaction *t = ptr->inicio;
        if(first == NULL){
            std::cout << "=====================" << std::endl;
            std::cout << std::endl;
             std::cout << "=====================" << std::endl;
        }
        else{
        while(!ptr){
            std::cout << "=====================" << std::endl;
            std::cout << "---------------------" << std::endl;
            std::cout << "Pos: " << pos << std::endl;
            std::cout << "Prev hash: " << prevhash << std::endl;
            std::cout << "Criador: " << minerador << std::endl;
            std::cout << "Transacoes: " << std::endl;
            if(pos != 1){
                while(!t)
                std::cout << t->a << " -> " << t->b << " (valor: " << t->valor << " , taxa: " << t->taxa << ")" << std::endl;
                t = t->next;
            }
            std::cout << "Proof of work: " << ptr->getProofWork() << std::endl;
            std::cout << "Hash: " << ptr->getHash() << std::endl;
            std::cout << "---------------------" << std::endl;
            }
        }
    }