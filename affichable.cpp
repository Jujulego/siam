// Importations
#include <string>

#include "affichable.h"
#include "alleg.h"
#include "console.h"

// Attributs statiques
Console Affichable::s_console;
Etat Affichable::s_etat = CONSOLE; // Par defaut mais il vaut mieux appeler initier quand même
allegro::BITMAP_PT Affichable::s_buffer = nullptr;

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

void Affichable::erreur(std::string err) noexcept { //affichage d'une erreur en rouge
    s_console.setColor(COLOR_RED);
    std::cerr << err << std::endl;//cerr:affiche sur le flux d'erreur
    s_console.setColor(COLOR_DEFAULT);
}

void Affichable::initier(Etat e) noexcept {
    // Enregistrement du choix
    s_etat = e;

    // Initialisation de Allegro
    if (s_etat == ALLEGRO) {
        allegro::init(800, 600);
        s_buffer = allegro::creer_bitmap(800, 600);
    }
}

void Affichable::liberer() noexcept {
    // Initialisation de Allegro
    if (s_etat == ALLEGRO) {
        allegro::allegro_exit();
    }
}

// Constructeur
Affichable::Affichable() noexcept {
}

//Destructeur
Affichable::~Affichable() noexcept {
}

// Méthodes
void Affichable::afficher() noexcept {
    // Appel de la bonne fonction pour l'affichage allegro ou console
    switch (s_etat) {
    case CONSOLE:
        afficher_console();
        break;

    case ALLEGRO:
        afficher_allegro();
        draw_sprite(allegro::screen, s_buffer, 0, 0);

        break;
    }
}
