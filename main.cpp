// Importations
#include <allegro.h>
#include <iostream>
#include <vector>

#include <unistd.h>

#include "affichable.h"
#include "ia.h"
#include "console.h"
#include "coordonnee.h"
#include "objpoussable.h"
#include "plateau.h"

#include "intellia.h"
#include "randomia.h"
#include "ConsoleJoueur.h"

int main() {
    // Initialisation
    std::cout << std::boolalpha;
    Affichable::initier(Affichable::choix());
    IA::init();

    // Déclarations
    Console c;
    Plateau p;

    Joueur* j1 = new RandomIA(RHINO);
    Joueur* j2 = new IntellIA(ELEPH);
    
    c.gotoLigCol(9, 60);

    // Tests
    bool fini = false;
    p.afficher();
    
    if (Affichable::getEtat() == ALLEGRO) {
        while ((!key[KEY_ESC]) && (!fini))
        {
            j1->afficher();
            fini = j1->jouer(p);
            p.afficher();

            if (fini)
                break;

            j2->afficher();
            fini = j2->jouer(p);
            p.afficher();
        }
    } else {
        c.gotoLigCol(40, 0);
        
        while (!fini) {
            j1->afficher();
            fini = j1->jouer(p);
            p.afficher();
            
            if (fini)
                break;
            
            j2->afficher();
            fini = j2->jouer(p);
            p.afficher();
        }
    }

    // Libérations
    Affichable::liberer();
    delete j1;
    delete j2;

    return 0;
} END_OF_MAIN();
