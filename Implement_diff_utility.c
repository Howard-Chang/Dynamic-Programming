#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int max(int a,int b)
{
	return a>b?a:b;
}
int lookup[20][25];
void diff(char *X,char *Y,int m,int n)
{
	if(m>0&&n>0&&X[m-1]==Y[n-1])
	{
		diff(X,Y,m-1,n-1);
		printf(" %c",X[m-1]);
	}
	else if(m>0&&(n==0||lookup[m][n-1]<lookup[m-1][n]))
	{
		diff(X,Y,m-1,n);
		printf(" -%c",X[m-1]);
	}
	else if(n>0&&(m==0||lookup[m][n-1]>=lookup[m-1][n]))
	{
		diff(X,Y,m,n-1);
		printf(" +%c",Y[n-1]);
	}
}
void lcs_length(char *X,char *Y,int len1,int len2)
{
	for(int i=0;i<=len1;i++)
		lookup[i][0]=0;
	for(int j=0;j<=len2;j++)
		lookup[j][0]=0;

	for(int i=1;i<=len1;i++)
	{
		for(int j=1;j<=len2;j++)
		{
			if(X[i-1]==Y[j-1])
				lookup[i][j]=lookup[i-1][j-1]+1;
			else
				lookup[i][j]=max(lookup[i-1][j],lookup[i][j-1]);
		}
	}
}
// Implement Diff Utility
int main()
{
	char* X = "ABCDFGHJQZ";
	char* Y = "ABCDEFGIJKRXYZ";
	int m = strlen(X), n = strlen(Y);

	// fill lookup table
	lcs_length(X, Y, m, n);

	// find difference by reading lookup table in top-down manner
	diff(X, Y, m, n);

	return 0;
}
