#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char* LCS(char *X,char *Y,int m,int n)
{
	int map[m+1][n+1],idx=0,maxlen=0;
	memset(map,0,sizeof(map));
	int i,j;
	for(i=1;i<m+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			if(X[i-1]==Y[j-1])
			{
				map[i][j]=map[i-1][j-1]+1;
				if(map[i][j]>maxlen)
				{
					maxlen=map[i][j];
					idx=i;
				}
			}
		}
	}
	char *ret=(char *)malloc(20);
	strcpy(ret,X);
	ret[idx]=0;
	//printf("%s",ret);
	return ret+idx-maxlen;
}
int main()
{
	char X[] = "ABCABA", Y[] = "BABA";
	int m = strlen(X), n = strlen(Y);

	// Find Longest common substring
	printf("The Longest common substring is %s", LCS(X, Y, m, n));

	return 0;
}
