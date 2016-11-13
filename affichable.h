#ifndef __AFFICHABLE
#define __AFFICHABLE

// Dépendances
#include "console.h"

// Enumérations
enum Etat {CONSOLE, ALLEGRO};

// Classe
class Affichable {
    public:
        // Méthodes statiques
        static Etat choix() noexcept;
        static void initier(Etat e) noexcept;
        static void liberer() noexcept;
        
        // Constructeur
        Affichable() noexcept;
        
        // Destructeur
        virtual ~Affichable() noexcept;
        
        // Méthodes
        void afficher() noexcept;
        
        // Méthodes à redéfinir
        virtual void afficher_allegro() = 0;
        virtual void afficher_console() = 0;
    
    protected:
        // Attributs statiques
        static Etat s_etat;
        static Console s_console;
};

#endif // __AFFICHABLE
