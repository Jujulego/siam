#ifndef __PLATEAU
#define __PLATEAU

// Dépendances
#include <memory>
#include <set>
#include <vector>

#include "alleg.h"
#include "affichable.h"
#include "coordonnee.h"
#include "objpoussable.h"
#include "pion.h"

// Enumerations
enum Retour {
    OK,
    FIN,
    PASPION,
    ERREUR,  // Peux signifier 2 choses : si renvoyé par placer : la place est prise, si renvoyé pas deplacer : mvt impossible
};

enum Action {
    P, // placer un pion
    D, // deplacer un pion
    T, // tourner un pion
};

// Structure
struct Mov {
    Mov(Action _a, Coordonnees _c, Direction _d)
    : a(_a),c(_c),d(_d) {}
    Action a;
    Coordonnees c;
    Direction d;

    // Constructeur
    Mov() : a(P), c(Coordonnees('F', 5)), d(BAS) {
    }
};

// Classe
class Plateau : public Affichable {
    private:
        // Attributs
        int m_haut = 5;
        int m_larg = 5;
        allegro::BITMAP_PT m_map;
        std::string m_message = "";

        std::vector<std::shared_ptr<Pion>> m_equipes;
        std::vector<std::shared_ptr<ObjPoussable>> m_pions_joues;

        Retour _deplacer(std::shared_ptr<ObjPoussable> p, Coordonnees coord, Direction dir);

    public:
        // Constructeurs
        Plateau();
        Plateau(Plateau const& p);

        // Opérateurs
        bool operator == (Plateau const& p);

        // Méthodes
        Retour placer(Equipe e, Coordonnees coord, Direction dir);
        Retour deplacer(Equipe e, Coordonnees coord, Direction dir);
        Retour tourner(Equipe e, Coordonnees coord, Direction dir);

        Retour appliquer_mov(Equipe e, Mov m);

        float get_resistance(Coordonnees coord, Direction dir, std::set<std::shared_ptr<ObjPoussable>>* objdevant = nullptr);
        std::shared_ptr<ObjPoussable> get_pion(Coordonnees coord);

        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;

        // Accesseurs
        std::vector<std::shared_ptr<Pion>> const& get_pions() const;           // Renvoie l'ensemble des pions ELEPH et RHINO, joués ou pas
        std::vector<std::shared_ptr<Pion>> get_equipe(Equipe e) const;         // Renvoie les pions de l'equipe donnée, joués (sur le plateau)
        std::vector<std::shared_ptr<Pion>> get_full_equipe(Equipe e) const;    // Renvoie les pions de l'equipe donnée, joués ou pas
        std::vector<std::shared_ptr<ObjPoussable>> const& get_plateau() const; // Renvoie l'ensemble des pions ELEPH et RHINO joués
};

#endif // __PLATEAU
