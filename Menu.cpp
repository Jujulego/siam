#include "alleg.h"
#include "ConsoleJoueur.h"
#include "Menu.h"
#include "randomia.h"
#include "objpoussable.h"

using namespace allegro;

// constructeur par defaut
Menu::Menu() : p(new Plateau()) {
}

Menu::~Menu() noexcept {
    delete j1;
    delete j2;
}

void Menu::afficher_allegro() noexcept
{
    bool action = false;
    BITMAP_PT menu = charger_bitmap("menu.bmp");

    draw_sprite(s_buffer, menu, 0, 0);
    rectfill(s_buffer, 420, 400, 620, 440, makecol(68,41,28));
    rect(s_buffer, 420, 400, 620, 440, makecol(91,64,45));
    textout_ex(s_buffer, font, "JOUER", 498, 417, makecol(255,255,255), -1);
    rectfill(s_buffer, 420, 460, 620, 500, makecol(68,41,28));
    rect(s_buffer, 420, 460, 620, 500, makecol(91,64,45));
    textout_ex(s_buffer, font, "QUITTER", 492, 477, makecol(255,255,255), -1);

    while (!action) {
        if (mouse_b&1) {
            if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 400) && (mouse_y <= 440)) action = true;
            //if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 460) && (mouse_y <= 500))
        }

        show_mouse(s_buffer);
        draw_sprite(screen, s_buffer, 0, 0);
    }
}

void Menu::afficherMenu() {

}
void Menu::creationJoueur()
{
    char choix;
    std::string choix1;
    std::string animal1;
    Equipe e1;
    Equipe e2;
    char animal;

    do
    {
        s_console.gotoLigCol(0,0);
        std::cout <<"Quel personnage voulez vous incarner ?"<<std::endl;
        std::cout <<"1. Elephant"<<std::endl;
        std::cout <<"2. Rhinoceros"<<std::endl;
        s_console.gotoLigCol(4,4);
        std::cin >> animal1;
        animal=animal1[0];
    }while (animal != '1'&& animal != '2');

    switch (animal)
    {
       case '1':

        e1 = ELEPH;
        e2 = RHINO;
        break;


        case '2':

        e1 = RHINO;
        e2 = ELEPH;

        default:

        std::cout<<"Erreur, ce choix n'est pas autorisé"<<std::endl;
        break;

    }

    do
    {
        s_console.gotoLigCol(0,0);
        std::cout << "Quel mode de jeu?"<<std::endl;
        std::cout << "1. J1 vs J2"<<std::endl;
        std::cout << "2. J1 vs IA (Tutoriel)"<<std::endl;
        std::cout << "3. J1 vs IA (intermediaire)"<<std::endl;
        std::cout << "4. J1 vs IA (difficile)"<<std::endl;
        std::cout <<"        "<<std::endl;
        std::cin  >> choix1;
        choix=choix1[0];

    }while( choix != '1'&&choix != '2'&&choix != '3'&&choix != '4');

    switch(choix)
    {
        case '1':
                j1 = new ConsoleJoueur(e1, p);
                j2 = new ConsoleJoueur(e2, p);

            break;

        case '2':
                j1 = new ConsoleJoueur(e1, p);
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
                j1 = new ConsoleJoueur(e1, p);
                j2 = new RandomIA(e2);
            break;

        case '4':
            j1 = new ConsoleJoueur(e1, p);
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
    std::string choix1;
    do
    {
    s_console.gotoLigCol(0,0);
    std::cout <<"Que souhaitez vous faire?"<<std::endl;
    std::cout <<"1. Jouer     "<<std::endl;
    std::cout <<"2. Quitter   "<<std::endl;
    s_console.gotoLigCol(4,4);
    std::cout <<"        "<<std::endl;
    s_console.gotoLigCol(4,4);
    std::cin >> choix1;

    choix=choix1[0];

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

    // Tests
    bool fini = false;
    p->afficher();

    while (!fini) {
        j1->afficher();
        fini = j1->jouer(*p);
        p->afficher();

        if (fini)
            break;

        if (Affichable::getEtat() == ALLEGRO) {
            if (key[KEY_ESC])
                break;
        }

        j2->afficher();
        fini = j2->jouer(*p);
        p->afficher();

        if (Affichable::getEtat() == ALLEGRO) {
            if (key[KEY_ESC])
                break;
        }
    }
}
