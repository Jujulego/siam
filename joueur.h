#ifndef __JOUEUR
#define __JOUEUR

// Dépendances
#include "objpoussable.h"
#include "plateau.h"

// Classe
class Joueur {
    protected:
        // Attributs
        Equipe m_equipe;
    
    public:
        // Constructeur
        Joueur(Equipe e);
        
        // Destructeur
        virtual ~Joueur();
        
        // Méthodes
        virtual bool jouer(Plateau& p) = 0;
};

#endif // __ABSJOUEUR
