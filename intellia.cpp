// Importations
#include <unistd.h>

#include <queue>
#include <vector>

#include "arbre.h"
#include "coordonnee.h"
#include "ia.h"
#include "intellia.h"
#include "objpoussable.h"
#include "plateau.h"

// Constructeur
IntellIA::IntellIA(Equipe e) : IA(e) {
    // Remplissage
    for (int i = 0; i < 5; i++) {
        for (char j = 'A'; j < 'F'; j++) {
            if ((j == 'A') || (j == 'E') || (i == 0) || (i == 4)) m_pos_placement.push_back(Coordonnees(j, i));
        }
    }
}

// Méthodes privées
void IntellIA::prevision(Plateau depart) {
    // Déclarations
    Arbre<ICoup> arbre(gen_icoup(depart, m_mov, OK));
    bool victoire = false;
    bool pplacer = false;   // 1er placement
    bool tourne = false;
    int nbpj = 0;
    
    std::queue<Arbre<ICoup>> noeuds;
    std::shared_ptr<ObjPoussable> tmp;
    noeuds.push(arbre);
    
    // Parcours de l'arbre (generation)
    while (!noeuds.empty() && !victoire) {
        // Récupération du noeud
        auto n = noeuds.front();
        noeuds.pop();
        
        // Réinit
        pplacer = false;
        Mov mvt;
        
        // Calcul des noeuds fils
        Plateau plateau(n.get_val()->p);
        
        // Parcours du plateau
        for (auto p : plateau.get_equipe(m_equipe)) {
            mvt.c = p->get_coord();
            
            // recupération du pion en face du pion p
            tourne = false;
            tmp = plateau.get_pion(mvt.c + p->get_dir());
            
            if (tmp) {
                // on peut tourner que s'il y a pas une montagne en face
                if (tmp->get_equipe() != MONTAGNE) {
                    tourne = true;
                }
            }
            
            // Parcours des 4 directions
            for (auto d : {HAUT, DROITE, BAS, GAUCHE}) {
                mvt.d = d;
                
                // deplacement
                mvt.a = D;
                victoire |= ajouter_noeud(n, plateau, mvt);
                
                // tourner !
                if (tourne & !victoire) {
                    tmp = plateau.get_pion(mvt.c + d);
                    
                    if (tmp) {
                        if (tmp->get_equipe() == MONTAGNE) {
                            mvt.a = T;
                            victoire |= ajouter_noeud(n, plateau, mvt);
                        }
                    }
                }
            }
        }
        
        // Si nécéssaire (on ne gagne pas) on essaye en placant un pion (s'il en reste)
        if (!victoire) {
            nbpj = plateau.get_equipe(m_equipe).size();
            
            if (nbpj < 5) {
                pplacer = (nbpj == 0);
                
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
                    if (pplacer) {
                        if ((c.get_col() == 2) && (c.get_lig() == 'A')) {
                            victoire |= ajouter_noeud(n, plateau, mvt);
                        }
                    } else {
                        victoire |= ajouter_noeud(n, plateau, mvt);
                    }
                }
            }
        }
        
        if (!victoire) {
            // Ajout des noeuds fils
            for (int i = 0; i < n.nb_fils(); i++) {
                noeuds.push(n[i]);
            }
        }
    }
    
    // Choix final du prochain mouvement
    int max = 0, t = 0, choix = -1;
    
    for (int i = arbre.nb_fils()-1; i >= 0; i--) {
        t = arbre[i].get_val()->cool;
        
        if (t > max) {
            max = t;
            choix = i;
        }
        
        std::cout << t << " ";
    }
    
    if (choix == -1) {
        m_mov = arbre[random(0, arbre.nb_fils())].get_val()->m;
    } else {
        m_mov = arbre[choix].get_val()->m;
    }
    
    // Destruction de l'arbre
    arbre.incendie();
}

bool IntellIA::ajouter_noeud(Arbre<ICoup> n, Plateau plateau, Mov mvt) {
    // Applaction du coup
    unsigned nbpj = plateau.get_equipe(m_equipe).size();
    Retour r = plateau.appliquer_mov(m_equipe, mvt);
    
    // Tests
    if (nbpj > plateau.get_equipe(m_equipe).size()) {
        return false;
    }
    
    Arbre<ICoup> p = n.get_pere();
    
    while (!p.is_null()) {
        if (plateau == p.get_val()->p) {
            return false;
        }
        
        p = p.get_pere();
    }
    
    // Création du noeud
    if (r == OK) {
        n.ajouter_fils(gen_icoup(plateau, mvt, r));
    
    } else if (r == FIN) {
        n.ajouter_fils(gen_icoup(plateau, mvt, r));
        
        // On augmente le niveau de coolitude du chemin !
        Arbre<ICoup> p = n;
        
        while (!(p.is_null())) {
            p.get_val()->cool++;
            p = p.get_pere();
        }
        
        return true;
    }
    
    return false;
}

ICoup IntellIA::gen_icoup(Plateau& dep, Mov mvt, Retour r) const {
    // Application du mvt
    return {mvt, dep, r == FIN, (r == FIN) ? 1 : 0};
}

// Méthodes
void IntellIA::afficher_allegro() noexcept {
}

void IntellIA::afficher_console() noexcept {
}

bool IntellIA::jouer(Plateau& p) {
    // On choisi l'action
    prevision(p);
    
    // On joue
    Retour ret = p.appliquer_mov(m_equipe, m_mov);
    
    s_console.gotoLigCol(35, 0);
    switch (m_mov.a) {
    case P:
        std::cout << "P " << m_mov.c.get_lig() << m_mov.c.get_col();
        break;
    
    case D:
        std::cout << "D " << m_mov.c.get_lig() << m_mov.c.get_col();
        break;
    
    case T:
        std::cout << "T " << m_mov.c.get_lig() << m_mov.c.get_col();
        break;
    }
    
    switch (m_mov.d) {
    case HAUT:
        std::cout << " H" << std::endl;
        break;
    
    case DROITE:
        std::cout << " D" << std::endl;
        break;
    
    case BAS:
        std::cout << " B" << std::endl;
        break;
    
    case GAUCHE:
        std::cout << " G" << std::endl;
        break;
    
    case NO_DIR:
        // Meme si ca n'arrive jamais !
        break;
    }
    
    s_attendre(1000);
    
    return ret == FIN;
}
