//字符串Hash，将字符串s变为一个数字
//预处理
p[0] = 1; // 131^0
for (int i = 1; i <= n; i++) {
    f[i] = f[i-1] * 131 + (s[i]-'a'+1); // hash of 1~i
    p[i] = p[i-1] * 131; // 131^i
}
//使用
f[r1] - f[l1-1] * p[r1-l1+1]  // hash of l1~r1
f[r2] - f[l2-1] * p[r2-l2+1]) // hash of l2~r2

/*扩展
字符串hash其实和进制进位有一些相似，我们想到了这一点就可以线性的时间正着求前缀字符串的hash值和前缀字符串的倒转的hash值

当我们求正序前缀的hash的时候，每一次操作就相当于再字符串的最前面插入一个值，所以我们要首先处理出每一位的指数级ans,然后f[i] = f[i - 1] + str[i] * ans;

当我们求逆序前缀的hash值的时候，每一次操作就相当于在字符串的最后插入一个值，整个字符串就要左移一位然后把这个位塞进去 也就是f [i]= f[i - 1] * tmp + str[i];
*/
//例题 判断一个字符串的每一个前缀是否相等
ULL ans = 1;
ULL f1[maxn],f2[maxn];
char str[maxn];
for(int i = 1 ; i <= l; i ++){
    if (str[i] >= '0' && str[i] <= '9')   str[i] = str[i] - '0';
    else if (str[i] >= 'a' && str[i] <= 'z') str[i] = str[i] - 'a' + 10;
    else str[i] = str[i] - 'A' + 36;
    f1[i] = f1[i - 1] * 131 + str[i];
    f2[i] = (f2[i - 1] + str[i] * ans);
    ans *= 131;
    if (f1[i] == f2[i]){
        puts("i is equal");
    }
}
