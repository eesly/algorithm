/*
一个高度为N的由正整数组成的三角形，从上走到下，求经过的数字和的最大值。 
每次只能走到下一层相邻的数上，例如从第3层的6向下走，只能走到第4层的2或9上。
   5
  8 4
 3 6 9
7 2 9 5
例子中的最优方案是：5 + 8 + 6 + 9 = 28。
*/
#include <iostream>
#include <ctime>

using namespace std;
const int FLOOR = 10;
int a[FLOOR][FLOOR];
int dp[FLOOR][FLOOR];

//打印塔树
void printNum(int a[], int n)
{
	for (int i = 0; i<FLOOR-n; i++)
		cout<<" ";
	for (int i = 0; i<n; i++)
		cout<<a[i]<<" ";
	cout<<endl;
}

void main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i<FLOOR; i++)
		for(int j=0;j<=i;j++)
			a[i][j]=rand()%10;
	for (int i = 0; i<FLOOR; i++)
		printNum(a[i], i+1);
	
	//最下面一层直接赋值
	int rs = 0;	
	for (int i = 0; i<FLOOR; i++)
		dp[FLOOR-1][i] = a[FLOOR-1][i];
	//从倒数第二行起， 按照状态转移方程
	//dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + a[i][j]向上递推
	//直到dp[0][0]， 此时dp[0][0]就是结果
	for (int i = FLOOR-2; i>=0; i--)
		for (int j = 0; j<=i;j++)
			dp[i][j] = max(dp[i+1][j],dp[i+1][j+1])+a[i][j];

	cout<<"最大的数和为："<<dp[0][0]<<endl;
	system("pause");
}
