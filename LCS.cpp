/*最长公共子序列
什么是最长公共子序列呢?好比一个数列 S，如果分别是两个或多个已知数列的子序列，
且是所有符合此条件序列中最长的，则S 称为已知序列的最长公共子序列。

举个例子，如：有两条随机序列，如 1 3 4 5 5 ，and 2 4 5 5 7 6，
则它们的最长公共子序列便是：4 5 5。

eesly
2014.9.8
*/
#include <iostream>
#include <ctime>

using namespace std;

const int MAX_NUM = 10;
int a[MAX_NUM];
int b[MAX_NUM];

void printNum(int a[], int n)
{
	for (int i = 0; i<n; i++)
		cout<<a[i]<<" ";
	cout<<endl;
}

int LCS(int a[], int lenA,int b[],int lenB)
{
	//实现细节，c对应的长度都加1，便于后续处理
	int **c = new int*[lenA+1];
	for(int i = 0; i<lenA+1; i++)
		c[i] = new int[lenB+1];

	//初始化c[i][0]和c[0][i]为0
	for(int i = 0; i<lenA+1; i++)
		c[i][0] = 0;
	for(int i = 0; i<lenB+1; i++)
		c[0][i] = 0;

	//两重循环复杂度为O(lenA*lenB)
	for(int i = 1; i<=lenA; i++)
		for(int j = 1; j<=lenB; j++)
		{
			//对于两个序列当前的值进行判断，如果相等则此时c[i][j]=c[i-1][j-1]+1;
			//含义：c[i][j]		表示a[0.....i]与b[0.....j]的最长公共子序列的长度
			//	    c[i-1][j-1]	表示a[0.....i-1]与b[0.....j-1]的最长公共子序列的长度
			if(a[i-1] == b[j-1])
				c[i][j] = c[i-1][j-1]+1;
			//如果不相等，则继承前面的最长的长度，离c[i][j]最近的分别为c[i][j-1]和c[i-1][j]
			else 
				c[i][j] = c[i][j-1]>c[i-1][j]?c[i][j-1]:c[i-1][j];
		}
	
	//逆序输出最长子序列
	int *LCSq = new int[c[lenA][lenB]];
	int i = lenA,j=lenB;
	int k = c[lenA][lenB]-1;
	while(i&&j)
	{
		if(c[i][j] == c[i-1][j-1]+1 && a[i-1] == b[j-1])
		{
			LCSq[k--] = a[i-1];
			i--; j--;
		}
		else if(a[i-1] != b[j-1]&&c[i][j-1]>c[i-1][j])
			j--;
		else
			i--;
	}
	printNum(LCSq, c[lenA][lenB]);
	//返回长度
	return c[lenA][lenB];
}

int main()
{
	srand((unsigned)time(NULL));
	for(int i = 0; i < MAX_NUM; i++)
	{
		a[i] = rand()%MAX_NUM;
		b[i] = rand()%MAX_NUM;
	}
	printNum(a,MAX_NUM);
	printNum(b,MAX_NUM);
	
	cout<<"最长公共序列为：";
	int len = LCS(a,MAX_NUM,b,MAX_NUM);
	cout<<"最长公共序列长度为："<<len<<endl;

	system("pause");
}
