#ifndef __MONTAGNE
#define __MONTAGNE

// Dépendances
#include "objpoussable.h"

// Classe
class Montagne : public ObjPoussable {
    public:
        // Constructeur
        Montagne();
        
        // Méthodes
        virtual float get_resistance() const;
};

#endif // __MONTAGNE
