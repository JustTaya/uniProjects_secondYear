//
// Created by taya on 9/23/18.
//

#ifndef LAB1_1_TREE_H
#define LAB1_1_TREE_H

#include <iostream>
#include <functional>
#include <list>
#include <queue>
#include <stack>


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

//abstract class for tree
template<typename TKey, typename TData, typename Cmp=std::less<TKey>>
class Tree {
public:
    explicit Tree() : _root(nullptr) {};

    explicit Tree(TKey key, TData data) : _root(TNode(key, data)) {};


    virtual bool insert(TKey, TData) = 0;

    virtual bool deleteNode(TKey) = 0;

    virtual bool deleteSubtree(TKey) = 0;

    //methods to print tree
    virtual void printInOrder(void (*print)(TKey, TData)) const = 0;

    virtual void printPreOrder(void (*print)(TKey, TData)) const = 0;

    virtual void printPostOrder(void (*print)(TKey, TData)) const = 0;

    virtual void printLevelOrder(void (*print)(TKey, TData)) const = 0;

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

template<typename TKey, typename TData, typename Cmp=std::less<TKey>>
class MultiTree : public Tree<TKey, TData, Cmp> {
public:
    MultiTree() : Tree<TKey, TData, Cmp>() {};

    MultiTree(TKey key, TData data) : Tree<TKey, TData, Cmp>(key, data) {};

    ~MultiTree();

    bool insert(TKey key, TData data);      //insert root if tree is empty

    MultiNode<TKey, TData> *insert(MultiNode<TKey, TData> *node, TKey key, TData data);     //insert node as son

    MultiNode<TKey, TData> *getRoot();      //reference to root

    bool deleteNode(TKey key);      //delete node by key

    bool deleteSubtree(TKey key);   //delete subtree with root with given key

    MultiNode<TKey, TData> *search(TKey key) const;

    //methods to print tree
    void printInOrder(void (*print)(TKey, TData)) const;     //the same as printPreOrder

    void printPreOrder(void (*print)(TKey, TData)) const;

    void printPostOrder(void (*print)(TKey, TData)) const;

    void printLevelOrder(void (*print)(TKey, TData)) const;

private:
    MultiNode<TKey, TData> *_root;

    MultiNode<TKey, TData> *searchParent(TKey key) const;
};

#include "MultiTree.inc"

template<typename TKey, typename TData, typename Cmp>
MultiTree<TKey, TData, Cmp>::~MultiTree() {
    deleteSubtree(this->_root->getKey());
}

template<typename TKey, typename TData, typename Cmp=std::less<TKey>>
class BinNode : public TNode<TKey, TData> {
public:
    template<typename K, typename D, typename C> friend
    class BSTree;

    explicit BinNode() : TNode<TKey, TData>(), left(nullptr), right(nullptr) {};

    explicit BinNode(TKey key, TData data) :
            TNode<TKey, TData>(key, data), left(nullptr), right(nullptr) {};
    BinNode<TKey, TData> *left;
    BinNode<TKey, TData> *right;
};


template<typename TKey, typename TData, typename Cmp=std::less<TKey>>
class BinTree : public Tree<TKey, TData, Cmp> {
public:
    BinTree() : Tree<TKey, TData, Cmp>() {};

    BinTree(TKey key, TData data) : Tree<TKey, TData, Cmp>(key, data) {};

    ~BinTree();

    bool insert(TKey key, TData data);      //insert root if tree is empty

    BinNode<TKey, TData> *insertleft(BinNode<TKey, TData> *node, TKey key, TData data);     //insert node as left son

    BinNode<TKey, TData> *insertright(BinNode<TKey, TData> *node, TKey key, TData data);     //insert node as left son


    BinNode<TKey, TData> *getRoot();      //reference to root

    bool deleteNode(TKey key);      //delete node by key if it has one or zero sons

    bool deleteSubtree(TKey key);   //delete subtree with root with given key

    BinNode<TKey, TData> *search(TKey key) const;

    //methods to print tree
    void printInOrder(void (*print)(TKey, TData)) const;

    void printPreOrder(void (*print)(TKey, TData)) const;

    void printPostOrder(void (*print)(TKey, TData)) const;

    void printLevelOrder(void (*print)(TKey, TData)) const;

private:
    BinNode<TKey, TData> *_root;

    BinNode<TKey, TData> *searchParent(TKey key) const; //searches a parent node for a node with key(for remove)
};

#include "BinTree.inc"


template<typename TKey, typename TData, typename Cmp=std::less<TKey>>
class BSTree : public BinTree<TKey, TData, Cmp> {
public:
    BSTree() : BinTree<TKey, TData, Cmp>() {};

    BSTree(TKey key, TData data) : BinTree<TKey, TData, Cmp>(key, data) {};

    ~BSTree();

    bool insert(TKey key, TData data, const Cmp &cmp = Cmp());    //insert node using comparator

    BinNode<TKey, TData> *search(TKey key, const Cmp &cmp = Cmp()) const;

