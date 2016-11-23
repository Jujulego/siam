// Importations
#include "affichable.h"
#include "coordonnee.h"

// Constantes
#define X_CONSOLE 7
#define Y_CONSOLE 3
#define XY_ALLEG 120

// Constructeur
Coordonnees::Coordonnees(char lig, int col) : m_lig(lig), m_col(col) {
}

Coordonnees::Coordonnees(Coordonnees const& c) : m_lig(c.get_lig()), m_col(c.get_col()) {
}

// Méthodes
int Coordonnees::get_as_x(Etat etat) const {
    if (etat == CONSOLE) {
        return (get_col() * (X_CONSOLE + 1)) + 4;
    }

    return (get_col() * XY_ALLEG)+ 35;
}

int Coordonnees::get_as_y(Etat etat) const {
    if (etat == CONSOLE) {
        return ((int) (get_lig() - 'A') * (Y_CONSOLE + 1)) + 5;
    }

    return ((get_lig() - 'A')* XY_ALLEG)+ 35;
}

// Accesseurs
char Coordonnees::get_lig() const {
    return m_lig;
}

int Coordonnees::get_col() const {
    return m_col;
}

//Setteurs
void Coordonnees::set_lig(char lig) {
    m_lig = lig;
}

void Coordonnees::set_col(int col) {
    m_col = col;
}

// Opérateurs
bool Coordonnees::operator == (Coordonnees const& c) {
    return (get_lig() == c.get_lig()) && (get_col() == c.get_col());
}

void Coordonnees::operator += (Direction const& d) {
    if (d % 2) {
        m_lig += (d == BAS) ? 1 : -1;
    } else {
        m_col += (d == DROITE) ? 1 : -1;
    }
}

Coordonnees Coordonnees::operator + (Direction const& d) {
    // Copie
    Coordonnees c = *this;
    c += d;
    
    return c;
}
