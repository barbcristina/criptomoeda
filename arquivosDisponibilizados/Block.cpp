#include <iostream>
#include "Block.h"
#include "SHA256.h"

//push back de uma lista encadeada de transaçoes
void Block::addTransaction(int _a, int _b, int valor1, int taxa1){
    if(inicio==NULL){
        inicio = fim = new Transaction(_a, _b, valor1, taxa1);
    }else{
        Transaction *newTransaction = new Transaction(_a, _b, valor1, taxa1);
        fim->next = newTransaction;
		  fim = fim->next;
    }
 }

 int Block::getHash() const{
   //cria um vetor com exatamente a quantidade de elementos necessarias, varre todos os dados do bloco e chama calcula
   int *v = new int[4+(size()*4)];
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
    delete ptr;
    return hash;
 }

 bool Block::validaBloco(){
   bool valido = false;
   //segui a dica que o senhor deu no moodle e fiz um bitwise and com um numero que tem os 10 ultimos bits 1
   if((getHash() & 1023) == 0)
   valido = true;
   return valido;
 }

 std::string Block::hashBinario(){
   int hash = getHash();
   std::string aux = "00000000000000000000000000000000";
   std::string hashbinario;
   //caso o hash seja positivo
   if(hash >= 0){
   for(int i = 0; i < 32; i++){
        hashbinario += ( hash % 2 == 0 ? "0" : "1" );    //Monta uma string com os restos das divisoes
         hash /= 2;
      }

      int k = hashbinario.length();
      for(int j = 0; j < 32; j++){
         aux[j] = hashbinario[k-1];    //Como hashbinario fica invertido devido a ordem das operacoes
         k--;                          //usaremos uma string aux para que ele esteja ordenado corretamente
      }
   //se o hash for negativo
   }else if(hash < 0){
      for(int i = 0; i < 32; i++){
        hashbinario += ( hash % 2 == 0 ? "1" : "0" ); //valores invertidos
         hash /= 2;
      }

      int k = hashbinario.length();
      for(int j = 0; j < 32; j++){
         aux[j] = hashbinario[k-1];
         k--;
      }

      //while que faz a "soma" do 1 no hash binario
      int h = aux.length();
      while(true){
         if(aux[h] == '0'){
            aux[h] = '1';
            break;
      }else if(aux[h] == '1'){
            aux[h] = '0';
         }
         h--;
      }
   }

    hashbinario = aux;   
    return hashbinario;
 }

void Block::minerar(std::string tipo){
   //testa proofworks de 0 a n até achar um que termine com 10 bits 0
   while(!validaBloco()){
      if(tipo == "verbose")
      verbose();
      proofWork++;
   }
      if(tipo == "verbose")
      verbose();
}

int Block::getProofWork() const{
   return proofWork;
}

//funcao para o modo verbose, responsavel por montar o array com todos os dados do meu bloco e imprimi-lo junto com o hash binario
void Block::verbose(){

   int *v = new int[4+(size()*4)];
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

   for(int k = 0; k <= i; k++)
   std::cout << v[k] << " ";
   std::cout << std::endl;
   std::cout << hashBinario() << std::endl;
   std::cout << std::endl;
   delete ptr;
   delete []v;
}

int Block::size() const{
   int j = 0;
   Transaction *elems = inicio;
   //conta quantas transações existem
   while(elems){
      elems = elems->next;
      j++;
   }
   delete elems;

   return j;
}

void Block::clear() {
	destroy();
	create();
}

Block & Block::operator=(const Block &other) {
	if(this==&other) 
   return *this; 
   destroy();
	clear();

   Block *bloco = new Block(other.pos, other.prevHash, other.criador, other.proofWork);

   Transaction *ptr = other.inicio;
   while(ptr){
      bloco->addTransaction(ptr->a, ptr->b, ptr->valor, ptr->taxa);
      ptr = ptr->next;
   }
   return *this;
}

Block::Block(const Block &other) {
	create();
	*this = other;
}

void Block::create() {
	inicio = fim = NULL;
}

//destroy com recursividade
void Block::destroy(const Transaction *ptr){
   if(ptr==NULL) return;
    destroy(ptr->next);
    delete ptr;
}

void Block::destroy(){
   destroy(inicio);
 }

//destrutor
Block::~Block() { destroy(); };



