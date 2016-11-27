#ifndef CONSOLEJOUEUR_H_INCLUDED
#define CONSOLEJOUEUR_H_INCLUDED
#include "Joueur.h"

class ConsoleJoueur:public Joueur
{

public:

    void afficher_allegro();
    void afficher_console() ;
    bool jouer(Plateau& p) ;
};

#endif // CONSOLEJOUEUR_H_INCLUDED
