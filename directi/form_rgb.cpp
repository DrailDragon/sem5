/***Question 1. We need to make a string of size n. Each character of the string is either ‘R’, ‘B’ or ‘G’. In the final string there needs to be at least r number of ‘R’, at least b number of ‘B’ and at least g number of ‘G’ (such that r + g + b <= n). We need to find number of such strings possible.*/
#include<iostream>
#include<math.h>
#include<cstring>
using namespace std;
int fact(int x){
	if(x==0)
	return 1;
	return(x*fact(x-1));
}

int main(){
	int n,r=0,g=0,b=0;
	cin>>n>>r>>g>>b;
	int t=r+g+b;
	int num=(2*fact(t)*pow(3,n-t))/(fact(r)*fact(g)*fact(b));
	cout<<num<<endl;
	
	return 0;
}
