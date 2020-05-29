//数位dp，最普遍的题目：求A到B中满足若干条件的数有多少个
//模板：条件是相邻数字的差至少大于2
const int maxn = 12;
int N,M,K,cnt;
int str[maxn];
int dp[maxn][maxn];   //i位置的j数
int dfs(int pos,int num,int zero,int limit){
	if(pos == 0) return (zero ^ 1);
	if(~dp[pos][num] && !zero && !limit) return dp[pos][num];
	int top = limit?str[pos - 1]:9;
	int ans = 0;
	for(int i = 0 ; i <= top; i ++){
		if(abs(i - num) <= 1 && !zero) continue;
		ans += dfs(pos - 1,i,zero && !i,limit && str[pos - 1] == i);
	}
	if(!zero && !limit) dp[pos][num] = ans;
	return ans;
}
int solve(int x){
	if(!x) return 0;
	Mem(dp,-1);
	cnt = 0;
	while(x){
		str[cnt++] = x % 10;
		x /= 10;
	}
	str[cnt] = 0;
	int ans = dfs(cnt,0,1,1);
	return ans; 
}
int main(){
    int A = read(), B = read();
    Pri(solve(B) - solve(A - 1));
    return 0;
}