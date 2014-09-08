algorithm
=========
学习算法的一些例程

- subNum.cpp求取子序列个数
利用dp实现，主要考虑出现相同字符时的情况，在这里进行了简单的hash。
- towerSelect.cpp塔选择最大和问题，采用dp思想，主要从后往前考虑，就很明朗了
- LIS.cpp最长递增子序列，以LIS[i]表示a[0....i]的最长递增子序列长度，对于
每个值a[i]分别判断其前面的每一个值a[j]与a[i]大小，并进行LIS[i]的更新
- LCS.cpp最长公共子序列长度，利用dp[i][j]表示a[0.....i]与b[0.....j]的最长公共子序列的长度，
对于两个序列当前的值进行判断，如果相等则此时c[i][j]=c[i-1][j-1]+1;
如果不相等，则继承前面的最长的长度，离c[i][j]最近的分别为c[i][j-1]和c[i-1][j]
- LIS2.cpp是最长递增子序列长度求取的第二种方法，将其转换为最长公共子序列问题
		1、将给定序列进行排序
		2、对给定序列和排序序列求取最长公共子序列
		3、由于有序序列保证了递增性，最终可以获得最长的递增子序列
		这种方法有个问题：如果给定的序列存在相同的字符，求取的最长递增子序列包括相同的字符，需要根据
		需求进行去除。
