#include "joueur.h"
#include "ConsoleJoueur.h"
#include "pion.h"
#include "alleg.h"
#include "plateau.h"
#include "coordonnee.h"

#include <memory>

Direction ConsoleJoueur::demanderDirection()
 {
    char D;
    std::string D1;

    do
        {
        s_console.gotoLigCol(4,70);
        std::cout<<"Dans quelle direction voulez vous tourner le pion: ";

        s_console.gotoLigCol(5,70);
        std::cout<<"h: Haut              "<<std::endl;

        s_console.gotoLigCol(6,70);
        std::cout<<"b: Bas               " <<std::endl;

        s_console.gotoLigCol(7,70);
        std::cout<<"d: Droite            "<<std::endl;

        s_console.gotoLigCol(8,70);
        std::cout<<"g: Gauche            "<<std::endl;

        s_console.gotoLigCol(9,70);
        std::cout <<"Votre choix: ";

        s_console.gotoLigCol(9,83);
        std::cin>>D1;
        D=D1[0];

        } while (D!='h'&& D!='b'&& D!='d'&& D!='g');

    Direction d = DROITE;

    switch (D) {
    case 'h' :
        d = HAUT;
        break;

    case 'b':

        d = BAS;
        break;

    case 'g':
        d = GAUCHE;

        break;
    case 'd':
        break;

    default:
        std::cout<<"Erreur, cette direction n'existe pas"<<std::endl;
        break;
    }

    return d;
 }

Coordonnees ConsoleJoueur::demanderCoord(std::string texte)
{
    char L;//Definition de la variable de la ligne
    std::string L1;
    char C;//Definition de la variable de la colonne
    std::string C1;

    s_console.gotoLigCol(4,70);
    std::cout<<texte<<std::endl;
    do
    {
    s_console.gotoLigCol(5,70);
    std::cout<<"numero de ligne?    "<<std::endl;
    s_console.gotoLigCol(6,70);
    std::cout<<"                         "<<std::endl;
    s_console.gotoLigCol(7,70);
    std::cout<<"                         "<<std::endl;
    s_console.gotoLigCol(8,70);
    std::cout<<"                         "<<std::endl;
    s_console.gotoLigCol(6,70);
    std::cin >>L1;
    L=L1[0];

    // Mise en majuscule
    if ((L >= 'a') && (L <= 'e')) {
        L += 'A' - 'a';
    }

    } while ((L!='A') && (L!='B')&&(L!='C')&& (L!='D')&& (L!='E'));

    do
    {
        s_console.gotoLigCol(5,70);
        std::cout<<"numero de colonne?    "<<std::endl;
        s_console.gotoLigCol(6,70);
        std::cout<<"                         "<<std::endl;
        s_console.gotoLigCol(6,70);
        std::cin>>C1;
        C=C1[0];

    }while ((C!='1')&& (C!='2')&& (C!='3')&& (C!='4')&& (C!='0'));

    return Coordonnees(L,C-'0');
}

ConsoleJoueur::ConsoleJoueur(Equipe e,std::shared_ptr<Plateau> p) : Joueur(e), m_p(p), m_mov({P, Coordonnees('F', 5), BAS})
{

}

Coordonnees ConsoleJoueur::find_coord_alleg(int x, int y)
{
    int tab_x = 6;
    char tab_y = 'G';

    if ((x >= 70) && (x <= 670) && (y >= 70) && (y <= 670)) {
        for (int i = 0; i < 5; i++) {
            if ((x >= 70+i*120) && (x <= 70+(i+1)*120)) tab_x = i;
        }

        for (int i = 0; i < 5; i++) {
            if ((y >= 70+i*120) && (y <= 70+(i+1)*120)) tab_y = 'A' + i;
        }
    }

    return Coordonnees(tab_y, tab_x);
}

void ConsoleJoueur::dess_fleches(Coordonnees clic_coord)
{
    int x = clic_coord.get_col()*120 + 70;
    int y = (clic_coord.get_lig() - 'A')*120 + 70;

    int points_h[8] = {x+40, y+36, x+60, y+9, x+80, y+36, x+60, y+18};
    int points_d[8] = {x+84, y+40, x+111, y+60, x+84, y+80, x+102, y+60};
    int points_b[8] = {x+40, y+84, x+60, y+111, x+80, y+84, x+60, y+102};
    int points_g[8] = {x+36, y+40, x+9, y+60, x+36, y+80, x+18, y+60};

    allegro::polygon(s_buffer, 4, points_h, allegro::makecol(255,0,0));
    allegro::polygon(s_buffer, 4, points_d, allegro::makecol(255,0,0));
    allegro::polygon(s_buffer, 4, points_b, allegro::makecol(255,0,0));
    allegro::polygon(s_buffer, 4, points_g, allegro::makecol(255,0,0));
}

