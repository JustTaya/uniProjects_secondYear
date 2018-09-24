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

//TODO:class to print nodes
/*
class Print
{
   std::ostream operator<<(std::ostream& os, const TKey key);
   std::ostream operator<<(std::ostream& os, const TKey data);
   };
*/

//abstract class for tree node
template <typename TKey,typename TData>
class TNode
{
public:
    TNode():key(0),data(0){};
    explicit TNode(TKey key,TData data):key(key),data(data){};
protected:
    TKey key;
    TData data;

    //methods to return data of tree node
    TKey returnKey();
    TData returnData();
   };

template<typename TKey, typename TData>
inline TKey TNode<TKey, TData>::returnKey() {
    return this->key;
}

template<typename TKey, typename TData>
inline TData TNode<TKey, TData>::returnData() {
    return this->data;
}

//abstract class for tree
template <typename TKey, typename TData, typename Cmp=std::less<TKey>>
class Tree
{
public:

    virtual bool insert(TKey,TData)=0;
    virtual bool remove(TKey)=0;
    virtual TNode<TKey,TData> search(TKey)=0;

    //methods to print tree
    virtual void printInOrder() const =0;
    virtual void printPreOrder() const =0;
    virtual void printPostOrder() const =0;
    virtual void printLevelOrder() const =0;
};

//TODO:class for tree with nodes with arbitrary number of sons
/*
template <typename TKey,typename TData>
class MultiTNode:public TNode<TKey,TData>
{
public:
    std::list<TNode<TKey,TData>*> nodes;
};


template <typename TKey, typename TData, typename Cmp=std::less<TKey>>
class MultiTree:public Tree<TKey,TData,Cmp>
{
public:
    MultiTree():_root(nullptr){};
    explicit MultiTree(TKey key, TData data):_root(MultiTNode(key,data)){};
private:
    MultiTNode<TKey,TData>* _root;
};
*/

//class for binary tree
template <typename TKey,typename TData>
class BinTNode:public TNode<TKey,TData>
{
public:
    explicit BinTNode():TNode<TKey,TData>(),left(nullptr),right(nullptr){};
    explicit BinTNode(TKey key,TData data):
        TNode<TKey,TData>(key,data),left(nullptr),right(nullptr){};
    BinTNode<TKey,TData> *left;
    BinTNode<TKey,TData> *right;
};


template <typename TKey, typename TData, typename Cmp=std::less<TKey>>
class BinTree:public Tree<TKey,TData>
{
public:
    explicit BinTree():_root(nullptr){};
    explicit BinTree(TKey key, TData data):_root(BinTNode(key,data)){};

    virtual void insert(TKey key,TData data) override;
    virtual bool remove(TKey)=0;
    virtual TNode<TKey,TData> search(TKey)=0;

    //methods to print tree
    virtual void printInOrder() const =0;
    virtual void printPreOrder() const =0;
    virtual void printPostOrder() const =0;
    virtual void printLevelOrder() const =0;

private:
    BinTNode<TKey,TData>* _root;
};

template<typename TKey, typename TData, typename Cmp>
void BinTree<TKey, TData, Cmp>::insert(TKey key, TData data) {
    if(this->_root== nullptr) {
        this->_root = new BinTNode<TKey,TData>(key,data);
        return;
    }

    BinTNode<TKey,TData>* tmp=this->_root;
    char buff=' ';
    while(tmp!=nullptr) {
        std::cout << "Current node key is: ";
        //std::cout<<this->key;
        std::cout << "Chose L for left/R for right node.\n";
        std::cin >> buff;
        switch(buff)
        {
            case 'L':
                if(tmp->left==nullptr)
                {
                    std::cout<<"Press Y to insert node here.\n"
                    std::cin>>buff;
                    if(buff=='Y')
                        tmp->left=new BinTNode<TKey,TData>(key,data);
                    return;
                }
                else
                    tmp=tmp->left;
                    break;
            case 'R':
                if(tmp->right==nullptr)
                {
                    std::cout<<"Press Y to insert node here.\n"
                    std::cin>>buff;
                    if(buff=='Y')
                        tmp->right=new BinTNode<TKey,TData>(key,data);
                    return;
                }
                else
                    tmp=tmp->right;
                break;
            default:
                std::cout<<"Input is not correct. Try one more time.";
                break;
        }
        break;
    }
}

