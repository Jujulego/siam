#ifndef __ARBRE
#define __ARBRE

// Dépendances
#include <memory>
#include <vector>

// Classe
template <typename T>
class Arbre {
    private:
        // Type interne
        struct Noeud {
            // Contenu
            T val;
            
            // Relations
            std::shared_ptr<Noeud> pere;
            std::vector<std::shared_ptr<Noeud>> fils;
        };
        
        // Constructeur privé
        Arbre(std::shared_ptr<Noeud> n) : m_racine(n) {
        }
        
        // Attribut
        std::shared_ptr<Noeud> m_racine;
    
    public:
        // Constructeur
        Arbre(T racine) : m_racine(new Noeud(racine, nullptr, std::vector<std::shared_ptr<Noeud>>())) {
        }
        
        // Opérateurs
        Arbre<T> operator [] (int index) {
            return Arbre<T>(m_racine->fils[index]);
        }
        
        // Méthodes
        int nb_fils() const {
            return m_racine->fils.size();
        }
        
        // Accesseurs
        T const& get_val() const {
            return m_racine->val;
        }
        
        // Modateurs
        void set_val(T& val) {
            return m_racine->val = val;
        }
};

#endif // __ARBRE
