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
    bool placer = true;
    bool tourne = false;
    
    std::queue<Arbre<ICoup>> noeuds;
    std::shared_ptr<ObjPoussable> tmp;
    noeuds.push(arbre);
//    int nb = 0;
    
    // Parcours de l'arbre (generation)
    while (!noeuds.empty()) {
        // Récupération du noeud
        auto n = noeuds.front();
        noeuds.pop();
        
        // Réinit
        pplacer = false;
        placer = true;
        Mov mvt;
        
        // Calcul des noeuds fils
        Plateau plateau(n.get_val()->p);
        
//        plateau.afficher();
//        s_console.gotoLigCol(35, 0);
//        std::cout << nb++ << " plus que " << noeuds.size() << std::endl;
//        usleep(50000);
        
        // Parcours du plateau
        for (auto p : plateau.get_full_equipe(m_equipe)) {
            // Pion est hors du plateau
            if (p->get_coord().get_lig() == 'F') {
                if (placer && !victoire) {
                    pplacer = (plateau.get_equipe(m_equipe).size() == 0);
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
                        if ((!pplacer) || ((c.get_col() != 0) && (c.get_col() != 4)))
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
        }
        
        // Ajout des noeuds fils
//        s_console.gotoLigCol(36, 0);
//        std::cout << "+ de noeuds ! " << victoire << std::endl;
        
        if (!victoire) {
            for (int i = 0; i < n.nb_fils(); i++) {
                noeuds.push(n[i]);
            }
        }
    }
    
    // Choix final du prochain mouvement
    int s = 0, rand = 0;
    
    for (int i = 0; i < arbre.nb_fils(); i++) {
        s += arbre[i].get_val()->cool;
        std::cout << arbre[i].get_val()->cool << " ";
    }
    
//    std::cout << "bonzai !!! " << arbre.is_null() << std::endl;
    std::cout << std::endl << "s : " << s;
    if (s) {
        std::cout << "    r : " << random(1, s) << std::endl;
    }
//    std::cout << "nb : " << arbre.nb_fils() << std::endl;
    
    if (s == 0) {
        m_mov = arbre[random(0, arbre.nb_fils())].get_val()->m;
    } else {
        rand = random(1, s);
        
        for (int i = 0; i < arbre.nb_fils(); i++) {
            rand -= arbre[i].get_val()->cool;
            
            if (rand <= 0) {
                m_mov = arbre[i].get_val()->m;
                break;
            }
        }
    }
}

bool IntellIA::ajouter_noeud(Arbre<ICoup> n, Plateau plateau, Mov mvt) {
    // Applaction du coup
    unsigned nbpj = plateau.get_equipe(m_equipe).size();
//    plateau.afficher();
//    usleep(500000);
    
    Retour r = plateau.appliquer_mov(m_equipe, mvt);
    
/*    plateau.afficher();
    
    s_console.gotoLigCol(37, 0);
    switch (r) {
    case OK:
        std::cout << "OK" << std::endl;
        break;
    
    case FIN:
        std::cout << "FIN" << std::endl;
        break;
    
    case ERREUR:
        std::cout << "ERREUR" << std::endl;
        break;
    
    case PASPION:
        std::cout << "PASPION" << std::endl;
        break;
    }*/
    
    // Tests
    if (!n.get_val()->tete) {
        if ((nbpj > plateau.get_equipe(m_equipe).size())) {// && (r != FIN)) {
//            s_console.gotoLigCol(38, 0);
//            std::cout << nbpj << " " << plateau.get_equipe(m_equipe).size() << " I" << std::endl;
//            usleep(5000);
            
            return false;
        }
        
        Arbre<ICoup> p = n.get_pere();
        
        while (!p.is_null()) {
            if (plateau == p.get_val()->p) {
//                s_console.gotoLigCol(38, 0);
//                std::cout << "boooouuum ! II" << std::endl;
//                usleep(500000);
                
                return false;
            }
            
            p = p.get_pere();
        }
    }
    
//    s_console.gotoLigCol(38, 0);
//    std::cout << "              " << std::endl;
//    usleep(500000);
    
    // Création du noeud
    if ((r == OK) || (r == FIN)) {
        n.ajouter_fils(gen_icoup(plateau, mvt, r));
    }
    
    if (r == FIN) {
        // On augmente le niveau de coolitude du chemin !
        Arbre<ICoup> p = n;
        
        while (!(p.is_null())) {
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
    return {mvt, dep, r == FIN, false, false, (r == FIN) ? 1 : 0};
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
    }
    
//    s_console.getch();
    s_attendre(1000);
    
    return ret == FIN;
}
