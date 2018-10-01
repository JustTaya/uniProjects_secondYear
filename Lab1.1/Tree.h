//
// Created by taya on 9/23/18.
//

#ifndef LAB1_1_TREE_H
#define LAB1_1_TREE_H

#endif //LAB1_1_TREE_H

#include <iostream>
#include <functional>
#include <list>
#include <queue>
#include <stack>

//default functor to print node key and data
class Print {
    void operator()(const int &key);

    void operator()(const int &key, const int &data);
};

void Print::operator()(const int &key) {
    std::cout << "Key: " << key << std::endl;
}

void Print::operator()(const int &key, const int &data) {
    std::cout << "Key: " << key << " Data: " << data << std::endl;
}

//abstract class of tree node
template<typename TKey, typename TData>
class TNode {
public:
    explicit TNode(TKey key, TData data) : key(key), data(data) {};

    TKey getKey() const;

    TData getData() const;

protected:
    TKey key;
    TData data;
};

template<typename TKey, typename TData>
TKey TNode<TKey, TData>::getKey() const {
    return this->key;
}

template<typename TKey, typename TData>
TData TNode<TKey, TData>::getData() const {
    return this->data;
}

template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
class Tree {
public:
    explicit Tree() : _root(nullptr) {};

    explicit Tree(TKey key, TData data) : _root(TNode(key, data)) {};

    virtual TNode<TKey, TData> *insert(TNode<TKey, TData> *, TKey, TData) = 0;

    virtual bool deleteNode(TKey) = 0;

    virtual bool deleteSubtree(TKey) = 0;

    virtual TNode<TKey, TData> *search(TKey) const = 0;

    //methods to print tree
    virtual void printInOrder() const = 0;

    virtual void printPreOrder() const = 0;

    virtual void printPostOrder() const = 0;

    virtual void printLevelOrder() const = 0;

private:
    TNode<TKey, TData> *_root;
};

template<typename TKey, typename TData>
class MultiNode : public TNode<TKey, TData> {
public:
    explicit MultiNode(TKey key, TData data) : TNode<TKey, TData>(key, data) {};

    void add(TKey key, TData data);

    std::list<MultiNode<TKey, TData> *> nodes;

protected:
    TKey key;
    TData data;
};

template<typename TKey, typename TData>
void MultiNode<TKey, TData>::add(TKey key, TData data) {
    MultiNode<TKey, TData> *node = new MultiNode<TKey, TData>(key, data);
    this->nodes.push_back(node);
}

template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
class MultiTree : public Tree<TKey, TData, P, Cmp> {
public:
    MultiTree() : Tree<TKey, TData, P, Cmp>() {};

    MultiTree(TKey key, TData data) : Tree<TKey, TData, P, Cmp>(key, data) {};

    virtual MultiNode<TKey, TData> *insert(MultiNode<TKey, TData> *node, TKey key, TData data);

    virtual bool deleteNode(TKey key);

    virtual bool deleteSubtree(TKey key);

    virtual MultiNode<TKey, TData> *search(TKey key) const;

    //methods to print tree
    virtual void printPreOrder() const;

    virtual void printPostOrder() const;

    virtual void printLevelOrder() const;

private:
    MultiNode<TKey, TData> *_root;

    MultiNode<TKey, TData> *searchParent(TKey key) const;
};

template<typename TKey, typename TData, typename P, typename Cmp>
MultiNode<TKey, TData> *MultiTree<TKey, TData, P, Cmp>::insert(MultiNode<TKey, TData> *node, TKey key, TData data) {
    if (node != nullptr) {
        node->add(key, data);
        return node->nodes.back();
    }
    return nullptr;
}

template<typename TKey, typename TData, typename P, typename Cmp>
MultiNode<TKey, TData> *MultiTree<TKey, TData, P, Cmp>::searchParent(TKey key) const {
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
        if (it != tmp->nodes.back())
            return tmp;
        std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [stack](const MultiNode<TKey, TData> *node) {
            stack.push(node);
        });
    }
    return nullptr;
}

