//表达式树
//我觉得说不定有一天会用到他
typedef pair<int, int>PII;
 
const int MX = 3e5 + 5;
 
char S[MX];
int LT[MX], RT[MX], rear, n;
LL A[MX];
string op[MX];
string last[10];
 
int build(int L, int R) {
    int cur = L, u;
    LL tmp = 0;
    while(cur <= R && isdigit(S[cur])) tmp = tmp * 10 + S[cur] - '0', cur++;
    if(cur == R + 1) {
        u = rear++;
        op[u] = ".";
        A[u] = tmp;
        return u;
    }
 
    int p[10], cnt = 0;
    for(int i = 1; i <= 9; i++) p[i] = -1;
    while(cur <= R) {
        string oper = "";
        if(!isdigit(S[cur])) {
            oper += S[cur];
            if(cur + 1 <= R) {
                if(S[cur] == '>' && S[cur + 1] == '=') oper += S[++cur];
                if(S[cur] == '<' && S[cur + 1] == '=') oper += S[++cur];
                if(S[cur] == '=' && S[cur + 1] == '=') oper += S[++cur];
                if(S[cur] == '!' && S[cur + 1] == '=') oper += S[++cur];
                if(S[cur] == '&' && S[cur + 1] == '&') oper += S[++cur];
                if(S[cur] == '|' && S[cur + 1] == '|') oper += S[++cur];
            }
        }
 
        if(oper == "(") cnt++;
        else if(oper == ")") cnt--;
        else if(cnt);
        else if(oper == "*" || oper == "/" || oper == "%") last[1] = oper, p[1] = cur;
        else if(oper == "+" || oper == "-") last[2] = oper, p[2] = cur;
        else if(oper == ">" || oper == ">=" || oper == "<" || oper == "<=") last[3] = oper, p[3] = cur;
        else if(oper == "==" || oper == "!=") last[4] = oper, p[4] = cur;
        else if(oper == "&") last[5] = oper, p[5] = cur;
        else if(oper == "^") last[6] = oper, p[6] = cur;
        else if(oper == "|") last[7] = oper, p[7] = cur;
        else if(oper == "&&") last[8] = oper, p[8] = cur;
        else if(oper == "||") last[9] = oper, p[9] = cur;
 
        cur++;
    }
    int w = -1, wi;
    for(int i = 9; i >= 1; i--) {
        if(p[i] != -1) {
            w = p[i];
            wi = i;
            break;
        }
    }
    if(w == -1) u = build(L + 1, R - 1);
    else {
        u = rear++;
        op[u] = last[wi];
        LT[u] = build(L, w - op[u].length());
        RT[u] = build(w + 1, R);
    }
    return u;
}
 
LL solve(int u) {
    if(op[u] == ".") return A[u];
    LL l = solve(LT[u]), r = solve(RT[u]);
    if(op[u] == "*") return l * r;
    if(op[u] == "/") return l / r;
    if(op[u] == "%") return l % r;
    if(op[u] == "+") return l + r;
    if(op[u] == "-") return l - r;
    if(op[u] == ">") return l > r;
    if(op[u] == ">=") return l >= r;
    if(op[u] == "<") return l < r;
    if(op[u] == "<=") return l <= r;
    if(op[u] == "==") return l == r;
    if(op[u] == "!=") return l != r;
    if(op[u] == "&") return l & r;
    if(op[u] == "^") return l ^ r;
    if(op[u] == "|") return l | r;
    if(op[u] == "&&") return l && r;
    if(op[u] == "||") return l || r;
}
 
int main() {
    //FIN;
    while(~scanf("%s", S)) {
        n = strlen(S);
        if(S[0] == '0' && n == 1) break;
 
        rear = 0;
        build(0, n - 1);
        printf("%lld\n", solve(0));
    }
    return 0;
}
