// Importations
#include <vector>

#include "arbre.h"
#include "coordonnee.h"
#include "ia.h"
#include "intellia.h"
#include "objpoussable.h"
#include "plateau.h"

// Constructeur
IntellIA::IntellIA(Equipe e, Plateau p) : IA(e) {
    // Création du 1er mouvement
    m_arbre.set_val(gen_icoup(p, {P, Coordonnees((e == RHINO) ? 'A' : 'E', random(1, 3)), (e == RHINO) ? BAS : HAUT}));
}

// Méthodes privées
ICoup IntellIA::gen_icoup(Plateau dep, Mov mvt) const {
    // Application du mvt
    Retour r = dep.appliquer_mov(m_equipe, mvt);
    
    return {mvt, dep, r == FIN, 1};
}

void IntellIA::maj_icoups(Plateau nouv) {
}

// Méthodes
void IntellIA::afficher_allegro() noexcept {
}

void IntellIA::afficher_console() noexcept {
}

bool IntellIA::jouer(Plateau& p) {
    return false;
}
