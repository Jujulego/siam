// Importations
#include "coordonnee.h"
#include "objpoussable.h"
#include "pion.h"

#ifndef __gnu_linux__
static const std::string FLECHE_GAUCHE = "<";
static const std::string FLECHE_HAUT   = "^";
static const std::string FLECHE_DROITE = ">";
static const std::string FLECHE_BAS    = "v";
/*static const std::string FLECHE_GAUCHE = "\x1b";
static const std::string FLECHE_HAUT   = "\x18";
static const std::string FLECHE_DROITE = "\x1a";
static const std::string FLECHE_BAS    = "\x19";*/
#else
static const std::string FLECHE_GAUCHE = "\xe2\x87\x90";
static const std::string FLECHE_HAUT   = "\xe2\x87\x91";
static const std::string FLECHE_DROITE = "\xe2\x87\x92";
static const std::string FLECHE_BAS    = "\xe2\x87\x93";
#endif

// Constructeur
Pion::Pion(Equipe e) : ObjPoussable(e, (e == ELEPH) ? 'E' : 'R', (e == ELEPH) ? "test_eleph.bmp" : "test_rhino.bmp", Coordonnees('F', 5)), m_dir(HAUT) {
}

// Méthodes
void Pion::afficher_allegro() noexcept {
}

void Pion::afficher_console() noexcept {
    ObjPoussable::afficher_console();

    switch (m_dir) {
    case HAUT:
        s_console.gotoLigCol(get_coord().get_as_y(s_etat), get_coord().get_as_x(s_etat) + 3);
        std::cout << FLECHE_HAUT;
        break;

    case BAS:
        s_console.gotoLigCol(get_coord().get_as_y(s_etat) + 2, get_coord().get_as_x(s_etat) + 3);
        std::cout << FLECHE_BAS;
        break;

    case DROITE:
        s_console.gotoLigCol(get_coord().get_as_y(s_etat) + 1, get_coord().get_as_x(s_etat) + 5);
        std::cout << FLECHE_DROITE;
        break;

    case GAUCHE:
        s_console.gotoLigCol(get_coord().get_as_y(s_etat) + 1, get_coord().get_as_x(s_etat) + 1);
        std::cout << FLECHE_GAUCHE;
        break;
    }
}

void Pion::placer(Coordonnees coord, Direction dir) { // placement des pions
    m_coord = coord;
    m_dir = dir;
}

void Pion::tourner(Direction dir) {  //position du pion
    m_dir = dir;
}

float Pion::get_resistance(Direction dir) const {
    return ((dir + 2) % 4 == get_dir()) ? 1.0f : 0.0f;
}

float Pion::get_force(Direction dir) const {
    return (dir == get_dir()) ? 1.0f : 0.0f;
}

// Accesseurs
Direction Pion::get_dir() const {
    return m_dir;
}
