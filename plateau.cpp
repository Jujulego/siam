// Importations
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "alleg.h"
#include "affichable.h"
#include "coordonnee.h"
#include "montagne.h"
#include "pion.h"
#include "plateau.h"

#ifndef __gnu_linux__
static const std::string LIGNE_HAUT = "\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf";
static const std::string LIGNE_MIL1 = "\xb3       \xb3       \xb3       \xb3       \xb3       \xb3";
static const std::string LIGNE_MIL2 = "\xc3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4";
static const std::string LIGNE_BAS  = "\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9";
#else
static const std::string LIGNE_HAUT = "\xe2\x95\xad\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xae";
static const std::string LIGNE_MIL1 = "\xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82";
static const std::string LIGNE_MIL2 = "\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xa4";
static const std::string LIGNE_BAS  = "\xe2\x95\xb0\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xaf";
#endif

// Construteurs
Plateau::Plateau() {
    // Chargement des images
    if (s_etat == ALLEGRO) {
        m_map = allegro::charger_bitmap("map.bmp");
    }

    // Ajout des montagnes
    for (unsigned i = 1; i < 4; i++)
        m_pions_joues.push_back((std::shared_ptr<ObjPoussable>) new Montagne(Coordonnees('C', i)));

    // Création des équipes
    for (auto e : {ELEPH, RHINO}) {
        for (unsigned i = 0; i < 5; i++) {
            m_equipes.push_back((std::shared_ptr<Pion>) new Pion(e));
        }
    }
}

// Méthodes
Retour Plateau::placer(Equipe e, Coordonnees coord, Direction dir) {
    // Récupération du pion
    Retour r = OK;

    for (auto p : m_equipes) {
        if ((p->get_equipe() == e) && (p->get_coord().get_lig() == 'F')) {
            coord -= dir;

            p->placer(coord, dir);
            r = _deplacer(p, coord, dir);

            if ((r == OK) || (r == FIN)) {
                m_pions_joues.push_back(p);
            } else {
                p->placer(Coordonnees('F', 5), BAS);
            }

            return r;
        }
    }

    m_message = "Vous n'avez plus le pion libre !";
    return PASPION;
}

Retour Plateau::deplacer(Equipe e, Coordonnees coord, Direction dir) {
    // Récupération du pion
    auto pion = get_pion(coord);

    if (pion == nullptr) {
        m_message = "Il n'y a pas de pion ici !";
        return PASPION;
    }

    if (pion->get_equipe() != e) {
        m_message = "Hey c'est pas un de tes pions ...";
        return PASPION;
    }

    return _deplacer(pion, coord, dir);
}

float Plateau::get_resistance(Coordonnees coord, Direction dir, std::set<std::shared_ptr<ObjPoussable>>* objdevant) {
    // Déclarations
    float resist = 0.0;

    // Parcours de ce qu'il y a avant le pion
    for (Coordonnees c = coord + dir; (c.get_lig() <= 'E') && (c.get_lig() >= 'A') && (c.get_col() <= 4) && (c.get_col() >= 0); c += dir) {
        auto p = get_pion(c);

        if (p == nullptr)
            break;

        resist += p->get_resistance(dir);

        if (objdevant != nullptr)
            objdevant->insert(p);
    }

    return resist;
}

Retour Plateau::_deplacer(std::shared_ptr<ObjPoussable> pion, Coordonnees coord, Direction dir) {
    // Récupérations des éléments dans la direction
    std::set<std::shared_ptr<ObjPoussable>> objdevant = {pion};

    if (dir == pion->get_dir()) {
        // Check resistance
        if (get_resistance(coord, dir, &objdevant) >= pion->get_force(dir)) {
            m_message = "Impossible de bouger, c'est trop lourd ...";
            return ERREUR;
        }
    } else {
        if (get_pion(coord + dir) != nullptr) {
            m_message = "C'est occupé !";
            return ERREUR;
        }
    }

    // Déplacements !
    Retour r = OK;
    for (auto p : objdevant) {
        if (p->deplacer(dir)) {
            if (p->get_equipe() == MONTAGNE) {
                if (pion->get_equipe() == RHINO) {
                    m_message = "Les Rhinoceros ont gagné !";
                } else if (pion->get_equipe() == ELEPH) {
                    m_message = "Les Elephants ont gagné !";
                }

                r = FIN;
            } else {
                for (auto it = m_pions_joues.begin(); it != m_pions_joues.end(); it++) {
                    if (*it == p) {
                        m_pions_joues.erase(it);
                        break;
                    }
                }
            }
        }
    }

    return r;
}

