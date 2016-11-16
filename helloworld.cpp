// Importations
#include "affichable.h"
#include "helloworld.h"

// Constructeur
HelloWorld::HelloWorld() noexcept : Affichable() {
}

// Méthodes
void HelloWorld::afficher_console() noexcept {
    s_console.setColor(COLOR_GREEN);
    std::cout << "Hello World !" << std::endl;
    s_console.setColor(COLOR_DEFAULT);
}

void HelloWorld::afficher_allegro() noexcept {
    allegro::textprintf_ex(allegro::screen, allegro::font, 10, 5, 0xffffff, 0x000000, "Hello World !");
}

void HelloWorld::attendre() noexcept {
    if (s_etat == ALLEGRO) {
        while (!allegro::key[allegro::KEY_ESC]) {
            allegro::rest(100);
        }
    } else {
        s_console.getch();
    }
}
