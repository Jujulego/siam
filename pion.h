#ifndef __PION
#define __PION

// Dépendances
#include "coordonnee.h"
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
        Direction m_dir;
        Equipe m_equipe;
    
    public:
        // Constructeur
        Pion(Equipe e);
        
        // Méthodes
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
        
        void placer(Coordonnees coord, Direction dir);
        void tourner(Direction dir);
        
        virtual float get_resistance(Direction dir) const;
        
        // Accesseurs
        Equipe get_equipe() const;
        Direction get_dir() const;
};

#endif // __PION
