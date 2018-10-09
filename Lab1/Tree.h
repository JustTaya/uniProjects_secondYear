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

    virtual ~TNode() {};

    virtual TKey getKey() const;

protected:
    TKey key;
};


template<typename TKey>
TKey TNode<TKey>::getKey() const {
    return key;
}


//abstract class for tree
template<typename TKey, typename Cmp=std::less<TKey>>
class Tree {
public:
    Tree(){};

    virtual ~Tree(){};

    explicit Tree(TKey key){};

    virtual bool insertRoot(TKey) = 0;

    virtual bool deleteNode(TKey) = 0;

    //methods to print tree
    virtual void printInOrder(void (*print)(TKey)) const = 0;

    virtual void printPreOrder(void (*print)(TKey)) const = 0;

    virtual void printPostOrder(void (*print)(TKey)) const = 0;

    virtual void printLevelOrder(void (*print)(TKey)) const = 0;

};

template<typename TKey>
class MultiNode : public TNode<TKey> {
public:
    explicit MultiNode(TKey key) : TNode<TKey>(key) {};
    ~MultiNode() {};

    void add(TKey key);

    std::list<MultiNode<TKey> *> nodes;

    TKey getKey() const {
        return TNode<TKey>::getKey();
    };
};

template<typename TKey>
void MultiNode<TKey>::add(TKey key) {
    MultiNode<TKey> *node = new MultiNode<TKey>(key);
    this->nodes.push_back(node);
}


template<typename TKey, typename Cmp=std::less<TKey>>
class MultiTree : public Tree<TKey, Cmp> {
public:
    MultiTree() : _root(nullptr) {};

    explicit MultiTree(TKey key) : _root(MultiNode<TKey>(key)) {};

    virtual ~MultiTree();

    bool insertRoot(TKey key);      //insert root if tree is empty

    MultiNode<TKey> *insert(MultiNode<TKey> *node, TKey key);     //insert node as son

    MultiNode<TKey> *getRoot();      //reference to root

    bool deleteNode(TKey key);      //delete node by key

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
    explicit BinNode(TKey key) :
            TNode<TKey>(key), left(nullptr), right(nullptr) {};
    ~BinNode(){};
    BinNode<TKey> *left;
    BinNode<TKey> *right;
    TKey getKey() const {
        return TNode<TKey>::getKey();
    };
};


template<typename TKey, typename Cmp=std::less<TKey>>
class BinTree : public Tree<TKey, Cmp> {
public:
    BinTree() : _root(nullptr) {};

    explicit BinTree(TKey key) : _root(BinNode<TKey>(key)) {};

    virtual ~BinTree();

    bool insertRoot(TKey key);      //insert root if tree is empty

    BinNode<TKey> *insertleft(BinNode<TKey> *node, TKey key);     //insert node as left son

    BinNode<TKey> *insertright(BinNode<TKey> *node, TKey key);     //insert node as left son


    BinNode<TKey> *getRoot();      //reference to root

    virtual bool deleteNode(TKey key);      //delete node by key if it has one or zero sons

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

    explicit BSTree(TKey key) : BinTree<TKey, Cmp>(key) {};

    ~BSTree(){};

    bool insertRoot(TKey key){this->_root=new BinNode<TKey>(key);}

    bool insertNode(TKey key, Cmp cmp = Cmp());    //insert node using comparator

    BinNode<TKey> *search(TKey key, Cmp cmp = Cmp()) const;

    bool deleteNode(TKey key);      //delete node by key if it has one or zero sons

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

    bool del(TKey key, Cmp cmp = Cmp());      //delete node by key if it has one or zero sons
};


#include "BSTree.inc"



#endif //LAB1_1_TREE_H