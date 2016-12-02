// Importatiom.ns
#include <allegro.h>
#include <iostream>
#include <vector>

#include <iostream>
#include "affichable.h"
#include "ia.h"
#include "console.h"
#include "coordonnee.h"
#include "objpoussable.h"
#include "plateau.h"

#include "intellia.h"
#include "randomia.h"
#include "ConsoleJoueur.h"
#include "Menu.h"

int main() {
    // Initialisation
    std::cout << std::boolalpha;
    Affichable::initier(Affichable::choix());
    IA::init();

    Menu m();
   // m.afficher();

    // Libérations
    Affichable::liberer();


    return 0;
} END_OF_MAIN();
