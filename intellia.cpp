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
IntellIA::IntellIA(Equipe e, Plateau p) : IA(e) {
    // Remplissage
    for (int i = 0; i < 5; i++) {
        for (char j = 'A'; j < 'F'; j++) {
            if ((j == 'A') || (j == 'E') || (i == 0) || (i == 4)) m_pos_placement.push_back(Coordonnees(j, i));
        }
    }
    
    // Création du 1er mouvement
    Mov mvt = {P, Coordonnees((e == RHINO) ? 'A' : 'E', random(1, 3)), (e == RHINO) ? BAS : HAUT};
    
    m_arbre.set_val({mvt, p, false, false, true, 0});
    ajouter_noeud(m_arbre, p, mvt);
}

// Méthodes privées
void IntellIA::prevision() {
    // Déclarations
    bool victoire = false;
    bool tourne = false;
    
    std::queue<Arbre<ICoup>> noeuds;
    std::shared_ptr<ObjPoussable> tmp;
    noeuds.push(m_arbre);
    int nb = 0;
    
    // Parcours de l'arbre (generation)
    while (!noeuds.empty()) {
        s_console.gotoLigCol(35, 0);
        nb++;
        
        // Récupération du noeud
        Mov mvt = {P, Coordonnees('F', 5), BAS};
        
        auto n = noeuds.front();
        noeuds.pop();
        
        // Calcul des noeuds fils (si cela n'a pas déjà été fait)
        if (!(n.get_val()->prevu)) {
            Plateau plateau(n.get_val()->p);
            bool placer = true;
            
            plateau.afficher();
            std::cout << nb << " plus que " << noeuds.size() << std::endl;
            usleep(500000);
            
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
                            victoire |= ajouter_noeud(n, plateau, mvt);
                        }
                    }
                } else {
                    // Le pion est déjà placé :
                    mvt.c = p->get_coord();
                    
                    tourne = false;
                    tmp = plateau.get_pion(mvt.c + p->get_dir());
                    
                    if (tmp) {
                        if (tmp->get_equipe() != MONTAGNE) {
                            tourne = true;
                        }
                    }
                    
                    for (auto d : {HAUT, DROITE, BAS, GAUCHE}) {
                        mvt.d = d;
                        
                        // Actions
                        mvt.a = D;
                        victoire |= ajouter_noeud(n, plateau, mvt);
                        
                        if (tourne) {
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
            }
            
            // Ajout des noeuds fils
            s_console.gotoLigCol(36, 0);
//            std::cout << "+ de noeuds ! " << victoire << std::endl;
            
            if (!victoire) {
                for (int i = 0; i < n.nb_fils(); i++) {
                    noeuds.push(n[i]);
                }
            }
            
            // C'est fait !
            n.get_val()->prevu = true;
        }
    }
}

bool IntellIA::ajouter_noeud(Arbre<ICoup> n, Plateau plateau, Mov mvt) {
    // Applaction du coup
    unsigned nbpj = plateau.get_equipe(m_equipe).size();
    Retour r = plateau.appliquer_mov(m_equipe, mvt);
    
    // Tests
    if (!n.get_val()->tete) {
        if ((nbpj > plateau.get_equipe(m_equipe).size()) && (r != FIN)) {
//            s_console.gotoLigCol(37, 0);
//            std::cout << "boooouuum ! I" << std::endl;
            return false;
        }
        
        Arbre<ICoup> p = n.get_pere();
        
        while (!p.is_null()) {
            if (plateau == p.get_val()->p) {
//                s_console.gotoLigCol(37, 0);
//                std::cout << "boooouuum ! II" << std::endl;
                return false;
            }
            
            p = p.get_pere();
        }
    }
    
    // Création du noeud
    if ((r == OK) || (r == FIN)) {
        n.ajouter_fils(gen_icoup(plateau, mvt, r));
    }
    
    if (r == FIN) {
        // On augmente le niveau de coolitude du chemin !
        Arbre<ICoup> p = n;
        
        while (!p.is_null()) {
            p.get_val()->cool++;
            p = p.get_pere();
        }
        
//        s_console.gotoLigCol(37, 0);
//        std::cout << "victoire !" << std::endl;
        
        return true;
    }
    
    return false;
}

ICoup IntellIA::gen_icoup(Plateau& dep, Mov mvt, Retour r) const {
    // Application du mvt
    return {mvt, dep, r == FIN, false, false, 0};
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
    Mov m = m_arbre.get_val()->m;
    int s = 0;
    
    for (int i = 0; i < m_arbre.nb_fils(); i++) {
        s += m_arbre[i].get_val()->cool;
    }
    
//    std::cout << "bonzai !!! " << m_arbre.is_null() << std::endl;
    if (s) {
        std::cout << "s  : " << s << " r : " << random(0, s) << std::endl;
    }
//    std::cout << "nb : " << m_arbre.nb_fils() << std::endl;
    
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
//    std::cout << m_arbre.is_null() << std::endl;
    Retour ret = p.appliquer_mov(m_equipe, m);
    
    // On met à jour l'arbre
    maj_icoups(p);
    prevision();
    
/*    s_console.gotoLigCol(35, 0);
    switch (m.a) {
    case P:
        std::cout << "P" << m.c.get_lig() << m.c.get_col() << std::endl;
        break;
    
    case D:
        std::cout << "D" << m.c.get_lig() << m.c.get_col() << std::endl;
        break;
    
    case T:
        std::cout << "T" << m.c.get_lig() << m.c.get_col() << std::endl;
        break;
    }*/
    
//    s_console.getch();
    usleep(1000000);
    
    return ret == FIN;
}
