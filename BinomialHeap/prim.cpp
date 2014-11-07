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
    test->insertKey(25);
    test->insertKey(35);
    test->insertKey(45);
    test->traverse();
    delete test;
    return 0;
}
