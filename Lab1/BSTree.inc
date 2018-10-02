
template<typename TKey, typename TData, typename Cmp>
bool BSTree<TKey, TData, Cmp>::insert(TKey key, TData data, Cmp cmp) {
    if (this->_root == nullptr) {
        this->_root = new BinNode<TKey, TData>(key, data);
        return true;
    }
    BinNode<TKey, TData> *tmp = this->_root;
    while (tmp != nullptr) {
        if (cmp(key, tmp->getKey())) {
            if (tmp->left == nullptr) {
                tmp->left = new BinNode<TKey, TData>(key, data);
                return true;
            }
            tmp = tmp->left;
        } else if (cmp(tmp->getKey(), key)) {
            if (tmp->right == nullptr) {
                tmp->right = new BinNode<TKey, TData>(key, data);

                return true;
            }
            tmp = tmp->right;
        } else
            return tmp;
    }
    return false;
}

template<typename TKey, typename TData, typename Cmp>
BinNode<TKey, TData> *BSTree<TKey, TData, Cmp>::search(TKey key, Cmp cmp) const {
    if (this->_root == nullptr)
        return nullptr;

    BinNode<TKey, TData> *tmp = this->_root;
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

template<typename TKey, typename TData, typename Cmp>
BinNode<TKey, TData> *BSTree<TKey, TData, Cmp>::searchParent(TKey key, Cmp cmp) const {
    if (this->_root == nullptr)
        return nullptr;

    BinNode<TKey, TData> *tmp = this->_root, *parent = this->_root;
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

template<typename TKey, typename TData, typename Cmp>
bool BSTree<TKey, TData, Cmp>::deleteNode(TKey key, Cmp cmp) {
    if (this->_root == nullptr)
        return false;
    BinNode<TKey, TData> *parent = searchParent(key);
    if (this->_root == parent && !cmp(parent->getKey(), key) && !cmp(key, parent->getKey())) {
        BinNode<TKey, TData> *tmp = this->_root->right;
        if (tmp->left != nullptr) {
            while (tmp->left->left != nullptr)
                tmp = tmp->left;
            this->_root->key = tmp->left->key;
            this->_root->data = tmp->left->data;
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

template<typename TKey, typename TData, typename Cmp>
BSTree<TKey, TData, Cmp>::~BSTree() {
    deleteSubtree(this->_root->getKey());
}

template<typename TKey, typename TData, typename Cmp>
bool BSTree<TKey, TData, Cmp>::deleteSubtree(TKey key, Cmp cmp) {
    if (this->_root == nullptr)
        return false;
    BinNode<TKey, TData> *parent = searchParent(key), *node = nullptr;
    if (cmp(key, parent->getKey())) {
        node = parent->left;
        parent->left = nullptr;
    } else if (cmp(parent->getKey(), key)) {
        node = parent->right;
        parent->right = nullptr;
    } else {
        node = parent;
    }
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(node);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
        delete tmp;
    }
    return true;
}


template<typename TKey, typename TData, typename Cmp>
bool BSTree<TKey, TData, Cmp>::deleteLeftNode(BinNode<TKey, TData> *parent) {
    BinNode<TKey, TData> *node = parent->left;
    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        parent->left = nullptr;
        return true;
    }
    if (node->left != nullptr && node->right != nullptr) {
        BinNode<TKey, TData> *tmp = node->right;
        if (tmp->left != nullptr) {
            while (tmp->left->left != nullptr)
                tmp = tmp->left;
            node->key = tmp->left->key;
            node->data = tmp->left->data;
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
        BinNode<TKey, TData> *tmp = node->left;
        parent->left = node->left;
        delete node;
        return true;
    }
    if (node->right != nullptr) {
        BinNode<TKey, TData> *tmp = node->right;
        parent->left = node->right;
        delete node;
        return true;
    }
    return false;
}

template<typename TKey, typename TData, typename Cmp>
bool BSTree<TKey, TData, Cmp>::deleteRightNode(BinNode<TKey, TData> *parent) {
    BinNode<TKey, TData> *node = parent->right;
    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        parent->right = nullptr;
        return true;
    }
    if (node->left != nullptr && node->right != nullptr) {
        BinNode<TKey, TData> *tmp = node->right;
        if (tmp->left != nullptr) {
            while (tmp->left->left != nullptr)
                tmp = tmp->left;
            node->key = tmp->left->key;
            node->data = tmp->left->data;
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
        BinNode<TKey, TData> *tmp = node->left;
        parent->right = node->left;
        delete node;
        return true;
    }
    if (node->right != nullptr) {
        BinNode<TKey, TData> *tmp = node->right;
        parent->right = node->right;
        delete node;
        return true;
    }
    return false;
}



template<typename TKey, typename TData, typename Cmp>
void BSTree<TKey, TData, Cmp>::printInOrder(void (*print)(TKey, TData)) const {
    BinTree<TKey,TData,Cmp>::printInOrder(print,this->_root);
}
template<typename TKey, typename TData, typename Cmp>
void BSTree<TKey, TData, Cmp>::printPreOrder(void (*print)(TKey, TData)) const {
    BinTree<TKey,TData,Cmp>::printPreOrder(print,this->_root);
}
template<typename TKey, typename TData, typename Cmp>
void BSTree<TKey, TData, Cmp>::printPostOrder(void (*print)(TKey, TData)) const {
    BinTree<TKey,TData,Cmp>::printPostOrder(print,this->_root);
}
template<typename TKey, typename TData, typename Cmp>
void BSTree<TKey, TData, Cmp>::printLevelOrder(void (*print)(TKey, TData)) const {
    BinTree<TKey,TData,Cmp>::printLevelOrder(print,this->_root);
}