#ifndef __PLATEAU
#define __PLATEAU

// Dépendances
#include "affichable.h"
#include <allegro.h>

// Classe
class Plateau : public Affichable {
    private:
        int m_haut = 5;
        int m_larg = 5;
        BITMAP* m_map;

    public:
        // Constructeur
        ~Plateau() noexcept;
        Plateau();
        Plateau(int hauteur, int largeur);

        // Méthodes
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
};

#endif // __PLATEAU
