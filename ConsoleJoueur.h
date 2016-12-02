#ifndef CONSOLEJOUEUR_H_INCLUDED
#define CONSOLEJOUEUR_H_INCLUDED

#include "joueur.h"
#include "coordonnee.h"
#include "plateau.h"


class ConsoleJoueur:public Joueur
{
private:
    Mov m_mov;

public:

    ConsoleJoueur(Equipe e);
    void afficher_allegro();
    void afficher_console() ;
    bool jouer(Plateau& p) ;
    Direction demanderDirection();
    Coordonnees demanderCoord(std::string texte);
};

#endif // CONSOLEJOUEUR_H_INCLUDED
