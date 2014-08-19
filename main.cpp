#include<iostream>
#include "AVL.cpp"

int main()
{
    int n,ch; 
    
    std::cout<<"Create Root. Value: ";
    std::cin>>n;
    Node *root;

    root = new Node;

    root->value = n;

    while(true) {
            std::cout<<"\n1. Insert Node.\n2. Find Node\n3. Delete Node\n4. Inorder traversal\n";
        std::cin>>ch;
        if (ch == 1)
            std::cin>>n,root->insertN(n);
        else if (ch == 2)
            std::cin>>n,root->findN(n);
        else if (ch == 3)
            std::cin>>n,root->deleteN(n);
        else if (ch == 4)
            root->walkSubTree();
        else
            break;
    }
    return 0;
}
