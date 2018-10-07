
template<typename TKey, typename Cmp>
bool BSTree<TKey,Cmp>::insert(TKey key, Cmp cmp) {
    if (this->_root == nullptr) {
        this->_root = new BinNode<TKey>(key);
        return true;
    }
    BinNode<TKey> *tmp = this->_root;
    while (tmp != nullptr) {
        if (cmp(key, tmp->getKey())) {
            if (tmp->left == nullptr) {
                tmp->left = new BinNode<TKey>(key);
                return true;
            }
            tmp = tmp->left;
        } else if (cmp(tmp->getKey(), key)) {
            if (tmp->right == nullptr) {
                tmp->right = new BinNode<TKey>(key);

                return true;
            }
            tmp = tmp->right;
        } else
            return tmp;
    }
    return false;
}

template<typename TKey,typename Cmp>
BinNode<TKey> *BSTree<TKey, Cmp>::search(TKey key, Cmp cmp) const {
    if (this->_root == nullptr)
        return nullptr;

    BinNode<TKey> *tmp = this->_root;
    while (tmp != nullptr) {
        if (cmp(key, tmp->getKey())) {
            if (tmp->left == nullptr)
                return nullptr;
            tmp = tmp->left;
        } else if (cmp(tmp->getKey(), key)) {
            if (tmp->right == nullptr)
                return nullptr;
            tmp = tmp->right;
        } else
            return tmp;
    }
    return nullptr;
}

template<typename TKey, typename Cmp>
BinNode<TKey> *BSTree<TKey, Cmp>::searchParent(TKey key, Cmp cmp) const {
    if (this->_root == nullptr)
        return nullptr;

    BinNode<TKey> *tmp = this->_root, *parent = this->_root;
    while (tmp != nullptr) {
        parent = tmp;
        if (cmp(key, tmp->getKey())) {
            if (tmp->left == nullptr)
                return nullptr;
            tmp = tmp->left;
        } else if (cmp(tmp->getKey(), key)) {
            if (tmp->right == nullptr)
                return nullptr;
            tmp = tmp->right;
        } else {
            return parent;
        }
    }
    return nullptr;
}

template<typename TKey, typename Cmp>
bool BSTree<TKey, Cmp>::deleteNode(TKey key, Cmp cmp) {
    if (this->_root == nullptr)
        return false;
    BinNode<TKey> *parent = searchParent(key);
    if (this->_root == parent && !cmp(parent->getKey(), key) && !cmp(key, parent->getKey())) {
        BinNode<TKey> *tmp = this->_root->right;
        if (tmp->left != nullptr) {
            while (tmp->left->left != nullptr)
                tmp = tmp->left;
            this->_root->key = tmp->left->key;
            delete tmp->left;
            tmp->left = nullptr;
            return true;
        }
        tmp->left = this->_root->left;
        delete this->_root;
        this->_root = tmp;
        return true;
    }
    if (cmp(key, parent->getKey()))
        return deleteLeftNode(parent);
    else if (cmp(parent->getKey(), key))
        return deleteRightNode(parent);
    else {
        delete parent;
        parent = nullptr;
        return true;
    }
    return false;
}

template<typename TKey, typename Cmp>
BSTree<TKey,  Cmp>::~BSTree() {
if(this->_root!=nullptr)
    deleteSubtree(this->_root->getKey());
}

template<typename TKey, typename Cmp>
bool BSTree<TKey,Cmp>::deleteSubtree(TKey key, Cmp cmp) {
    if (this->_root == nullptr)
        return false;
    BinNode<TKey> *parent = searchParent(key), *node = nullptr;
    if(parent== nullptr)
        return  false;
    if (cmp(key, parent->getKey())) {
        node = parent->left;
        parent->left = nullptr;
    } else if (cmp(parent->getKey(), key)) {
        node = parent->right;
        parent->right = nullptr;
    } else {
        this->_root= nullptr;
        node = parent;
    }
    std::stack<BinNode<TKey> *> stack;
    BinNode<TKey> *tmp = nullptr;
    stack.push(node);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
        delete tmp;
        tmp= nullptr;
    }
    return true;
}


template<typename TKey, typename Cmp>
bool BSTree<TKey, Cmp>::deleteLeftNode(BinNode<TKey> *parent) {
    BinNode<TKey> *node = parent->left;
    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        parent->left = nullptr;
        return true;
    }
    if (node->left != nullptr && node->right != nullptr) {
        BinNode<TKey> *tmp = node->right;
        if (tmp->left != nullptr) {
            while (tmp->left->left != nullptr)
                tmp = tmp->left;
            node->key = tmp->left->key;
            delete tmp->left;
            tmp->left = nullptr;
            return true;
        }
        parent->left = tmp;
        tmp->left = node->left;
        delete node;
        return true;
    }
    if (node->left != nullptr) {
        BinNode<TKey> *tmp = node->left;
        parent->left = node->left;
        delete node;
        return true;
    }
    if (node->right != nullptr) {
        BinNode<TKey> *tmp = node->right;
        parent->left = node->right;
        delete node;
        return true;
    }
    return false;
}

template<typename TKey, typename Cmp>
bool BSTree<TKey, Cmp>::deleteRightNode(BinNode<TKey> *parent) {
    BinNode<TKey> *node = parent->right;
    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        parent->right = nullptr;
        return true;
    }
    if (node->left != nullptr && node->right != nullptr) {
        BinNode<TKey> *tmp = node->right;
        if (tmp->left != nullptr) {
            while (tmp->left->left != nullptr)
                tmp = tmp->left;
            node->key = tmp->left->key;
            delete tmp->left;
            tmp->left = nullptr;
            return true;
        }
        parent->right = tmp;
        tmp->left = node->left;
        delete node;
        return true;
    }
    if (node->left != nullptr) {
        BinNode<TKey> *tmp = node->left;
        parent->right = node->left;
        delete node;
        return true;
    }
    if (node->right != nullptr) {
        BinNode<TKey> *tmp = node->right;
        parent->right = node->right;
        delete node;
        return true;
    }
    return false;
}



template<typename TKey, typename Cmp>
void BSTree<TKey, Cmp>::printInOrder(void (*print)(TKey)) const {
    BinTree<TKey,Cmp>::printInOrder(print,this->_root);
}
template<typename TKey, typename Cmp>
void BSTree<TKey, Cmp>::printPreOrder(void (*print)(TKey)) const {
    BinTree<TKey,Cmp>::printPreOrder(print,this->_root);
}
template<typename TKey, typename Cmp>
void BSTree<TKey,  Cmp>::printPostOrder(void (*print)(TKey)) const {
    BinTree<TKey,Cmp>::printPostOrder(print,this->_root);
}
template<typename TKey, typename Cmp>
void BSTree<TKey,  Cmp>::printLevelOrder(void (*print)(TKey)) const {
    BinTree<TKey,Cmp>::printLevelOrder(print,this->_root);
}

