Eu li as regras

Bárbara Cristina Fonseca de Souza 	102037

Parte 1
Para o addTransaction usei como referencia a funcão push_back do Mylist.h;
Para a função validaBloco, segui uma dica que o senhor deu no moodle de fazer um bitwise and ao inves de comparar posicao por posicao de strings;
Para a função hashBinario pesquisei como transformar decimais negativos em binario e esse foi o site que usei:
https://www.out4mind.com/numeros-inteiros-negativos-em-binario/
O construtor de copia, destrutor, função destroy e clear são inspirados nos que vimos em aula;
Para erros de vazamento de memória usei o valgrind, já que ele diz a origem do erro;


Parte 2
Para a função addBlocos, usei o push_back da lista duplamente encadeada como referencia;
O destrutor tambem foi inspirado no que vimos em aula;
O merge sort usado para escolher as melhores transaçoes foi adaptado do que vimos em aula;
E parte do iterador tambem foi adaptado do arquivo das praticas;


Pergunta 1: Quantas Capicoins existirão no mundo? (supondo que aceitamos apenas valores inteiros, o primeiro bloco recompensa 256 Capicoins
e esse valor cai pela metade a cada novo bloco).
Resposta: Representando o numero total como a soma das recompensas até que recompensa/2 = 0 temos:
256 + 128 + 64 + 32 + 16 + 8 + 4 + 2 + 1 = 511 moedas capicoins no total.

Pergunta 2: Dadas duas blockchains válidas (onde cada bloco contém o hash correto do bloco anterior),
é possível ver se as duas são iguais de forma muito eficiente: basta comparar o hash do último bloco das duas.
Por que isso “garante” a igualdade (responda no seu README)? 
Resposta: O calculo do hash de um bloco, leva em consideração TODOS os dados do seu bloco atual, incluindo o prevHash,
que é o hash do bloco anterior. Assim se algum valor de algum bloco for alterado, o hash mudaria drasticamente 
e com isso o hash de todos os blocos posteriores teriam que ser alterados tambem, porem como já vimos, isso custa muito caro computacionalmente.
