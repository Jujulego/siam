// Importations
#include <allegro.h>
#include <iostream>
#include <vector>

#include "affichable.h"
#include "console.h"
#include "coordonnee.h"
#include "pion.h"
#include "plateau.h"

struct Mov {
    Coordonnees c;
    Direction d;
};

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());
    Console c;
    
    std::vector<Mov> deps = {
        {Coordonnees('A', 4), BAS},
        {Coordonnees('D', 3), BAS},
        {Coordonnees('B', 4), GAUCHE},
        {Coordonnees('E', 3), HAUT},
        {Coordonnees('B', 3), BAS},
    };

    // Tests
    Plateau p;
    p.placer(RHINO, Coordonnees('A', 4), BAS);
    p.placer(ELEPH, Coordonnees('D', 3), DROITE);
    p.afficher();
    
    for (auto m : deps) {
        c.gotoLigCol(40, 0);
        c.getch();
        
        p.deplacer(m.c, m.d);
        p.afficher();
        
        c.gotoLigCol(40, 0);
    }

    // Libérations
    Affichable::liberer();

    return 0;
} END_OF_MAIN();
