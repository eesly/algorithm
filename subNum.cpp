/*
子序列的定义：对于一个序列a=a[1],a[2],......a[n]，则非空序列
a'=a[p1],a[p2]......a[pm]为a的一个子序列 其中1<=p1<p2<.....<pm<=n。 
例如：4,14,2,3和14,1,2,3都为4,13,14,1,2,3的子序列。
	1、对于给出序列a，有些子序列可能是相同的，这里只算做1个。
	2、要求输出a的不同子序列的数量。
	
eesly
2014.9.8
*/

#include <iostream>
#include <ctime>

using namespace std;

const int MAX_NUM = 10;
int a[MAX_NUM];
//打印序列
void printNum(int a[], int n)
{
	for (int i = 0; i<n; i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
//获取子序列数
int subNum(int a[],int n)
{
	//记录下标表示是否出现过，简单的hash
	int *index = new int[n];
	memset((int*)index,-1,n*sizeof(int));
	int *dp = new int[n];
	memset((int*)dp,0,n*sizeof(int));
	dp[0] = 1;
	index[a[0]] = 0;
	for (int i = 1; i<n; i++)
	{
		//如果前面没有相同的,则a[i]自身成为一个子序列，故+1
		//还包括之前的子序列+dp[i-1]
		//还包括之前的子序列和a[i]构成新的子序列+dp[i-1],故总共有d[i-1]*2+1
		if (index[a[i]] == -1)
			dp[i] = dp[i-1]*2+1;
		//如果前面已有相同的，首先假定与前面不同获得d[i-1]*2+1个子序列，然后再扣除
			//情况1：和第一个数相同故只需要-1即可
		else if(index[a[i]] == 0)
			dp[i] = dp[i-1]*2+1 -1;
			//情况2：和后面数相同，则首先a[i]自身构成的子序列已经重复，需-1
			//同时，前一个位置的与a[i]相同的数位置，由于增加了该数所增加的全部子序列数需要扣除-dp[index[a[i]]-1]即可
		else
			dp[i] = dp[i-1]*2+1 -1 - dp[index[a[i]]-1];
		index[a[i]]=i;	
		//根据上述推导，可以发现如果对每个子序列进行操作会是一个O(2^n)级的复杂度
	}
	return dp[n-1];
}

int main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i<MAX_NUM; i++)
		a[i]=rand()%MAX_NUM;

	cout<<"序列为："<<endl;
	printNum(a,MAX_NUM);

	cout<<"子序列个数为："<<subNum(a,MAX_NUM)<<endl;
	system("pause");
}
