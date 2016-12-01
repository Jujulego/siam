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
    IntellIA* j2 = new IntellIA(ELEPH, p);
    
    c.gotoLigCol(9, 60);

    // Tests
    bool fini = false;
    p.afficher();
    
/*    if (Affichable::getEtat() == ALLEGRO) {
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
    } else {*/
        c.gotoLigCol(40, 0);
        
        while (!fini) {
//            j1->afficher();
//            fini = j1->jouer(p);
//            p.afficher();
            
            if (fini)
                break;
            
            c.gotoLigCol(10, 60);
            std::cout << "null  : " << j2->m_arbre.is_null() << std::endl;
            
            c.gotoLigCol(11, 60);
            std::cout << "prevu : " << j2->m_arbre.get_val()->prevu << std::endl;
            
            c.gotoLigCol(12, 60);
            std::cout << "cool  : " << j2->m_arbre.get_val()->cool << std::endl;
            
            sleep(1);
            
            c.gotoLigCol(40, 0);
            std::cout << std::endl;
            
            j2->afficher();
            fini = j2->jouer(p);
            p.afficher();
        }
//    }

    // Libérations
    Affichable::liberer();
    delete j1;
    delete j2;

    return 0;
} END_OF_MAIN();
