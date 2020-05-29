//n封信对应n个信封,求恰好全部装错了信封的方案数
//dp[i] = (i-1) * (dp[i-1] + dp[i-2])
int N,M,K;
LL dp[30];
int main(){
	dp[1] = 0,dp[2] = 1;
	for(int i = 3; i <= 20; i ++) dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
	while(~Sca(N)) Prl(dp[N]);
	return 0;
}