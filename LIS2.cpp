/*给定一个长度为N的数组a0,a1,a2...,an-1，找出一个最长的单调递增子序列
（注：递增的意思是对于任意的i<j，都满足ai<aj，此外子序列的意思是不要求连续，顺序不乱即可）。

例如：给定一个长度为6的数组A{5， 6， 7， 1， 2， 8}，则其最长的单调递增子序列为{5，6，7，8}，长度为4。

提示：一种解法是转换为最长公共子序列问题，另外一种解法则是动态规划。这里考虑最长公共子序列的方法
		1、将给定序列进行排序
		2、对给定序列和排序序列求取最长公共子序列
		3、由于有序序列保证了递增性，最终可以获得最长的递增子序列
		这种方法有个问题：如果给定的序列存在相同的字符，求取的最长递增子序列包括相同的字符，需要根据
		需求进行去除。

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

int mycmp(const void *a,const void *b)
{
	return (*((int*)a))-(*((int*)b));	//此处选择-号不要使用小于号，使用a-b对应小到大排序
}

int LCS(int a[],int lenA,int b[],int lenB)
{
	int **c = new int*[lenA+1];
	for(int i = 0; i <lenA+1; i++)
		c[i] = new int[lenB+1];

	//初始化c[i][0]和c[0][j]为0
	for(int i = 0; i<lenA; i++)
		c[i][0] = 0;
	for(int j = 0; j<lenB; j++)
		c[0][j] = 0;

	//两重循环，复杂度o(lenA*lenB)
	for(int i = 1; i<lenA+1; i++)
		for(int j = 1; j<lenB+1; j++)
		{
			//对于两个序列当前的值进行判断，如果相等则此时c[i][j]=c[i-1][j-1]+1;
			//含义：c[i][j]		表示a[0.....i]与b[0.....j]的最长公共子序列的长度
			//	    c[i-1][j-1]	表示a[0.....i-1]与b[0.....j-1]的最长公共子序列的长度
			if(a[i-1]==b[j-1])
				c[i][j] = c[i-1][j-1]+1;
			//如果不相等，则继承前面的最长的长度，离c[i][j]最近的分别为c[i][j-1]和c[i-1][j]
			else
				c[i][j] = c[i-1][j]>c[i][j-1]?c[i-1][j]:c[i][j-1];
		}

	//逆序输出最长递增子序列
	int i = lenA,j = lenB;
	int k = c[lenA][lenB]-1;
	int *LISq = new int[c[lenA][lenB]];
	while(i&&j)
	{
		if(a[i-1]==b[j-1]&&c[i][j] == c[i-1][j-1]+1)
		{
			LISq[k--] = a[i-1];
			i--;
			j--;
		}
		else if(a[i-1]!=b[j-1]&&c[i-1][j] > c[i][j-1])
			i--;
		else
			j--;			
	}
	printNum(LISq, c[lenA][lenB]);

	//资源回收
	int rs = c[lenA][lenB];
	for(int i = 0; i <lenA+1; i++)
		delete [] c[i];
	delete [] LISq;

	return rs;
}

int main()
{
	srand((unsigned)time(NULL));
	for(int i = 0; i < MAX_NUM; i++)
		a[i] = rand()%MAX_NUM;
	memcpy(b,a,MAX_NUM*sizeof(int));
	printNum(a,MAX_NUM);

	qsort(b,MAX_NUM,sizeof(int),mycmp);
	printNum(b,MAX_NUM);

	cout<<"最长递增子序列为：";
	int len = LCS(a,MAX_NUM,b,MAX_NUM);
	cout<<"最长递增子序列长度为："<<len<<endl;

	system("pause");
}
