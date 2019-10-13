#ifndef _CYSTRUCTS_H
#define _CYSTRUCTS_H

#include <stack>
#include <stdexcept>

namespace cystructs {

template <typename T>
class Tree {
    struct Node;

    public:
    class iterator {
        public:
        iterator() {}
        iterator(Node* pi_node) { st.push(pi_node); }
        T operator*() const;
        bool operator==(const iterator& pi_iter) const;
        bool operator!=(const iterator& pi_iter) const;
        T operator->() const;
        iterator& operator++();

        private:
        std::stack<Node*> st;
        friend iterator& Tree<T>::begin() const;
    };
    
    Tree() : root(nullptr) {}
    ~Tree();
    void insert(const T pi_t);
    template<typename K>
    iterator& search(const K& pi_key);
    iterator& begin() const;
    iterator& end() const;

    private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T pi_d) : data(pi_d), left(nullptr), right(nullptr) {}
    };  /* struct Node */

    Node* root;
    void binaryInsert(Node*& pio_root, const Node* pi_data);
    template <typename K>
    Node* binarySearch(Node* pi_root, K& pi_key) const;
};  /* class Tree */

#include "cystructs.tcc"

}   /* namespace cystructs */
#endif
