#ifndef __PLATEAU
#define __PLATEAU

// Dépendances
#include <memory>
#include <vector>

#include "alleg.h"
#include "affichable.h"
#include "coordonnee.h"
#include "objpoussable.h"
#include "pion.h"

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
    
    public:
        // Constructeur
        Plateau();

        // Méthodes
        bool placer(Equipe e, Coordonnees coord, Direction dir);
        std::shared_ptr<ObjPoussable> get_pion(Coordonnees coord);
        bool deplacer(Coordonnees coord, Direction dir); // Renvoie vrai s'il n'y a pas de pions au coordonnees donnée, ou si le déplacement est impossible
        bool tourner(Coordonnees coord, Direction dir); // Renvoie vrai s'il n'y a pas de pions au coordonnees donnée
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
};

#endif // __PLATEAU
