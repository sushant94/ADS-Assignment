#include <iostream>
#include <string.h>
#include "binomialHeap.h"

using namespace std;

int main()
{
    int n,en;
    int sa,sb,w;
    int parents[100];
    memset(parents, 0, sizeof(parents));
    int weights[100][100];
    int start;

    cout<<"Enter number of nodes: ";
    cin>>n;

    BinomialHeap *Q;
    Q = new BinomialHeap;

    for (int i = 1; i <= n; i++)
        Q->insertKey(1000, i);
   
    cout<<"Enter number of edges: ";
    cin>>en;
    cout<<"Enter edges. FORMAT: <node1> <node2> <weight>\n";
    cout<<"NOTE: nodes are indexed 1 - n\n";
    for (int i = 1; i <= en; i++)
        cin>>sa>>sb>>w, weights[sa][sb] = w;
    cout<<"Enter start node for Prim's: ";
    cin>>start;

    BinomialTree *t;
    Q->findKey(start, &t);
    if (t)
        t->decreaseKey(0);
    while(Q->head) {
        int index = Q->extractMin();
        // We have the extracted index.
        for (int i = 1; i <= n; i++) {
            Q->findKey(i, &t);
            if (t && weights[index][i] < t->val.value) {
                t->decreaseKey(weights[index][i]);
                t->val.parent = index;
                parents[t->val.n] = index;
            }
        }
    }

    cout<<"MST (";
    cout<<"FORMAT: <node>[parent]):\n";
    for (int i = 1; i <= n; i ++)
        cout<<i<<"["<<(parents[i])<<"] ";
    cout<<"\n";
    // Go through its connections.
    // Set parent.
    // Continue till empty.
    return 0;
}
