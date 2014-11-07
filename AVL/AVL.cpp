#include "AVL.h"

Node *
Node::findN(int key)
{
    if (key == value)
        return this;

    if (key < value && leftChild)
        return leftChild->findN(key);
    
    if (key > value && rightChild)
        return rightChild->findN(key);

    return this;
}

void
Node::insertN(int key)
{
    if (value == key)
        return;

    Node *child;

    if (key > value) {
        if (rightChild) {
            rightChild->insertN(key);
            maintain();
            return;
        }

        child = new Node;
        child->value = key;
        rightChild = child;
        child->parent = this;
    } else {
        if (leftChild) {
            leftChild->insertN(key);
            maintain();
            return;
        }
        child = new Node;
        child->value = key;
        leftChild = child;
        child->parent = this;
    }
}

void
Node::deleteN(int key)
{
    if (key > value && !rightChild)
        return;

    if (key < value && !leftChild)
        return;

 

    if (key > value)
        rightChild->deleteN(key);
    else if (key < value)
        leftChild->deleteN(key);
    else if (key == value) {
        if (rightChild) {
            value = rightChild->value;
            rightChild->deleteN(rightChild->value);
        }
        else if (leftChild) {
            value = leftChild->value;
            leftChild->deleteN(leftChild->value);
        } else {

            if (!parent) {
                std::cout<<"Cannot delete root without any other node.\n";
                return;
            }
            
            if (parent->leftChild == this)
                parent->leftChild = NULL;
            else if(parent)
                parent->rightChild = NULL;

            parent = NULL;
            delete(this);
            return;
        }
    }
    maintain();
}

void
Node::walkSubTree()
{
    if (leftChild)
        leftChild->walkSubTree();
    
    std::cout<<value;
    if (parent == NULL)
        std::cout<<"*";

    std::cout<<" ";

    if (rightChild)
        rightChild->walkSubTree();
}


void
Node::maintain()
{
    // If leaf, we don't have to do anything.
    if (!rightChild && !leftChild)
        return;

    int rightHeight,leftHeight;
    rightHeight = leftHeight = 0;
    
    if (rightChild)
        rightHeight = rightChild->height;
    if (leftChild)
        leftHeight = leftChild->height;

    height = (rightHeight > leftHeight ? rightHeight:leftHeight) + 1;

    balanceFactor  = leftHeight - rightHeight;
    
    // The height of right and left subtrees can differ maximum by 1.
    if (balanceFactor > 1) {
        // Left-Right Case.
        if (leftChild->balanceFactor == -1)
            leftChild->rotateLeft();
        // Left-Left Case.
        rotateRight();
    } 
    else if (balanceFactor < -1) {
        // Right-Left Case.
        if (rightChild->balanceFactor == 1)
            rightChild->rotateRight();
        // Right-Right Case.
        rotateLeft();
    }
    return;
}

void
Node::rotateRight()
{
    Node *temp = leftChild;
    leftChild = leftChild->rightChild;
    temp->rightChild = this;
    temp->parent = NULL;
    parent = temp;
}

void
Node::rotateLeft()
{
    Node *temp = rightChild;
    rightChild = rightChild->leftChild;
    temp->leftChild = this;
    temp->parent = NULL;
    parent = temp;
}
