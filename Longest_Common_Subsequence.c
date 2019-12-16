Method1:
/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int max(int a,int b)
{
	return a>b?a:b;
}
int LCS(char *x,char *y,int xlen,int ylen)
{
	if(!xlen||!ylen)
		return 0;
	if(x[xlen-1]==y[ylen-1])
		return LCS(x,y,xlen-1,ylen-1)+1;
	else
		return max(LCS(x,y,xlen-1,ylen),LCS(x,y,xlen,ylen-1));
}
int main()
{

	char *X = "ABCBDAB", *Y = "BDCABA";

	printf("The length of LCS is %d.",LCS(X, Y, strlen(X), strlen(Y)));

	return 0;
} */
Method2:
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int max(int a,int b)
{
	return a>b?a:b;
}
struct node{
    char* key;
    int val;
    struct node *next;
};
struct table{
    int size;
    struct node **list;
};
struct table *createTable(int size){
    struct table *t = (struct table*)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node**)malloc(sizeof(struct node*)*size);
    int i;
    for(i=0;i<size;i++)
        t->list[i] = NULL;
    return t;
}
int hashCode(struct table *t,char* key){
    /*if(key<0)
        return -(key%t->size);*/
    return *key%t->size;
}
void insert(struct table *t,char* key,int val){
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    struct node *temp = list;
    while(temp){
        if(strcmp(temp->key,key)==0){
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->val = val;
    newNode->next = list;
    t->list[pos] = newNode;
}
int lookup(struct table *t,char* key){
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    struct node *temp = list;
    while(temp){
        if(strcmp(temp->key,key)==0){
            return temp->val;
        }
        temp = temp->next;
    }
    return -1;
}


int LCSLength(char* X, char* Y, int m, int n, struct table *t)
{
	// return if we have reached the end of either string
	if (m == 0 || n == 0)
		return 0;

	// construct a unique map key from dynamic elements of the input
	char *key=calloc(10,1); 
	sprintf(key,"%d|%d",m,n);

	// if sub-problem is seen for the first time, solve it and
	// store its result in a map
	if (lookup(t,key)==-1)
	{
		// if last character of X and Y matches
		if (X[m - 1] == Y[n - 1])
			insert(t,key,LCSLength(X, Y, m - 1, n - 1, t) + 1);

		else
		// else if last character of X and Y don't match
		insert(t,key,max(LCSLength(X, Y, m, n - 1, t),
						 LCSLength(X, Y, m - 1, n, t)));
	}

	// return the subproblem solution from the map
	return lookup(t,key);
}

// Longest Common Subsequence
int main()
{
	struct table *t = createTable(5);
	char *X = "ABCBDAB", *Y = "BDCABA";

	// create a map to store solutions of subproblems
	//unordered_map<string, int> lookup;

	printf("The length of LCS is %d.",LCSLength(X,Y,strlen(X),strlen(Y),t));

	return 0;
}
