#include "Transaction.h"
#include "Block.h"
#include <iostream>

void Transaction::imprime(){
    std::cout << from << " -> " << to << " (valor: " << valor << " , " << "taxa: " << taxa << ")" << std::endl;
}