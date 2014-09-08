/*给定一个长度为N的数组a0,a1,a2...,an-1，找出一个最长的单调递增子序列
（注：递增的意思是对于任意的i<j，都满足ai<aj，此外子序列的意思是不要求连续，顺序不乱即可）。

例如：给定一个长度为6的数组A{5， 6， 7， 1， 2， 8}，则其最长的单调递增子序列为{5，6，7，8}，长度为4。

提示：一种解法是转换为最长公共子序列问题，另外一种解法则是动态规划。当我们考虑动态规划解决时，
可以定义dp[i]为以ai为末尾的最长递增子序列的长度，故以ai结尾的递增子序列
	1\要么是只包含ai的子序列
	2\要么是在满足j<i并且aj<ai的以ai为结尾的递增子序列末尾，追加上ai后得到的子序列
如此，便可建立递推关系，在O(N^2)时间内解决这个问题

eesly
2014.9.8
*/
#include <iostream>
#include <ctime>

using namespace std;

const int MAX_NUM = 10;
int a[MAX_NUM];

void printNum(int a[], int n)
{
	for (int i = 0; i<n; i++)
		cout<<a[i]<<" ";
	cout<<endl;
}

//说明：后面加有*********的行是为了输出最终的递增子序列，如果不需要输出，只需要长度可以不要这部分代码
int LIS(int a[],int n)
{
	int len = n;
	int *dp = new int[n];	//dp[i]表示a[0...i]的最长序列长度
	int *last_index = new int[n];//记录dp[i]表示的最长子序列上一个位置下标*********
	int end = 0;			//记录最终的最长子序列最后一个值的下表*********
	int rs = 0;
	for(int i = 0; i<n; i++)
	{
		//每个位置最初的递增序列长度为1，即序列只有一个值为其本身
		dp[i]=1;
		last_index[i] = i;	//*********
		//检查该值前面的每一个值，如果当前值大于它
		//则比较LIS[当前值]与LIS[前面值]+1的大小,如果其更大则更新
		//这样经过O(n^2)可以获得最长的递增序列长度
		for(int j = 0;j<i;j++)
			if(a[j]<a[i] && dp[i]<dp[j]+1)
			{
				dp[i]=dp[j]+1;
				last_index[i] = j;//*********
			}
		if(dp[i]>rs)
		{
			rs = dp[i];
			end = i;			//*********
		}
	}
	int sublen = rs;
	while(sublen--)				//*********
	{							//*********
		cout<<a[end]<<" ";		//*********
		end = last_index[end];	//*********
	}							//*********
	cout<<endl;					//*********
	return rs;
}

int main()
{
	srand((unsigned)time(NULL));
	for(int i = 0; i < MAX_NUM; i++)
		a[i] = rand()%MAX_NUM;
	printNum(a,MAX_NUM);

	cout<<"最长递增子序列为：";
	LIS(a,MAX_NUM);
	system("pause");
}
