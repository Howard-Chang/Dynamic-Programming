#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int min(int a,int b)
{
	return a>b?b:a;
}

int SCSLength(char* X, char* Y, int m, int n)
{
	if (m == 0 || n == 0)
		return n + m;
	if(X[m-1]==Y[n-1])
		return SCSLength(X,Y,m-1,n-1)+1;
	return min(SCSLength(X,Y,m-1,n)+1,SCSLength(X,Y,m,n-1)+1);
}
int main()
{
	char *X = "ABCBDAB", *Y = "BDCABA";
	int m = strlen(X), n = strlen(Y);

	printf("The length of shortest Common supersequence is %d\n",SCSLength(X, Y, m, n));

	return 0;
}
