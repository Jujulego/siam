// Importations
#include <iostream>

#include "console.h"

int main() {
    Console c;
    
    c.setColor(COLOR_GREEN);
    std::cout << "Salut le monde !" << std::endl;
    c.setColor();
    
    return 0;
}