template<typename TKey, typename TData, typename P, typename Cmp>
MultiNode<TKey, TData> *MultiTree<TKey, TData, P, Cmp>::search(TKey key) const {
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
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [stack](const MultiNode<TKey, TData> *node) {
                stack.push(node);
            });
    }
    return nullptr;
}

template<typename TKey, typename TData, typename P, typename Cmp>
bool MultiTree<TKey, TData, P, Cmp>::deleteNode(TKey key) {
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

template<typename TKey, typename TData, typename P, typename Cmp>
bool MultiTree<TKey, TData, P, Cmp>::deleteSubtree(TKey key) {
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
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [stack](const MultiNode<TKey, TData> *node) {
                stack.push(node);
            });
        delete tmp;
        tmp = nullptr;
    }
    return true;
}

template<typename TKey, typename TData, typename P, typename Cmp>
void MultiTree<TKey, TData, P, Cmp>::printPreOrder() const {

    if (this->_root == nullptr)
        return;
    std::stack<MultiNode<TKey, TData> *> stack;
    MultiNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        //P(tmp->key, tmp->data);
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [](const MultiNode<TKey, TData> *node) {
                //P(node->key,node->data);
            });
    }
}

template<typename TKey, typename TData, typename P, typename Cmp>
void MultiTree<TKey, TData, P, Cmp>::printPostOrder() const {
    if (this->_root == nullptr)
        return;
    std::stack<MultiNode<TKey, TData> *> stack;
    MultiNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (!tmp->nodes.empty())
            std::for_each(tmp->nodes.begin(), tmp->nodes.end(), [](const MultiNode<TKey, TData> *node) {
                //P(node->key,node->data);
            });
        //P(tmp->key, tmp->data);
    }
}

template<typename TKey, typename TData>
struct MultiTreeLevel {
    size_t level = 0;
    MultiNode<TKey, TData> *node = nullptr;
};

template<typename TKey, typename TData, typename P, typename Cmp>
void MultiTree<TKey, TData, P, Cmp>::printLevelOrder() const {
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
//P(key,data);
        if (!tmp->node->nodes.empty()) {
            std::for_each(tmp->node->nodes.begin(), tmp->node->nodes.end(),
                          [queue, l](const MultiNode<TKey, TData> *node) {
                              MultiTreeLevel<TKey, TData> *tmp = new MultiTreeLevel<TKey, TData>();
                              tmp->node = node;
                              tmp->level = l + 1;
                              queue.push(tmp);
                          });
        }
    }
    delete tmp;
}

