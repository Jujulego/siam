#ifndef __RANDOMIA
#define __RANDOMIA

// Dépendances
#include <map>
#include <vector>

#include "coordonnee.h"
#include "ia.h"
#include "objpoussable.h"
#include "plateau.h"

// Structure
struct RCoup {
    int s; // somme => intérêt de la case
    int d; // Déplacer
    int p; // Placer
    int t; // Tourner
};

// Classe
class RandomIA : public IA {
    private:
        // Attributs
        unsigned m_somme;
        std::map<char,std::vector<RCoup>> m_map;
        
        // Méthodes
        void set_coup(char lig, int col, Action a, int val);
        void reset_map(int p);
    
    public:
        // Constructeur
        RandomIA(Equipe e) noexcept;
        
        // Destructeur
        virtual ~RandomIA() noexcept;
        
        // Méthodes
        virtual void allegro_console() noexcept;
        virtual void allegro_allegro() noexcept;
        virtual bool jouer(Plateau& p);
};

#endif // __RANDOMIA
