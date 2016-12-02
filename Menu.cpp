#include "alleg.h"
#include "ConsoleJoueur.h"
#include "Menu.h"
#include "randomia.h"
#include "objpoussable.h"

using namespace allegro;

// constructeur par defaut
Menu::Menu() {
}

Menu::~Menu() noexcept {
    delete j1;
    delete j2;
}


void Menu::afficher_allegro() noexcept {
}

void Menu::afficherMenu() {

}
void Menu::creationJoueur()
{
    char choix;
    char animal;
    Equipe e1;
    Equipe e2;




    s_console.gotoLigCol(0,0);
    std::cout <<"Quel personnage voulez vous incarner ?"<<std::endl;
    std::cout <<"1. Elephant"<<std::endl;
    std::cout <<"2. Rhinoceros"<<std::endl;
    s_console.gotoLigCol(4,4);
    std::cin >> animal;

    if (animal =='1')
    {
        e1 = ELEPH;
        e2 = RHINO;
    }


    else if (animal=='2')
    {
        e1 = RHINO;
        e2 = ELEPH;
    }

    else
        std::cout<<"Erreur, ce choix n'est pas autorisé"<<std::endl;
    s_console.gotoLigCol(0,0);
    std::cout << "Quel mode de jeu?"<<std::endl;
    std::cout << "1. J1 vs J2"<<std::endl;
    std::cout << "2. J1 vs IA (Tutoriel)"<<std::endl;
    std::cout << "3. J1 vs IA (intermediaire)"<<std::endl;
    std::cout << "4. J1 vs IA (difficile)"<<std::endl;

    std::cin  >> choix;

    switch(choix)
    {
        case '1':
                j1 = new ConsoleJoueur(e1);
                j2 = new ConsoleJoueur(e2);

            break;

        case '2':
                j1 = new ConsoleJoueur(e1);
                j2 = new ProgJoueur(e2, {{P, Coordonnees('A', 4), BAS},
                                         {P, Coordonnees('A', 4), BAS},
                                         {P, Coordonnees('D', 2), DROITE},
                                         {D, Coordonnees('A', 4), BAS},
                                         {D, Coordonnees('B', 4), GAUCHE},
                                         {D, Coordonnees('B', 3), BAS},
                                         {D, Coordonnees('D', 2), DROITE},
                                         {D, Coordonnees('D', 3), DROITE}});
            break;

        case '3':
                j1 = new ConsoleJoueur(e1);
                j2 = new RandomIA(e2);
            break;

        case '4':
            j1 = new ConsoleJoueur(e1);
            j2 = new IntellIA(e2);
        break;

        default:
        std::cout<<"Erreur, cette direction n'existe pas"<<std::endl;
        break;
    }
}

void Menu::afficher_console()noexcept
{
    char choix;
    do
    {
    s_console.gotoLigCol(0,0);
    std::cout <<"Que souhaitez vous faire?"<<std::endl;
    std::cout <<"1. Jouer     "<<std::endl;
    std::cout <<"2. Quitter   "<<std::endl;
    s_console.gotoLigCol(4,4);
    std::cin >> choix;

    }while (choix !='1' && choix !=2);


    switch(choix)
    {
        case '1':
            break;

        case '2':
            return;

            break;

        default:
        std::cout<<"Erreur, cette direction n'existe pas"<<std::endl;
        break;


    }
    //afficherMenu();
    creationJoueur();

    // Declarations
    Console c;
    Plateau p;


/*    Joueur* j2 = new ProgJoueur(ELEPH, {
        {P, Coordonnees('E', 2), GAUCHE},
        {P, Coordonnees('D', 3), GAUCHE},
        {P, Coordonnees('E', 4), HAUT},
        {D, Coordonnees('D', 3), DROITE},
        {T, Coordonnees('D', 4), HAUT},
        {D, Coordonnees('E', 4), GAUCHE},
        {D, Coordonnees('E', 3), DROITE},
    });*/

    // Tests
    bool fini = false;
    p.afficher();

    if (Affichable::getEtat() == ALLEGRO)
    {
        while ((!key[KEY_ESC]) && (!fini))
        {
            j1->afficher();
            fini = j1->jouer(p);
            p.afficher();

            if (fini)
                break;

            j2->afficher();
            fini = j2->jouer(p);
            p.afficher();
        }
    }
    else
    {
        c.gotoLigCol(40, 0);

        while (!fini)
        {
            j1->afficher();
            fini = j1->jouer(p);
            p.afficher();

            if (fini)
                break;

            j2->afficher();
            fini = j2->jouer(p);
            p.afficher();
        }
    }
}
