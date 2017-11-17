#ifndef BINARYTREETYPE_H
#define BINARYTREETYPE_H

#include "header.h"

using namespace std;

struct nodeType {
    int info;
    nodeType *lLink;
    nodeType *rLink;
    nodeType *parent;
};

class binaryTreeType {
public:
    const binaryTreeType& operator=(const binaryTreeType&);
    bool isEmpty() const;
    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    void breadthfirstTraversal(bool) const;
    int treeHeight() const;
    void destroyTree();
    virtual bool search(const int& searchItem) const = 0;
    virtual void insert(const int& insertItem) = 0;
    virtual void deleteNode(const int& deleteItem) = 0;
    binaryTreeType(const binaryTreeType& otherTree);
    binaryTreeType();
    ~binaryTreeType();
protected:
    nodeType *root;
private:
    void copyTree(nodeType* &copiedTreeRoot, nodeType* otherTreeRoot);
    void destroy(nodeType* &p);
    void inorder(nodeType *p) const;
    void preorder(nodeType *p) const;
    void postorder(nodeType *p) const;
    int height(nodeType *p) const;
    int max(int x, int y) const;
};

bool binaryTreeType::isEmpty() const
{
    return (root == nullptr);
}

binaryTreeType::binaryTreeType()
{
    root = nullptr;
}

void binaryTreeType::inorderTraversal() const
{
    inorder(root);
}

void binaryTreeType::preorderTraversal() const
{
    preorder(root);
}

void binaryTreeType::postorderTraversal() const
{
    postorder(root);
}

void binaryTreeType::breadthfirstTraversal(bool rel) const
{
    if (!root)
        return;

    std::queue<nodeType*> q;
    q.push(root);

    while (!q.empty()) {
        /* print front */
        nodeType* node = q.front();
        q.pop();

        if (rel) {
            std::cout << node->info << std::endl;

            /* print possible parents */
            if (node->parent != nullptr) {
                std::cout << "Parent: " << node->parent->info << std::endl;
            } else {
                std::cout << "Root node" << std::endl;
            }
        } else {
            if (node->parent != nullptr)
                std::cout << " ";
            std::cout << node->info;
        }

        /* print and push possible left children */
        if (node->lLink != nullptr) {
            if (rel)
                std::cout << "Left child: " << node->lLink->info << std::endl;
            q.push(node->lLink);
        } else if (rel) {
            std::cout << "No left child" << std::endl;
        }

        /* print and push possible right children */
        if (node->rLink != nullptr) {
            if (rel)
                std::cout << "Right child: " << node->rLink->info << std::endl;
            q.push(node->rLink);
        } else if (rel) {
            std::cout << "No right child" << std::endl;
        }
    }
}

int binaryTreeType::treeHeight() const
{
    return height(root);
}

void binaryTreeType::destroyTree()
{
    destroy(root);
}

void binaryTreeType::copyTree(nodeType* &copiedTreeRoot, nodeType* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
        copiedTreeRoot = nullptr;
    else {
        copiedTreeRoot = new nodeType;
        copiedTreeRoot->info = otherTreeRoot->info;
        copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
        copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
    }
}

void binaryTreeType::destroy(nodeType* &p)
{
    if (p != nullptr) {
        destroy(p->lLink);
        destroy(p->rLink);
        delete p;
        p = nullptr;
    }
}

void binaryTreeType::inorder(nodeType *p) const
{
    if (p != nullptr)
    {
        inorder(p->lLink);
        cout << p->info << " ";
        inorder(p->rLink);
    }
}

void binaryTreeType::preorder(nodeType *p) const
{
    if (p != nullptr)
    {
        cout << p->info << " ";
        preorder(p->lLink);
        preorder(p->rLink);
    }
}

void binaryTreeType::postorder(nodeType *p) const
{
    if (p != nullptr)
    {
        postorder(p->lLink);
        postorder(p->rLink);
        cout << p->info << " ";
    }
}

int binaryTreeType::height(nodeType *p) const
{
    if (p == nullptr)
        return 0;
    else
        return 1 + max(height(p->lLink), height(p->rLink));
}

int binaryTreeType::max(int x, int y) const
{
    if (x >= y)
        return x;
    else
        return y;
}

binaryTreeType::~binaryTreeType()
{
    destroy(root);
}

#endif // BINARYTREETYPE_H