Retour Plateau::tourner(Equipe e, Coordonnees coord, Direction dir) {
    // Récupération du pion
    auto pion = get_pion(coord);

    if (pion == nullptr) {
        m_message = "Il n'y a pas de pion ici !";
        return PASPION;
    }

    if (pion->get_equipe() != e) {
        m_message = "Hey c'est pas un de test pions ...";
        return ERREUR;
    }

    pion->tourner(dir);
    return OK;
}

Retour Plateau::appliquer_mov(Equipe e, Mov m) {
    // Branchement !
    Retour r;

    switch (m.a) {
    case P:
        r = placer(e, m.c, m.d);
        break;

    case D:
        r = deplacer(e, m.c, m.d);
        break;

    case T:
        r = tourner(e, m.c, m.d);
        break;
    }

    return r;
}

std::shared_ptr<ObjPoussable> Plateau::get_pion(Coordonnees coord) {
    for (auto p : m_pions_joues) {
        if (p->get_coord() == coord)
            return p;
    }

    return nullptr;
}

std::vector<std::shared_ptr<Pion>> const& Plateau::get_pions() const {
    return m_equipes;
}

std::vector<std::shared_ptr<Pion>> Plateau::get_equipe(Equipe e) const {
    std::vector<std::shared_ptr<Pion>> equipe;

    for (auto p : get_pions()) {
        if ((p->get_coord().get_lig() == 'F') && (p->get_equipe() == e)) equipe.push_back(p);
    }

    return equipe;
}

std::vector<std::shared_ptr<ObjPoussable>> const& Plateau::get_plateau() const {
    return m_pions_joues;
}

void Plateau::afficher_allegro() noexcept {
    allegro::draw_sprite(s_buffer, m_map, 0, 0);

    // Affichage des pions sur le plateau
    for (auto o : m_pions_joues) {
        o->afficher_allegro();
    }

    // Affichage des pions restants
    unsigned nbr = 0;
    unsigned nbe = 0;
    /*COLOR_MAP calque;
    create_trans_table(&calque)*/

    for (auto p : m_equipes) {
        switch (p->get_equipe()) {
        case RHINO:
            if (p->get_coord().get_lig() == 'F') draw_sprite(s_buffer,p->get_image(),720+(nbr*62),460);

            nbr++;
            break;

        case ELEPH:
            if (p->get_coord().get_lig() == 'F') draw_sprite(s_buffer,p->get_image(),720+(nbe*62),165);

            nbe++;
            break;

        default:
            break;
        }
    }

    allegro::show_mouse(s_buffer);
}

//Affichage sur la console
void Plateau::afficher_console() noexcept {
    // Affichage du plateau
    s_console.clear();
    s_console.gotoLigCol(3, 0);

    char l;

    std::cout << "       0       1       2       3       4" << std::endl;
    std::cout << "   " << LIGNE_HAUT << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            l = ' ';
            if (j % 2) {
                l = 'A' + i;
            }

            std::cout << " " << l << " " << LIGNE_MIL1 << " " << l << std::endl;
        }

        if (i != 4) {
            std::cout << "   " << LIGNE_MIL2 << std::endl;
        }
    }
    std::cout << "   " << LIGNE_BAS << std::endl;
    std::cout << "       0       1       2       3       4" << std::endl;

    // Affichage des Equipes
    s_console.gotoLigCol(0, 0);
    std::cout << "Equipes des Rhinoceros :" << std::endl;

    s_console.gotoLigCol(27, 0);
    std::cout << "Equipes des Elephants :" << std::endl;

    // Affichage des pions restants
    unsigned nbr = 0;
    unsigned nbe = 0;

    for (auto p : m_equipes) {
        switch (p->get_equipe()) {
        case RHINO:
            s_console.gotoLigCol(1, nbr * 2 + 5);

            s_console.setColor(COLOR_RED);
            if (p->get_coord().get_lig() == 'F')
                s_console.setColor(COLOR_GREEN);

            std::cout << "R" << std::endl;
            s_console.setColor();
            nbr++;
            break;

        case ELEPH:
            s_console.gotoLigCol(28, nbe * 2 + 5);

            s_console.setColor(COLOR_RED);
            if (p->get_coord().get_lig() == 'F')
                s_console.setColor(COLOR_GREEN);

            std::cout << "E" << std::endl;
            s_console.setColor();
            nbe++;
            break;

        default:
            break;
        }
    }

    // Affichage des pions
    for (auto o : m_pions_joues) {
        o->afficher();
    }

    // Affichage du message
    s_console.gotoLigCol(30, 2);
    Affichable::erreur(m_message);
    m_message = "";
}
