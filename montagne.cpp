// Importations
#include "coordonnee.h"
#include "objpoussable.h"
#include "montagne.h"

// Constructeur
Montagne::Montagne(Coordonnees coord) : ObjPoussable('M', "test_mont.bmp", coord) {
}

// Méthodes
float Montagne::get_resistance(__attribute__((unused)) Direction dir) const {
    return 0.9;
}
