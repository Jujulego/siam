// Importations
#include "console.h"

#ifndef __gnu_linux__
# include <conio.h>
# include <windows.h>
#else
# include <fcntl.h>
# include <unistd.h>
# include <termios.h>

extern "C" {
    int getch(void) {
        struct termios oldattr, newattr;
        int ch;
        
        // Sauvegarde de la config
        tcgetattr(STDIN_FILENO, &oldattr);
        
        // Modification du terminal
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        
        // Récupération du char
        fflush(stdin);
        ch = getchar();
        
        // Rétablissement du terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        
        return ch;
    }
    
    int kbhit() {
        struct termios oldt, newt;
        int ch;
        int oldf;
        
        // Sauvegarde de la config
        tcgetattr(STDIN_FILENO, &oldt);
        
        // Modification du terminal
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        // Préparation de stdin (rendu non bloquant)
        fflush(stdin);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        
        // Récupération d'un charactère (ou EOF)
        ch = getchar();
        
        // Rétablissement
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        
        // Test !
        if (ch != EOF) {
            // Renvoi du charactère
            ungetc(ch, stdin);
            return 1;
        }
        
        return 0;
    }
}
#endif

// Constructeur
Console::Console() {
}

// Destructeur
Console::~Console() {
}

// Méthodes
void Console::gotoLigCol(int lig, int col) {
#ifndef __gnu_linux__
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
#else
    std::cout << "\x1b[" << lig+1 << ";" << col+1 << "H";
#endif
}

void Console::clear() {
#ifndef __gnu_linux__
    system("cls");
#else
    std::cout << "\x1b[2J";
#endif
}

int Console::getInputKey() {
    return getch();
}

bool Console::isKeyboardPressed() {
    return kbhit();
}

/*
Couleurs Windows :      Couleurs Linux :
0: noir                 0: noir
1: bleu foncé           1: rouge
2: vert                 2: vert
3: bleu-gris            3: jaune
4: marron               4: bleu
5: pourpre              5: magenta (violet)
6: kaki                 6: cyan
17: gris clair          7: blanc
8: gris
9: bleu                 9: defaut
10: vert fluo
11: turquoise
12: rouge
13: rose fluo
14: jaune fluo
15: blanc
*/
void Console::_setColor(int front, int back) {
#ifndef __gnu_linux__
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,front*16+back);
#else
    std::cout << "\x1b[" << front + 30 << ";" << back + 40 << "m";
#endif
}

void Console::setColor(Color front, Color back) {
#ifndef __gnu_linux__
    int couleurs[] = {0, 15, 12, 10, 9, 14, 11, 7};
#else
    int couleurs[] = {0, 7, 1, 2, 4, 3, 5, 6, 9};
#endif
    _setColor(couleurs[front], couleurs[back]);
}
