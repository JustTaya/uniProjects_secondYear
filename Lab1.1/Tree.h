//
// Created by taya on 9/23/18.
//

#ifndef LAB1_1_TREE_H
#define LAB1_1_TREE_H

#endif //LAB1_1_TREE_H

#include <iostream>
#include <functional>


//abstract class for tree node
template <typename TKey,typename TData>
class TNode
{
protected:
    TNode():key(0),data(0){};
    explicit TNode(TKey key,TData data):key(key),data(data){};
    TKey key;
    TData data;
   };

//abstract class for tree
template <typename TKey, typename TData, typename Cmp=std::less<TKey>>
class Tree
{
public:

    virtual void insert(TKey,TData)=0;
    virtual void remove(TKey)=0;

    virtual void printInOrder() const =0;
    virtual void printPreOrder() const =0;
    virtual void printPostOrder() const =0;
    virtual void printLevelOrder() const =0;

    virtual void merge(Tree&)=0;
protected:
    Tree():_root(nullptr){};
    explicit Tree(TKey key,TData data):_root(TNode(key,data)){};
    virtual ~Tree();
    TNode<TKey,TData>* _root;
};

