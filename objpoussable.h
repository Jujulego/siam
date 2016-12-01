#ifndef __OBJPOUSSABLE
#define __OBJPOUSSABLE

// Dépendances
#include <string>

#include "alleg.h"
#include "affichable.h"
#include "coordonnee.h"

// Enumerations
enum Equipe {
    ELEPH,
    RHINO,
    MONTAGNE,
};

// Classe
class ObjPoussable : public Affichable {
    protected:
        // Attributs protégés
        Equipe m_equipe;
        char m_char;
        Coordonnees m_coord;
        allegro::BITMAP_PT m_image;

    public:
        // Constructeur
        ObjPoussable(Equipe e, char c, std::string img, Coordonnees coord);

        // Destructeur
        virtual ~ObjPoussable()  noexcept;

        // Méthodes
        bool deplacer(Direction dir); // renvoie vrai si le pion sort du plateau
        virtual void tourner(Direction dir) = 0;
        virtual float get_resistance(Direction dir) const = 0;
        virtual float get_force(Direction dir) const = 0;
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;

        // Accesseur
        Equipe get_equipe() const;
        Coordonnees get_coord() const;
        virtual Direction get_dir() const = 0;
        allegro::BITMAP_PT get_image() const;

        // Setter
        void set_coord(Coordonnees _coord);
};

#endif // __OBJPOUSSABLE
