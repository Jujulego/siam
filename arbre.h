#ifndef __ARBRE
#define __ARBRE

// Dépendances
#include <memory>
#include <vector>
#include <queue>

// Classe
template <typename T>
class Arbre {
    private:
        // Type interne
        struct Noeud {
            // Contenu
            std::shared_ptr<T> val;
            int generation;
            
            // Relations
            std::shared_ptr<Noeud> pere;
            std::vector<std::shared_ptr<Noeud>> fils;
            
            // Constructeur
            Noeud(T v, std::shared_ptr<Noeud> p, int g) : val(new T(v)), generation(g), pere(p) {
            }
            
            // Méthodes
            void incendie() {
                // destruction des fils
                for (auto f : fils) {
                    f->incendie();
                }
                
                // destruction du noeud
                fils.clear();
                pere = nullptr;
            }
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
        
        Arbre(T racine) : m_racine(new Noeud(racine, nullptr, 1)) {
        }
        
        // Opérateurs
        Arbre<T> operator [] (int index) {
            if (!is_null())
                return Arbre<T>(m_racine->fils[index]);
            
            return Arbre<T>();
        }
        
        // Méthodes
        int nb_fils() const {
            if (!is_null())
                return m_racine->fils.size();
            
            return 0;
        }
        
        Arbre<T> get_pere() {
            if (!is_null())
                return Arbre<T>(m_racine->pere);
            
            return Arbre<T>();
        }
        
        bool is_null() const {
            return m_racine == nullptr;
        }
        
        void ajouter_fils(T val) {
            if (!is_null())
                m_racine->fils.push_back(std::shared_ptr<Noeud>(new Noeud(val, m_racine, m_racine->generation + 1)));
        }
        
        void suppr_parents() {
            if (!is_null())
                m_racine->pere = nullptr;
        }
        
        void incendie() {
            m_racine->incendie();
        }
        
        // Accesseurs
        int get_generation() const {
            if (!is_null())
                return m_racine->generation;
            
            return 0;
        }
        
        std::shared_ptr<T> get_val() const {
            if (!is_null())
                return std::shared_ptr<T>(m_racine->val);
            
            return nullptr;
        }
        
        // Modateurs
        void set_val(T const& val) {
            if (m_racine) {
                *(m_racine->val) = val;
            } else {
                m_racine = std::shared_ptr<Noeud>(new Noeud(val, nullptr, 0));
            }
        }
};

#endif // __ARBRE
