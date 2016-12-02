#ifndef __ALLEGRO
#define __ALLEGRO

// Dépandances
#include <memory>
#include <map>
#include <string>

// Namespace
namespace allegro {
    // La librairie
    #include <allegro.h>

    // Alias
    using BITMAP_PT = BITMAP*;
    
    // Variables
    static std::map<std::string, BITMAP_PT> tab_bitmaps;

    // Fonctions
    void init(int l, int h);
    void exit();
    BITMAP_PT creer_bitmap(int l, int h);
    BITMAP_PT charger_bitmap(std::string nom);
};

#endif // __ALLEGRO
