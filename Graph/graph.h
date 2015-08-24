#ifndef G_HEADER
#define G_HEADER
#include "stack.h"
#include "que.h"
#include<iostream>
using namespace std;
class graph
{
int** G;
int n;
int* depth1;
int* visited;
int* visitedc;
int* ancestor;
int* ancestord;
int* depth;
public:
graph(int);
virtual ~graph();
bool AddEdge(int,int);
bool deleteEdge(int,int);
int DFS(int);
int BFS(int);
int BFS1(int);
bool get_numberofcomponents(int);
bool check_ifbipartite(int);
};
#endif
