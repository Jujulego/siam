#ifndef __PION
#define __PION

// Dépendances
#include "coordonnee.h"
#include "objpoussable.h"

// Classe
class Pion : public ObjPoussable {
    protected:
        // Attributs
        Direction m_dir;
    
    public:
        // Constructeur
        Pion(Equipe e);
        
        // Méthodes
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
        
        void placer(Coordonnees coord, Direction dir);
        virtual void tourner(Direction dir);
        
        virtual float get_resistance(Direction dir) const;
        virtual float get_force(Direction dir) const;
        
        // Accesseurs
        Direction get_dir() const;
};

#endif // __PION
