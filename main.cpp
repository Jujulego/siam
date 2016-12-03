// Importatiom.ns
#include <allegro.h>

#include "affichable.h"
#include "ia.h"
#include "Menu.h"

int main() {
    // Initialisation
    std::cout << std::boolalpha;
    Affichable::initier(Affichable::choix());
    IA::init();

    // On joue !
    Menu m;
    m.afficher();

    // Libérations
    Affichable::liberer();
    return 0;
} END_OF_MAIN();
