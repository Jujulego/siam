#ifndef __COORDONNEES
#define __COORDONNEES

// Dépendances
#include "affichable.h"

// Classe
class Coordonnees {
    private:
        char m_lig;
        int m_col;
    
    public:
        // Constructeur
        Coordonnees(char lig, int col);
        
        // Méthodes
        int get_as_x(Etat etat) const;
        int get_as_y(Etat etat) const;
        
        // Accesseurs
        char get_lig() const;
        int  get_col() const;
        
        void set_lig(char lig);
        void set_col(int col);
        
        // Opérateurs
        bool operator==(Coordonnees const& c);
};

#endif // __COORDONNEES
