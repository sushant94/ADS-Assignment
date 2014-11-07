// Only store positive values.
// -1 is -INF.
#define -INF -1
class binomialTree
{
    // Each binomial tree node has 3 pointers:
    // (Parent, Left Child, Right sibling)
    binomialTree *parent;
    binomialTree *left;
    binomialTree *right;

    int32_t value;
    int32_t index;

    friend class binomialHeap;

    public:
    
    binomialTree() {
        parent = NULL;
        left = NULL;
        right = NULL;
        value = -INF;
        index = 0;
    }

    binomialTree(int32_t key) {
        parent = NULL;
        left = NULL;
        right = NULL;
        value = key;
        index = 0;
    }
};

// binomialHeap is basically a linked list with heads of binomial trees.
class binomialHeap
{
    // Head points to the smallest binomial tree part of this binomial heap.
    // For the roots, we have height of root = index of the binomial tree in the heap.
    binomialTree *head;

    // Members is a bit-string to store the members of binomial heap.
    // i.e. Which binary trees are a part of this binomial heap.
    int32_t members;

    public:

    binomialHeap() {
        members = 0;
        head = NULL;
    }

    int32_t power2(int32_t i) {
        return (1 << i);
    }

    // Returns if the heap has a tree with index 'i'.
    bool hasIndexi(int32_t i) {
        return (members & power2(i));
    }

    // Union 2 binomial heaps.
    void union(binomialHeap *other);

    int32_t extractMin();
    int32_t decreaseKey();

    void insertKey(int32_t key);
    void deleteKey(int32_t key);

    // Finds a key in a binomial heap.
    // Node is returned in the node argument. Must be set to null before passing into the function.
    void findKey(int32_t key, binomialTree *node);
};
