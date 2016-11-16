// Importations
#include "coordonnees.h"

// Constructeur
Coordonnees(char lig, int col) : m_lig(lig), m_col(col) {
}

// Accesseurs
char get_lig() const {
    return m_lig;
}

int  get_col() const {
    return m_col;
}

void set_lig(char lig) {
    m_lig = lig;
}

void set_col(int col) {
    m_col = col;
}
