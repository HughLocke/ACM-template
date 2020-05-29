//康拓展开，将一个长度为n的全排列(1 - n)映射为一个数字
//如果要求当前全排列是第几个排列，则需要把数字 + 1
int cantor(int *a, int n)
{
    int ans = 0;
    for (int i = 0; i < n; i++){
        int x = 0;
        int c = 1, m = 1; //c记录后面的阶乘
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[i]) x++;
            m *= c;
            c++;
        }
        ans += x * m;
    }
    return ans;
}

//康托展开逆运算，将一个数字映射回全排列，模板假设排列小于10
static const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};   // 阶乘
void decantor(int x, int n){   //x转化为n个数字的全排列
    vector<int> v; // 存放当前可选数
    vector<int> a; // 所求排列组合
    for (int i = 1; i <= n; i++) v.push_back(i);
    for (int i = n; i >= 1; i--){
        int r = x % FAC[i - 1];
        int t = x / FAC[i - 1];
        x = r;
        sort(v.begin(), v.end()); // 从小到大排序
        a.push_back(v[t]);        // 剩余数里第t+1个数为当前位
        v.erase(v.begin() + t);   // 移除选做当前位的数
    }
}
