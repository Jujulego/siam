#ifndef __AFFICHABLE
#define __AFFICHABLE

// Dépendances
#include <string>

#include "alleg.h"
#include "console.h"

// Enumérations
enum Etat {CONSOLE, ALLEGRO};

// Classe
class Affichable {
    public:
        // Méthodes statiques
        static Etat choix() noexcept;
        static void erreur(std::string err) noexcept;
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
//        static allegro::ECRAN s_ecran;
};

#endif // __AFFICHABLE