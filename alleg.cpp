// Importations
#include <allegro.h>

#include "affichable.h"
#include "alleg.h"

using namespace allegro;

// Fonctions
void allegro::init() {
    // Initialisation
    allegro_init();
    install_keyboard();
    install_mouse();
    
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0)) {
        Affichable::erreur("Erreur : GFX Mode");
        allegro_exit();
        exit(1);
    }
}

BITMAP_PT allegro::charger_bitmap(std::string nom) {
    // Allocation
    BITMAP_PT pt = load_bitmap(nom.c_str(), nullptr);
    
    // Cas d'erreur
    if (pt == nullptr) {
        Affichable::erreur("Erreur : load_bitmap(\"" + nom + "\")");
        exit(0);
    }
    
    return pt;
}
