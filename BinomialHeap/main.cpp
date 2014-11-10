#include <iostream>
#include "binomialHeap.h"

using namespace std;

int main()
{
    BinomialHeap *test;
    BinomialTree *node;
    node = NULL;
    test = new BinomialHeap;
    int choice = 1;
    while (choice) {
        cout<<"\nChoices:\n1.Insert into heap.\n2.Extract Minimum\n3.Traverse\n4.Exit\n";
        cin>>choice;
        int key;
        switch(choice) {
          case 1:
              cout<<"Enter Key: ";
              cin>>key;
              test->insertKey(key);
              break;
          case 2:
              cout<<"Minimum: "<<test->extractMin();
              break;
          case 3:
              cout<<"\nTraversal:";
              test->traverse();
              break;
          default: choice = 0;
              break;
        }
    }

    delete test;
    return 0;
}
