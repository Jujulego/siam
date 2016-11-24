// Importations
#include <cstdlib>

#include "coordonnee.h"
#include "joueur.h"
#include "objpoussable.h"
#include "plateau.h"
#include "randomia.h"

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
    Coup* c = &(m_map[lig][col]);
    int s = c->s;
    
    switch (a) {
    case D:
        c->s += val - c->d;
        c->d = val;
        break;
    
    case P:
        c->s += val - c->p;
        c->p = val;
        break;
    
    case T:
        c->s += val - c->t;
        c->t = val;
        break;
    }
    
    // Modif de la somme générale
    m_somme += c->s - s;
}

void RandomIA::reset_map() {
    // Mise à zéro
    m_somme = 0;
    
    // Etat de départ
    for (char l = 'A'; l <= 'E'; l++) {
        for (int c = 0; c <= 4; c++) {
            m_map[l][c] = {0, 0, 0, 0};
            
            if ((l == 'A') || (l == 'E') || (c == 0) || (c == 4)) {
                set_coup(l, c, P, 1);
            }
        }
    }
}

void RandomIA::allegro_console() noexcept {
}

void RandomIA::allegro_allegro() noexcept {
}

bool RandomIA::jouer(Plateau& p) {
    // Analyse du plateau
    reset_map();
    
    // Détermination du coup
    int coup = random(0, m_somme), c = 0;
    char l = 'A';
    
    for (; l <= 'E'; l++) {
        for (c = 0; c <= 4; c++) {
            std::cout << coup << " ";
            coup -= m_map[l][c].s;
            
            if (coup <= 0) break;
        }
        std::cout << std::endl;
        
        if (coup <= 0) break;
    }
    
    std::cout << l << c;
    s_console.getch();
    
    if ((l != 'F') && (c != 5)) {
        return (p.placer(m_equipe, Coordonnees(l, c), BAS) == FIN);
    }
    
    return false;
}
