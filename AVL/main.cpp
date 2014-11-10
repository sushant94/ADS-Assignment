#include<iostream>
#include "AVL.h"
using namespace std;
int main()
{
    int n,ch = 1; 
    AVLTree *t;
    t = new AVLTree;
    while(ch) {
        cout<<"\n1. Insert Node.\n2. Find Node\n3. Delete Node\n4. Inorder traversal\n";
        cin>>ch;
        switch(ch) {
          case 1:
            cout<<"Enter key: ";
            cin>>n;
            t->insertN(n);
            break;
          case 2:
            cout<<"Enter key: ";
            cin>>n;
            t->findN(n);
            break;
          case 3:
            cout<<"Enter key: ";
            cin>>n;
            t->deleteN(n);
            break;
          case 4:
            t->walkTree();
            break;
          default:
            ch = 0;
        }
    }
    return 0;
}
