#include <cstddef>
// -1 is INF_
#define INF_ -1

class BinomialTree
{
    // Each Binomial tree node has 3 pointers:
    // (Parent, Left Child, Right sibling)
    BinomialTree *parent;
    BinomialTree *left;
    BinomialTree *right;

    int value;
    int index;

    friend class BinomialHeap;

    public:
    
    BinomialTree()
    {
        parent = NULL;
        left = NULL;
        right = NULL;
        value = INF_;
        index = 0;
    }

    BinomialTree(int key) 
    {
        parent = NULL;
        left = NULL;
        right = NULL;
        value = key;
        index = 0;
    }

    int getValue() 
    {
        return value;
    }

    void findNode(int key, BinomialTree **node);
    void maintainHeap();
    void traverse();
};

// BinomialHeap is basically a linked list with heads of Binomial trees.
class BinomialHeap
{
    // Head points to the smallest Binomial tree part of this Binomial heap.
    // For the roots, we have height of root = index of the Binomial tree in the heap.
    BinomialTree *head;

    // Members is a bit-string to store the members of Binomial heap.
    // i.e. Which binary trees are a part of this Binomial heap.
    int members;

    public:

    BinomialHeap() {
        members = 0;
        head = NULL;
    }

    BinomialHeap(BinomialTree *t) {
        head = t;
        // Need to fix this.
        members = 0;
    }

    int power2(int i) {
        return (1 << i);
    }

    // Returns if the heap has a tree with index 'i'.
    bool hasIndexi(int i) {
        return (members & power2(i));
    }

    // Union 2 Binomial heaps.
    void unionHeap(BinomialHeap *other);

    int extractMin();
    void decreaseKey(int key, int newKey);

    void insertKey(int key);
    void deleteKey(int key);

    // Finds a key in a Binomial heap.
    // Node is returned in the node argument. Must be set to null before passing into the function.
    void findKey(int key, BinomialTree **node);

    void traverse();
};
