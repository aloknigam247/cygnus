/**
 * @file cystructs.h
 * @brief Generic structures
 *
 * Generic data structures and suported methods for corresponding structres
 *
 * @author Alok Nigam
 */

#ifndef _CYSTRUCTS_H
#define _CYSTRUCTS_H

#include <stack>
#include <stdexcept>

/**
 * @namespace cystructs
 * @brief Container for all Cygnus Structures
 */
namespace cystructs {

/**
 * @class Tree
 * @brief Generic tree data structure
 * @tparam T Type of data to store in Tree
 */
template <typename T>
class Tree {
    struct Node;

    public:
    /**
     * @class iterator
     * @brief Iterator class for class Tree
     */
    class iterator {
        public:
        /**
         * Default constructor
         */
        iterator() {}

        /**
         * Parametrised constructor
         *
         * @param[in] pi_node node to push while creating iterator
         */
        iterator(Node* pi_node) { st.push(pi_node); }

        /**
         * Operator*
         *
         * @returns data pointed by iterator
         * @throws underflow_error if iterator points nowhere
         */
        T operator*() const;

        /**
         * Operator==
         *
         * @param[in] pi_iter iterator object to compare
         * @returns true if both iterator are equal
         */
        bool operator==(const iterator& pi_iter) const;

        /**
         * Operator!=
         *
         * @param[in] pi_iter iterator object to compare
         * @returns true if both iterator are not equal
         */
        bool operator!=(const iterator& pi_iter) const;

        /**
         * Operator->
         *
         * @note Compiles only for pointer to userdefined type
         * @returns data
         * @throws underflow_error if iterator points nowhere
         */
        T operator->() const;

        /**
         * Operator++
         *
         * @returns reference to incremented
         * @note incremenets in inorder
         */
        iterator& operator++();

        private:
        std::stack<Node*> st;

        /**
         * Friend class that creates stack for first inorder in tree
         *
         * @returns iterator that points to first inorder element
         */
        friend iterator& Tree<T>::begin() const;
    };

    /**
     * Default constructor
     */
    Tree() : root(nullptr) {}

    /**
     * Default destructor
     */
    ~Tree();

    /**
     * Inserts new data in Tree
     *
     * @param[in] pi_t data to insert
     */
    void insert(const T pi_t);

    /**
     * Searches in Tree
     *
     * @tparam K type of search key
     * @param[in] pi_key search key
     * @returns iterator that contains the result
     */
    template<typename K>
    iterator& search(const K& pi_key);

    /**
     * Iterator to first position
     *
     * @returns iterator to first position
     */
    iterator& begin() const;

    /**
     * Iterator to first position
     *
     * @returns iterator to first position
     */
    iterator& end() const;

    private:
    /**
     * @struct Node
     * @brief Stores data in a singly linked node
     */
    struct Node {
        T data;
        Node* left;
        Node* right;

        /**
         * Parametrised Constructor
         * @param[in] pi_d takes data to store
         */
        Node(const T pi_d) : data(pi_d), left(nullptr), right(nullptr) {}
    };

    Node* root;

    /**
     * Inserts in binary tree
     *
     * @param[in,out] pio_root root node
     * @param[in] pi_data data to insert
     */
    void binaryInsert(Node*& pio_root, const Node* pi_data);

    /**
     * Searches in binary tree
     *
     * @tparam K type of search key
     * @param[in] pi_root node
     * @param[in] pi_key search key
     * @returns node if found, nullptr if not found
     */
    template <typename K>
    Node* binarySearch(Node* pi_root, K& pi_key) const;
};

#include "cystructs.tcc"

}   /* namespace cystructs */
#endif
