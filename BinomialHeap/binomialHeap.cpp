#include "binomialHeap.h"
#include <iostream>

void 
BinomialTree::findNode(int n, BinomialTree **node)
{
    if (val.n == n)
        *node = (this);
    /* 
     * If val.n > n, don't check children.
     * If no child, can't search.
     * If already found, don't continue.
     */
    if (val.n < n && this->left && *node == NULL)
        this->left->findNode(n, node);
    if (this->right && *node == NULL)
        this->right->findNode(n, node);
}

void
BinomialTree::maintainHeap()
{
    // Base case - we're at root.
    if (parent == NULL)
        return;
    // As long as we can bubble up, we do so.
    if (parent->val.value > val.value) {
        Node tmp = val;
        val = parent->val;
        parent->val = tmp;
        parent->maintainHeap();
    }
}

// Merge 2 Binomial Trees.
void
BinomialTree::mergeTrees(BinomialTree *other)
{
    if (index != other->index)
        return;

    BinomialTree *smaller = this;
    BinomialTree *bigger = other;

    if (smaller->val.value > bigger->val.value) {
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
    std::cout<<"["<<val.value;
    if (parent == NULL)
        std::cout<<"r";
    else
        std::cout<<"("<<parent->val.value<<")";
    std::cout<<"<"<<index<<">";
    std::cout<<"]";
    // Left child.
    if (left)
        left->traverse();
    // Right sibling.
    if (right)
        right->traverse();
}

void
BinomialTree::decreaseKey(int key)
{
    if (key > this->val.value)
        return;

    val.value = key;

    maintainHeap();
}

void
BinomialHeap::unionHeap(BinomialHeap *other)
{
    BinomialTree *i = head;
    BinomialTree *j = other->head;

    BinomialTree *nnexti;
    BinomialTree *nexti;
    BinomialTree *nextj;

    if (head == NULL) {
        head = j;
        return;
    }

    // We always have to maintain this condition:
    // i->index < j->index.
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

            // Merging 2 Binomial trees will cause a carry.
            // Loop to merge the new tree with existing tree of same index if it exists.
            while (nexti && (i->index == nexti->index)) {
                nnexti = nexti->right;
                i->mergeTrees(nexti);
                
                if (i->parent)
                    i = i->parent;
                if (head->parent)
                    head = head->parent;

                nexti = nnexti;
            } 
            if (i->parent)
                i = i->parent;
            if (head->parent)
                head = head->parent;
            i->right = nexti;
        } else {
            // j->index can never be < i->index.
            if (i->right && j->index < i->right->index) {
                BinomialTree *nexti = i->right;
                BinomialTree *nextj = j->right;
                i->right = j;
                j->right = nexti;
                i = i->right;
                j = nextj;
                continue;
            } else if (i->right == NULL && j) {
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
    // STEPS:
    //  - Find  minimum among the roots.
    //  - Delete.
    //  - Union the two broken up heaps.
    if (!head)
        return -1;

    int min = head->val.value;
    int ret = 0;
    BinomialTree *d = head;
    BinomialTree *tmp = head;
    bool flag = true;

    while (tmp->right) {
        if (tmp->right->val.value < min)
            min = tmp->right->val.value, d = tmp, flag = false;
        tmp = tmp->right;
    }
    // d->right gives us the node to be deleted.
    // Note. d->left will have the heap in reverse order. We will have to reverse it before calling merge on it.
    BinomialTree *piece;
    if (flag) {
        head = d->left;
        piece = d->right;
        
        if (d->right)
            head = d->right, piece = d->left;

        d->right = NULL;
        d->left = NULL;
        ret = d->val.n;
        delete d;
        
        if (piece) {
            BinomialHeap h(piece);
            h.reverse();
            unionHeap(&h);
        } else {
            if (head)
                reverse();
        }
    } else {
        piece = d->right->left;
        d->right = d->right->right;
        d = piece->parent;
        d->left = NULL;
        d->right = NULL;
        ret = d->val.n;
        delete d;

        BinomialHeap h(piece);
        h.reverse();
        unionHeap(&h);
    }

    return ret;
}

void
BinomialHeap::decreaseKey(int n, int newKey)
{
    // Find Node with the key.
    BinomialTree *node;
    findKey(n, &node);

    if (node->val.value < newKey)
        return;

    if (node == NULL)
        return;

    // Decrease and bubble up.
    node->val.value = newKey;
    node->maintainHeap();
}

void
BinomialHeap::insertKey(int key, int n)
{
    // Make heap with key.
    BinomialTree *t;
    t = new BinomialTree(key, n);
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
BinomialHeap::findKey(int n, BinomialTree **node)
{
    // Find key in the heap.
    *node = NULL;
    if (head)
        head->findNode(n, node);
}

void
BinomialHeap::traverse()
{
    if (head)
        head->traverse();
    else
        std::cout<<"\nNULL\n";
}

void
BinomialHeap::reverse()
{
    BinomialTree *tmp2 = NULL;
    BinomialTree *tmp = head;
    BinomialTree *tmp1 = head->right;
    if (tmp1)
        tmp2 = tmp1->right;
    else {
        tmp->parent = NULL;
        tmp->index--;
        return;
    }
    tmp->right = NULL;
    while (tmp2) {
        tmp->parent = NULL;
        tmp->index--;
        tmp1->right = tmp;
        tmp = tmp1;
        tmp1 = tmp2;
        tmp2 = tmp2->right;
    }
    tmp1->right = tmp;
    tmp->parent = NULL;
    tmp->index--;
    tmp1->parent = NULL;
    tmp1->index--;
    head = tmp1;
}

