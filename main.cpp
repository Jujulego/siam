// Importations
#include <allegro.h>
#include <iostream>

#include "affichable.h"
#include "console.h"
#include "coordonnee.h"
#include "pion.h"
#include "plateau.h"

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());

    // Tests
    Plateau p;
    p.placer(RHINO, Coordonnees('A', 4), BAS);
    p.placer(ELEPH, Coordonnees('D', 3), DROITE);
    p.afficher();

    Console c;
    c.gotoLigCol(40, 0);

    // Libérations
    Affichable::liberer();

    return 0;
} END_OF_MAIN();
