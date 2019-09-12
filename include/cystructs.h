#ifndef _CYSTRUCTS_H
#define _CYSTRUCTS_H
namespace cystructs {
template <typename T>
class Tree {
    public:
        Tree() : root(nullptr) {}
        ~Tree();
        void insert(const T pi_t);
        //size_t size() const;
        //T search(T) const;
    private:
        struct Node {
            T data;
            Node* left, right;

            Node(const T pi_d) : data(pi_d), left(nullptr), right(nullptr) {}
        };
        
        Node* root;
};
}
#endif
