#ifndef __PROGJOUEUR
#define __PROGJOUEUR

// Dépendances
#include <vector>

#include "coordonnee.h"
#include "joueur.h"
#include "plateau.h"

// Enumérations
enum Action {
    P, // placer un pion
    D, // deplacer un pion
    T, // tourner un pion
};

struct Mov {
    Action a;
    Coordonnees c;
    Direction d;
};

// Classe
class ProgJoueur : public Joueur {
    private:
        // Attributs
        std::vector<Mov> m_actions;
        unsigned m_i = 0;
    
    public:
        // Constructeur
        ProgJoueur(Equipe e, std::vector<Mov> const& actions);
        
        // Méthodes
        virtual void afficher_console() noexcept;
        virtual void afficher_allegro() noexcept;
        virtual bool jouer(Plateau& p);
};

#endif // __PROGJOUEUR
