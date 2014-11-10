#include <cstddef>
// -1 is INF_
#define INF_ -1

class Node
{
    public:
        int value;
        Node *parent;

        Node()
        {
            value = 0;
            parent = NULL;
        }

        // Overload of all needed operators.
        // Compatible to make it templates later.
        bool operator>(const Node &other)
        {
            return value > other.value;
        }

        void operator=(const int &other)
        {
            value = other;
        }

        void operator=(const Node &other)
        {
            value = other.value;
            parent = other.parent;
        }

        bool operator==(const Node &other)
        {
            return value == other.value;
        }

        bool operator==(const int &other)
        {
            return value == other;
        }

        bool operator>(const int &other)
        {
            return value > other;
        }

        bool operator<(const int &other)
        {
            return value < other;
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

    Node value;
    int index;

    friend class BinomialHeap;


    
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

    void findNode(int key, BinomialTree **node);
    void maintainHeap();
    void traverse();
    void mergeTrees(BinomialTree *other);
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
    void decreaseKey(int key, int newKey);

    void insertKey(int key);
    void deleteKey(int key);

    // Finds a key in a Binomial heap.
    // Node is returned in the node argument. Must be set to null before passing into the function.
    void findKey(int key, BinomialTree **node);

    void traverse();
    void reverse();
};
