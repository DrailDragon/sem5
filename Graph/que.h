#ifndef QUE_H
#define QUE_H
#include<iostream>
using namespace std;
class que
{
    int head;
    int tail;
    int* q;
    int n;
public:
    que(int);
    virtual ~que();	
    bool enque(int);
    int dequeue();
    bool if_empty();
    bool is_full();
    bool display();

};
#endif
