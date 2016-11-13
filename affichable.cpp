// Importations
#include <allegro.h>
#include <cassert>

#include "affichable.h"
#include "console.h"

// Attributs statiques
Console Affichable::s_console;
Etat Affichable::s_etat = CONSOLE; // Par defaut mais il vaut mieux appeler initier quand même

// Méthodes statiques
Etat Affichable::choix() noexcept {
    // Boucle
    char choix;
    
    do {
        // Affichage
        s_console.clear();
        s_console.gotoLigCol(0, 0);

        // Message d'erreur
        if (choix != '\0') {
            s_console.setColor(COLOR_RED);
            std::cout << "Choix '" << choix << "' inconnu !" << std::endl;
            s_console.setColor(COLOR_DEFAULT);
        }

        std::cout << "Quel mode ?" << std::endl;
        std::cout << "a : Allegro" << std::endl;
        std::cout << "c : Console" << std::endl;
        std::cout << std::endl;
        std::cout << ">>> "; std::cin  >> choix;
    } while ((choix != 'a') && (choix != 'c'));
    
    return (choix == 'a') ? ALLEGRO : CONSOLE;
}

void Affichable::initier(Etat e) noexcept {
    // Enregistrement du choix
    s_etat = e;
    
    // Initialisation de Allegro
    if (s_etat == ALLEGRO) {
        allegro_init();
        
        install_mouse();
        install_keyboard();
        
        set_color_depth(desktop_color_depth());
        assert(!set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0));
    }
}

void Affichable::liberer() noexcept {
    // Initialisation de Allegro
    if (s_etat == ALLEGRO) {
        allegro_exit();
    }
}

// Constructeur
Affichable::Affichable() noexcept {
}

Affichable::~Affichable() noexcept {
}

// Méthodes
void Affichable::afficher() noexcept {
    // Appel de la bonne fonction
    switch (s_etat) {
    case CONSOLE:
        afficher_console();
        break;
    
    case ALLEGRO:
        afficher_allegro();
        break;
    }
}
