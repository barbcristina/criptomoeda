#include <iostream>
#include <string>
#include "SHA256.h"
#include "Block.h"
#include "Blockchain.h"
#include "Transaction.h"
using namespace std;


//sua main devera ter esse include e usar a funcao imprimeTransacoes
//para imprimir...
//o arquivo imprimeTransacoes.h nao precisa ser enviado (o submitty ja tem uma copia dele, para garantir
//que ninguem vai modificar a funcao de impressao)
//O include abaixo pode ser mantido comentado quando voce for enviar a primeira parte do trabalho 
//e tambem enquanto voce nao termina a implementacao dos iteradores (caso contrario seu programa nao compilara)
#include "imprimeTransacoes.h"

int main() {
	std::string entrada;
	int pos, prevHash, criador, proofWork, n, a, b, valor, taxa, mx, minerador;

	cin >> entrada;

	if(entrada == "validarBloco"){
		//entradas para criaçao do bloco
		cin >> pos >> prevHash >> criador >> proofWork;
		Block *bloco = new Block(pos,prevHash,criador, proofWork);
		//numero de linhas com dados de transacoes
		std::cin >> n;
		//para criacao do vetor
	
		//cin para dados das transacoes
		for(int i = 0; i < n; i++){
			std::cin >> a >> b >> valor >> taxa;
			bloco->addTransaction(a, b, valor, taxa);
		}

		//testa o construtor de copia 
		Block *c = bloco;
		
		std::cout << bloco->getHash() << std::endl;
		std::cout << bloco->hashBinario() << std::endl;
		if(bloco->validaBloco() == true)
		std::cout << "OK" << std::endl;
		else 
		std::cout << "Nao minerado" << std::endl;

		delete bloco;

	}

	if(entrada == "minerarBloco"){
		std::string modo;
		std::cin >> modo;

			std::cin >> pos >> prevHash >> criador;
			Block *bloco = new Block(pos,prevHash,criador);

			std::cin >> n;

			for(int i = 0; i < n; i++){
			std::cin >> a >> b >> valor >> taxa;
			bloco->addTransaction(a, b, valor, taxa);
		}

		bloco->minerar(modo);
		std::cout << bloco->getProofWork() << std::endl;
		std::cout << bloco->getHash() << std::endl;
		std::cout << bloco->hashBinario() << std::endl;

		delete bloco;
	}

	if(entrada == "operacoes"){
		std::string operacao;
		//cria uma nova blockchain
		Blockchain b;
		//while para podermos realizazr varias operações
		while(cin >> operacao){
		if(operacao == "imprimeBlockchain"){
			b.imprimeBlockchain();
			Blockchain c = b; //teste do construtor de copia
		}
		else if(operacao == "imprimeTransacoes"){
			imprimeTransacoes(b);
		}
		else if(operacao == "alteraTransacao"){
			//é pedido a posição do bloco e a posução da transação que será alterada
			//e pede os 4 dados das transações
			int bloco, transacao, dados1, dados2, dados3, dados4;
			std::cin >> bloco >> transacao >> dados1 >> dados2 >> dados3 >> dados4;
			b.alteraTransacao(bloco, transacao, dados1, dados2, dados3, dados4);
		}
		else if(operacao == "imprimeSaldo"){
			int B;
			std::cin >> B;
			//simula todas as transações e recompensas de todos usuarios até o bloco B
			b.imprimeSaldo(B);
		}
		else if(operacao == "criarBloco"){
			// n = numero de transacoes, mx = numero maximo de transacoes por bloco
			std::cin >> n >> mx >> minerador;
			//struct que armazena as transacoes
			dadosTransacao t[n];
			for(int i = 0; i<n; i++){
				std::cin >> t[i].origem;
				std::cin >> t[i].destino;
				std::cin >> t[i].valores;
				std::cin >> t[i].taxas;
			}
			b.criaBloco(t, n, mx, minerador);	
			}
		} 
	}

}
