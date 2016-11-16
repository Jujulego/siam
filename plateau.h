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
        std::vector<std::shared_ptr<Pion>> equipes;
        std::vector<std::shared_ptr<ObjPoussable>> pions_joues;
    
    public:
        // Constructeur
        Plateau();

        // Méthodes
        void placer(Equipe e, Coordonnees coord, Direction dir);
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
};

#endif // __PLATEAU
