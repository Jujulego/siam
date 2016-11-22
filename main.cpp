// Importations
#include <allegro.h>
#include <iostream>
#include <vector>

#include "affichable.h"
#include "console.h"
#include "coordonnee.h"
#include "objpoussable.h"
#include "plateau.h"

enum Action {
    PE,
    PR,
    D,
    T,
};

struct Mov {
    Action a;
    Coordonnees c;
    Direction d;
};

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());
    Console c;
    
    std::vector<Mov> deps = {
        {PR, Coordonnees('A', 4), BAS},
        {PE, Coordonnees('D', 3), GAUCHE},
        {PR, Coordonnees('D', 2), DROITE},
        {PE, Coordonnees('E', 4), HAUT},
        {D,  Coordonnees('A', 4), BAS},
        {D,  Coordonnees('D', 3), DROITE},
        {D,  Coordonnees('B', 4), GAUCHE},
        {T,  Coordonnees('D', 4), HAUT},
        {D,  Coordonnees('B', 3), BAS},
        {D,  Coordonnees('E', 4), GAUCHE},
        {D,  Coordonnees('D', 2), DROITE},
        {D,  Coordonnees('E', 3), DROITE},
        {D,  Coordonnees('D', 3), DROITE},
    };

    // Tests
    Plateau p;
    p.afficher();
    
    for (auto m : deps) {
        c.gotoLigCol(40, 0);
        c.getch();
        
        switch (m.a) {
        case PR:
            p.placer(RHINO, m.c, m.d);
            break;
        
        case PE:
            p.placer(ELEPH, m.c, m.d);
            break;
        
        case D:
            p.deplacer(m.c, m.d);
            break;
        
        case T:
            p.tourner(m.c, m.d);
            break;
        }
        
        p.afficher();
        c.gotoLigCol(40, 0);
    }
    
    // Libérations
    Affichable::liberer();

    return 0;
} END_OF_MAIN();
