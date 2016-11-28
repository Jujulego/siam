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
    Mov m;    // Mouvement
    Plateau p;// Plateau après mvt
    bool v;   // Victoire !!!
    
    int cool; // Niveau de coolitude !
};

// Classe
class IntellIA : public IA {
    private:
        // Attributs
        Arbre<ICoup> m_arbre;
        
        // Méthodes privées
        ICoup gen_icoup(Plateau dep, Mov mvt) const;
        void maj_icoups(Plateau nouv);
    
    public:
        // Constructeur
        IntellIA(Equipe e, Plateau p);
        
        // Méthodes
        virtual void afficher_allegro() noexcept;
        virtual void afficher_console() noexcept;
        virtual bool jouer(Plateau& p);
};

#endif // __INTELLIA
