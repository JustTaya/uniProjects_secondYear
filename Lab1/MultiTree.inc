
template<typename TKey, typename TData, typename Cmp>
MultiNode<TKey, TData> *MultiTree<TKey, TData, Cmp>::insert(MultiNode<TKey, TData> *node, TKey key, TData data) {
    if (node != nullptr) {
        node->add(key, data);
        return node->nodes.back();
    }
    return nullptr;
}

template<typename TKey, typename TData, typename Cmp>
MultiNode<TKey, TData> *MultiTree<TKey, TData, Cmp>::searchParent(TKey key) const {
    if (this->_root == nullptr || this->_root->getKey() == key)
        return this->_root;
    MultiNode<TKey, TData> *tmp = nullptr;
    std::stack<MultiNode<TKey, TData> *> stack;
    typename std::list<MultiNode<TKey, TData> *>::iterator it;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->nodes.empty())
            continue;
        it = std::find_if(tmp->nodes.begin(), tmp->nodes.end(),
                          [key](const MultiNode<TKey, TData> *node) -> bool {
                              return (node->getKey() == key);
                          });
        if(it!=tmp->nodes.end())
            return tmp;
        std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [&stack](MultiNode<TKey, TData> *node) {
            stack.push(node);
        });
    }
    return nullptr;
}

template<typename TKey, typename TData,typename Cmp>
MultiNode<TKey, TData> *MultiTree<TKey, TData,Cmp>::search(TKey key) const {
    if (this->_root == nullptr || this->_root->getKey() == key)
        return this->_root;
    MultiNode<TKey, TData> *tmp = nullptr;
    std::stack<MultiNode<TKey, TData> *> stack;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->getKey() == key)
            return tmp;
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [&stack](MultiNode<TKey, TData> *node) {
                stack.push(node);
            });
    }
    return nullptr;
}

template<typename TKey, typename TData, typename Cmp>
bool MultiTree<TKey, TData,Cmp>::deleteNode(TKey key) {
    MultiNode<TKey, TData> *parent = searchParent(key);
    if (parent == nullptr)
        return false;
    if (parent == this->_root && parent->nodes.empty()) {
        delete this->_root;
        this->_root = nullptr;
        return true;
    }
    typename std::list<MultiNode<TKey, TData> *>::iterator it =
            std::find_if(parent->nodes.begin(), parent->nodes.end(),
                         [key](const MultiNode<TKey, TData> *node) -> bool {
                             return (node->getKey() == key);
                         });
    MultiNode<TKey, TData> *node = *it;
    std::for_each(node->nodes.begin(), node->nodes.end(), [parent, node](const MultiNode<TKey, TData> *tmp) {
        parent->nodes.push_back(node);
    });
    parent->nodes.erase(it);
    node = nullptr;
    return true;
}

template<typename TKey, typename TData,typename Cmp>
bool MultiTree<TKey, TData,Cmp>::deleteSubtree(TKey key) {
    MultiNode<TKey, TData> *parent = searchParent(key);
    if (parent == nullptr)
        return false;
    if (parent == this->_root && parent->nodes.empty()) {
        delete this->_root;
        this->_root = nullptr;
        return true;
    }
    typename std::list<MultiNode<TKey, TData> *>::iterator it =
            std::find_if(parent->nodes.begin(), parent->nodes.end(),
                         [key](const MultiNode<TKey, TData> *node) -> bool {
                             return (node->getKey() == key);
                         });
    MultiNode<TKey, TData> *node = *it;
    MultiNode<TKey, TData> *tmp = nullptr;
    std::stack<MultiNode<TKey, TData> *> stack;
    stack.push(node);
    tmp->nodes.remove(node);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [&stack](MultiNode<TKey, TData> *node) {
                stack.push(node);
            });
        delete tmp;
        tmp = nullptr;
    }
    return true;
}

template<typename TKey, typename TData, typename Cmp>
void MultiTree<TKey, TData,Cmp>::printPreOrder(void (*print)(TKey,TData)) const {

    if (this->_root == nullptr)
        return;
    std::stack<MultiNode<TKey, TData> *> stack;
    MultiNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        print(tmp->getKey(), tmp->getData());
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [print](const MultiNode<TKey, TData> *node) {
                print(node->getKey(),node->getData());
            });
    }
}

template<typename TKey, typename TData, typename Cmp>
void MultiTree<TKey, TData,Cmp>::printPostOrder(void (*print)(TKey,TData)) const {
    if (this->_root == nullptr)
        return;
    std::stack<MultiNode<TKey, TData> *> stack;
    MultiNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [print](const MultiNode<TKey, TData> *node) {
                print(node->getKey(),node->getData());
            });
        print(tmp->getKey(), tmp->getData());
    }
}

template<typename TKey, typename TData>
struct MultiTreeLevel {
    size_t level = 0;
    MultiNode<TKey, TData> *node = nullptr;
};

template<typename TKey, typename TData,typename Cmp>
void MultiTree<TKey, TData, Cmp>::printLevelOrder(void (*print)(TKey,TData)) const {
    std::queue<MultiTreeLevel<TKey, TData> *> queue;
    size_t l = 1;
    MultiTreeLevel<TKey, TData> *tmp = new MultiTreeLevel<TKey, TData>();
    tmp->level = 0;
    tmp->node = this->_root;
    queue.push(tmp);
    while (!queue.empty()) {
        tmp = queue.front();
        queue.pop();
        if (l != tmp->level) {
            std::cout << std::endl;
            std::cout << "level" << tmp->level << " ";
            l = tmp->level;
        }
        print(tmp->node->getKey(),tmp->node->getData());
        if (!tmp->node->nodes.empty()) {
            std::for_each(tmp->node->nodes.begin(), tmp->node->nodes.end(),
                          [&queue, l](MultiNode<TKey, TData> *node) {
                              MultiTreeLevel<TKey, TData> *level = new MultiTreeLevel<TKey, TData>();
                              level->node = node;
                              level->level = l + 1;
                              queue.push(level);
                          });
        }
    }
    delete tmp;
}

template<typename TKey, typename TData, typename Cmp>
bool MultiTree<TKey, TData, Cmp>::insert(TKey key, TData data) {
    if(this->_root==nullptr){
        this->_root=new MultiNode<TKey,TData>(key,data);
        return true;
    }
    return false;
}

template<typename TKey, typename TData, typename Cmp>
void MultiTree<TKey, TData, Cmp>::printInOrder(void (*print)(TKey,TData)) const {
    printPreOrder(print);
}

template<typename TKey, typename TData, typename Cmp>
MultiNode<TKey, TData> *MultiTree<TKey, TData, Cmp>::getRoot() {
    return this->_root;
}