// Dépendances
#include <cstdlib>

#include "ia.h"
#include "joueur.h"
#include "objpoussable.h"

// Constructeur
IA::IA(Equipe e) : Joueur(e) {
}

// Destructeur
IA::~IA() noexcept {
}

// Méthodes
void IA::afficher_allegro() noexcept {
}

void IA::afficher_console() noexcept {
}

// Méthodes statiques
void IA::init() noexcept {
    // Générateur de nombres aléatoires
    srand(time(NULL));
}

int IA::random(int min, int max) noexcept {
    return (rand() % (max - min +1)) + min;
}

Direction IA::as_dir(int d) noexcept {
    // Modulo !
    d %= 4;
    
    // Convertion
    switch (d) {
    case HAUT:
        return HAUT;
    
    case DROITE:
        return DROITE;
    
    case BAS:
        return BAS;
    
    case GAUCHE:
        break;
    }
    
    return GAUCHE;
}
