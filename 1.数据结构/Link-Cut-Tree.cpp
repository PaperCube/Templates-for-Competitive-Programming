//1. access(x), 使根到x的链连接
//2. makeRoot(x), 使x成为根
//3. findRoot(x), 寻找x的根
//4. split(x, y), 把x到y的链单独拿出来，以y为根
//5. link(x, y), 连接边<x,y>
//6. cut(x, y), 切断边<x,y>
//7. check(x, y), 判断x与y是否连通
namespace LinkCutTree {
    int fa[MAXN], val[MAXN], ch[MAXN][2];
    int sum[MAXN], rev[MAXN], st[MAXN], siz[MAXN];
    void PushUp(int x) {
        sum[x] = val[x] ^ sum[ch[x][0]] ^ sum[ch[x][1]];
        siz[x] = 1 + siz[ch[x][0]] + siz[ch[x][1]];
    }
    void Rev(int x) {
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    void PushDown(int x) {
        if(rev[x]) {
            if(ch[x][0]) Rev(ch[x][0]);
            if(ch[x][1]) Rev(ch[x][1]);
            rev[x] ^= 1;
        }
    }
    bool nroot(int x) {
        return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
    }
    void rotate(int x) {
        int y = fa[x], z = fa[y], k = ch[y][1] == x, w = ch[x][!k];
        if(nroot(y)) ch[z][ch[z][1]==y] = x;
        ch[x][!k] = y; ch[y][k] = w;
        if(w) fa[w] = y; 
        fa[x] = z; fa[y] = x;
        PushUp(y); PushUp(x);
    }

    void Splay(int x) {
        int y = x, top = 0;
        st[++top] = y;
        while(nroot(y)) st[++top] = fa[y], y = fa[y];
        while(top) PushDown(st[top--]);
        while(nroot(x)) {
            int y = fa[x], z = fa[y];
            if(nroot(y)) rotate((ch[z][0] == y) ^ (ch[y][0] == x) ? x : y);
            rotate(x);
        }
        PushUp(x);
    }
    void access(int x) {
        for(int y = 0; x; y = x, x = fa[x])
            Splay(x), ch[x][1] = y, PushUp(x);
    }
    void makeRoot(int x) {
        access(x); Splay(x); Rev(x);
    }
    int findRoot(int x) {
        access(x); Splay(x); 
        while(ch[x][0]) PushDown(x), x = ch[x][0];
        Splay(x);
        return x;
    }
    void split(int x, int y) {
        makeRoot(x); access(y); Splay(y);
    }
    void link(int x, int y) {
        makeRoot(x);
        if(findRoot(y) != x) fa[x] = y;
    }
    void cut(int x, int y) {
        makeRoot(x);
        if(findRoot(y) == x && fa[y] == x && !ch[y][0]) 
            fa[y] = ch[x][1] = 0, PushUp(x);
    }
    bool check(int x, int y) {
		makeRoot(x);
		return findRoot(y) != x;
	}
}
