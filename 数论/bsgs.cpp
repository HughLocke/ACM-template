//baby step,giant step 算法
//给定整数a,b,p,其中a,p互质，求一个非负整数x，使得a ^ x ≡ b (mod p)
LL bsgs(LL a,LL b,LL p){
    map<LL,LL> hash; hash.clear();
    b %= p;
    int t = (int)sqrt(p) + 1;
    for(int j = 0 ; j < t; j ++){
        int val = (LL)b * quick_power(a,j,p) % p;
        hash[val] = j;
    }
    a = quick_power(a,t,p);
    if(a == 0) return b == 0?1:-1;
    for(int i = 0 ; i <= t; i ++){
        int val = quick_power(a,i,p);
        int j = hash.find(val) == hash.end() ? -1:hash[val];
        if(j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;
}