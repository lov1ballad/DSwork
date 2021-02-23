#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int max(int x, int y)
{
	return x>y ? x : y;
}
int main()
{
	int i, j;
	int n, maxv;
	int v[101], c[101];
	int dp[10001];
	scanf("%d%d", &n, &maxv);
	for (i = 1; i <= n; i++)
		scanf("%d%d", v + i, c + i);
	for (i = 1; i <= n; i++)
	for (j = maxv; j >= v[i]; j--)
		dp[j] = max(dp[j], dp[j - v[i]] + c[i]);
	printf("%d\n", dp[maxv]);
}