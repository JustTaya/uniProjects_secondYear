template<typename TKey, typename Cmp>
bool BinTree<TKey, Cmp>::insertRoot(TKey key) {
    if (this->_root == nullptr) {
        this->_root = new BinNode<TKey>(key);
        return true;
    }
    return false;
}

template<typename TKey, typename Cmp>
BinNode<TKey> *BinTree<TKey, Cmp>::insertleft(BinNode<TKey> *node, TKey key) {
    if (node != nullptr && node->left == nullptr) {
        node->left = new BinNode<TKey>(key);
        return node->left;
    }
    return nullptr;
}

template<typename TKey, typename Cmp>
BinNode<TKey> *BinTree<TKey, Cmp>::insertright(BinNode<TKey> *node, TKey key) {
    if (node != nullptr && node->right == nullptr) {
        node->right = new BinNode<TKey>(key);
        return node->right;
    }
    return nullptr;
}

template<typename TKey, typename Cmp>
BinNode<TKey> *BinTree<TKey, Cmp>::getRoot() {
    return this->_root;
}

template<typename TKey, typename Cmp>
bool BinTree<TKey, Cmp>::deleteNode(TKey key) {
    BinNode<TKey> *parent = searchParent(key), *node = nullptr;
    if (parent == nullptr)
        return false;
    if (parent->getKey() == key) {
        node = parent;
        delete node;
        node = nullptr;
        return true;
    }
    if(parent->left!=nullptr)
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
    if(parent->right!=nullptr)
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

template<typename TKey, typename Cmp>
BinNode<TKey> *BinTree<TKey,Cmp>::searchParent(TKey key) const {
    if (this->_root == nullptr || this->_root->getKey() == key)
        return this->_root;
    std::stack<BinNode<TKey> *> stack;
    BinNode<TKey> *tmp = nullptr;
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

template<typename TKey,typename Cmp>
BinNode<TKey> *BinTree<TKey,Cmp>::search(TKey key) const {
    if (this->_root == nullptr)
        return nullptr;
    std::stack<BinNode<TKey> *> stack;
    BinNode<TKey> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->getKey() == key) {
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

template<typename TKey, typename Cmp>
void BinTree<TKey,Cmp>::printInOrder(void (*print)(TKey)) const {
    printInOrder(print,this->_root);
}

template<typename TKey, typename Cmp>
void BinTree<TKey, Cmp>::printPreOrder(void (*print)(TKey)) const {
   printPreOrder(print,this->_root);
}


template<typename TKey, typename Cmp>
void BinTree<TKey, Cmp>::printPostOrder(void (*print)(TKey)) const {
    printPostOrder(print,this->_root);
}

template<typename TKey>
struct BinLevel {
    int level = 0;
    BinNode<TKey> *node = nullptr;
};

template<typename TKey, typename Cmp>
void BinTree<TKey, Cmp>::printLevelOrder(void (*print)(TKey)) const {

    printLevelOrder(print,this->_root);

}

template<typename TKey, typename Cmp>
BinTree<TKey, Cmp>::~BinTree() {
if(this->_root!=nullptr){
 std::stack<BinNode<TKey> *> stack;
    BinNode<TKey> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if(tmp==nullptr)
        break;
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
        delete tmp;
        tmp= nullptr;
}
    }
    this->_root=nullptr;
}


template<typename TKey, typename Cmp>
void BinTree<TKey, Cmp>::printInOrder(void (*print)(TKey), BinNode<TKey> *root) const {
    if (root == nullptr)
        return;
    std::stack<BinNode<TKey> *> stack;
    BinNode<TKey> *tmp = nullptr;
    stack.push(root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        print(tmp->getKey());
        if (tmp->right != nullptr)
            stack.push(tmp->right);
    }
}


template<typename TKey,typename Cmp>
void BinTree<TKey, Cmp>::printPreOrder(void (*print)(TKey), BinNode<TKey> *root) const {
    if (root == nullptr)
        return;
    std::stack<BinNode<TKey> *> stack;
    BinNode<TKey> *tmp = nullptr;
    stack.push(root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        print(tmp->getKey());
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
    }
}

template<typename TKey,  typename Cmp>
void BinTree<TKey, Cmp>::printPostOrder(void (*print)(TKey), BinNode<TKey> *root) const {
    if (root == nullptr)
        return;
    std::stack<BinNode<TKey> *> stack;
    BinNode<TKey> *tmp = nullptr;
    stack.push(root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
        print(tmp->getKey());
    }
}


template<typename TKey, typename Cmp>
void BinTree<TKey, Cmp>::printLevelOrder(void (*print)(TKey), BinNode<TKey> *root) const {
    if(root==nullptr)
        return;
    std::queue<BinLevel<TKey> *> queue;
    int l = 1;
    BinLevel<TKey> *tmp = new BinLevel<TKey>();
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
        if(tmp->node==nullptr)
                  continue;
        print(tmp->node->getKey());
        if (tmp->node->left != nullptr) {
            BinLevel<TKey> *left = new BinLevel<TKey>();
            left->node = tmp->node->left;
            left->level = l + 1;
            queue.push(left);
        }
        if (tmp->node->right != nullptr) {
            BinLevel<TKey> *right = new BinLevel<TKey>();
            right->node = tmp->node->right;
            right->level = l + 1;
            queue.push(right);
        }
    }
    delete tmp;
}
