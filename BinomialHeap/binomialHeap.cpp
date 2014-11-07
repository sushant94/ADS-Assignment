#include "binomialHeap.h"
#include <iostream>

void 
BinomialTree::findNode(int key, BinomialTree **node)
{
    if (value == key)
        *node = (this);

    /* 
     * If value > key, don't check children.
     * If no child, can't search.
     * If already found, don't continue.
     */
    if (value < key && this->left && *node == NULL)
        this->left->findNode(key, node);
    if (this->parent && this->right && *node == NULL)
        this->right->findNode(key, node);
}

void
BinomialTree::maintainHeap()
{
    // Base case - we're at root.
    if (parent == NULL)
        return;

    // As long as we can bubble up, we do so.
    if (parent->value > value) {
        int tmp = value;
        value = parent->value;
        parent->value = tmp;
        parent->maintainHeap();
    }
}

void
BinomialTree::traverse()
{
    std::cout<<"\n";
    std::cout<<"["<<value;
    if (parent == NULL)
        std::cout<<"r";
    else
        std::cout<<"("<<parent->value<<")";
    std::cout<<"]";
    // Left child.
    if (left)
        left->traverse();
    // Right sibling.
    if (right)
        right->traverse();
}

void
BinomialHeap::unionHeap(BinomialHeap *other)
{
    // Base case. Insertion of first node.
    if (head == NULL) {
        head = other->head;
        return;
    }

    BinomialTree *tmp = head;
    BinomialTree *otherTmp = other->head;
    std::cout<<"\n"<<"="<<head->index<<" "<<other->head->index<<"\n";
    while (tmp && otherTmp) {
        BinomialTree *smaller, *bigger;
        // Do they have same Binomial tree index?
        if (tmp->index == otherTmp->index) {
            // Merge
            // Two trees of index i merge to give a tree of index i+1.
            tmp->index = otherTmp->index = tmp->index + 1;
            if (tmp->value > otherTmp->value)
                smaller = otherTmp, bigger = tmp;
            else
                smaller = tmp, bigger = otherTmp;

            bigger->parent = smaller;
            BinomialTree *next = bigger->right;
            bigger->right = smaller->left;
            smaller->left = bigger;
            if (next == NULL)
                next = smaller->right;
            tmp = next;
            otherTmp = smaller;
        } else {
            bigger = otherTmp, smaller = tmp;
            if (tmp->index > otherTmp->index)
                bigger = tmp, smaller = otherTmp;

            BinomialTree *next = smaller->right;
            smaller->right = bigger;
            tmp = next;
            otherTmp = bigger; // smaller->right
            if (smaller->index == 0)
                head = smaller;
        }
    }

    // We may end up with trees of same degree after merge. We need to fix this.
}

int
BinomialHeap::extractMin()
{
    // Find  minimum among the roots.
    // Delete.
    // Union the two broken up heaps.
    int min = INF_;
    BinomialTree *t = head;
    BinomialTree *d = NULL;

    while (t->right) {
        if (t->right->value < min)
            min = t->right->value, d = t;
        t = t->right;
    }

    // We now have the pointer to the node in root list which is a 
    // sibling of the node we want to delete.
    // i.e. d->right = Node we need to extract/min node.
    BinomialTree *piece = d->right->left;
    d->right = d->right->right;

    d = piece->parent;
    d->left = NULL;
    d->right = NULL;
    delete d;

    BinomialTree *tmp = piece;
    int i = 1;
    while (tmp) {
        tmp->parent = NULL;
        tmp->index = tmp->index - i;
        i++;
        tmp = tmp->right;
    }

    BinomialHeap *other;
    other = new BinomialHeap(piece);

    unionHeap(other);

    delete other;
}

void
BinomialHeap::decreaseKey(int key, int newKey)
{
    if (key < newKey)
        return;

    // Find Node with the key.
    BinomialTree *node;
    findKey(key, &node);

    if (node == NULL)
        return;

    // Decrease and bubble up.
    node->value = newKey;
    node->maintainHeap();
}

void
BinomialHeap::insertKey(int key)
{
    // Make heap with key.
    BinomialTree *t;
    t = new BinomialTree(key);
    BinomialHeap *h;
    h = new BinomialHeap(t);
    // Union the two heaps.
    unionHeap(h);
    std::cout<<"--"<<head->right<<"--";
}

void
BinomialHeap::deleteKey(int key)
{
    // Decrease key to INF_.
    decreaseKey(key, INF_);
    // Delete Min.
    extractMin();
}

void
BinomialHeap::findKey(int key, BinomialTree **node)
{
    // Find key in the heap.
    *node = NULL;
    head->findNode(key, node);
}

void
BinomialHeap::traverse()
{
    head->traverse();
}
