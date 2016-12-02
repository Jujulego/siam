#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "affichable.h"
#include "joueur.h"

class Menu : public Affichable {
    private:
        Joueur* j1 = nullptr;
        Joueur* j2 = nullptr;
    
    public:
        Menu();
        virtual ~Menu() noexcept;
        
        void afficherMenu();
        void creationJoueur();
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
};



#endif // MENU_H_INCLUDED
