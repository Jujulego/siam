// Importations
#include <allegro.h>
#include <iostream>
#include <vector>

#include "affichable.h"
#include "ia.h"
#include "console.h"
#include "coordonnee.h"
#include "objpoussable.h"
#include "plateau.h"
#include "progjoueur.h"
#include "randomia.h"
#include "ConsoleJoueur.h"

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());
    IA::init();

    // Déclarations
    Console c;
    Plateau p;

/*    Joueur* j1 = new ProgJoueur(RHINO, {
        {P, Coordonnees('A', 4), BAS},
        {P, Coordonnees('A', 4), BAS},
        {P, Coordonnees('D', 2), DROITE},
        {D, Coordonnees('A', 4), BAS},
        {D, Coordonnees('B', 4), GAUCHE},
        {D, Coordonnees('B', 3), BAS},
        {D, Coordonnees('D', 2), DROITE},
        {D, Coordonnees('D', 3), DROITE},
    });*/

    Joueur* j1 = new ConsoleJoueur(RHINO);
    Joueur* j2 = new ConsoleJoueur(ELEPH);
/*    Joueur* j2 = new ProgJoueur(ELEPH, {
        {P, Coordonnees('E', 2), GAUCHE},
        {P, Coordonnees('D', 3), GAUCHE},
        {P, Coordonnees('E', 4), HAUT},
        {D, Coordonnees('D', 3), DROITE},
        {T, Coordonnees('D', 4), HAUT},
        {D, Coordonnees('E', 4), GAUCHE},
        {D, Coordonnees('E', 3), DROITE},
    });*/

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
