// Importations
#include <string>

#include "alleg.h"
#include "affichable.h"
#include "coordonnee.h"
#include "objpoussable.h"

// Constructeur
ObjPoussable::ObjPoussable(char c, std::string img, Coordonnees coord) : Affichable(), m_char(c), m_coord(coord) {
    if (s_etat == ALLEGRO) {
        m_image = allegro::charger_bitmap(img);
    }
}

// Destructeur
ObjPoussable::~ObjPoussable() noexcept{
}

// Méthodes
void ObjPoussable::deplacer(Direction dir) {
}

void ObjPoussable::afficher_allegro() noexcept {
}

void ObjPoussable::afficher_console() noexcept {
    s_console.gotoLigCol(get_coord().get_as_y(s_etat) + 1, get_coord().get_as_x(s_etat));
    std::cout << "   " << m_char;
}

// Accesseur
Coordonnees ObjPoussable::get_coord() const {
    return m_coord;
}
