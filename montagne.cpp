// Importations
#include "coordonnee.h"
#include "objpoussable.h"
#include "montagne.h"

// Constructeur
Montagne::Montagne(Coordonnees coord) : ObjPoussable('M', "montagne.bmp", coord) {
}

// Méthodes
float Montagne::get_resistance(Direction dir) const {
    return 0.9;
}
