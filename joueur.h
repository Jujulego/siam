#ifndef __JOUEUR
#define __JOUEUR

// Dépendances
#include "affichable.h"
#include "objpoussable.h"
#include "plateau.h"

// Classe
class Joueur : public Affichable {
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
