template<typename TKey, typename TData, typename Cmp>
bool BinTree<TKey, TData, Cmp>::insert(TKey key, TData data) {
    if (this->_root == nullptr) {
        this->_root = new BinNode<TKey, TData>(key, data);
        return true;
    }
    return false;
}

template<typename TKey, typename TData, typename Cmp>
BinNode<TKey, TData> *BinTree<TKey, TData, Cmp>::insertleft(BinNode<TKey, TData> *node, TKey key, TData data) {
    if (node != nullptr && node->left == nullptr) {
        node->left = new BinNode<TKey, TData>(key, data);
        return node->left;
    }
    return nullptr;
}

template<typename TKey, typename TData, typename Cmp>
BinNode<TKey, TData> *BinTree<TKey, TData, Cmp>::insertright(BinNode<TKey, TData> *node, TKey key, TData data) {
    if (node != nullptr && node->right == nullptr) {
        node->right = new BinNode<TKey, TData>(key, data);
        return node->right;
    }
    return nullptr;
}

template<typename TKey, typename TData, typename Cmp>
BinNode<TKey, TData> *BinTree<TKey, TData, Cmp>::getRoot() {
    return this->_root;
}

template<typename TKey, typename TData, typename Cmp>
bool BinTree<TKey, TData, Cmp>::deleteNode(TKey key) {
    BinNode<TKey, TData> *parent = searchParent(key), *node = nullptr;
    if (parent == nullptr)
        return false;
    if (parent->getKey() == key) {
        node = parent;
        delete node;
        node = nullptr;
        return true;
    }
    if (parent->left->getKey() == key) {
        node = parent->left;
        if (node->left == nullptr) {
            parent->left = node->right;
            delete node;
            return true;
        }
        if (node->right == nullptr) {
            parent->left = node->left;
            delete node;
            return true;
        }
    }
    if (parent->right->getKey() == key) {
        node = parent->right;
        if (node->left == nullptr) {
            parent->right = node->right;
            delete node;
            return true;
        }
        if (node->right == nullptr) {
            parent->right = node->left;
            delete node;
            return true;
        }
    }

    return false;
}

template<typename TKey, typename TData, typename Cmp>
bool BinTree<TKey, TData, Cmp>::deleteSubtree(TKey key) {
    BinNode<TKey, TData> *parent = searchParent(key), *node = nullptr;
    if (parent == nullptr)
        return false;
    if (parent->getKey() == key)
        node = parent;
    else if (parent->left->getKey() == key) {
        node = parent->left;
        parent->left = nullptr;
    } else if (parent->right->getKey() == key) {
        node = parent->right;
        parent->right = nullptr;
    }
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
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
BinNode<TKey, TData> *BinTree<TKey, TData, Cmp>::searchParent(TKey key) const {
    if (this->_root == nullptr || this->_root->getKey() == key)
        return this->_root;
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr) {
            if (tmp->left->getKey() == key)
                return tmp;
            stack.push(tmp->left);
        }
        if (tmp->right != nullptr) {
            if (tmp->right->getKey() == key)
                return tmp;
            stack.push(tmp->right);
        }
    }
    return nullptr;
}

template<typename TKey, typename TData, typename Cmp>
BinNode<TKey, TData> *BinTree<TKey, TData, Cmp>::search(TKey key) const {
    if (this->_root == nullptr)
        return nullptr;
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->returnKey() == key) {
            return tmp;
        } else {
            if (tmp->left != nullptr)
                stack.push(tmp->left);
            if (tmp->right != nullptr)
                stack.push(tmp->right);
        }
    }
    return nullptr;
}

template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::printInOrder(void (*print)(TKey, TData)) const {
    printInOrder(print,this->_root);
}

template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::printPreOrder(void (*print)(TKey, TData)) const {
   printPreOrder(print,this->_root);
}


template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::printPostOrder(void (*print)(TKey, TData)) const {
    printPostOrder(print,this->_root);
}

template<typename TKey, typename TData>
struct BinLevel {
    int level = 0;
    BinNode<TKey, TData> *node = nullptr;
};

template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::printLevelOrder(void (*print)(TKey, TData)) const {

    printLevelOrder(print,this->_root);

}

template<typename TKey, typename TData, typename Cmp>
BinTree<TKey, TData, Cmp>::~BinTree() {
    deleteSubtree(this->_root->getKey());
}


template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::printInOrder(void (*print)(TKey, TData), BinNode<TKey, TData> *root) const {
    if (root == nullptr)
        return;
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        print(tmp->getKey(), tmp->getData());
        if (tmp->right != nullptr)
            stack.push(tmp->right);
    }
}


template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::printPreOrder(void (*print)(TKey, TData), BinNode<TKey, TData> *root) const {
    if (root == nullptr)
        return;
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        print(tmp->getKey(), tmp->getData());
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
    }
}

template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::printPostOrder(void (*print)(TKey, TData), BinNode<TKey, TData> *root) const {
    if (root == nullptr)
        return;
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
        print(tmp->getKey(), tmp->getData());
    }
}


template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::printLevelOrder(void (*print)(TKey, TData), BinNode<TKey, TData> *root) const {
    if(root==nullptr)
        return;
    std::queue<BinLevel<TKey, TData> *> queue;
    int l = 1;
    BinLevel<TKey, TData> *tmp = new BinLevel<TKey, TData>();
    tmp->level = 0;
    tmp->node = root;
    queue.push(tmp);
    while (!queue.empty()) {
        tmp = queue.front();
        queue.pop();
        if (l != tmp->level) {
            std::cout << std::endl;
            std::cout << "level" << tmp->level << " ";
            l = tmp->level;
        }
        print(tmp->node->getKey(), tmp->node->getData());
        if (tmp->node->left != nullptr) {
            BinLevel<TKey, TData> *left = new BinLevel<TKey, TData>();
            left->node = tmp->node->left;
            left->level = l + 1;
            queue.push(left);
        }
        if (tmp->node->right != nullptr) {
            BinLevel<TKey, TData> *right = new BinLevel<TKey, TData>();
            right->node = tmp->node->right;
            right->level = l + 1;
            queue.push(right);
        }
    }
    delete tmp;
}
