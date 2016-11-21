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
bool ObjPoussable::deplacer(Direction dir) {
    switch (dir) {
    case HAUT:
        if (get_coord().get_lig() == 'A') {
            m_coord.set_lig('F');
            m_coord.set_col(5);
            return true;
        }
        
        m_coord.set_lig(get_coord().get_lig() - 1);
        
        break;
    
    case BAS:
        if (get_coord().get_lig() == 'E') {
            m_coord.set_lig('F');
            m_coord.set_col(5);
            return true;
        }
        
        m_coord.set_lig(get_coord().get_lig() + 1);
        
        break;
    
    case DROITE:
        if (get_coord().get_col() == 4) {
            m_coord.set_lig('F');
            m_coord.set_col(5);
            return true;
        }
        
        m_coord.set_col(get_coord().get_col() + 1);
        
        break;
    
    case GAUCHE:
        if (get_coord().get_col() == 0) {
            m_coord.set_lig('F');
            m_coord.set_col(5);
            return true;
        }
        
        m_coord.set_col(get_coord().get_col() - 1);
        
        break;
    }
    
    return false;
}

void ObjPoussable::afficher_allegro() noexcept {
}

void ObjPoussable::afficher_console() noexcept {
    s_console.gotoLigCol(get_coord().get_as_y(s_etat) + 1, get_coord().get_as_x(s_etat) + 3);
    std::cout << m_char;
}

// Accesseur
Coordonnees ObjPoussable::get_coord() const {
    return m_coord;
}
