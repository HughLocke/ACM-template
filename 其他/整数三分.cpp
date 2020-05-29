//整数三分
int solve(int x)
{
    int r = N, l = x;
    while (l < r - 1){
        int m = (l + r) >> 1;
        int mm = (r + m) >> 1;
        if (check(m, x) > check(mm, x)){
            l = m;
        }
        else{
            r = mm;
        }
    }
    return min(check(l, x), check(r, x));
}