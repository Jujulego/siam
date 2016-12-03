#ifndef __INTELLIA
#define __INTELLIA

// Dépendances
#include <vector>

#include "arbre.h"
#include "coordonnee.h"
#include "ia.h"
#include "objpoussable.h"
#include "plateau.h"

// Structure
struct ICoup {
    // Attributs
    Mov m;      // Mouvement
    Plateau p;  // Plateau après mvt
//    std::vector<std::shared_ptr<ObjPoussable>> p;  // Plateau après mvt
    bool v;     // Victoire !!!
    int cool;   // Niveau de coolitude !
};

// Classe
class IntellIA : public IA {
    private:
        // Attributs
        std::vector<Coordonnees> m_pos_placement;
        Mov m_mov;
        
        // Méthodes privées
        void prevision(Plateau depart);
        bool ajouter_noeud(Arbre<ICoup> n, Plateau plateau, Mov mvt);
        ICoup gen_icoup(Plateau& dep, Mov mvt, Retour r) const;
    
    public:
        // Constructeur
        IntellIA(Equipe e);
        
        // Méthodes
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
        virtual bool jouer(Plateau& p);
};

#endif // __INTELLIA
