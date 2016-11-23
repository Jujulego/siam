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

void Coordonnees::set_lig(char lig) {
    m_lig = lig;
}

void Coordonnees::set_col(int col) {
    m_col = col;
}
