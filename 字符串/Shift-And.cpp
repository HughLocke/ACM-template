/*Shift-and 算法
b[i][j]表示在字符i模式串中第j个位置出现
ans[i]表示当前字符串的后缀与模式串的长度为i的前缀匹配
每次加入字符的时候；
1.将ans左移一位2.ans[0]置1 3.ans与b[str[i]]进行与运算，str[i]为当前加入的字符
就更新完成了
*/
//模板 hdu5972
/*给你N位数,接下来有N行,第i行先输入n,表示这个数的第i位上可以在接下来的n个数中挑选,然后i行再输n个数。
然后输入需要匹配的母串,让你输出母串中有多少个可行的N位子串并输出
 */
char str[maxn];
bitset<1010>b[12],ans;
int main(){
    while(~Sca(N)){
        for(int i = 0 ; i < 10; i ++) b[i].reset();
        for(int i = 0; i < N ; i ++){
            int x; x = read();
            while(x--) b[read()][i] = 1;
        }
        scanf("%s",str); ans.reset();
        LL sum = 0;
        for(int i = 0;str[i]; i ++){
            ans <<= 1; ans[0] = 1;
            ans &= b[str[i] - '0'];
            if(ans[N - 1]){
                char tmp = str[i + 1];
                str[i + 1] = '\0';  printf("%s\n",str + (i - N + 1));
                str[i + 1] = tmp;
            }
        }
    }
    return 0;
}