//TODO: check, refactor & rewrite
/*
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
class BinTNode : public TNode<TKey, TData> {
public:
    template<typename K, typename D> friend
    class BSTree;
    explicit BinTNode() : TNode<TKey, TData>(), left(nullptr), right(nullptr) {};
    explicit BinTNode(TKey key, TData data) :
            TNode<TKey, TData>(key, data), left(nullptr), right(nullptr) {};
    BinTNode<TKey, TData> *left;
    BinTNode<TKey, TData> *right;
};
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
class BinTree : public Tree<TKey, TData> {
public:
    explicit BinTree() : _root(nullptr) {};
    explicit BinTree(TKey key, TData data) : _root(BinTNode(key, data)) {};
    virtual ~BinTree();
    virtual void insert(TKey key, TData data);
    virtual bool deleteNode(TKey);   //delete the least of the tree
    virtual bool deleteSubtree(TKey);
    BinTNode<TKey, TData> *search(TKey key) const;
    //methods to print tree
    virtual void printInOrder() const;
    virtual void printPreOrder() const;
    virtual void printPostOrder() const;
    virtual void printLevelOrder() const;
private:
    BinTNode<TKey, TData> *_root;
    BinTNode<TKey, TData> *findParentOf(TKey key) const;  //searches a parent node for a node with key(for remove)
};
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
void BinTree<TKey, TData,P,Cmp>::insert(TKey key, TData data) {
    if (this->_root == nullptr) {
        this->_root = new BinTNode<TKey, TData>(key, data);
        return;
    }
    BinTNode<TKey, TData> *tmp = this->_root;
    char buff = ' ';
    while (tmp != nullptr) {
        std::cout << "Current node key is: ";
        //std::cout<<this->getKey();
        std::cout << "Chose L for left/R for right node.\n";
        std::cin >> buff;
        switch (buff) {
            case 'L':
                if (tmp->left == nullptr) {
                    std::cout << "Press Y to insert node here.\n";
                    std::cin >> buff;
                    if (buff == 'Y')
                        tmp->left = new BinTNode<TKey, TData>(key, data);
                    return;
                } else
                    tmp = tmp->left;
                break;
            case 'R':
                if (tmp->right == nullptr) {
                    std::cout << "Press Y to insert node here.\n";
                    std::cin >> buff;
                    if (buff == 'Y')
                        tmp->right = new BinTNode<TKey, TData>(key, data);
                    return;
                } else
                    tmp = tmp->right;
                break;
            default:
                std::cout << "Input is not correct. Try one more time.";
                break;
        }
        break;
    }
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
bool BinTree<TKey, TData,P,Cmp>::deleteNode(TKey key) {
    BinTNode<TKey, TData> *parent = findParentOf(key), *node = nullptr;
    if (parent == nullptr)
        return false;
    if (parent->getKey() == key) {
        node = parent;
        delete node;
        return true;
    }
    if (parent->left->getKey() == key) {
        node = parent->left;
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            parent->left = nullptr;
            return true;
        }
    }
    if (parent->right->getKey() == key) {
        node = parent->right;
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            parent->right = nullptr;
            return true;
        }
    }
    return false;
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
BinTNode<TKey, TData,P,Cmp>*BinTree<TKey, TData>::findParentOf(TKey key) const {
    if (this->_root == nullptr || this->_root->getKey() == key)
        return this->_root;
    std::stack<BinTNode<TKey, TData> *> stack;
    BinTNode<TKey, TData> *tmp = nullptr;
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
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
bool BinTree<TKey, TData,P,Cmp>::deleteSubtree(TKey key) {
    BinTNode<TKey, TData> *parent = findParentOf(key), *node = nullptr;
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
    std::stack<BinTNode<TKey, TData> *> stack;
    BinTNode<TKey, TData> *tmp = nullptr;
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
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
void BinTree<TKey, TData,P,Cmp>::printInOrder() const {
    if (this->_root == nullptr)
        return;
    std::stack<BinTNode<TKey, TData> *> stack;
    BinTNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        //std::cout<<tmp->getKey()<<' '<<tmp->getData<<std::endl;
        if (tmp->right != nullptr)
            stack.push(tmp->right);
    }
}
//TODO:check this
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
BinTree<TKey, TData,P,Cmp>::~BinTree() {
    deleteSubtree(this->_root->getKey());
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
void BinTree<TKey, TData,P,Cmp>::printPreOrder() const {
    if (this->_root == nullptr)
        return;
    std::stack<BinTNode<TKey, TData> *> stack;
    BinTNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        //std::cout<<tmp->getKey()<<' '<<tmp->getData<<std::endl;
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
    }
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
void BinTree<TKey, TData,P,Cmp>::printPostOrder() const {
    if (this->_root == nullptr)
        return;
    std::stack<BinTNode<TKey, TData> *> stack;
    BinTNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->left != nullptr)
            stack.push(tmp->left);
        if (tmp->right != nullptr)
            stack.push(tmp->right);
        //std::cout<<tmp->getKey()<<' '<<tmp->getData<<std::endl;
    }
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
struct Level {
    int level = 0;
    BinTNode<TKey, TData> *node = nullptr;
};
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
void BinTree<TKey, TData,P,Cmp>::printLevelOrder() const {
    std::queue<Level<TKey, TData> *> queue;
    int l = 1;
    Level<TKey, TData> *tmp = new Level<TKey, TData>();
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
        //std::cout << tmp->node->key << " ";
        if (tmp->node->left != nullptr) {
            Level<TKey, TData> *left = new Level<TKey, TData>();
            left->node = tmp->node->left;
            left->level = l + 1;
            queue.push(left);
        }
        if (tmp->node->right != nullptr) {
            Level<TKey, TData> *right = new Level<TKey, TData>();
            right->node = tmp->node->right;
            right->level = l + 1;
            queue.push(right);
        }
    }
    delete tmp;
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
BinTNode<TKey, TData,P,Cmp> *BinTree<TKey, TData>::search(TKey key) const {
    if (this->_root == nullptr)
        return nullptr;
    std::stack<BinTNode<TKey, TData> *> stack;
    BinTNode<TKey, TData> *tmp = nullptr;
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
//TODO: insert, delete & search methods
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
class BSTree : public BinTree<TKey, TData> {
public:
    explicit BSTree() : _root(nullptr) {};
    explicit BSTree(TKey key, TData data) : _root(BinTNode(key, data)) {};
    virtual void insert(TKey key, TData data);
    virtual bool deleteNode(TKey);
    virtual bool deleteSubtree(TKey);
    //virtual TNode<TKey,TData> search(TKey key) const;
private:
    BinTNode<TKey, TData> *_root;
    BinTNode<TKey, TData> *findLeftLeafParent();
    BinTNode<TKey, TData> *
    void replaceNode(BinTNode<TKey, TData> *parent, BinTNode<TKey, TData> *node);
};
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
void BSTree<TKey, TData,P,Cmp>::insert(TKey key, TData data) {
    if (this->_root == nullptr) {
        this->_root = new BinTNode<TKey, TData>(key, data);
        return;
    }
    BinTNode<TKey, TData> *tmp = this->_root;
    while (tmp != nullptr) {
        if (key < tmp->getKey()) {
            if (tmp->left == nullptr) {
                BinTNode<TKey, TData> *node = new BinTNode<TKey, TData>(key, data);
                tmp->left = node;
                return;
            } else
                tmp = tmp->left;
        } else if (key > tmp->getKey()) {
            if (tmp->right == nullptr) {
                BinTNode<TKey, TData> *node = new BinTNode<TKey, TData>(key, data);
                tmp->right = node;
                return;
            } else
                tmp = tmp->right;
        } else {
            tmp->data = data;
        }
    }
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
bool BSTree<TKey, TData,P,Cmp>::deleteNode(TKey key) {
    if (this->_root == nullptr)
        return false;
    BinTNode<TKey, TData> *tmp = this->_root,
            *node = nullptr;
    while (tmp != nullptr) {
        if (key < tmp->key) {
            if (tmp->left == nullptr)
                return false;
            else if (tmp->left->key != key)
                tmp = tmp->left;
            else {
                node = tmp->left;
                break;
            }
        } else if (key > tmp->getKey()) {
            if (tmp->right == nullptr)
                return false;
            else if (tmp->right->key != key)
                tmp = tmp->right;
            else {
                node = tmp->right;
                break;
            }
        } else {
            delete tmp;
            this->_root = nullptr;
        }
    }
    return true;
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
BinTNode<TKey, TData,P,Cmp> *BSTree<TKey, TData>::findLeftLeafParent() {
    if (this->_root == nullptr)
        return nullptr;
    BinTNode<TKey, TData> *node = this->_root;
    while (node->left->left != nullptr)
        node = node->left;
    return node;
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
void BSTree<TKey, TData,P,Cmp>::replaceNode(BinTNode<TKey, TData> *parent, BinTNode<TKey, TData> *node) {
    if (node->left == nullptr && node->right == nullptr) {
        if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete node;
    } else if (node->left == nullptr) {
        if (parent->left == node)
            parent->left = node->right;
        else
            parent->right = node->right;
        delete node;
    } else if (node->right == nullptr) {
        if (parent->left == node)
            parent->left = node->left;
        else
            parent->right = node->left;
        delete node;
    } else {
        if (node->right->left == nullptr) {
            if (parent->left == node)
                parent->left = node->right;
            else
                parent->right = node->right;
            delete node;
        } else {
            BinTNode<TKey, TData> *tmp = findLeftLeafParent();
            node->key = tmp->left->key;
            node->data = tmp->left->data;
            tmp->left->left = node->left;
            tmp->left->right = node->right;
            delete tmp->left;
            tmp->left = nullptr;
        }
    }
}
template<typename TKey, typename TData, typename P=Print, typename Cmp=std::less<TKey>>
bool BSTree<TKey, TData,P,Cmp>::deleteSubtree(TKey) {
}
*/
