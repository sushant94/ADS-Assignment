#include "binomialHeap.h"

void 
binomialTree::findNode(int32_t key, binomialTree *node)
{
    if (root == NULL)
        return;

    if (value == key)
        node = root;

    // If value > key, don't check children.
    // If no child, can't search.
    // If already found, don't continue.
    if (value < key && root->left && node == NULL)
        root->left->findNode(key, node);
    if (root->parent && root->right && node == NULL)
        root->right->findNode(key, node);
}

void
binomialHeap::unionHeap(binomialHeap *other)
{
    // Base case. Insertion of first node.
    if (head == NULL) {
        head = other->head;
        return;
    }

    binomialTree *tmp = head;
    binomialTree *otherTmp = other->head;
    while (tmp && otherTmp) {
        binomialTree *smaller, *bigger;
        // Do they have same binomial tree index?
        if (tmp->index == otherTmp->index) {
            // Merge
            // Two trees of index i merge to give a tree of index i+1.
            tmp->index = otherTmp->index = tmp->index + 1;
            if (tmp->value > otherTmp->value)
                smaller = otherTmp, bigger = tmp;
            else
                smaller = tmp, bigger = otherTmp;

            bigger->parent = smaller;
            binomialTree *next = bigger->right;
            bigger->right = smaller->left;
            smaller->left = bigger;
            tmp = next;
            otherTmp = smaller;
        } else {
            bigger = otherTmp->index, smaller = tmp->index;
            if (tmp->index > otherTmp->index)
                bigger = tmp->index, smaller = otherTmp->index;

            binomialTree *next = smaller->right;
            smaller->right = bigger;
            tmp = next;
            otherTmp = bigger; // smaller->right
        }
    }
}

int32_t
binomialHeap::extractMin()
{
    // Find  minimum among the roots.
    // Delete.
    // Union the two broken up heaps.
    int32_t min = -INF;
    binomialTree *t = head;
    binomialTree *d = NULL;

    while (t) {
        if (t->value < min)
            min = t->value, d = t;
        t = t->right;
    }

    free(d);


}

int32_t
binomialHeap::decreaseKey(int32_t key, int32_t newKey)
{
    // Find Node with the key.
    // Decrease and bubble up.
}

void
binomialHeap::insertKey(int32_t key)
{
    // Make heap with key.
    binomialTree t(key);
    // Union the two heaps.
    unionHeap(&t);
}

void
binomialHeap::deleteKey(int32_t key)
{
    // Decrease key to -INF.
    // Delete Min.
}

void
binomialHeap::findKey(int32_t key, binomialTree *node)
{
    // Find key in the heap.
    binomialTree *tmp = head;
    node = NULL;

    tmp->findNode(key, node);
}

