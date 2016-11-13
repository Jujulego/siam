#ifndef __HELLO_WORLD
#define __HELLO_WORLD

// Dépendances
#include "affichable.h"

// Classe
class HelloWorld : public Affichable {
    public:
        // Constructeur
        HelloWorld() noexcept;
        
        // Méthodes
        virtual void afficher_console() noexcept;
        virtual void afficher_allegro() noexcept;
        
        void attendre() noexcept;
};

#endif // __HELLO_WORLD
