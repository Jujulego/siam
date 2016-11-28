#ifndef CONSOLEJOUEUR_H_INCLUDED
#define CONSOLEJOUEUR_H_INCLUDED

#include "joueur.h"

class ConsoleJoueur:public Joueur
{
private:
    Mov m_mov;

public:

    void afficher_allegro();
    void afficher_console() ;
    bool jouer(Plateau& p) ;
};

#endif // CONSOLEJOUEUR_H_INCLUDED
