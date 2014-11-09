#include <iostream>
#include "binomialHeap.h"

using namespace std;

int main()
{
    BinomialHeap *test;
    BinomialTree *node;
    node = NULL;
    test = new BinomialHeap;
    test->insertKey(15);
    test->insertKey(5);
    test->insertKey(35);
    test->insertKey(45);
    test->insertKey(55);
    test->insertKey(65);
    test->insertKey(75);
    test->insertKey(85);
    test->insertKey(95);
    cout<<"\nTraversal:";
    test->traverse();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nExtracted:"<<test->extractMin();
    cout<<"\nTraversal:";
    test->traverse();
    delete test;
    return 0;
}
