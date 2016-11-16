// Importations
#include "alleg.h"

#include <iostream>

#include "affichable.h"
#include "console.h"
#include "helloworld.h"
#include "plateau.h"

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());

    // Tests
 /*   HelloWorld h;
    h.afficher();
    h.attendre();*/
    Plateau p;
    p.afficher();

    // Libérations
    Affichable::liberer();

    return 0;
} END_OF_MAIN();
