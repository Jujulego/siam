#include "joueur.h"
#include "ConsoleJoueur.h"
#include "pion.h"
#include "alleg.h"
#include "plateau.h"

#include <memory>

Direction ConsoleJoueur::demanderDirection()
 {
    char D;

    do
        {
        s_console.gotoLigCol(4,70);
        std::cout<<"Dans quelle direction voulez vous deplacer le pion: ";

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
        std::cin>>D;

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
    char L; //Definition de la variable de la ligne
    char C;//Definition de la variable de la colonne

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
    std::cin >>L;
    }while ((L!='A')&& (L!='B')&& (L!='C')&& (L!='D')&& (L!='E'));

    do
    {
        s_console.gotoLigCol(5,70);
        std::cout<<"numero de colonne?    "<<std::endl;


    s_console.gotoLigCol(6,70);
    std::cout<<"                         "<<std::endl;
    s_console.gotoLigCol(6,70);
        std::cin>>C;

    }while ((C!='1')&& (C!='2')&& (C!='3')&& (C!='4')&& (C!='0'));

    return Coordonnees(L,C-'0');
}

ConsoleJoueur::ConsoleJoueur(Equipe e,std::shared_ptr<Plateau> p) : Joueur(e), m_p(p), m_mov({P, Coordonnees('F', 5), BAS})
{

}


void ConsoleJoueur::afficher_allegro()
{
    std::shared_ptr<Pion> VIPion;

    if (allegro::mouse_b&1) {
        for (auto plat : m_p->get_pions()) {
            if (plat->get_equipe() == m_equipe) {
                if (plat->get_coord().get_lig() == 'F') {
                    if ((plat->get_equipe() == RHINO) && (allegro::mouse_x >= 715) && (allegro::mouse_x <= 1022) && (allegro::mouse_y >= 455) && (allegro::mouse_y <= 515)) VIPion = plat;
                    if ((plat->get_equipe() == ELEPH) && (allegro::mouse_x >= 715) && (allegro::mouse_x <= 1022) && (allegro::mouse_y >= 160) && (allegro::mouse_y <= 220)) VIPion = plat;
                }
                else {
                    if ((allegro::mouse_x >= plat->get_coord().get_as_x(s_etat)) && (allegro::mouse_x <= plat->get_coord().get_as_x(s_etat)+50) && (allegro::mouse_y >= plat->get_coord().get_as_y(s_etat)) && (allegro::mouse_y <= plat->get_coord().get_as_y(s_etat)+50)) VIPion = plat;
                }
            }
        }
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

    } while((a!='1') && (a!='2') && (a!='3'));

   switch (a) {

    case '1':
        texte="Quelles sont les coordonnees de la case ou vous voulez placer votre pion ?";
        s_console.gotoLigCol(4,70);
        demanderCoord(texte);
        demanderDirection();
        break;

    case '2':
        texte="Quelles sont les coordonnees du pions que vous voulez deplacer?";
        s_console.gotoLigCol(4,70);
        demanderCoord(texte);
        demanderDirection();
        break;

    case '3':
        texte="Quelles sont les coordonnees du pions que vous voulez deplacer?";
        s_console.gotoLigCol(4,70);
        demanderCoord(texte);
        demanderDirection();
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


