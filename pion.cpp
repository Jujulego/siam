// Importations
#include "coordonnee.h"
#include "objpoussable.h"
#include "pion.h"

// Constructeur
Pion::Pion(Equipe e) : ObjPoussable((e == ELEPH) ? 'E' : 'R', "pas d'image !", Coordonnees('F', 6)), m_dir(HAUT), m_equipe(e) {
}

// Méthodes
void Pion::placer(Coordonnees coord, Direction dir) {
    m_coord = coord;
    m_dir = dir;
}

void Pion::tourner(Direction dir) {
    m_dir = dir;
}

float Pion::get_resistance(Direction dir) const {
    return ((dir + 2) % 4 == get_dir()) ? 1.0f : 0.0f;
}

// Accesseurs
Equipe Pion::get_equipe() const {
    return m_equipe;
}

Direction Pion::get_dir() const {
    return m_dir;
}
