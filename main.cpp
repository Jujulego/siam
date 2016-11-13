// Importations
#include <allegro.h>

#include <iostream>

#include "affichable.h"
#include "helloworld.h"

int main() {
    // Initialisation
    Affichable::initier(ALLEGRO);
    
    // Tests
    HelloWorld h;
    h.afficher();
    h.attendre();
    
    // Libérations
    Affichable::liberer();
    
    return 0;
} END_OF_MAIN();
