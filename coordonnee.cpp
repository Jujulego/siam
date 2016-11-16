// Importations
#include "coordonnee.h"

// Constructeur
Coordonnees::Coordonnees(char lig, int col) : m_lig(lig), m_col(col) {
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
