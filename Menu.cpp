#include "Menu.h"

Menu::Menu()
{
    //constructeur par default
}

Menu:: ~Menu() noexcept
{

}


void afficher_allegro() noexcept
{

}



void Menu::afficherMenu()
{
    char choix;

    std::cout <<"Que souhaitez vous faire?"<<std::endl;
    std::cout <<"1. Jouer"<<std::endl;
    std::cout <<"2. Quitter"<<std::endl;
    std::cin>>choix;

    switch(choix)
    {
        case '1':
    std::cout <<"1. Jouer"<<std::endl;
            break;

        case '2':
        std::cout <<"2. Quitter"<<std::endl;
            break;
    }


}
void Menu::creationJoueur()
{
    char choix;
    char animal;
    Equipe e1;
    Equipe e2;
    Joueur* j1=NULL;
    Joueur* j2=NULL;

    std::cout <<"Quel personnage voulez vous incarner ?"<<std::endl;
    std::cout <<"1. Elephant"<<std::endl;
    std::cout <<"2. Rhinoceros"<<std::endl;
    std::cin>>animal;

    if (animal =='1')
    {
        e1=ELEPH;
        e2=RHINO;
    }


    else if (animal=='2')
    {
        e1=RHINO;
        e2=ELEPH;
    }

    else
        std::cout<<"Erreur, ce choix n'est pas autorisé"<<std::endl;

    std::cout <<"Quel mode de jeu?"<<std::endl;
    std::cout <<"1. J1 vs J2"<<std::endl;
    std::cout <<"2. J1 vs IA"<<std::endl;
    std::cin>>choix;

    switch(choix)
    {
        case '1':
                j1 = new ConsoleJoueur(e1);
                j2 = new ConsoleJoueur(e2);

            break;

        case '2':
                j1 = new ConsoleJoueur(e1);
                j2 = new RandomIA(e2);
            break;
    }


}

void Menu::afficher_console()noexcept
{
    Joueur* j1=NULL;
    Joueur* j2=NULL;
    afficherMenu();
    creationJoueur();

    // Déclarations
    Console c;
    Plateau p;


/*    Joueur* j1 = new ProgJoueur(RHINO, {
        {P, Coordonnees('A', 4), BAS},
        {P, Coordonnees('A', 4), BAS},
        {P, Coordonnees('D', 2), DROITE},
        {D, Coordonnees('A', 4), BAS},
        {D, Coordonnees('B', 4), GAUCHE},
        {D, Coordonnees('B', 3), BAS},
        {D, Coordonnees('D', 2), DROITE},
        {D, Coordonnees('D', 3), DROITE},
    });*/
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
    delete j1;
    delete j2;
}
