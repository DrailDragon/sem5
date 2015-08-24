#include "que.h"
que::que(int siz)
{
    head=0;
    tail=0;
    q=NULL;
    n=siz;
	q=new int[n];
}
que::~que(){}
bool que::enque(int a)
{
    if(is_full())
    {
        cout<<"queue is full.increasing size by 10"<<endl;

        int* b=new int[n+10];
        for(int i=0;i<n;i++)
            b[i]=q[i];
             q=NULL;
        b[n]=a;
        q=b;
        tail++;
        n+=10;
    }
        else
        {
            q[tail]=a;
            tail++;
	}

return true;
}
int que::dequeue()
{
    if(if_empty())
    {
        cout<<"Que is empty"<<endl;
        return false;
    }
    else
    {
        tail--;
        int tmp=q[head];
	for(int i=0;i<=tail;i++)
		q[i]=q[i+1];
	return tmp;
    }
}
bool que::if_empty()
{
    if(head==0 && tail==0)
        return true;
    else
        return false;
}
bool que::is_full()
{
    if(head==0 && tail==n)
       return true;
       else
        return false;

}
bool que::display()
{
    if(if_empty())
    {
        cout<<"Nothing to display"<<endl;
    }
    while(!if_empty())
    {
        cout<<dequeue()<<endl;
    }
    return true;

}
