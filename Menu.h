#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "affichable.h"
#include "joueur.h"
#include "ConsoleJoueur.h"
#include "randomia.h"
#include <vector>
#include "allegro.h"
#include "ia.h"
#include "console.h"
#include "coordonnee.h"
#include "objpoussable.h"
#include "plateau.h"
#include "progjoueur.h"
#include "randomia.h"
using namespace allegro;

class Menu: public Affichable
{
private:

public:
    Menu();
    void afficherMenu();
    void creationJoueur();
    void afficher_allegro() noexcept;
    void afficher_console() noexcept;
    virtual ~Menu() noexcept;
};



#endif // MENU_H_INCLUDED
