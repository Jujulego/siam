// Importations
#include <vector>

#include "affichable.h"
#include "coordonnee.h"
#include "joueur.h"
#include "plateau.h"
#include "progjoueur.h"

// Constructeur
ProgJoueur::ProgJoueur(Equipe e, std::vector<Mov> const& actions) : Joueur(e), m_actions(actions) {
}

// Méthodes
void ProgJoueur::afficher_console() noexcept {
}

void ProgJoueur::afficher_allegro() noexcept {
}

bool ProgJoueur::jouer(Plateau& p) {
    s_console.gotoLigCol(40, 0);
    s_console.getch();
    
    Mov m = m_actions[m_i];
    
    m_i++;
    m_i %= m_actions.size();
    
    return p.appliquer_mov(m_equipe, m) == FIN;
}
