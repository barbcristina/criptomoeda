#include <iostream>
#include "Block.h"
#include "SHA256.h"
void Block::addTransaction(int _a, int _b, int valor1, int taxa1){
    if(inicio==NULL){
        inicio = fim = new Transaction(_a, _b, valor1, taxa1);
    }else{
        Transaction *newTransaction = new Transaction(_a, _b, valor1, taxa1);
        fim->next = newTransaction;
		  fim = fim->next;
    }
 }

 void Block::getQtdTransacoes(int qtd){
      nTransacoes = qtd;
 }

 int Block::getHash(){
   //cria um vetor com exatamente a quantidade de elementos necessarias
   int *v = new int[3+(nTransacoes*4)];
   int i = 3;
   v[0] = pos;
   v[1] = prevHash;
   v[2] = criador;
   Transaction *ptr = inicio;
   while(ptr){
      v[i] = ptr->a;
      i++;
      v[i] = ptr->b;
      i++;
      v[i] = ptr->valor;
      i++;
      v[i] = ptr->taxa;
      i++;
      ptr = ptr->next;
   }

    v[i] = proofWork;
    SHA256 aux;
    int hash = aux.calcula(v, i+1);
    delete [] v;
    return hash;
 }

 bool Block::validaBloco(){
   bool valido = false;
   if((getHash() & 1023) == 0)
   valido = true;
   return valido;
 }

 std::string Block::hashBinario(){
   int hash = getHash();
   std::string hashbinario;
   if(hash >= 0){
   while (hash != 0){
        hashbinario += ( hash % 2 == 0 ? "0" : "1" );
         hash /= 2;
      }
   }else if(hash < 0){
      while (hash != 0){
        hashbinario += ( hash % 2 == 0 ? "1" : "0" );
         hash /= 2;
      }
   }
    hashbinario += "1";
    return hashbinario;
 }

void Block::minerar(std::string tipo){
   while(!validaBloco()){
      if(tipo == "verbose")
      verbose();
      proofWork++;
   }
      if(tipo == "verbose")
      verbose();
}

int Block::getProofWork(){
   return proofWork;
}

void Block::verbose(){
   int *v = new int[3+(nTransacoes*4)];
   int i = 3;
   v[0] = pos;
   v[1] = prevHash;
   v[2] = criador;
   Transaction *ptr = inicio;
   while(ptr){
      v[i] = ptr->a;
      i++;
      v[i] = ptr->b;
      i++;
      v[i] = ptr->valor;
      i++;
      v[i] = ptr->taxa;
      i++;
      ptr = ptr->next;
   }
      v[i] = proofWork;

   for(int j = 0; j <= i; j++)
   std::cout << v[j] << " ";
   std::cout << std::endl;
   std::cout << hashBinario() << std::endl;
   std::cout << std::endl;
   delete []v;
}

 Block::~Block(){
   Transaction *aux = inicio;
	while(aux!=NULL){
		delete aux;
		aux = aux->next;
   }
 }


