#ifndef _CYSTRUCTS_H
#define _CYSTRUCTS_H

#include "Log.h"
namespace cystructs {

typedef bool Result;

template <typename T>
class Tree {
    public:
    Tree() : root(nullptr), last_result(nullptr) {}
    ~Tree();
    void insert(const T pi_t);
    template<typename K>
    Result search(const K& pi_key);
    T get_result();
    
    private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T pi_d) : data(pi_d), left(nullptr), right(nullptr) {}
    };  /* struct Node */

    Node* root;
    Node* last_result;
    void binaryInsert(Node*& pio_root, const Node* pi_data);
    template <typename K>
    Node* binarySearch(Node* pi_root, K& pi_key) const;
};  /* class Tree */

#include "cystructs.tcc"

}   /* namespace cystructs */
#endif
