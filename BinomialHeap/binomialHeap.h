#include <cstddef>
// -1 is INF_
#define INF_ -1

class Node
{
    public:
        int value;
        int parent;
        int n;

        Node()
        {
            value = 1000;
            parent = -1;
            n = -1;
        }

        Node(int n)
        {
            value = 1000;
            parent = -1;
            this->n = n;
        }
};

class BinomialTree
{
    // Each Binomial tree node has 3 pointers:
    // (Parent, Left Child, Right sibling)
    public:
    BinomialTree *parent;
    BinomialTree *left;
    BinomialTree *right;

    Node val;

    int value;
    int index;

    friend class BinomialHeap;


    
    BinomialTree()
    {
        parent = NULL;
        left = NULL;
        right = NULL;
        index = 0;
    }

    BinomialTree(int key) 
    {
        parent = NULL;
        left = NULL;
        right = NULL;
        val.value = key;
        index = 0;
    }

    BinomialTree(int key, int n)
    {
        parent = NULL;
        left = NULL;
        right = NULL;
        val.value = key;
        val.n = n;
        index = 0;
    }

    void findNode(int n, BinomialTree **node);
    void maintainHeap();
    void traverse();
    void mergeTrees(BinomialTree *other);
    void decreaseKey(int key);
};

// BinomialHeap is basically a linked list with heads of Binomial trees.
class BinomialHeap
{
    // Head points to the smallest Binomial tree part of this Binomial heap.
    // For the roots, we have height of root = index of the Binomial tree in the heap.


    // Members is a bit-string to store the members of Binomial heap.
    // i.e. Which binary trees are a part of this Binomial heap.
    int members;

    public:

    BinomialTree *head;
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
    void decreaseKey(int n, int newKey);

    void insertKey(int key, int n);
    void deleteKey(int key);

    // Finds a key in a Binomial heap.
    // Node is returned in the node argument. Must be set to null before passing into the function.
    void findKey(int n, BinomialTree **node);

    void traverse();
    void reverse();
};
