#ifndef CONSOLEJOUEUR_H_INCLUDED
#define CONSOLEJOUEUR_H_INCLUDED

#include "joueur.h"
#include "coordonnee.h"
#include "plateau.h"

#include <memory>

class ConsoleJoueur : public Joueur
{
private:
    std::shared_ptr<Plateau> m_p;
    Mov m_mov;

public:
    // Constructeur
    ConsoleJoueur(Equipe e,std::shared_ptr<Plateau> p);

    // Methodes
    void afficher_allegro();
    void afficher_console();
    bool jouer(Plateau& p);
    Direction demanderDirection();
    Coordonnees demanderCoord(std::string texte);
    Coordonnees find_coord_alleg(int x, int y);
    void dess_fleches(Coordonnees clic_coord);
};

#endif // CONSOLEJOUEUR_H_INCLUDED
