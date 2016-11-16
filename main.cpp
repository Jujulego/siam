// Importations
#include "alleg.h"

#include <iostream>

#include "alleg.h"
#include "affichable.h"
#include "console.h"
#include "helloworld.h"
#include "plateau.h"

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());

    // Tests
    Plateau p;
    p.afficher();
    
    while (!allegro::key[allegro::KEY_ESC]) {
        allegro::rest(100);
    }

    // Libérations
    Affichable::liberer();

    return 0;
} END_OF_MAIN();
