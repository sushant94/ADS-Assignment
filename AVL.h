#include<cstddef>

class Node
{
    
    Node *leftChild;
    Node *rightChild;
    Node *parent;
    int balanceFactor;

    // Functions to height balance the tree.
    void maintain();
    void rotateRight();
    void rotateLeft();
    
    public:
        int value;
        int height; // stores the height of the Node from the leaves.
        
        // Constructor
        Node(int value = 0)
        {
            leftChild = rightChild = parent  = NULL;
            height = 1;
            this->value = value;
            balanceFactor = 0;
        }

        // Find the key in Node's subtree.
        Node * findN(int key);
        // Insert the key in the Node's subtree and balance.
        void insertN(int key);
        // Delete key from the Node's subtree and balance.
        void deleteN(int key);
        // Inorder walk subtree of this node.
        void walkSubTree();
};
