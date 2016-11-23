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

    Console c;
    c.gotoLigCol(40, 0);

    while (!fini) {
        j1->afficher();
        fini = j1->jouer(p);

        if (fini)
            break;

        j2->afficher();
        fini = j2->jouer(p);
    }

    // Libérations
    Affichable::liberer();
    delete j1;
    delete j2;

    return 0;
} END_OF_MAIN();
