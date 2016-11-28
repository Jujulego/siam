#include "joueur.h"
#include "ConsoleJoueur.h"


 void ConsoleJoueur::afficher_allegro()
 {

 }
 void ConsoleJoueur::afficher_console() //print les choix
 {
      s_console.gotoLigCol(18,5);
        std::cout<<">";
        std::cout<<"<";

 }



 bool ConsoleJoueur::jouer(Plateau& p) //réalisation des actions
 {
    p.appliquer_mov(m_equipe, m_mov);
 }
