// Importations
#include <string>

#include "alleg.h"
#include "affichable.h"
#include "coordonnee.h"
#include "objpoussable.h"

// Constructeur
ObjPoussable::ObjPoussable(Equipe e, char c, std::string img, Coordonnees coord) : Affichable(), m_equipe(e), m_char(c), m_coord(coord) {
    if (s_etat == ALLEGRO) {
        m_image = allegro::charger_bitmap(img);
    }
}

// Destructeur
ObjPoussable::~ObjPoussable() noexcept{
}

// Méthodes
bool ObjPoussable::deplacer(Direction dir) {
    m_coord += dir;

    if ((m_coord.get_lig() < 'A') || (m_coord.get_lig() > 'E') || (m_coord.get_col() < 0) || (m_coord.get_col() > 4)) {
        m_coord.set_lig('F');
        m_coord.set_col(5);
        return true;
    }

    return false;
}

void ObjPoussable::afficher_allegro() noexcept {
    if (m_equipe == MONTAGNE) {
        draw_sprite(s_buffer,m_image,get_coord().get_as_x(s_etat)-10,get_coord().get_as_y(s_etat)-20);
    }
}

void ObjPoussable::afficher_console() noexcept {
    if (get_coord().get_lig() != 'F') {
        s_console.gotoLigCol(get_coord().get_as_y(s_etat) + 1, get_coord().get_as_x(s_etat) + 3);
        std::cout << m_char;
    }
}

// Accesseur
Coordonnees ObjPoussable::get_coord() const {
    return m_coord;
}

Equipe ObjPoussable::get_equipe() const {
    return m_equipe;
}

allegro::BITMAP_PT ObjPoussable::get_image() const {
    return m_image;
}

void ObjPoussable::set_coord(Coordonnees _coord)
{
    m_coord = _coord;
}

