#include<stdio.h>
#include<stdlib.h>
typedef struct node* node_ptr;
typedef struct node {
	int data;
	node_ptr next;
}node;
node* top;

int node_count=0;/****node-count can't be used*************/
enum boolean{false,true};
enum boolean push(int el){
	if(node_count==0){
	top=(node*)malloc(sizeof(node));
	top->data=el;/******instead of -> . can't be used********/
	top->next=NULL;
	}else{  
		node* temp;
		temp=(node*)malloc(sizeof(node));
		temp->data=el;
		temp->next=top;
		top=temp;
		}
node_count++;
return true;
}
enum boolean is_empty(){
	if(node_count==0)
		return true;
	else
		return false;
}
node* pop(){
	if(is_empty()){
		printf("Stack is empty\n");
		return NULL;
	}
	else{
	    node* tmp;
	    tmp=top;
	    top=top->next;
	    tmp->next=NULL;
	    node_count--;
	    return tmp;
	   }
}
enum boolean display_contents(){
	if(is_empty()){
		printf("Stack is empty\n");
		return false;
	}
	else{
		node* t=top;
		while(t){
		printf("%d\t",t->data);
		t=t->next;
		}
	return true;
	}
}
int main(){
int choice;
int new_el;
node* popped_el;
do{printf("Choose the option: \n");
printf("1.Push  \n");
printf("2.Pop \n");
printf("3.Check if stack is empty \n");
printf("4.Display stack-contents \n");
printf("Any other option to Exit \n");
printf("Enter your choice: \n");
scanf("%d",&choice);
printf("You entered:%d \n",choice);
switch(choice){
	case 1:
	printf("Enter the integer: \n");
	scanf("%d",&new_el);
	if(push(new_el)){
		printf("Successfully pushed\t%d\n",top->data);
		break;
	}else{
		printf("Error pushing the integer \n");
		break;
		}
	case 2:	
	popped_el=pop();
	if(popped_el){
	printf("Popped %d \n",popped_el->data);
	break;
		}else{
	break;
	}
	case 3:
	if(is_empty())
	printf("Stack is empty\n");
	else
	printf("Stack has \t%d\t elements\n",node_count);
	break;
	case 4:
	if(display_contents()){
		printf("\nStack-contents are displayed from top to bottom\n");
		}
	break;
	default:
	printf("Exiting\n");
	return 0;
	}}while(true);
	return 0;
}
