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
Result Tree<T>::search(const K& pi_key) {
    Node* p = binarySearch(root, pi_key);
    if(p) {
        last_result = p;
        return true;
    }
    return false;
}

template <typename T>
T Tree<T>::get_result() {
    if(last_result)
        return last_result->data;
    else {
        if(std::is_pointer<T>::value)
            return nullptr;
        else
            return T(0);
    }
}

template <typename T>
void Tree<T>::binaryInsert(Node*& pio_root, const Node* pi_data) {
    if(!pio_root) {
        pio_root = const_cast<Node*>(pi_data);
        return;
    }
    
    if(std::is_pointer<T>::value) {
        if(*pio_root->data > *pi_data->data)
            binaryInsert(pio_root->right, pi_data);
        else
            binaryInsert(pio_root->left, pi_data);
    }
    else {
        if(pio_root->data > pi_data->data)
            binaryInsert(pio_root->right, pi_data);
        else
            binaryInsert(pio_root->left, pi_data);
    }
}

template <typename T> template <typename K>
typename Tree<T>::Node* Tree<T>::binarySearch(Node* pi_root, K& pi_key) const {
    if(!pi_root)
        return nullptr;
    
    if(std::is_pointer<T>::value) {
        if(*pi_root->data == pi_key)
            return pi_root;
        else if(*pi_root->data > pi_key)
            return binarySearch(pi_root->right, pi_key);
        else
            return binarySearch(pi_root->left, pi_key);
    }
    else {
        // TODO: find solution to this problem
        /*if(*getPtr(pi_root->data) == pi_key)
            return pi_root;
        else if(*pi_root->data > pi_key)
            return binarySearch(pi_root->right, pi_key);
        else 
            return binarySearch(pi_root->left, pi_key);
            */
    }
}
