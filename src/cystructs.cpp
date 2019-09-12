#include"cystructs.h"

template <typename T>
Tree<T>::~Tree() {
    if(root)
        delete root;
}

template <typename T>
void cystructs::Tree<T>::insert(const T pi_t) {
   Node* n = new Node(pi_t);
}
