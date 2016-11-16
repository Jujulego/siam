#ifndef __OBJPOUSSABLE
#define __OBJPOUSSABLE

// Dépendances
#include <string>

#include "alleg.h"
#include "affichable.h"
#include "coordonnees.h"

// Enumerations
enum Direction {
    DROITE,
    GAUCHE,
    HAUT,
    BAS,
};

// Classe
class ObjPoussable : public Affichable {
    protected:
        // Attributs protégés
        char m_char;
        Coordonnees m_coord;
        allegro::BITMAP_PT m_image;
    
    public:
        // Constructeur
        ObjPoussable(char c, std::string img, Coordonnees coord);
        
        // Destructeur
        virtual ~ObjPoussable();
        
        // Méthodes
        virtual void deplacer(Direction dir);
        virtual float get_resistance(Direction dir) const = 0;
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
        
        // Accesseur
        Coordonnees get_coord() const;
};

#endif // __OBJPOUSSABLE
