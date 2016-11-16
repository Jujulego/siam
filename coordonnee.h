#ifndef __COORDONNEES
#define __COORDONNEES

// Classe
class Coordonnees {
    private:
        char m_lig;
        int m_col;
    
    public:
        // Constructeur
        Coordonnees(char lig, int col);
        
        // Accesseurs
        char get_lig() const;
        int  get_col() const;
        
        void set_lig(char lig);
        void set_col(int col);
};

#endif // __COORDONNEES
