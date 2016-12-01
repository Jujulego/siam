// Importations
#include <queue>
#include <vector>

#include <unistd.h>

#include "arbre.h"
#include "coordonnee.h"
#include "ia.h"
#include "intellia.h"
#include "objpoussable.h"
#include "plateau.h"

// Constructeur
IntellIA::IntellIA(Equipe e, Plateau p) : IA(e) {
    // Remplissage
    for (int i = 0; i < 5; i++) {
        for (char j = 'A'; j < 'F'; j++) {
            if ((j == 'A') || (j == 'E') || (i == 0) || (i == 4))
                m_pos_placement.push_back(Coordonnees(j, i));
        }
    }
    
    // Création du 1er mouvement
    Mov mvt  = {P, Coordonnees((e == RHINO) ? 'A' : 'E', random(1, 3)), (e == RHINO) ? BAS : HAUT};
    Retour r = p.appliquer_mov(m_equipe, mvt);
    
    m_arbre.set_val(gen_icoup(p, mvt, r));
    prevision();
}

// Méthodes privées
void IntellIA::prevision() {
    // Déclarations
    bool victoire = false;
    std::queue<Arbre<ICoup>> noeuds;
    noeuds.push(m_arbre);
    int nb = 0;
    
    // Parcours de l'arbre (fraterie)
    while (!noeuds.empty() && !victoire) {
        std::cout << nb++ << std::endl;
        
        // Récupération du noeud
        Mov mvt = {P, Coordonnees('F', 5), BAS};
        
        auto n = noeuds.front();
        noeuds.pop();
        
        // Calcul des noeuds fils (si cela n'a pas déjà été fait)
        if (!(n.get_val()->prevu)) {
            Plateau plateau(n.get_val()->p);
            bool placer = true;
            
            plateau.afficher();
            usleep(250000);
            
            // Parcours du plateau
            for (auto p : plateau.get_full_equipe(m_equipe)) {
                // Pion est hors du plateau
                if (p->get_coord().get_lig() == 'F') {
                    if (placer) {
                        placer = false;
                        
                        for (auto c : m_pos_placement) {
                            // Choix de l'action
                            mvt.a = P;
                            mvt.c = c;
                            
                            if (c.get_lig() == 'A')
                                mvt.d = BAS;
                            else if (c.get_lig() == 'E')
                                mvt.d = HAUT;
                            else if (c.get_col() == 0)
                                mvt.d = DROITE;
                            else if (c.get_col() == 4)
                                mvt.d = GAUCHE;
                            
                            // création du noeud (sauf erreur ...)
                            victoire = ajouter_noeud(n, plateau, mvt);
                        }
                    }
                } else {
                    // Le pion est déjà placé :
                    mvt.c = p->get_coord();
                    
                    for (auto d : {HAUT, DROITE, BAS, GAUCHE}) {
                        mvt.d = d;
                        
                        // Actions
                        for (auto a : {D, T}) {
                            mvt.a = a;
                            victoire = ajouter_noeud(n, plateau, mvt);
                        }
                    }
                }
            }
            
            // C'est fait !
            n.get_val()->prevu = true;
        }
        
        // Ajout des noeuds fils
        for (int i = 0; i < n.nb_fils(); i++) {
            noeuds.push(n[i]);
        }
    }
}

bool IntellIA::ajouter_noeud(Arbre<ICoup> n, Plateau plateau, Mov mvt) {
    // Test
    Retour r = plateau.appliquer_mov(m_equipe, mvt);
    bool victoire;
    
    if ((r == OK) || (r == FIN)) {
        n.ajouter_fils(gen_icoup(plateau, mvt, r));
        victoire = (r == FIN);
    }
    
    if (r == FIN) {
        // On augmente le niveau de coolitude du chemin !
        Arbre<ICoup> p = n;
        
        while (!p.is_null()) {
            p.get_val()->cool++;
            p = p.get_pere();
        }
    }
    
    return victoire;
}

ICoup IntellIA::gen_icoup(Plateau& dep, Mov mvt, Retour r) const {
    // Application du mvt
    return {mvt, dep, r == FIN, false, (r == FIN) ? 1 : 0};
}

void IntellIA::maj_icoups(Plateau nouv) {
}

// Méthodes
void IntellIA::afficher_allegro() noexcept {
}

void IntellIA::afficher_console() noexcept {
}

bool IntellIA::jouer(Plateau& p) {
    // On choisi le coup
    int s = 0;
    
    for (int i = 0; i < m_arbre.nb_fils(); i++) {
        s += m_arbre[i].get_val()->cool;
    }
    
    if (s == 0) {
        m_arbre = m_arbre[random(0, m_arbre.nb_fils())];
    } else {
        int rand = random(0, s);
        
        for (int i = 0; i < m_arbre.nb_fils(); i++) {
            rand -= m_arbre[i].get_val()->cool;
            
            if (rand <= 0) {
                m_arbre = m_arbre[i];
                break;
            }
        }
    }
    
    m_arbre.suppr_parents();
    
    // On joue
    Retour ret = p.appliquer_mov(m_equipe, m_arbre.get_val()->m);
    
    // On met à jour l'arbre
    maj_icoups(p);
    prevision();
    
    usleep(1000000);
    
    return ret == FIN;
}
