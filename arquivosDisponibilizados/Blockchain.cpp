#include "Blockchain.h"
#include "Block.h"
#include <iostream>
#include "vector"

Blockchain::Blockchain() {}

void Blockchain::criaBloco(transacoes *t, int n, int mx, int min){
    //chama o merge sort para ordenar as transações em ordem decrescente
	ordenaTransacoes(t, n);

////////////////////////////////////////////////////////////

    //calculamos o prevHesh que servirá como parametro para a criação de um novo bloco
    int posicao = 1;
    int hashant;
    if(first == NULL){ //caso nao tenha nenhum bloco na nossa blockchain, atibuimos o primeiro com posicao 1 e prevHesh 0
        posicao = 1;
        hashant = 0;
    }else{  //caso contrario, calculamos a posicao que será atribuida ao bloco sendo criado
        Block *b = first;
        while(b){
            posicao++;
            if(b->prox == NULL){
                hashant = b->getHash(); //e calculamos o hash do bloco anterior
            }
            b = b->prox;
        }

    }

    //se não existe nenhum bloco na minha lista, crio um bloco, minero esse bloco e ele será o primeiro e ultimo da minha lista
    if(first == NULL){
        Block *bloco = new Block(posicao, hashant , min);
    
        bloco->minerar("quiet");

        first = last = bloco;
        
    }else{  //caso contrario criamos esses blocos, adicionamos as transações, mineramos e damos um "push back" para o fim da lista
        Block *bloco = new Block(posicao, hashant , min);
        if(n!=0 && mx!=0){
            for(int i = 0; i<mx ; i++){
            bloco->addTransaction(t[i].origem, t[i].destino, t[i].valores, t[i].taxas);
            }
        }

        bloco->minerar("quiet");

        last->prox = bloco;
		last->prox->ant = last;
        last = last->prox;
    }
}

void Blockchain::ordenaTransacoes(transacoes *t, int n){
    transacoes *aux = new transacoes[n];

    mergeSortTransacoes(t, 0, n, aux);

    delete[] aux;
}

void Blockchain::mergeSortTransacoes(transacoes *t, int comeco, int fim, transacoes *aux){
    if(comeco==fim)
    return;
    else if(comeco<fim-1){
        int meio = (comeco+fim)/2;
        mergeSortTransacoes(t, comeco, meio, aux);
        mergeSortTransacoes(t, meio, fim, aux);
        mergeTransacoes(t, comeco, meio, fim, aux);
    }
}

void Blockchain::mergeTransacoes(transacoes *t, int comeco, int meio, int fim, transacoes *aux){
    int i = comeco;
    int j = meio;
    int k = 0;

    int tam = fim-comeco;

    while(i<meio && j<fim){
        if(t[i].taxas >= t[j].taxas){
            aux[k] = t[i];
            k++;
            i++;
        }
        else{
            aux[k] = t[j];
            k++;
            j++;
        }
    }

    while(i<meio){
        aux[k] = t[i];
        k++;
        i++;
    }
    while(j<fim){
        aux[k] = t[j];
        k++;
        j++;
    }
    for(k=0; k<tam; k++)
    t[comeco+k] = aux[k];
}

