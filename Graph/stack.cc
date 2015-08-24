#include "stack.h"
stack1::stack1(int siz){
st=NULL;
n=siz;
top=-1;
st=new int[n];
}
stack1::~stack1(){}
bool stack1::if_empty()
{
    if(top==-1)
        return true;
    else
        return false;
}
bool stack1::is_full()
{
    if(top==n)
        return true;
    else
        return false;
}
bool stack1::push(int x)
{
    if(is_full())
    {
        cout<<"stack is full increasing size by 10"<<endl;
        int * t=new int[n+10];
        for(int i=0;i<n;i++)
            t[i]=st[i];
        t[++top]=x;
        n+=10;
        st=NULL;
        st=t;
    }
    else
    st[++top]=x;
    return true;

}
int stack1::pop()
{
    if(if_empty()==true)
    {
        cout<<"stack is empty"<<endl; return false;
    }
    else
    return st[top--];
}
bool stack1::display()
{
    if(if_empty())
        {cout<<"stack is empty"<<endl;
    return false;}
    else
    {
        while(!if_empty())
            cout<<pop()<<endl;
        return true;
    }
}
