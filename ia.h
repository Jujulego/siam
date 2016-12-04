#ifndef __IA
#define __IA

// Dépendances
#include "coordonnee.h"
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
        static Direction as_dir(int d) noexcept;
};

#endif // __IA
