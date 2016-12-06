/// {{{ general graph matching template by jacky860226
#define MAXN 505
vector<int> g[MAXN];//用vector存圖
int pa[MAXN] , match[MAXN] , st[MAXN] , S[MAXN] , vis[MAXN];
//pa表示交錯樹每個節點的父母節點
//match[u]=v表示u和v匹配，同時match[v]=u
//st[u]=B表示節點u屬於B這朵花
//S[u]={-1:沒走過 0:偶點 1:奇點}
//vis只用在找lca的時候檢查是不是走過了
int n;//n個點，編號為1 ~ n
inline int lca(int u,int v){
    //找花的花托，也就是交錯樹的lca
    //這種方法可以不用清空vis陣列就可以判斷有沒有經過
    static int t=0;
    for(++t;;swap(u,v)){
        if(u==0)continue;
        if(vis[u]==t)return u;
        vis[u]=t;
        u=st[pa[match[u]]];
    }
}
#define qpush(u) q.push(u),S[u]=0
//因為丟進queue裡的節點必為偶點，故把兩個操作寫在一起
inline void flower(int u,int v,int l,queue<int> &q){
    //這個函數用來設定花裡面所有點的pa
    while(st[u]!=l){
        pa[u]=v;//所有未匹配邊的pa都是雙向的
        v=match[u];
        if(S[v]==1)qpush(v);//所有奇點變偶點
        st[u]=st[v]=l;
        //注意這邊以花的花托代表這個花
        //所以 st[u]=st[v]=l 就是設定 u 和 v 屬於 l 這朵花
        u=pa[v];
    }
}
inline bool agument(int u,int v){
    //擴充增廣路
    for(int lst;u;v=lst,u=pa[v]){
        lst=match[u];
        match[u]=v;
        match[v]=u;
    }
}
inline bool bfs(int u){
    for(int i=1;i<=n;++i)st[i]=i;//自己一個點也是奇環
    memset(S+1,-1,sizeof(int)*n);
    queue<int>q;
    qpush(u);
    while(q.size()){
        u=q.front(),q.pop();
        for(size_t i=0;i<g[u].size();++i){
            int v=g[u][i];
            if(S[v]==-1){
                pa[v]=u;
                S[v]=1;
                if(!match[v]){//有增廣路直接擴充
                    agument(u,v);
                    return true;
                }
                qpush(match[v]);
            }else if(!S[v]&&st[v]!=st[u]){
                int l=lca(v,u);//遇到花，做花的處理
                flower(v,u,l,q);
                flower(u,v,l,q);
            }
        }
    }
    return false;
}
inline int blossom(){
    //ans表示最大匹配數量
    memset(pa+1,0,sizeof(int)*n);
    memset(match+1,0,sizeof(int)*n);
    int ans=0;
    for(int i=1;i<=n;++i)
        if(!match[i]&&bfs(i))++ans;
    return ans;
}
/// }}}
int main() {
    int t;
    RI(t);
    while(t--) {
        int m;
        RI(n , m);
        REP1(i , 1 , n) g[i].clear();
        REP(i , m) {
            int x , y;
            RI(x , y);
            x++ , y++;
            g[x].PB(y);
            g[y].PB(x);
        }
        PL(blossom());
    }
    return 0;
}
