template <typename T>
Tree<T>::~Tree() {
    if(root)
        delete root;
}

template <typename T>
void Tree<T>::insert(const T pi_t) {
   Node* n = new Node(pi_t);
   binaryInsert(root, n);
}

template <typename T> template <typename K>
typename Tree<T>::iterator& Tree<T>::search(const K& pi_key) {
    Node* p = binarySearch(root, pi_key);
    if(p)
        return *(new iterator(p));
    return *(new iterator);
}

template <typename T>
T Tree<T>::iterator::operator*() const {
    if(st.empty())
        throw std::underflow_error("iterator is empty");
    return st.top()->data;
}

template <typename T>
bool Tree<T>::iterator::operator==(const iterator& pi_iter) const {
    return this->st == pi_iter.st;
}

template <typename T>
bool Tree<T>::iterator::operator!=(const iterator& pi_iter) const {
    return !(*this == pi_iter);
}

template <typename T>
T Tree<T>::iterator::operator->() const {
    if(st.empty())
        throw std::underflow_error("iterator is empty");
    return st.top()->data;
}

template <typename T>
typename Tree<T>::iterator& Tree<T>::iterator::operator++() {
    if(!st.empty()) {
        Node* curr = this->st.top()->right;
        this->st.pop();
        while(curr) {
            this->st.push(curr);
            curr = curr->left;
        }
    }
    return *this;
}

template <typename T>
typename Tree<T>::iterator& Tree<T>::begin() const {
    iterator* iter = new iterator;
    Node* curr = root;
    while(curr) {
        iter->st.push(curr);
        curr = curr->left;
    }
    return *iter;
}

template <typename T>
typename Tree<T>::iterator& Tree<T>::end() const {
    static iterator iter;
    return iter;
}

/** @cond */
template <typename T>
static T& ref_of(T &o) {return o;}
template <typename T>
static T& ref_of(T *o) {return *o;}
/** @endcond */

template <typename T>
void Tree<T>::binaryInsert(Node*& pio_root, const Node* pi_data) {
    if(!pio_root) {
        pio_root = const_cast<Node*>(pi_data);
        return;
    }    
    if(ref_of(pio_root->data) > ref_of(pi_data->data))
        binaryInsert(pio_root->left, pi_data);
    else
        binaryInsert(pio_root->right, pi_data);
}

template <typename T> template <typename K>
typename Tree<T>::Node* Tree<T>::binarySearch(Node* pi_root, K& pi_key) const {
    if(!pi_root)
        return nullptr;
    
    if(ref_of(pi_root->data) == pi_key)
        return pi_root;
    else if(*pi_root->data > pi_key)
        return binarySearch(pi_root->left, pi_key);
    else
        return binarySearch(pi_root->right, pi_key);
}
