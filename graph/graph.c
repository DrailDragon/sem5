#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node* nodeptr;
typedef struct node{
	int data;
	nodeptr next;
}node;
node** graph=NULL;
int node_count=0;
bool add_edge(int v1,int v2){
	if(v1>node_count-1 || v2>node_count-1){
		printf("Enter a node value less than:%d or increment graph size\n",node_count);
		return false;
	}
	/********add node to the list graph[v1]******************/
	node* tmp=graph[v1];
	while(tmp->next){
		tmp=tmp->next;
		if(tmp->data==v2){
			printf("Edge between %d and %d already exists\n",v1,v2);
			return false;
		}
	}
	tmp->next=(node*)malloc(sizeof(node));
	(tmp->next)->data=v2;
	tmp->next->next=NULL;
	/********add node to the list graph[v2]******************/
	node* t=graph[v2];
	while(t->next){
		t=t->next;
		if(t->data==v1){
			printf("Edge between %d and %d already exists\n",v2,v1);
			return false;
		}
	}
	t->next=(node*)malloc(sizeof(node));
	(t->next)->data=v1;
	t->next->next=NULL;
	if(tmp->next && t->next)
	{
		printf("Edge added between %d and %d\n",v1,v2);
		return true;
	}
	printf("Error adding edge,try again...\n");
	return false;
}
bool delete_edge(int v1,int v2){
	if(v1>node_count-1 || v2>node_count-1){
		printf("Enter a node value less than:%d\n",node_count);
		return false;
	}
	/********delete node at the list graph[v1]******************/
	node* tmp=graph[v1];
	node* tmp1=NULL;
	while(tmp && tmp->next){
		tmp1=tmp;
		tmp=tmp->next;
		if(tmp->data==v2){
			tmp1->next=tmp->next;
			tmp->next=NULL;
			free(tmp);
			tmp=NULL;
			tmp1=NULL;
		}
	}
	if(tmp){
	 	printf("Edge between %d and %d doesn't exist\n",v1,v2);
		return false;
	}
	/********delete node at the list graph[v2]******************/
	node* t=graph[v2];
	node* t1=NULL;
	while(t && t->next){
		t1=t;
		t=t->next;
		if(t->data==v1){
			t1->next=t->next;
			t->next=NULL;
			free(t);
			t=NULL;
			t1=NULL;
		}
	}
	if(t){
	 	printf("Edge between %d and %d doesn't exist\n",v2,v1);
		return false;
	}
	printf("Edge between %d and %d deleted\n",v1,v2);
	return true;
}
bool push(int* stk,int* top,int v){
	if(*top>=node_count-1){
	return false;
	}
	*top+=1;
	stk[*top]=v;
	return true;
}
int pop(int* stk,int* top){
 	if(*top==-1)
	return -1;
	*top-=1;
	return stk[(*top)+1];
}
bool enqueue(int* q,int* tail,int v){
	if(*tail>=node_count)
	return false;
	q[*tail]=v;
	*tail+=1;
	return true;
}
int dequeue(int* q,int* tail){
	if(*tail==0)
	return -1;
	*tail-=1;
	return q[*tail];
}
bool bfs(int s){
	if(s>node_count-1){
		printf("Enter a node value less than:%d or increment graph size\n",node_count);
		return false;
	}
	node* tmp=NULL;
	int i,root=s,p=-1;
	bool visited[node_count];
	for(i=0;i<node_count;i++)
	visited[i]=false;
	int q[node_count],tail=0;
	enqueue(q,&tail,s);
	visited[s]=true;
	printf("vertex is:%d\tparent is %d\n",root,p);
	while(tail!=0){
		root=dequeue(q,&tail);
		tmp=graph[root];
		p=root;
		while(tmp){
			tmp=tmp->next;
			if(tmp && !visited[tmp->data])
			{		
			enqueue(q,&tail,tmp->data);
			visited[tmp->data]=true;
			printf("vertex is:%d\tparent is %d\n",tmp->data,p);
			}
		}
	}
	return true;
}
bool dfs(int s){
	if(s>node_count-1){
		printf("Enter a node value less than:%d or increment graph size\n",node_count);
		return false;
	}
	node* tmp=NULL;
	int i,root=s,p=-1;
	bool visited[node_count];
	for(i=0;i<node_count;i++)
	visited[i]=false;
	int stk[node_count],top=-1;
	push(stk,&top,s);
	while(top!=-1){
		root=pop(stk,&top);
		if(visited[root])
		continue;
		visited[root]=true;
		tmp=graph[root];
		if(p!=root)
		printf("vertex is:%d\tparent is %d\n",root,p);
		p=root;
			tmp=tmp->next;
			while(tmp){
			if(visited[tmp->data])
			 tmp=tmp->next;		
			if(tmp && !visited[tmp->data]){
			push(stk,&top,tmp->data);
			tmp=tmp->next;
				}
			}
	}
	return true;
}
bool delete_graph(){
	int i;
 	for(i=0;i<node_count;i++){
		node* tmp=graph[i];
		node* t=tmp->next;
		while(tmp){
			if(t)
			tmp->next=NULL;
			free(tmp);
			tmp=t;
			t=t->next;
		}
	}
	if(!graph){
		printf("Existing graph deleted\n");
		return true;
	}
	printf("Error deleting existing gaph,try again...\n");
	return false;
}
bool increment_graphsize(int newsize){
	if(newsize<=node_count){
		printf("Please enter the new size greater than %d\n",node_count);
		return false;
	}
	graph=(node**)realloc(graph,newsize*sizeof(node*));
	if(graph){
		int i;
		for(i=node_count;i<newsize;i++){
			graph[i]=(node*)malloc(sizeof(node));
			graph[i]->data=i;
			graph[i]->next=NULL;
			}
		node_count=newsize;
		printf("graph size incremented to %d\n",node_count);
		return true;
	}
	printf("Error reallocating graph of new size:%d\n",newsize);
	return false;
}
/******just for test*****/
bool print_list(){
	int i;
	for(i=0;i<node_count;i++){
		node* tmp=graph[i];
		while(tmp){
		printf("%d\t",tmp->data);
		tmp=tmp->next;
		}
		printf("\n");
	}
	return true;
}
int main(){
int choice,i;
int v1,v2;
	do{
		printf("Choose the option:\n");
		printf("1.Create new empty graph\n");
		printf("2.Add edge\n");
		printf("3.Delete edge\n");
		printf("4.bfs\n");
		printf("5.dfs\n");
		printf("6.Increment graph-size\n");
		printf("7.Print list");	
		printf("Enter any other integer to exit\n");
		scanf("%d",&choice);
		printf("You entered:%d\n",choice);
		switch(choice){
			case 1:
			if(graph)
			 choice=delete_graph();
			if(choice){
				printf("Enter the initial number of nodes you want in the graph\n");
				scanf("%d",&node_count);
				graph=(node**)malloc(node_count*sizeof(node*));
				if(graph){
					printf("Empty graph of size:%d created\n",node_count);
					for(i=0;i<node_count;i++){
					graph[i]=(node*)malloc(sizeof(node));
					graph[i]->data=i;
					graph[i]->next=NULL;
					}
					break;
				}
				printf("Error allocating memory for empty graph of size:%d,try again...\n",node_count);
				break;	
			}
			case 2:
				if(!graph){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the two vertices to add edge between them\n");
				scanf("%d%d",&v1,&v2);
				add_edge(v1,v2);
				break;
			case 3:
				if(!graph){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the two vertices to delete edge between them\n");
				scanf("%d%d",&v1,&v2);
				delete_edge(v1,v2);
				break;
			case 4:
				if(!graph){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the vertex to start bfs from\n");
				scanf("%d",&v1);
				bfs(v1);
				break;
			case 5:
				if(!graph){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the vertex to start dfs from\n");
				scanf("%d",&v1);
				dfs(v1);
				break;
			case 6:
				if(!graph){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the new size of the graph you want\n");
				scanf("%d",&choice);
				increment_graphsize(choice);
				break;
			case 7:
				if(!graph){
					printf("First Create a new empty graph\n");
					break;
				}
				print_list();
				break;
			default:
				printf("Exiting\n");
				return 0;
		}
	}while(true);
return 0;
}
