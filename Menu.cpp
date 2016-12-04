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
    bool action = false, play = true, fini = false;
    int win;
    BITMAP_PT menu = charger_bitmap("menu.bmp");
    Equipe e1;
    Equipe e2;

    // Premier menu
    draw_sprite(s_buffer, menu, 0, 0);
    rectfill(s_buffer, 420, 400, 620, 440, makecol(68,41,28));
    rect(s_buffer, 420, 400, 620, 440, makecol(91,64,45));
    textout_ex(s_buffer, font, "JOUER", 498, 417, makecol(255,255,255), -1);
    rectfill(s_buffer, 420, 450, 620, 490, makecol(68,41,28));
    rect(s_buffer, 420, 450, 620, 490, makecol(91,64,45));
    textout_ex(s_buffer, font, "QUITTER", 492, 467, makecol(255,255,255), -1);

    while (!action) {
        if (mouse_b&1) {
            if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 400) && (mouse_y <= 440)) {
                action = true;
                play = true;
            }

            if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 450) && (mouse_y <= 490)) {
                action = true;
                play = false;
            }
        }

        show_mouse(s_buffer);
        draw_sprite(screen, s_buffer, 0, 0);
    }

    action = false;
    mouse_b &= 0;

    if (play) {
        // Choix équipe
        draw_sprite(s_buffer, menu, 0, 0);
        textout_ex(s_buffer, font, "Quelle equipe voulez-vous prendre ?", 390, 370, makecol(255,255,255), -1);
        rectfill(s_buffer, 420, 400, 620, 440, makecol(68,41,28));
        rect(s_buffer, 420, 400, 620, 440, makecol(91,64,45));
        textout_ex(s_buffer, font, "ELEPHANT", 490, 417, makecol(255,255,255), -1);
        rectfill(s_buffer, 420, 450, 620, 490, makecol(68,41,28));
        rect(s_buffer, 420, 450, 620, 490, makecol(91,64,45));
        textout_ex(s_buffer, font, "RHINOCEROS", 482, 467, makecol(255,255,255), -1);

        while (!action) {
            if (mouse_b&1) {
                if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 400) && (mouse_y <= 440)) {
                    action = true;
                    e1 = ELEPH;
                    e2 = RHINO;
                }

                if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 450) && (mouse_y <= 490)) {
                    action = true;
                    e1 = RHINO;
                    e2 = ELEPH;
                }
            }

            show_mouse(s_buffer);
            draw_sprite(screen, s_buffer, 0, 0);
        }

        action = false;
        mouse_b &= 0;

        // Choix mode de jeu
        draw_sprite(s_buffer, menu, 0, 0);
        textout_ex(s_buffer, font, "Quel mode de jeu ?", 450, 370, makecol(255,255,255), -1);
        rectfill(s_buffer, 420, 400, 620, 440, makecol(68,41,28));
        rect(s_buffer, 420, 400, 620, 440, makecol(91,64,45));
        textout_ex(s_buffer, font, "J1 vs J2", 490, 417, makecol(255,255,255), -1);
        rectfill(s_buffer, 420, 450, 620, 490, makecol(68,41,28));
        rect(s_buffer, 420, 450, 620, 490, makecol(91,64,45));
        textout_ex(s_buffer, font, "J1 vs IA (Tutoriel)", 449, 467, makecol(255,255,255), -1);
        rectfill(s_buffer, 420, 500, 620, 540, makecol(68,41,28));
        rect(s_buffer, 420, 500, 620, 540, makecol(91,64,45));
        textout_ex(s_buffer, font, "J1 vs IA (intermediaire)", 427, 517, makecol(255,255,255), -1);
        rectfill(s_buffer, 420, 550, 620, 590, makecol(68,41,28));
        rect(s_buffer, 420, 550, 620, 590, makecol(91,64,45));
        textout_ex(s_buffer, font, "J1 vs IA (difficile)", 443, 567, makecol(255,255,255), -1);

        while (!action) {
            if (mouse_b&1) {
                if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 400) && (mouse_y <= 440)) {
                    action = true;
                    j1 = new ConsoleJoueur(e1, p);
                    j2 = new ConsoleJoueur(e2, p);
                }

                if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 450) && (mouse_y <= 490)) {
                    action = true;
                    j1 = new ConsoleJoueur(e1, p);
                    j2 = new ProgJoueur(e2, {{P, Coordonnees('A', 4), BAS},
                                             {P, Coordonnees('A', 4), BAS},
                                             {P, Coordonnees('D', 2), DROITE},
                                             {D, Coordonnees('A', 4), BAS},
                                             {D, Coordonnees('B', 4), GAUCHE},
                                             {D, Coordonnees('B', 3), BAS},
                                             {D, Coordonnees('D', 2), DROITE},
                                             {D, Coordonnees('D', 3), DROITE}});
                }

                if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 500) && (mouse_y <= 540)) {
                    action = true;
                    j1 = new ConsoleJoueur(e1, p);
                    j2 = new RandomIA(e2);
                }

                if ((mouse_x >= 420) && (mouse_x <= 620) && (mouse_y >= 550) && (mouse_y <= 590)) {
                    action = true;
                    j1 = new ConsoleJoueur(e1, p);
                    j2 = new IntellIA(e2);
                }
            }

            show_mouse(s_buffer);
            draw_sprite(screen, s_buffer, 0, 0);
        }

        // Jeu
        p->afficher();

        while (!fini) {
            j1->afficher();
            fini = j1->jouer(*p);
            p->afficher();

            if (fini) {
                win = 1;
                break;
            }

            j2->afficher();
            fini = j2->jouer(*p);
            p->afficher();

            if (fini) win = 2;
        }

        while (!key[KEY_ESC]){
            draw_sprite(s_buffer, menu, 0, 0);
            switch (win)
            {
            case 1:
                if (e1 == ELEPH) textout_ex(s_buffer, font, "Les elephants ont gagné ! BRAVO !!", 406, 400, makecol(255,255,255), -1);
                else textout_ex(s_buffer, font, "Les rhinoceros ont gagné ! BRAVO !!", 406, 400, makecol(255,255,255), -1);
                break;

            case 2:
                if (e2 == ELEPH) textout_ex(s_buffer, font, "Les elephants ont gagné ! BRAVO !!", 406, 400, makecol(255,255,255), -1);
                else textout_ex(s_buffer, font, "Les rhinoceros ont gagné ! BRAVO !!", 406, 400, makecol(255,255,255), -1);
                break;
            }

            textout_ex(s_buffer, font, "Appuyez sur ECHAP pour quitter.", 415, 430, makecol(255,255,255), -1);
            show_mouse(s_buffer);
            draw_sprite(screen, s_buffer, 0, 0);
        }
    }
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
    bool play = true;

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
            play = true;
            break;

        case '2':
            play = false;
            break;

            break;

        default:
        std::cout<<"Erreur, ce choix n'existe pas"<<std::endl;
        break;


    }

    if (play) {
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

            j2->afficher();
            fini = j2->jouer(*p);
            p->afficher();
        }
    }
}
