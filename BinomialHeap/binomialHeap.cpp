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

// Merge 2 BinomialTrees.
// Warning. The binomialTrees should have right = NULL,
// Else you will lose this data.
void
BinomialTree::mergeTrees(BinomialTree *other)
{
    if (index != other->index)
        return;

    BinomialTree *smaller = this;
    BinomialTree *bigger = other;

    if (smaller->value > bigger->value) {
        BinomialTree *tmp = smaller;
        smaller = bigger;
        bigger = tmp;
    }

    bigger->parent = smaller;
    smaller->right = NULL;
    bigger->right = NULL;
    bigger->right = smaller->left;
    smaller->left = bigger;
    smaller->index++;
    bigger->index++;
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
    // i is used to iterate over this->head.
    BinomialTree *i = head;
    // j is used to iterate over other->head.
    BinomialTree *j = other->head;

    BinomialTree *nnexti;
    BinomialTree *nexti;
    BinomialTree *nextj;

    if (head == NULL) {
        head = j;
        return;
    }

    if (i->index > j->index) {
        BinomialTree *tmp = i;
        i = j;
        j = tmp;
        head = i;
    }

    while (i && j) {
        if (i->index == j->index) {
            nexti = i->right;
            nextj = j->right;
            i->mergeTrees(j);
            j = nextj;
            while (nexti && (i->index == nexti->index)) {
                nnexti = nexti->right;
                i->mergeTrees(nexti);
                if (i->parent)
                    i = i->parent;
                nexti = nnexti;
            } 
            i->right = nexti;
        } else {
            // j->index can never be < i->index.
            // i.e. j->index >= i->index.
            if (i->right && j->index < i->right->index) {
                BinomialTree *nexti = i->right;
                BinomialTree *nextj = j->right;
                i->right = j;
                j->right = nexti;
                i = i->right;
                j = nextj;
                continue;
            }
            else if (i->right == NULL && j) {
                i->right = j;
                break;
            }
            i = i->right;
        }

    }

    while (head->parent != NULL)
        head = head->parent;
}

int
BinomialHeap::extractMin()
{
    // Find  minimum among the roots.
    // Delete.
    // Union the two broken up heaps.
    int min = head->value;
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

    tmp = piece->right;
    BinomialTree *tmp1 = tmp->right;
    piece->right = NULL;

    while (tmp1) {
        tmp->right = piece;
        piece = tmp;
        tmp = tmp1;
        tmp1 = tmp1->right;
    }

    tmp->right = piece;
    piece = tmp;

    BinomialHeap *other;
    other = new BinomialHeap(piece);

    unionHeap(other);

    delete other;

    return min;
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
