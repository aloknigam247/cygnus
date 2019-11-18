/************************************************************************************
 * MIT License                                                                      *
 *                                                                                  *
 * Copyright (c) 2019 Alok Nigam                                                    *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person obtaining a copy     *
 * of this software and associated documentation files (the "Software"), to deal    *
 * in the Software without restriction, including without limitation the rights     *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 * copies of the Software, and to permit persons to whom the Software is            *
 * furnished to do so, subject to the following conditions:                         *
 *                                                                                  *
 * The above copyright notice and this permission notice shall be included in all   *
 * copies or substantial portions of the Software.                                  *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    *
 * SOFTWARE.                                                                        *
 ************************************************************************************/

/**
 * @file cystructs.h
 * @brief Generic structures
 *
 * Generic data structures and suported methods for corresponding structres
 *
 * @author Alok Nigam
 */

#ifndef BASE_CYSTRUCTS_H
#define BASE_CYSTRUCTS_H

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
        iterator(): m_st() {}

        /**
         * Parametrised constructor
         *
         * @param[in] node node to push while creating iterator
         */
        explicit iterator(Node* node): iterator() { m_st.push(node); }

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
         * @param[in] iter iterator object to compare
         * @returns true if both iterator are equal
         */
        bool operator==(const iterator& iter) const;

        /**
         * Operator!=
         *
         * @param[in] iter iterator object to compare
         * @returns true if both iterator are not equal
         */
        bool operator!=(const iterator& iter) const;

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
        std::stack<Node*> m_st;

        /**
         * Friend class that creates stack for first inorder in tree
         *
         * @returns iterator that points to first inorder element
         */
        friend iterator Tree<T>::begin() const;
    };

    /**
     * Default constructor
     */
    Tree() : m_root(nullptr) {}

    /**
     * Copy Constructor
     *
     * @param[in] to_copy object to copy
     */
    Tree(const Tree<T>& to_copy);

    /**
     * Move Constructor
     *
     * @param[in,out] to_copy object to move
     */
    Tree(Tree<T>&& to_move) noexcept;

    /**
     * Operator=
     *
     * @param[in] to_copy object to copy
     */
    Tree<T>& operator=(const Tree<T>& to_copy);

    /**
     * Move Assignemnt
     *
     * @param[in,out] to_copy object to move
     */
    Tree<T>& operator=(Tree<T>&& to_move) noexcept;

    /**
     * Default destructor
     */
    ~Tree();

    /**
     * Inserts new data in Tree
     *
     * @param[in] t data to insert
     */
    void insert(T t);

    /**
     * Searches in Tree
     *
     * @tparam K type of search key
     * @param[in] key search key
     * @returns iterator that contains the result
     */
    template<typename K>
    iterator search(const K& key);

    /**
     * Iterator to first position
     *
     * @returns iterator to first position
     */
    iterator begin() const;

    /**
     * Iterator to first position
     *
     * @returns iterator to first position
     */
    iterator end() const;

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
         * @param[in] d takes data to store
         */
        Node(const T d) : data(d), left(nullptr), right(nullptr) {}

        /**
         * Copy Constructor
         *
         * @param[in] to_copy Node to copy
         */
        Node(const Node& to_copy);

        /**
         * Move Constructor
         *
         * @param[in,out] to_move Node to move
         */
        Node(Node&& to_move) noexcept;

        ~Node();
        /**
         * Operator=
         *
         * @param[in] to_copy Node to copy
         */
        Node& operator=(const Node& to_copy);

        /**
         * Move Assignemnt
         *
         * @param[in,out] to_move Node to move
         */
        Node& operator=(Node&& to_move) noexcept;
    };

    Node* m_root;

    /**
     * Inserts in binary tree
     *
     * @param[in,out] root root node
     * @param[in] data data to insert
     */
    void binaryInsert(Node*& root, const Node* data);

    /**
     * Searches in binary tree
     *
     * @tparam K type of search key
     * @param[in] root node
     * @param[in] key search key
     * @returns node if found, nullptr if not found
     */
    template <typename K>
    Node* binarySearch(Node* root, K& key) const;
};

#include "cystructs.tcc"

}   /* namespace cystructs */
#endif
