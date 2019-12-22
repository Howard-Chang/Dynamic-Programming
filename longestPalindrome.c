Method1:
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int max(int a,int b)
{
	return a>b?a:b;
}
int longestPalindrome(char* X, int i, int j)
{
	if(i>j)
		return 0;
	if(i==j)
		return 1;
	if(X[i]==X[j])
		return longestPalindrome(X,i+1,j-1)+2;
	return max(longestPalindrome(X,i+1,j),longestPalindrome(X,i,j-1));
}
int main()
{
	char *X = "ABBDCACB";
	int n = strlen(X);

	printf("The length of Longest Palindromic Subsequence is %d",longestPalindrome(X, 0, n - 1));

	return 0;
}
/******************************************************************************/
Method2:
#include<stdio.h>
#include<stdlib.h>
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


int longestPalindrome(char* X, int i, int j,struct table *t)
{
	if(i>j)
		return 0;
	if(i==j)
		return 1;
	char *key=malloc(20);
	sprintf(key,"%d|%d",i,j);
	if(lookup(t,key)==-1)
	{
		if(X[i]==X[j])
			insert(t,key,longestPalindrome(X,i+1,j-1,t)+2);
		else
			insert(t,key,max(longestPalindrome(X,i,j-1,t),longestPalindrome(X,i+1,j,t)));
			
	}
	return lookup(t,key);
}

int main()
{
	struct table *t = createTable(5);	
	char *X = "ABBDCACB";
	int n = strlen(X);
	printf("The length of Longest Palindromic Subsequence is %d",longestPalindrome(X, 0, n - 1,t));

	return 0;
}


//https://www.techiedelight.com/longest-palindromic-subsequence-using-dynamic-programming/
