#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "binarytreetype.h"

class bSearchTreeType: public binaryTreeType {
public:
    bool search(const int& searchItem) const;
    void insert(const int& insertItem);
    void deleteNode(const int& deleteItem);
private:
    void deleteFromTree(nodeType* &p);
};

bool bSearchTreeType::search(const int& searchItem) const
{
    nodeType *current;
    bool found = false;

    if (root == nullptr)
        cout << "Cannot search an empty tree." << endl;
    else {
        current = root;

        while (current != nullptr && !found) {
            if (current->info == searchItem)
                found = true;
            else if (current->info > searchItem)
                current = current->lLink;
            else
                current = current->rLink;
        }
    }

    return found;
}

void bSearchTreeType::insert(const int& insertItem)
{
    nodeType *current; //pointer to traverse the tree
    nodeType *trailCurrent; //pointer behind current
    nodeType *newNode; //pointer to create the node

    newNode = new nodeType;
    newNode->info = insertItem;
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;

    if (root == nullptr) {
        root = newNode;
        root->parent = nullptr;
    } else {
        current = root;
        while (current != nullptr) {
            trailCurrent = current;

            if (current->info > insertItem)
                current = current->lLink;
            else
                current = current->rLink;
        }
        if (trailCurrent->info > insertItem) {
            trailCurrent->lLink = newNode;
            trailCurrent->lLink->parent = trailCurrent;
        } else {
            trailCurrent->rLink = newNode;
            trailCurrent->rLink->parent = trailCurrent;
        }
    }
}

void bSearchTreeType::deleteNode(const int& deleteItem)
{
    nodeType *current; //pointer to traverse the tree
    nodeType *trailCurrent; //pointer behind current
    bool found = false;
    if (root == nullptr)
        cout << "Cannot delete from an empty tree."
             << endl;
    else
    {
        current = root;
        trailCurrent = root;
        while (current != nullptr && !found)
        {
            if (current->info == deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                if (current->info > deleteItem)
                    current = current->lLink;
                else
                    current = current->rLink;
            }
        }//end while
        if (current == nullptr)
            cout << "The item to be deleted is not in the tree."
                 << endl;
        else if (found)
        {
            if (current == root)
                deleteFromTree(root);
            else if (trailCurrent->info > deleteItem)
                deleteFromTree(trailCurrent->lLink);
            else
                deleteFromTree(trailCurrent->rLink);
        }
        else
            cout << "The item to be deleted is not in the tree."
                 << endl;
    }
}

void bSearchTreeType::deleteFromTree(nodeType* &p)
{
    nodeType *current;
    nodeType *trailCurrent;
    nodeType *temp;

    if (p == nullptr)
        cout << "Error: The node to be deleted does not exist."
             << endl;
    else if (p->lLink == nullptr && p->rLink == nullptr) {
        temp = p;
        p = nullptr;
        delete temp;
    } else if (p->lLink == nullptr) {
        temp = p;
        p = temp->rLink;
        delete temp;
    } else if (p->rLink == nullptr) {
        temp = p;
        p = temp->lLink;
        delete temp;
    } else {
        current = p->lLink;
        trailCurrent = nullptr;

        while (current->rLink != nullptr) {
            trailCurrent = current;
            current = current->rLink;
        }

        p->info = current->info;

        if (trailCurrent == nullptr) //current did not move;
            //current == p->lLink; adjust p
            p->lLink = current->lLink;
        else
            trailCurrent->rLink = current->lLink;
        delete current;
    }
}

#endif // BINARYSEARCHTREE_H
