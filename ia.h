#ifndef __IA
#define __IA

// Dépendances
#include "joueur.h"
#include "objpoussable.h"

// Classe
class IA : public Joueur {
    public:
        // Constructeur
        IA(Equipe e);
        
        // Destructeur
        virtual ~IA() noexcept;
        
        // Méthodes
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
        
        // Méthodes statiques
        static void init() noexcept;
        static int random(int min, int max) noexcept;
};

#endif // __IA
