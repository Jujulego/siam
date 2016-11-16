#ifndef __ALLEGRO
#define __ALLEGRO

// Dépandances
#include <memory>

// Namespace
namespace allegro {
    // La librairie
    #include <allegro.h>
    
    // Alias
    using BITMAP_PT = BITMAP*;
    
    // Fonctions
    void init();
    BITMAP_PT charger_bitmap(std::string nom);
};

#endif // __ALLEGRO
