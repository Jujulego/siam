#ifndef __COORDONNEES
#define __COORDONNEES

// Dépendances
#include "affichable.h"

// Enumerations
enum Direction {
    DROITE = 0,
    HAUT   = 1,
    GAUCHE = 2,
    BAS    = 3,
};

// Classe
class Coordonnees {
    private:
        char m_lig;
        int m_col;
    
    public:
        // Constructeur
        Coordonnees(char lig, int col);
        Coordonnees(Coordonnees const& c);
        
        // Méthodes
        int get_as_x(Etat etat) const;
        int get_as_y(Etat etat) const;
        
        // Accesseurs
        char get_lig() const;
        int  get_col() const;
        
        void set_lig(char lig);
        void set_col(int col);
        
        // Opérateurs
        bool operator == (Coordonnees const& c);
        void operator += (Direction const& d);
        void operator -= (Direction const& d);
        Coordonnees operator + (Direction const& d);
        Coordonnees operator - (Direction const& d);
};

#endif // __COORDONNEES
