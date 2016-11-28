#include "joueur.h"
#include "ConsoleJoueur.h"
#include "pion.h"

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

    switch (D) {

    case 'h' :
        return HAUT;
        break;

    case 'b':

        return BAS;
        break;

    case 'g':
        return GAUCHE;

        break;
    case 'd':
        return DROITE;
        break;

    default:
        std::cout<<"Erreur, cette direction n'existe pas"<<std::endl;
        break;
    }

 }

Coordonnees ConsoleJoueur::demanderCoord(std::string texte)
{
    char L;
    char C;
    s_console.gotoLigCol(8,83);
    std::cout<<texte<<std::endl;
    do
    {
    s_console.gotoLigCol(9,83);
    std::cout<<"numero de ligne?"<<std::endl;
    s_console.gotoLigCol(10,83);
    std::cin >>L;
    s_console.gotoLigCol(11,83);
    std::cout<<"numero de colonne?"<<std::endl;
    s_console.gotoLigCol(12,83);
    std::cin>>C;
    }while (L!='A'||L!='B'||L!='C'||L!='D'||L!='E'||C!='1'||C!='2'||C!='3'||C!='4'||C!='0');


}

ConsoleJoueur::ConsoleJoueur(Equipe e)
:Joueur(e)
{

}


 void ConsoleJoueur::afficher_allegro()
 {
     //ne fait rien pour le moment
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
        s_console.gotoLigCol(8,83);
        texte="Quelles sont les coordonnees de la case ou vous voulez placer votre pion ?";

        demanderCoord(texte);
        demanderDirection();
        break;

    case '2':
        s_console.gotoLigCol(8,83);
        texte="Quelles sont les coordonnees du pions que vous voulez deplacer?";
        s_console.gotoLigCol(9,83);
        demanderCoord(texte);
        demanderDirection();
        break;

    case '3':
        texte="Quelles sont les coordonnees du pions que vous voulez deplacer?";
        demanderCoord(texte);
        demanderDirection();
        break;
    default:
        std::cout<<"Error, le choix n'existe pas !"<<std::endl;
        break;
}

      s_console.gotoLigCol(27,50);
        std::cout<<FLECHE_HAUT;

        s_console.gotoLigCol(29,52);
        std::cout<<FLECHE_BAS;

        s_console.gotoLigCol(28,51);
        std::cout<<FLECHE_GAUCHE;

        s_console.gotoLigCol(28,49);
        std::cout<<FLECHE_DROITE;

 }



 bool ConsoleJoueur::jouer(Plateau& p) //réalisation des actions
 {

 }


