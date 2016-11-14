#ifndef __PLATEAU
#define __PLATEAU

// Dépendances
#include "affichable.h"

// Classe
class Plateau : public Affichable {
    private:
        int m_haut = 5;
        int m_larg = 5;
    
    public:
        // Constructeur
        Plateau();
        Plateau(int hauteur, int largeur);
        
        // Méthodes
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
};

#endif // __PLATEAU
