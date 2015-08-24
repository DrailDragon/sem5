#ifndef S_HEADER
#define S_HEADER
#include<iostream>
using namespace std;
class stack1
{
    int* st;
    int n;
    int top;
public:
    stack1(int);
    virtual ~stack1();
    bool push(int);
    int pop();
    bool if_empty();
    bool is_full();
    bool display();
};
#endif // S_HEADER
