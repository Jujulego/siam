#ifndef __OBJPOUSSABLE
#define __OBJPOUSSABLE

// Dépendances
#include <string>

#include "alleg.h"
#include "affichable.h"
#include "coordonnee.h"

// Enumerations
enum Direction {
    DROITE = 0,
    HAUT   = 1,
    GAUCHE = 2,
    BAS    = 3,
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
        virtual ~ObjPoussable()  noexcept;

        // Méthodes
        bool deplacer(Direction dir); // renvoie vrai si le pion sort du plateau
        virtual float get_resistance(Direction dir) const = 0;
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;

        // Accesseur
        Coordonnees get_coord() const;
};

#endif // __OBJPOUSSABLE
