#include <cstddef>

// For convienence we assume -INF to be -1
// and INF to be 1000
#define INF_ -1
#define INF 1000

class Node
{
    public:
        // Value stores the 'key' using which the priority Queue is dequeued.
        // n is the index of the node.
        int value, n;

        // Constructors.
        Node()
        {
            value = INF;
            n = -1;
        }
        Node(int n)
        {
            value = INF;
            this->n = n;
        }
};

class BinomialTree
{
    friend class BinomialHeap;

    public:
        // Each Binomial tree node has 3 pointers:
        // (Parent, Left Child, Right sibling)
        BinomialTree *parent;
        BinomialTree *left;
        BinomialTree *right;
        Node val;
        int index;

        // Constructors.
        BinomialTree()
        {
            parent = NULL;
            left = NULL;
            right = NULL;
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

// BinomialHeap is made of BinomialTrees.
class BinomialHeap
{
    // Head points to the smallest Binomial tree part of this Binomial heap.
    BinomialTree *head;

    void unionHeap(BinomialHeap *other);
    void reverse();    

    public:
      // Constructors.
      BinomialHeap()
      {
          head = NULL;
      }
      BinomialHeap(BinomialTree *t)
      {
          head = t;
      }

      bool isEmpty()
      {
          return !(head == NULL);
      }

      // extractMin returns the index of the node.
      // Although, to be correct we should return the whole node
      // But as we need only the index, This should be sufficient.
      int extractMin();
      void decreaseKey(int n, int newKey);
      void insertKey(int key, int n);
      void deleteKey(int key);

      // Finds a node with index 'n' in a Binomial heap.
      // Node must be set to null before passing into the function.
      void findKey(int n, BinomialTree **node);
      void traverse();
};

