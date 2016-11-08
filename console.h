#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <iostream>

enum Color {
    COLOR_BLACK = 0,
    COLOR_WHITE = 1,
    COLOR_RED = 2,
    COLOR_GREEN = 3,
    COLOR_BLUE = 4,
    COLOR_YELLOW = 5,
    COLOR_PURPLE = 6,
    COLOR_CYAN = 7,
    COLOR_DEFAULT = 8, // gris couleur de base de la console
};

class Console {
    private:
        // Méthodes privées
        void _setColor(int front, int back);
    
    public:
        // Constructeur
        Console();
        
        // Destructeur
        ~Console();

        // Méthodes publiques
        void gotoLigCol(int lig, int col);
        void clear();
        bool isKeyboardPressed();
        int  getInputKey();
        void setColor(Color front=COLOR_DEFAULT, Color back=COLOR_DEFAULT);
};

#endif // CONSOLE_H_INCLUDED
