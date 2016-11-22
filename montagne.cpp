// Importations
#include "coordonnee.h"
#include "objpoussable.h"
#include "montagne.h"

// Constructeur
Montagne::Montagne(Coordonnees coord) : ObjPoussable(MONTAGNE, 'M', "montagne.bmp", coord) {
}

// Méthodes
void Montagne::tourner(__attribute__((unused)) Direction dir) {
}

float Montagne::get_resistance(__attribute__((unused)) Direction dir) const {
    return 0.9f;
}

float Montagne::get_force(__attribute__((unused)) Direction dir) const {
    return 0.0f;
}

Direction Montagne::get_dir() const {
    return HAUT; // Pourquoi pas !
}
