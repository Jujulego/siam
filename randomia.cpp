// Importations
#include <cstdlib>

#include "coordonnee.h"
#include "joueur.h"
#include "objpoussable.h"
#include "plateau.h"
#include "randomia.h"

// Constantes de contrôle
#define INTERET_P 1
#define INTERET_D 10
#define INTERET_T 5

// Constructeur
RandomIA::RandomIA(Equipe e) noexcept : IA(e) {
    // Remplissage de la map
    m_map = {
        {'A', std::vector<Coup>(5, {0, 0, 0, 0})},
        {'B', std::vector<Coup>(5, {0, 0, 0, 0})},
        {'C', std::vector<Coup>(5, {0, 0, 0, 0})},
        {'D', std::vector<Coup>(5, {0, 0, 0, 0})},
        {'E', std::vector<Coup>(5, {0, 0, 0, 0})},
    };
}

// Destructeur
RandomIA::~RandomIA() noexcept {
}

// Méthodes
void RandomIA::set_coup(char lig, int col, Action a, int val) {
    // Modif du coup
    Coup& c = m_map[lig][col];
    int s = c.s;
    
    switch (a) {
    case D:
        c.s += val - c.d;
        c.d = val;
        break;
    
    case P:
        c.s += val - c.p;
        c.p = val;
        break;
    
    case T:
        c.s += val - c.t;
        c.t = val;
        break;
    }
    
    // Modif de la somme générale
    m_somme += c.s - s;
}

void RandomIA::reset_map(int p) {
    // Mise à zéro
    m_somme = 0;
    
    // Etat de départ
    for (char l = 'A'; l <= 'E'; l++) {
        for (int c = 0; c <= 4; c++) {
            m_map[l][c] = {0, 0, 0, 0};
            
            if ((l == 'A') || (l == 'E') || (c == 0) || (c == 4)) set_coup(l, c, P, p);
        }
    }
}

void RandomIA::allegro_console() noexcept {
}

void RandomIA::allegro_allegro() noexcept {
}

bool RandomIA::jouer(Plateau& p) {
    // Analyse du plateau
    reset_map(INTERET_P * p.get_equipe(m_equipe).size());
    
    // ajout des positions déplacables
    for (auto p : p.get_plateau()) {
        Coordonnees c = p->get_coord();
        
        if ((c.get_lig() != 'F') && (p->get_equipe() == m_equipe))
            set_coup(c.get_lig(), c.get_col(), D, INTERET_D);
    }
    
    // Détermination du pion
    int case_ = random(1, m_somme), c = 0;
    char l = 'A';
    
    for (; l <= 'E'; l++) {
        for (c = 0; c <= 4; c++) {
            std::cout << case_ << " ";
            case_ -= m_map[l][c].s;
            
            if (case_ <= 0) break;
        }
        std::cout << std::endl;
        
        if (case_ <= 0) break;
    }
    
    std::cout << l << c << std::endl;
    bool r = false;
    
    if ((l != 'F') && (c != 5)) {
        // Détermination de l'action
        Coordonnees coord = Coordonnees(l, c);
        Coup& coup = m_map[l][c];
        
        int act = random(1, coup.s);
        
        // déplacement
        std::cout << act;
        act -= coup.d;
        std::cout << " " << act;
        
        if (act <= 0) {
            std::cout << " D";
            r = (p.deplacer(m_equipe, coord, p.get_pion(coord)->get_dir()) == FIN);
        } else {
            // placer
            act -= coup.p;
            std::cout << " " << act;
            
            if (act <= 0) {
                std::cout << " P";
                
                // Choix de la direction
                Direction d = GAUCHE;
                
                if (l == 'A')
                    d = BAS;
                else if (l == 'E')
                    d = HAUT;
                else if (c == 0)
                    d = DROITE;
                
                r = (p.placer(m_equipe, coord, d) == FIN);
            } else {
                // tourner
                std::cout << " T";
            }
        }
        
    }
    
    s_console.getch();
    return r;
}