    bool deleteNode(TKey key, const Cmp &cmp = Cmp());      //delete node by key if it has one or zero sons

    bool deleteSubtree(TKey key, const Cmp &cmp = Cmp());   //delete subtree with root with given key

    void printInOrder(void (*print)(TKey, TData)) const;

    void printPreOrder(void (*print)(TKey, TData)) const;

    void printPostOrder(void (*print)(TKey, TData)) const;

    void printLevelOrder(void (*print)(TKey, TData)) const;

private:
    BinNode<TKey, TData> *_root;

    BinNode<TKey, TData> *
    searchParent(TKey key, Cmp &cmp = Cmp()) const; //searches a parent node for a node with key(for remove)
};

template<typename TKey, typename TData, typename Cmp>
bool BSTree<TKey, TData, Cmp>::insert(TKey key, TData data, const Cmp &cmp) {
    if (this->_root == nullptr) {
        this->_root = new BinNode<TKey, TData>(key, data);
        return true;
    }
    BinNode<TKey, TData> *tmp = this->_root;
    while (tmp != nullptr) {
        if (cmp(tmp->getKey(), key)) {
            if (tmp->left == nullptr) {
                tmp->left = new BinNode<TKey, TData>(key, data);

                return true;
            }
            tmp = tmp->left;
        } else if (cmp(key, tmp->getKey())) {
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
BinNode<TKey, TData> *BSTree<TKey, TData, Cmp>::search(TKey key, const Cmp &cmp) const {
    if (this->_root == nullptr)
        return nullptr;

    BinNode<TKey, TData> *tmp = this->_root;
    while (tmp != nullptr) {
        if (cmp(tmp->getKey(), key)) {
            if (tmp->left == nullptr)
                return nullptr;
            tmp = tmp->left;
        } else if (cmp(key, tmp->getKey())) {
            if (tmp->right == nullptr)
                return nullptr;
            tmp = tmp->right;
        } else
            return tmp;
    }
    return nullptr;
}

template<typename TKey, typename TData, typename Cmp>
BinNode<TKey, TData> *BSTree<TKey, TData, Cmp>::searchParent(TKey key, Cmp &cmp) const {
    if (this->_root == nullptr)
        return nullptr;

    BinNode<TKey, TData> *tmp = this->_root, *parent = nullptr;
    while (tmp != nullptr) {
        if (cmp(tmp->getKey(), key)) {
            parent = tmp;
            if (tmp->left == nullptr)
                return nullptr;
            tmp = tmp->left;
        } else if (cmp(key, tmp->getKey())) {
            parent = tmp;
            if (tmp->right == nullptr)
                return nullptr;
            tmp = tmp->right;
        } else
            return parent;
    }
    return nullptr;
}

//TODO: delete method
template<typename TKey, typename TData, typename Cmp>
bool BSTree<TKey, TData, Cmp>::deleteNode(TKey key, const Cmp &cmp) {
    if (this->_root == nullptr)
        return false;
    BinNode<TKey, TData> *parent = searchParent(key), *node = nullptr;
    if (cmp(parent->getKey(), key)) {
        node = parent->left;
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
            }
            node->key = tmp->left->key;
            node->data = tmp->left->data;
            tmp->left = tmp->left->right;
        }
    } else if (cmp(key, parent->getKey())) {
        node = parent->right;
        parent->right = nullptr;
    } else {
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
bool BSTree<TKey, TData, Cmp>::deleteSubtree(TKey key, const Cmp &cmp) {
    if (this->_root == nullptr)
        return false;
    BinNode<TKey, TData> *parent = searchParent(key), *node = nullptr;
    if (cmp(parent->getKey(), key)) {
        node = parent->left;
        parent->left = nullptr;
    } else if (cmp(key, parent->getKey())) {
        node = parent->right;
        parent->right = nullptr;
    } else {
        delete parent;
        parent = nullptr;
        return true;
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
void BSTree<TKey, TData, Cmp>::printInOrder(void (*print)(TKey, TData)) const {
    if (this->_root == nullptr)
        return;
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
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
void BSTree<TKey, TData, Cmp>::printPreOrder(void (*print)(TKey, TData)) const {
    if (this->_root == nullptr)
        return;
    std::stack<BinNode<TKey, TData> *> stack;
    BinNode<TKey, TData> *tmp = nullptr;
    stack.push(this->_root);
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
void BSTree<TKey, TData, Cmp>::printPostOrder(void (*print)(TKey, TData)) const {
    if (this->_root == nullptr)
        return;
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
        print(tmp->getKey(), tmp->getData());
    }
}

template<typename TKey, typename TData, typename Cmp>
void BSTree<TKey, TData, Cmp>::printLevelOrder(void (*print)(TKey, TData)) const {
    if (this->_root == nullptr)
        return;
    std::queue<BinLevel<TKey, TData> *> queue;
    int l = 1;
    BinLevel<TKey, TData> *tmp = new BinLevel<TKey, TData>();
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


#endif //LAB1_1_TREE_H