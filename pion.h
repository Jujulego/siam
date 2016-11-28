#ifndef __PION
#define __PION

// Dépendances
#include "coordonnee.h"
#include "objpoussable.h"

//Definition des termines
#ifndef __gnu_linux__
static const std::string FLECHE_GAUCHE = "<";
static const std::string FLECHE_HAUT   = "^";
static const std::string FLECHE_DROITE = ">";
static const std::string FLECHE_BAS    = "v";
/*static const std::string FLECHE_GAUCHE = "\x1b";
static const std::string FLECHE_HAUT   = "\x18";
static const std::string FLECHE_DROITE = "\x1a";
static const std::string FLECHE_BAS    = "\x19";*/
#else
static const std::string FLECHE_GAUCHE = "\xe2\x87\x90";
static const std::string FLECHE_HAUT   = "\xe2\x87\x91";
static const std::string FLECHE_DROITE = "\xe2\x87\x92";
static const std::string FLECHE_BAS    = "\xe2\x87\x93";
#endif

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
