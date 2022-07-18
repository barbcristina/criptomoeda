#include "Transaction.h"
#include "Block.h"
#include <iostream>

void Transaction::imprime(){
    std::cout << a << " -> " << b << "(valor: " << valor << " , " << "taxa: " << taxa << ")" << std::endl;
}