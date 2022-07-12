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
//#include "imprimeTransacoes.h"

int main() {
	std::string entrada;
	int pos, prevHash, criador, proofWork, n, a, b, valor, taxa, mx, minerador;

	cin >> entrada;

	if(entrada == "validarBloco"){
		//entradas para criaçao do bloco
		cin >> pos >> prevHash >> criador >> proofWork;
		Block bloco(pos,prevHash,criador, proofWork);
		//numero de linhas com dados de transacoes
		std::cin >> n;
		//para criacao do vetor
	
		//cin para dados das transacoes
		for(int i = 0; i < n; i++){
			std::cin >> a >> b >> valor >> taxa;
			bloco.addTransaction(a, b, valor, taxa);
		}

		Block c = bloco;
		
		std::cout << bloco.getHash() << std::endl;
		std::cout << bloco.hashBinario() << std::endl;
		if(bloco.validaBloco() == true)
		std::cout << "OK" << std::endl;
		else 
		std::cout << "Nao minerado" << std::endl;

	}

	if(entrada == "minerarBloco"){
		std::string modo;
		std::cin >> modo;

			std::cin >> pos >> prevHash >> criador;
			Block bloco(pos,prevHash,criador);

			std::cin >> n;

			for(int i = 0; i < n; i++){
			std::cin >> a >> b >> valor >> taxa;
			bloco.addTransaction(a, b, valor, taxa);
		}

		bloco.minerar(modo);
		std::cout << bloco.getProofWork() << std::endl;
		std::cout << bloco.getHash() << std::endl;
		std::cout << bloco.hashBinario() << std::endl;
	}

	if(entrada == "operacoes"){
		std::string operacao;
		Blockchain b;
		cin >> operacao;
		
		if(operacao == "criarBloco"){
			std::cin >> n >> mx >> minerador;
			int *vec = new int[mx];
			int maior = 0;
			int maiorant = 0;
			int m = 0;
			transacoes t[n];
			transacoes aux[n];
			transacoes melhores[mx];
			for(int i = 0; i<n; i++){
				std::cin >> t[i].origem;
				std::cin >> t[i].destino;
				std::cin >> t[i].valores;
				std::cin >> t[i].taxas;
			}
			b.imprime();	
		} 
	}

}
