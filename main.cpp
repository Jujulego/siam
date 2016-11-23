// Importations
#include <allegro.h>
#include <iostream>
#include <vector>

#include "affichable.h"
#include "console.h"
#include "coordonnee.h"
#include "objpoussable.h"
#include "plateau.h"
#include "progjoueur.h"

int main() {
    // Initialisation
    Affichable::initier(Affichable::choix());
    Console c;
    Plateau p;

    Joueur* j1 = new ProgJoueur(ELEPH, {
        {P, Coordonnees('D', 3), GAUCHE},
        {P, Coordonnees('E', 4), HAUT},
        {D, Coordonnees('D', 3), DROITE},
        {T, Coordonnees('D', 4), HAUT},
        {D, Coordonnees('E', 4), GAUCHE},
        {D, Coordonnees('E', 3), DROITE},
    });

    Joueur* j2 = new ProgJoueur(RHINO, {
        {P, Coordonnees('A', 4), BAS},
        {P, Coordonnees('D', 2), DROITE},
        {D, Coordonnees('A', 4), BAS},
        {D, Coordonnees('B', 4), GAUCHE},
        {D, Coordonnees('B', 3), BAS},
        {D, Coordonnees('D', 2), DROITE},
        {D, Coordonnees('D', 3), DROITE},
    });

    // Tests
    bool fini = false;
    p.afficher();

    if (Affichable::getEtat())
    {
        while (!key[KEY_ESC])
        {

        }
    }

    else {

        c.gotoLigCol(40, 0);

        while (!fini) {
            fini = j1->jouer(p);
            p.afficher();
            j1->afficher();

            if (fini)
                break;

            fini = j2->jouer(p);
            p.afficher();
            j2->afficher();
        }
    }

    // Libérations
    Affichable::liberer();
    delete j1;
    delete j2;

    return 0;
} END_OF_MAIN();
