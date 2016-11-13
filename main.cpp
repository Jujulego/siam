// Importations
#include <allegro.h>

#include <iostream>

#include "affichable.h"
#include "console.h"
#include "helloworld.h"

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());
    
    // Tests
    HelloWorld h;
    h.afficher();
    h.attendre();
    
    // Libérations
    Affichable::liberer();
    
    return 0;
} END_OF_MAIN();
