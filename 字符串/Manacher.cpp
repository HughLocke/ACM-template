//Manacher算法，O(n)求解最大回文子串
//Ma数组为变换后的串，Mp数组为变换后串的i位置为中心最长回文串
const int maxn = 11000010;
char str[maxn];
char Ma[maxn << 1];
int Mp[maxn << 1];
void Manacher(char s[],int len){
    int l = 0;
    Ma[l++] = '$';
    Ma[l++] = '#';
    for(int i = 0 ; i < len ; i ++){
        Ma[l++] = s[i];
        Ma[l++] = '#';
    }
    Ma[l] = 0;
    int mx = 0,id = 0;
    for(int i = 0 ; i < l ; i ++){
        Mp[i] = mx > i?min(Mp[2 * id - i],mx - i):1;
        while(Ma[i + Mp[i]] == Ma[i - Mp[i]]) Mp[i]++;
        if(i + Mp[i] > mx){
            mx = i + Mp[i];
            id = i;
        }
    }
}
int main(){
    scanf("%s",str);
    int len = strlen(str);
    Manacher(str,len);
    int ans = 0;
    for(int i = 0 ; i < 2 * len + 2; i ++) ans = max(ans,Mp[i] - 1);
    Pri(ans);
    return 0;
}