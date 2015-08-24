#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
int* st;
int i,j;
int st_size;
int top=-1;
/*******bool equivalent of c++*******************/
enum boolean{false,true};
enum boolean push(int el){
           if(top==st_size-1){
		printf("Stack full,incrementing the size by 10\n");
		st=(int*)realloc(st,(st_size+10)*sizeof(int));/******in c++  we do it manually realloc does three tasks:
									1.copy contents of original array in a temp array
									2.Allocate specified memory
									3.copy back the contents from temp to original array
									 **********/
                st_size+=10;
		st[++top]=el;
	   }else{
         st[++top]=el;
	    }
 return true;
	}
enum boolean is_empty(){
	if(top==-1)
		return true;
	else
		return false;
}
int pop(){
   if(is_empty()){
		printf("Stack is empty\n");
		return 0;
		}else{ 
			int temp=st[top];
			st[top]=0;/*********0 is not considered here the normal element ****************/
			top--;
		     return temp;
			}
	}
enum boolean display_elements(){
	if(is_empty()){
		printf("Stack is empty\n");
		return false;
		}else{ 
			int t=top;
			while(top>=0){
			printf("%d\t",st[top]);
			top--;
			}
		top = t;
		return true;
	}
}
int peak_element(){
	if(is_empty()){
		printf("Stack is empty\n");
		return 0;
		}else{ 
			return st[top];
			}
	
}
int main(int argc,char* argv[]){
  int new_el;
  int ch;
	printf("Enter the initial size of the stack to be implemented\n");
	scanf("%d",&st_size);
	printf("You entered \t%d\n",st_size);
	st=(int*)malloc(st_size*sizeof(int));
do{
	printf("1. Push an element\n");
	printf("2. Pop an element\n");
	printf("3. Check if stack is empty\n");
	printf("4. Display stack elements\n");
	printf("5. Get top element\n");
	printf("Enter any other option to exit\n");
	printf("Choose the option\n");
	scanf("%d",&ch);
	printf("You entered \t%d\n",ch);
	switch(ch){
		case 1:
		printf("Eneter the integer to push on the stack\n");
		scanf("%d",&new_el);
		push(new_el);
		printf("Pushed\t%d\n",st[top]);
		break;
		case 2:
		new_el = pop();
		if(new_el!=0)
			printf("Popped\t%d\n",new_el);
		break;
		case 3:
		if(is_empty()){
		printf("Stack is empty\n");
		}else{
			printf("Stack has \t%d\t elements\n",top+1);
			}
		break;
		case 4:
		if(display_elements()){
		printf("\nStack contents are (dispalyed top to bottom)\n");
		printf("\n");
			}
		break;
		 case 5:
		new_el = peak_element();
		if(new_el!=0)
		printf("Peak element is\t%d\n",new_el);
		break;
		default:
		printf("Exiting\n");
		return 0;
		}
	}while(true);
return 0;
}
