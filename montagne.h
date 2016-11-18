#ifndef __MONTAGNE
#define __MONTAGNE

// Dépendances
#include "coordonnee.h"
#include "objpoussable.h"

// Classe
class Montagne : public ObjPoussable {
    public:
        // Constructeur
        Montagne(Coordonnees coord);
        
        // Méthodes
        virtual float get_resistance(Direction dir) const;
};

#endif // __MONTAGNE
