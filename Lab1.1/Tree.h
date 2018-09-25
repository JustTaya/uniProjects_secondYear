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
template<typename TKey, typename TData>
class TNode {
public:
    TNode() : key(0), data(0) {};

    explicit TNode(TKey key, TData data) : key(key), data(data) {};

    //methods to return data of tree node
    TKey getKey() const;

    TData getData() const;

protected:
    TKey key;
    TData data;
};

template<typename TKey, typename TData>
inline TKey TNode<TKey, TData>::getKey() const {
    return this->key;
}

template<typename TKey, typename TData>
inline TData TNode<TKey, TData>::getData() const {
    return this->data;
}

//abstract class for tree
template<typename TKey, typename TData>
class Tree {
public:
    virtual void insert(TKey, TData) = 0;

    virtual bool deleteNode(TKey) = 0;

    virtual bool deleteSubtree(TKey) = 0;
    //virtual TNode<TKey,TData> search(TKey)=0;

    //methods to print tree
    virtual void printInOrder() const = 0;

    virtual void printPreOrder() const = 0;

    virtual void printPostOrder() const = 0;

    virtual void printLevelOrder() const = 0;
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
template<typename TKey, typename TData>
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

template<typename TKey, typename TData>
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

template<typename TKey, typename TData>
void BinTree<TKey, TData>::insert(TKey key, TData data) {
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

template<typename TKey, typename TData>
bool BinTree<TKey, TData>::deleteNode(TKey key) {
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


template<typename TKey, typename TData>
BinTNode<TKey, TData> *BinTree<TKey, TData>::findParentOf(TKey key) const {
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

template<typename TKey, typename TData>
bool BinTree<TKey, TData>::deleteSubtree(TKey key) {
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

template<typename TKey, typename TData>
void BinTree<TKey, TData>::printInOrder() const {
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
template<typename TKey, typename TData>
BinTree<TKey, TData>::~BinTree() {
    deleteSubtree(this->_root->getKey());
}

template<typename TKey, typename TData>
void BinTree<TKey, TData>::printPreOrder() const {
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

template<typename TKey, typename TData>
void BinTree<TKey, TData>::printPostOrder() const {
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

template<class TKey, class TData>
struct Level {
    int level = 0;
    BinTNode<TKey, TData> *node = nullptr;
};

template<typename TKey, typename TData>
void BinTree<TKey, TData>::printLevelOrder() const {
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

template<typename TKey, typename TData>
BinTNode<TKey, TData> *BinTree<TKey, TData>::search(TKey key) const {
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
template<typename TKey, typename TData>
class BSTree : public BinTree<TKey, TData> {
public:
    explicit BSTree() : _root(nullptr) {};

    explicit BSTree(TKey key, TData data) : _root(BinTNode(key, data)) {};

    virtual void insert(TKey key, TData data);

    virtual bool deleteNode(TKey);
    //virtual bool deleteSubtree(TKey);
    //virtual TNode<TKey,TData> search(TKey key) const;
private:
    BinTNode<TKey, TData> *_root;

    BinTNode<TKey, TData> *findLeftLeaf();
    void replaceNode(BinTNode<TKey,TData>* parent, BinTNode<TKey,TData>* node);
};

template<typename TKey, typename TData>
void BSTree<TKey, TData>::insert(TKey key, TData data) {
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

template<typename TKey, typename TData>
bool BSTree<TKey, TData>::deleteNode(TKey key) {
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

template<typename TKey, typename TData>
BinTNode<TKey, TData> *BSTree<TKey, TData>::findLeftLeaf() {
    if (this->_root == nullptr)
        return nullptr;
    BinTNode<TKey, TData> *node = this->_root;
    while (node->left != nullptr)
        node = node->left;
    return node;
}

/*
template<typename TKey, typename TData>
void BSTree<TKey, TData>::replaceNode(BinTNode<TKey, TData> *parent, BinTNode<TKey, TData> *node) {
    if (node->left == nullptr && node->right == nullptr) {
        if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete node;
    } else if (node->left = nullptr) {
        if (parent->left == node)
            parent->left = node->right;
        else
            parent->right = node->right;
        delete node;
    } else if (node->right = nullptr) {
        if (parent->left == node)
            parent->left = node->left;
        else
            parent->right = node->left;
        delete node;
    } else {
        if(node->right->left==nullptr)
        {
            if (parent->left == node)
                parent->left = node->right;
            else
                parent->right = node->right;
            delete node;
        }
        else
        {
            BinTNode<TKey,TData>* tmp=findLeftLeaf();
            tmp->left=node->left;
            tmp->right=node->right;

        }
    }
}
*/