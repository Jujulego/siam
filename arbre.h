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
        // Constructeurs
        Arbre() : m_racine(nullptr) {
        }
        
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
        
        Arbre<T> get_pere() {
            return Arbre<T>(m_racine->pere);
        }
        
        void ajouter_fils(T val) {
            m_racine->fils.push_back(new Noeud(val, m_racine, std::vector<std::shared_ptr<Noeud>>()));
        }
        
        // Accesseurs
        T const& get_val() const {
            return m_racine->val;
        }
        
        // Modateurs
        void set_val(T const& val) {
            m_racine->val = val;
        }
};

#endif // __ARBRE