Direction ConsoleJoueur::find_dir_alleg(int x, int y, Coordonnees clic_coord)
{
    if ((x >= clic_coord.get_col()*120 + 110) && (x <= clic_coord.get_col()*120 + 150) && (y >= (clic_coord.get_lig() - 'A')*120 + 79) && (y <= (clic_coord.get_lig() - 'A')*120 + 106)) return HAUT;
    if ((x >= clic_coord.get_col()*120 + 154) && (x <= clic_coord.get_col()*120 + 171) && (y >= (clic_coord.get_lig() - 'A')*120 + 110) && (y <= (clic_coord.get_lig() - 'A')*120 + 150)) return DROITE;
    if ((x >= clic_coord.get_col()*120 + 110) && (x <= clic_coord.get_col()*120 + 150) && (y >= (clic_coord.get_lig() - 'A')*120 + 154) && (y <= (clic_coord.get_lig() - 'A')*120 + 172)) return BAS;
    if ((x >= clic_coord.get_col()*120 + 79) && (x <= clic_coord.get_col()*120 + 106) && (y >= (clic_coord.get_lig() - 'A')*120 + 110) && (y <= (clic_coord.get_lig() - 'A')*120 + 150)) return GAUCHE;
    return NO_DIR;
}

void ConsoleJoueur::afficher_allegro()
{
    bool action = false;
    int Y_REF;
    std::shared_ptr<Pion> VIPion = nullptr;
    Coordonnees coord_clic = Coordonnees('G',6);

    if (m_equipe == RHINO) Y_REF = 455;
    else Y_REF = 160;

    allegro::textout_ex(s_buffer, allegro::font, "A votre tour de jouer :", 775, Y_REF + 75, allegro::makecol(193,0,0), -1);

    while (!VIPion) {
        // Clic sur un pion
        if (allegro::mouse_b&1) {
            for (auto plat : m_p->get_pions()) {
                if (plat->get_equipe() == m_equipe) {
                    if (plat->get_coord().get_lig() == 'F') {
                        if ((allegro::mouse_x >= 715) && (allegro::mouse_x <= 1022) && (allegro::mouse_y >= Y_REF) && (allegro::mouse_y <= Y_REF + 60)) VIPion = plat;
                    }
                    else {
                        if ((allegro::mouse_x >= plat->get_coord().get_as_x(s_etat)) && (allegro::mouse_x <= plat->get_coord().get_as_x(s_etat)+50) && (allegro::mouse_y >= plat->get_coord().get_as_y(s_etat)) && (allegro::mouse_y <= plat->get_coord().get_as_y(s_etat)+50)) VIPion = plat;
                    }
                }
            }
        }

        draw_sprite(allegro::screen, s_buffer, 0, 0);
    }

    allegro::mouse_b &= 0;

    // Affichage en fonction : pion non placé
    if (VIPion->get_coord().get_lig() == 'F') {
        allegro::textout_ex(s_buffer, allegro::font, "Choisissez une case pour rentrer", 720, Y_REF + 90, allegro::makecol(193,0,0), -1);

        while (!action) {
            if (allegro::mouse_b&1) {
                coord_clic = find_coord_alleg(allegro::mouse_x, allegro::mouse_y);

                if ((coord_clic.get_col() == 0) || (coord_clic.get_col() == 4) || (coord_clic.get_lig() == 'A') || (coord_clic.get_lig() == 'E')) {
                    action = true;
                    m_mov.a = P;
                    m_mov.c = coord_clic;
                    m_mov.d = NO_DIR;
                }
            }

            draw_sprite(allegro::screen, s_buffer, 0, 0);
        }

        action=false;
        allegro::mouse_b &= 0;

        dess_fleches(coord_clic);
        allegro::textout_ex(s_buffer, allegro::font, "Dans quel sens voulez-vous rentrer ?", 720, Y_REF + 105, allegro::makecol(193,0,0), -1);

        while (m_mov.d == NO_DIR) {
            if (allegro::mouse_b&1) {
                if ((allegro::mouse_x >= coord_clic.get_col()*120 + 70) && (allegro::mouse_x <= coord_clic.get_col()*120 + 190) && (allegro::mouse_y >= (coord_clic.get_lig() - 'A')*120 + 70) && (allegro::mouse_y <= (coord_clic.get_lig() - 'A')*120 + 190)) {
                    m_mov.d = find_dir_alleg(allegro::mouse_x, allegro::mouse_y, coord_clic);
                }
            }

            draw_sprite(allegro::screen, s_buffer, 0, 0);
        }

        allegro::mouse_b &= 0;
    }

    // Affichage en fonction : pion placé
    else {
        allegro::textout_ex(s_buffer, allegro::font, "Que voulez-vous faire ?", 720, Y_REF + 90, allegro::makecol(193,0,0), -1);
        allegro::rect(s_buffer, 755, Y_REF + 105, 845, Y_REF + 135, allegro::makecol(190,0,0));
        allegro::textout_ex(s_buffer, allegro::font, "Tourner", 773, Y_REF + 116, allegro::makecol(193,0,0), -1);
        allegro::rect(s_buffer, 895, Y_REF + 105, 985, Y_REF + 135, allegro::makecol(190,0,0));
        allegro::textout_ex(s_buffer, allegro::font, "Déplacer", 911, Y_REF + 116, allegro::makecol(193,0,0), -1);

        while (!action) {
            if (allegro::mouse_b&1) {
                if ((allegro::mouse_x >= 755) && (allegro::mouse_x <= 845) && (allegro::mouse_y >= Y_REF + 105) && (allegro::mouse_y <= Y_REF + 135)) m_mov.a = T;
                if ((allegro::mouse_x >= 895) && (allegro::mouse_x <= 985) && (allegro::mouse_y >= Y_REF + 105) && (allegro::mouse_y <= Y_REF + 135)) m_mov.a = D;
                action = true;
            }

            draw_sprite(allegro::screen, s_buffer, 0, 0);
        }

        action=false;
        allegro::mouse_b &= 0;

        if (m_mov.a == T) {
            allegro::textout_ex(s_buffer, allegro::font, "Dans quel sens voulez-vous tourner", 720, Y_REF + 150, allegro::makecol(193,0,0), -1);
            allegro::textout_ex(s_buffer, allegro::font, "le pion ?", 720, Y_REF + 160, allegro::makecol(193,0,0), -1);
            dess_fleches(VIPion->get_coord());

            while (!action) {
                if (allegro::mouse_b&1) {
                    m_mov.d = find_dir_alleg(allegro::mouse_x, allegro::mouse_y, VIPion->get_coord());

                    if ((m_mov.d != VIPion->get_dir()) && (m_mov.d != NO_DIR)) action = true;
                }

                draw_sprite(allegro::screen, s_buffer, 0, 0);
            }

            action=false;
            allegro::mouse_b &= 0;
        }

        else if (m_mov.a == D) {
            allegro::textout_ex(s_buffer, allegro::font, "Dans quelle direction voulez-vous", 720, Y_REF + 150, allegro::makecol(193,0,0), -1);
            allegro::textout_ex(s_buffer, allegro::font, "bouger le pion ?", 720, Y_REF + 162, allegro::makecol(193,0,0), -1);
            dess_fleches(VIPion->get_coord());

            while (!action) {
                if (allegro::mouse_b&1) {
                    m_mov.d = find_dir_alleg(allegro::mouse_x, allegro::mouse_y, VIPion->get_coord());

                    if (m_mov.d != NO_DIR) action = true;
                }

                draw_sprite(allegro::screen, s_buffer, 0, 0);
            }

            action=false;
            allegro::mouse_b &= 0;
        }

        m_mov.c = VIPion->get_coord();
    }
}

 void ConsoleJoueur::afficher_console() //print les choix


 {
    std::string texte;
    char a;

    do

    {
    s_console.gotoLigCol(4,70);
    std::cout<<"Choississez une fontion:"<<std::endl;

    s_console.gotoLigCol(5,70);
    std::cout <<"1 = Placer un pion"<<std::endl;

    s_console.gotoLigCol(6,70);
    std::cout <<"2 = Tourner un pion"<<std::endl;

    s_console.gotoLigCol(7,70);
    std::cout <<"3 = Deplacer un pion"<<std::endl;

    s_console.gotoLigCol(8,70);
    std::cout <<"Votre choix:          ";

    s_console.gotoLigCol(8,83);
    std::cin >> a;

    } while((a!='1') && (a!='2') && (a!='3')&& (a<'0'));

   switch (a) {

    case '1':
        s_console.gotoLigCol(4,70);
          do{
              m_mov.c=demanderCoord("Quelles sont les coordonnees de la case ou vous voulez placer votre pion ?");
          }while (!((m_mov.c.get_lig()=='A')||(m_mov.c.get_lig()=='E' )||(m_mov.c.get_col()==0)||(m_mov.c.get_col()==4)));


        m_mov.d=demanderDirection();
        m_mov.a=P;

        break;

    case '2':
        s_console.gotoLigCol(4,70);
        m_mov.c=demanderCoord("Quelles sont les coordonnees du pions que vous voulez faire tourner        ?");
        m_mov.d=demanderDirection();
        m_mov.a=T;
        break;

    case '3':
        s_console.gotoLigCol(4,70);
        m_mov.c=demanderCoord("Quelles sont les coordonnees du pions que vous voulez deplacer             ?");
        m_mov.d=demanderDirection();
        m_mov.a=D;
        break;

    default:
        std::cout<<"Error, le choix n'existe pas !"<<std::endl;
        break;
   }

 }




 bool ConsoleJoueur::jouer(Plateau& p) //réalisation des actions
 {

    return p.appliquer_mov(m_equipe, m_mov) == FIN;
 }


