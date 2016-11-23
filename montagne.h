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
        virtual void tourner(Direction dir);
        virtual float get_resistance(Direction dir) const;
        virtual float get_force(Direction dir) const;
        virtual Direction get_dir() const;
};

#endif // __MONTAGNE
