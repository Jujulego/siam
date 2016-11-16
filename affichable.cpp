// Importations
#include <string>

#include "affichable.h"
#include "alleg.h"
#include "console.h"

// Attributs statiques
Console Affichable::s_console;
//allegro::ECRAN Affichable::s_ecran;
Etat Affichable::s_etat = CONSOLE; // Par defaut mais il vaut mieux appeler initier quand même

// Méthodes statiques
Etat Affichable::choix() noexcept {
    // Boucle
    char choix = '\0';

    do {
        // Affichage
        s_console.clear();
        s_console.gotoLigCol(0, 0);

        // Message d'erreur
        if (choix != '\0')
            Affichable::erreur((std::string) "Choix '" + choix + "' inconnu !");

        std::cout << "Quel mode ?" << std::endl;
        std::cout << "a : Allegro" << std::endl;
        std::cout << "c : Console" << std::endl;
        std::cout << std::endl;
        std::cout << ">>> "; std::cin  >> choix;
    } while ((choix != 'a') && (choix != 'c'));

    return (choix == 'a') ? ALLEGRO : CONSOLE;
}

void Affichable::erreur(std::string err) noexcept {
    s_console.setColor(COLOR_RED);
    std::cout << err << std::endl;
    s_console.setColor(COLOR_DEFAULT);
}

void Affichable::initier(Etat e) noexcept {
    // Enregistrement du choix
    s_etat = e;

    // Initialisation de Allegro
    if (s_etat == ALLEGRO) {
        allegro::init();
//        s_ecran = allegro::creer_ecran(800, 600);
    }
}

void Affichable::liberer() noexcept {
    // Initialisation de Allegro
    if (s_etat == ALLEGRO) {
        allegro::allegro_exit();
//        allegro::al_destroy_display(s_ecran);
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
