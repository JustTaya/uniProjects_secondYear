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
template<typename TKey>
class TNode {
public:
    explicit TNode(TKey key) : key(key) {};

    TKey getKey() const;

protected:
    TKey key;
};

template<typename TKey>
TKey TNode<TKey>::getKey() const {
    return this->key;
}


//abstract class for tree
template<typename TKey, typename Cmp=std::less<TKey>>
class Tree {
public:
    explicit Tree() : _root(nullptr) {};

    explicit Tree(TKey key) : _root(TNode(key)) {};


    virtual bool insert(TKey) = 0;

    virtual bool deleteNode(TKey) = 0;

    virtual bool deleteSubtree(TKey) = 0;

    //methods to print tree
    virtual void printInOrder(void (*print)(TKey)) const = 0;

    virtual void printPreOrder(void (*print)(TKey)) const = 0;

    virtual void printPostOrder(void (*print)(TKey)) const = 0;

    virtual void printLevelOrder(void (*print)(TKey)) const = 0;

private:
    TNode<TKey> *_root;
};

template<typename TKey>
class MultiNode : public TNode<TKey> {
public:
    explicit MultiNode(TKey key) : TNode<TKey>(key) {};

    void add(TKey key);

    std::list<MultiNode<TKey> *> nodes;

protected:
    TKey key;
};

template<typename TKey>
void MultiNode<TKey>::add(TKey key) {
    MultiNode<TKey> *node = new MultiNode<TKey>(key);
    this->nodes.push_back(node);
}

template<typename TKey, typename Cmp=std::less<TKey>>
class MultiTree : public Tree<TKey, Cmp> {
public:
    MultiTree() : Tree<TKey, Cmp>() {};

    MultiTree(TKey key) : Tree<TKey, Cmp>(key) {};

    ~MultiTree();

    bool insert(TKey key);      //insert root if tree is empty

    MultiNode<TKey> *insert(MultiNode<TKey> *node, TKey key);     //insert node as son

    MultiNode<TKey> *getRoot();      //reference to root

    bool deleteNode(TKey key);      //delete node by key

    bool deleteSubtree(TKey key);   //delete subtree with root with given key

    MultiNode<TKey> *search(TKey key) const;

    //methods to print tree
    void printInOrder(void (*print)(TKey)) const;     //the same as printPreOrder

    void printPreOrder(void (*print)(TKey)) const;

    void printPostOrder(void (*print)(TKey)) const;

    void printLevelOrder(void (*print)(TKey)) const;

private:
    MultiNode<TKey> *_root;

    MultiNode<TKey> *searchParent(TKey key) const;
};


#include "MultiTree.inc"



template<typename TKey, typename Cmp=std::less<TKey>>
class BinNode : public TNode<TKey> {
public:
    template<typename K, typename C> friend
    class BSTree;

    explicit BinNode() : TNode<TKey>(), left(nullptr), right(nullptr) {};

    explicit BinNode(TKey key) :
            TNode<TKey>(key), left(nullptr), right(nullptr) {};
    BinNode<TKey> *left;
    BinNode<TKey> *right;
};


template<typename TKey, typename Cmp=std::less<TKey>>
class BinTree : public Tree<TKey, Cmp> {
public:
    BinTree() : Tree<TKey, Cmp>() {};

    BinTree(TKey key) : Tree<TKey, Cmp>(key) {};

    ~BinTree();

    bool insert(TKey key);      //insert root if tree is empty

    BinNode<TKey> *insertleft(BinNode<TKey> *node, TKey key);     //insert node as left son

    BinNode<TKey> *insertright(BinNode<TKey> *node, TKey key);     //insert node as left son


    BinNode<TKey> *getRoot();      //reference to root

    bool deleteNode(TKey key);      //delete node by key if it has one or zero sons

    bool deleteSubtree(TKey key);   //delete subtree with root with given key

    BinNode<TKey> *search(TKey key) const;

    //methods to print tree
    virtual void printInOrder(void (*print)(TKey)) const;

    virtual void printPreOrder(void (*print)(TKey)) const;

    virtual void printPostOrder(void (*print)(TKey)) const;

    virtual void printLevelOrder(void (*print)(TKey)) const;

private:
    BinNode<TKey> *_root;

    BinNode<TKey> *searchParent(TKey key) const; //searches a parent node for a node with key(for remove)
protected:
    void printInOrder(void (*print)(TKey), BinNode<TKey> *root) const;

    void printPreOrder(void (*print)(TKey), BinNode<TKey> *root) const;

    void printPostOrder(void (*print)(TKey), BinNode<TKey> *root) const;

    void printLevelOrder(void (*print)(TKey), BinNode<TKey> *root) const;
};

#include "BinTree.inc"


template<typename TKey, typename Cmp=std::less<TKey>>
class BSTree : public BinTree<TKey, Cmp> {
public:
    BSTree() : BinTree<TKey, Cmp>() {};

    BSTree(TKey key) : BinTree<TKey, Cmp>(key) {};

    ~BSTree();

    bool insert(TKey key, Cmp cmp = Cmp());    //insert node using comparator

    BinNode<TKey> *search(TKey key, Cmp cmp = Cmp()) const;

    bool deleteNode(TKey key, Cmp cmp = Cmp());      //delete node by key if it has one or zero sons

    bool deleteSubtree(TKey key, Cmp cmp = Cmp());   //delete subtree with root with given key

    void printInOrder(void (*print)(TKey)) const;

    void printPreOrder(void (*print)(TKey)) const;

    void printPostOrder(void (*print)(TKey)) const;

    void printLevelOrder(void (*print)(TKey)) const;

private:
    BinNode<TKey> *_root;

    BinNode<TKey> *
    searchParent(TKey key, Cmp cmp = Cmp()) const; //searches a parent node for a node with key(for remove)
    bool deleteLeftNode(BinNode<TKey> *parent);

    bool deleteRightNode(BinNode<TKey> *parent);

};

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

#include "BSTree.inc"

#endif //LAB1_1_TREE_H