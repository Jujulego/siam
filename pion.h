#ifndef __PION
#define __PION

// Dépendances
#include "objpoussable.h"

// Enumerations
enum Equipe {
    RHINO,
    ELEPH,
};

// Classe
class Pion : public ObjPoussable {
    protected:
        // Attributs
        Equipe m_equipe;
        Direction m_dir;
    
    public:
        // Constructeur
        Pion(Equipe e);
        
        // Méthodes
        void tourner(Direction dir);
        virtual float get_resistance() const;
        
        // Accesseurs
        Equipe get_equipe() const;
        Direction get_dir() const;
};

#endif // __PION
