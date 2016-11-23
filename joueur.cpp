// Imporations
#include "joueur.h"
#include "plateau.h"
#include "objpoussable.h"

// Constructeur
Joueur::Joueur(Equipe e) : Affichable(), m_equipe(e) {
};

// Destructeur
Joueur::~Joueur() noexcept {
}
