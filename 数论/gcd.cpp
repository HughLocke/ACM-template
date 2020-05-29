/*
1.lcm(S/a, S/b) = S/gcd(a, b)
2.gcd(a,b) = gcd(a,a - b) => gcd(a1,a2,a3...an) = gcd(a1,a2 - a1,a3 - a2,a4 - a3...an - an - 1);
3.gcd(a,lcm(b,c)) = lcm(gcd(a,b),gcd(a,c))
4.lcm(a,gcd(b,c)) = gcd(lcm(a,b),lcm(a,c))
5.在坐标里，将点(0, 0)和(a, b)连起来，通过整数坐标的点的数目（除了(0, 0)一点之外）就是gcd(a, b)。
6.gcd(a,b)=gcd(b, a mod b)
7.gcd(ab,m)=gcd(a,m) * gcd(b,m)
 */
int gcd(int a,int b) {
    return b==0?a:gcd(b,a%b);
}