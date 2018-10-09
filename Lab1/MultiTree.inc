template<typename TKey, typename Cmp>
MultiNode<TKey> *MultiTree<TKey, Cmp> ::insert(MultiNode<TKey> *node, TKey key) {
    if (node != nullptr) {
        node->add(key);
        return node->nodes.back();
    }
return nullptr;
}

template<typename TKey, typename Cmp>
MultiNode<TKey> *MultiTree<TKey, Cmp>:: searchParent(TKey key) const {
    if (this->_root == nullptr || this->_root->getKey() == key)
        return this->_root;
    MultiNode<TKey> *tmp = nullptr;
    std::stack<MultiNode<TKey> *> stack;
    typename std::list<MultiNode<TKey> *>::iterator it;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->nodes.empty())
            continue;
        it = std::find_if(tmp->nodes.begin(), tmp->nodes.end(),
                          [key](const MultiNode<TKey> *node) -> bool {
                              return (node->getKey() == key);
                          });
if(it!=tmp->nodes.end())
    return tmp;
std ::for_each(tmp->nodes.begin(), tmp->nodes.end(), [&stack](MultiNode<TKey> *node) {
            stack.push(node);
        });
}
return nullptr;
}

template<typename TKey, typename Cmp>
MultiNode<TKey> *MultiTree<TKey, Cmp> :: search(TKey key) const {
    if (this->_root == nullptr || this->_root->getKey() == key)
        return this->_root;
    MultiNode<TKey> *tmp = nullptr;
    std::stack<MultiNode<TKey> *> stack;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->getKey() == key)
            return tmp;
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [&stack](MultiNode<TKey> *node) {
                stack.push(node);
            });
}
return nullptr;
}

template<typename TKey, typename Cmp>
bool MultiTree<TKey, Cmp> :: deleteNode(TKey key) {
    MultiNode<TKey> *parent = searchParent(key);
    if (parent == nullptr)
        return false;
    if (parent == this->_root && parent->nodes.empty()) {
        delete this->_root;
        this->_root = nullptr;
        return true;
    }
typename std :: list<MultiNode<TKey> *> :: iterator it =
std :: find_if(parent->nodes.begin(), parent->nodes.end(),
[key](const MultiNode<TKey> *node) -> bool {
                             return (node->getKey() == key);
                         });
MultiNode<TKey> *node = *it;
std :: for_each(node->nodes.begin(), node->nodes.end(), [parent, node](const MultiNode<TKey> *tmp) {
        parent->nodes.push_back(node);
    });
parent->nodes.erase(it);
node = nullptr;
return true;
}


template<typename TKey, typename Cmp>
void MultiTree<TKey, Cmp> :: printPreOrder(void (*print)(TKey)) const {

    if (this->_root == nullptr)
        return;
    std::stack<MultiNode<TKey> *> stack;
    MultiNode<TKey> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        print(tmp->getKey());
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [print](const MultiNode<TKey> *node) {
                print(node->getKey());
            });
    }
}

template<typename TKey, typename Cmp>
void MultiTree<TKey,Cmp>::printPostOrder(void (*print)(TKey)) const {
    if (this->_root == nullptr)
        return;
    std::stack<MultiNode<TKey> *> stack;
    MultiNode<TKey> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [print](const MultiNode<TKey> *node) {
                print(node->getKey());
            });
        print(tmp->getKey());
    }
}

template<typename TKey>
struct MultiTreeLevel {
    size_t level = 0;
    MultiNode<TKey> *node = nullptr;
};

template<typename TKey,typename Cmp>
void MultiTree<TKey, Cmp>::printLevelOrder(void (*print)(TKey)) const {
    std::queue<MultiTreeLevel<TKey> *> queue;
    size_t l = 1;
    MultiTreeLevel<TKey> *tmp = new MultiTreeLevel<TKey>();
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
        if(tmp->node==nullptr)
          continue;
        print(tmp->node->getKey());
        if (!tmp->node->nodes.empty()) {
            std::for_each(tmp->node->nodes.begin(), tmp->node->nodes.end(),
                          [&queue, l](MultiNode<TKey> *node) {
                              MultiTreeLevel<TKey> *level = new MultiTreeLevel<TKey>();
                              level->node = node;
                              level->level = l + 1;
                              queue.push(level);
                          });
        }
    }
    delete tmp;
}

template<typename TKey,typename Cmp>
bool MultiTree<TKey, Cmp>::insertRoot(TKey key) {
    if(this->_root==nullptr){
        this->_root=new MultiNode<TKey>(key);
        return true;
    }
    return false;
}

template<typename TKey, typename Cmp>
void MultiTree<TKey, Cmp>::printInOrder(void (*print)(TKey)) const {
    printPreOrder(print);
}

template<typename TKey, typename Cmp>
MultiNode<TKey> *MultiTree<TKey, Cmp>::getRoot() {
    return this->_root;
}
template<typename TKey, typename Cmp>
MultiTree<TKey,Cmp>::~MultiTree(){
 if (this->_root != nullptr)
       {
       MultiNode<TKey> *tmp = nullptr;
           std::stack<MultiNode<TKey> *> stack;
           stack.push(this->_root);
           while(!stack.empty()){
           tmp=stack.top();
           stack.pop();
               if (!tmp->nodes.empty())
                   std::for_each(tmp->nodes.begin(), tmp->nodes.end(),
                                 [&stack](MultiNode<TKey> *node) {
                                     stack.push(node);
       });
       delete tmp;
       }
       }
}