//percorre todos os bloco e todas as transações, imprimindo-as
void Blockchain::imprimeBlockchain() const {
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
                std::cout << "Transacoes:" << std::endl;
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

void Blockchain::alteraTransacao(int posBloco, int posTransaction, int novaOrigem, int novoDestino, int novoValor, int novaTaxa){
    Block *b = first;
    //chego no bloco que quero alterar
    while(b->pos != posBloco){
        b = b->prox;
    }
    int posTransacao = 1;

    //chego na transação que quero alterar
    Transaction *t = b->inicio;
    while(posTransacao != posTransaction){
        t = t->next;
        posTransacao++;
    }

    //altero os dados e minero esse bloco
    t->a = novaOrigem;
    t->b = novoDestino;
    t->valor = novoValor;
    t->taxa = novaTaxa;
    b->proofWork = 0;

    b->minerar("quiet");
}

void Blockchain::imprimeSaldo(int bloco) const{
    //vetor que armazena todos usuarios do bloco 1 até B e vetor para armazenar saldo
    std::vector<int> maiorU;
    std::vector<int> saldo;

    std::cout << "=====================" << std::endl;
    std::cout << "Saldo apos bloco " << bloco << std::endl;

    Block *b = first;
    Transaction *t = b->inicio;
    
    //enquanto a posicao de b for <= a do bloco que o usuario inseriu
    while(b->pos <= bloco){
        t = b->inicio;
        //insere o criador do bloco atual no vetor maiorU
        maiorU.push_back(b->criador);
            if(!b->inicio){ //se b nao tiver transacoes
                //enquanto b nao for null, proximo b nao for null, b nao tiver transações e posição de b diferente do bloco pedido
                //vai para o proximo bloco e insere o criador no vetor maiorU
	            while(b && b->prox && !b->inicio && (b->pos != bloco))
                    b = b->prox;
                    maiorU.push_back(b->criador);
                //Se b for valido, atribuimos t a seu inicio, caso contrario, t é nulo
                if(b)
                    t = b->inicio;
                else 
                    t = NULL;
                //agora, se t for valido, temos um while que insere a origem e o destino de cada transação do bloco no vetor maiorU
                if(t){
                    while(t){
                        maiorU.push_back(t->a);
                        maiorU.push_back(t->b);
                        t = t->next;
                    }
                }
                 if(b->prox)    //depois disso, caso o proximo bloco seja valido, passamos para ele
                    b = b->prox;
                    else break;
            }else{      //caso b tenha transações
                    while(t){                   //temos um while que insere a origem e o destino de cada transação do bloco no vetor maiorU
                        maiorU.push_back(t->a);
                        maiorU.push_back(t->b);
                        t = t->next;
                    }
                    if(b->prox) //depois disso, caso o proximo bloco seja valido, passamos para ele
                        b = b->prox;
                        else break;
                }
        }

    int maior = 0;

    //decide qual maior usuario percorrendo maiorU
    for(int i = 0; i < maiorU.size(); i++){
        if(maiorU[i] > maior)
        maior = maiorU[i];
    }

    //redimensiona vetor de saldo para o valor do maior usuario
    saldo.resize(maior+1);

    //volto para o primeiro bloco para realizar os calculos do saldo
    b = first;

    int j = 1;

    //enquanto a posicao de b for <= a do bloco que o usuario inseriu
    while(b->pos <= bloco){

        int recompensa = 256;

        //j começa como 1, entao o primeiro bloco terá recompensa de 256
        //o segundo de 128 e assim por diante
        for(int i = 1; i < j; i++)
        recompensa /= 2;
        j++;

        //soma a recompensa ao saldo do criador
        saldo[b->criador] += recompensa;

        //se esse bloco tiver transações, enquanto tiver, simula as transações somando e subtraindo dos saldos
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

        //se o proximo bloco for valido passamos para ele
        if(b->prox)
        b = b->prox;
        else break;
    }


    //imprime os saldos de cada usuario
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

   //copia a lista de blocos usando recursividade
   bloco->prox = copyBlock(ptr->prox);

   return bloco;
}

Blockchain & Blockchain::operator=(const Blockchain &other) {
	if(this==&other) 
    return *this; 
    destroy();

    this->first = copyBlock(other.first);
    this->last = other.last;
   
    return *this;
}

Blockchain::Blockchain(const Blockchain &other) {
	*this = other;
}

void Blockchain::destroy(const Block *ptr){
    if(ptr==NULL) return;
    destroy(ptr->prox); // destroy todos os blocos recursivamente 
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
    if(!ptr->next){ //caso as transações de um bloco acabe
        if(b && !b->prox->inicio){ //e se o proximo bloco nao tiver transações
            b = b->prox; //pulamos para esse prox bloco
	        while(b && !b->inicio)  //e enquanto nao houver transações, vamos passando para o proximo
                b = b->prox;
                //Se b for valido, atribuimos t a seu inicio, caso contrario, t é nulo
                if(b)
                    ptr = b->inicio;
                else 
                    ptr = NULL;
        }
        else{ //se o proximo bloco tem transações pulamos pra ele e atribuimos t a seu inicio
            b = b->prox;
            ptr = b->inicio;
        }
    }
    else{ //caso o bloco ainda tenha transações
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
    if(!b->inicio){ //se b nao tiver transações
	    while(b && !b->inicio) //enquanto b for valido e nao tiver transações
        b = b->prox; //pulamos para o prox bloco
        //Se b for valido, atribuimos t a seu inicio, caso contrario, t é nulo
        if(b)
        ptr = b->inicio;
        else 
        ptr = NULL;
    }
    return TransactionIterator(ptr, b); //cria um iterador para a primeira transação da blockchain recebendo
}

Blockchain::TransactionIterator Blockchain::transactionEnd() const {
    return TransactionIterator(NULL, first);
}