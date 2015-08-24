#include<stdio.h>
#include<stdlib.h>
typedef struct node* node_ptr;
typedef struct node{
	int data;
	node_ptr next;
}node;
node* head;
node* tail;
int node_count=0;/*number of nodes*/
enum boolean{false,true};
enum boolean enqueue(int el){
		if(node_count==0){
			tail=(node*)malloc(sizeof(node));
			tail->data=el;
			tail->next=NULL;
			head=tail;
			node_count++;
			}else{
			node* temp=(node*)malloc(sizeof(node));
			temp->data=el;
			temp->next=NULL;
			tail->next=temp;
			tail=temp;
			node_count++;
			}
return true;
	}
enum boolean is_empty(){
	if(node_count==0)
		return true;
	else
		return false;
}
node* dequeue(){
	if(is_empty()){
		printf("Queue is empty\n");
		return NULL;
		}else{
			node* tmp=head;
			if(tail==head){
				head=NULL;
				tail=NULL;				
				}else{
				head=head->next;
				}
			node_count--;
			tmp->next=NULL;
			return tmp;
			}
	}
enum boolean display(){
	if(is_empty()){
		printf("Queue is empty\n");
		return false;
		}else{
			node* t=head;
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
node* tmp_node;
do{
printf("Choose the options:\n");
printf("1.Enqueue\n");
printf("2.Dequeue\n");
printf("3.Check if queue is empty\n");
printf("4.Display queue-content\n");
printf("Enter any other integer to exit\n");
printf("Enter the choice\n");
scanf("%d",&choice);
printf("You entered\t %d\n",choice);
switch(choice){
	case 1:
		printf("Enter the integer to enqueue\n");
		scanf("%d",&new_el);
		if(enqueue(new_el)){
			printf("%d \t Enqueued\n",tail->data);
			break;
			}else{
			printf("Error enqueueing \t%d\n",new_el);
			break;
			}
	case 2:
		tmp_node=dequeue();
		if(tmp_node){
		printf("Dequeued\t%d\n",tmp_node->data);
		}
		break;
	case 3:	
		if(is_empty()){
		printf("Queue is empty \n");
		break;
		}else{
		printf("Queue has \t%d\telements\n",node_count);
		break;
		}
	case 4:
		if(display())
		printf("\nQueue-contents are displayed head to tail\n");
		break;
	default:
		printf("Exiting\n");
		return 0;
	}}while(true);
return 0;
}
