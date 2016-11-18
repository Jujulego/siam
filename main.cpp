// Importations
#include <iostream>

#include "alleg.h"
#include "affichable.h"
#include "console.h"
#include "coordonnee.h"
#include "montagne.h"
#include "plateau.h"

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());

    // Tests
    Plateau p;
    p.afficher();
    
    Console c;
    c.gotoLigCol(21, 0);
    
    // Libérations
    Affichable::liberer();

    return 0;
} END_OF_MAIN();
