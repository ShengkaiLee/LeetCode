class Solution {
private:
using ll = long long;
const static int maxn = 1e5+7;
//线段树维护区间和 涉及区间修改
ll tree[maxn<<2];//表示对应的区间和 有时候需要 -- /*fill(tree,tree+(maxn<<2), 0);*/
ll lazy[maxn<<2];//懒标记 表示当前区间的子区间还未被标记信息更新 这里是区间值的变动
int n,m;
int lc[maxn<<2],rc[maxn<<2];//动态开点
int root=1,cnt=1;//root用于传引用,cnt记录开点数目

inline void pushup(int &rt)
{   
    tree[rt]=tree[lc[rt]]+tree[rc[rt]]; //父节点与子节点的关系
}
inline void update_p(int &rt, int l,int r,int x,int v)  //单点更新 x 点, [l,r] -- 总 search space
{
    if(!rt) rt=++cnt;
    if(l == r)
    {
        tree[rt]=v;
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update_p(lc[rt],l,mid,x,v);
    else update_p(rc[rt],mid+1,r,x,v);
    pushup(rt);
}
inline void pushdown(int rt,int l,int r)
{
    if(lazy[rt])
    {
        if(!lc[rt]) lc[rt]=++cnt;//动态开点就这里不一样
        if(!rc[rt]) rc[rt]=++cnt;
        int mid=(l+r)>>1;
        lazy[lc[rt]]=lazy[rt];
        lazy[rc[rt]]=lazy[rt];
        tree[lc[rt]]=(mid-l+1)*lazy[rt];
        tree[rc[rt]]=(r-mid)*lazy[rt];
        lazy[rt]=0;
    }
}
inline void update(int &rt,int l,int r,int vl,int vr,int v)//rt start with root(1), [vl,vr] 区间每个数加v, [l,r] -- 总 search space
{
    if(r<vl || l>vr) return ;
    if(!rt) rt=++cnt;//动态开点 边访问边开点
    if(vl<=l && r<=vr) 
    {
        tree[rt]=(r-l+1)*v;
        lazy[rt]=v;
        return ;
    }
    int mid=(l+r)>>1;
    pushdown(rt,l,r);
    update(lc[rt],l,mid,vl,vr,v);
    update(rc[rt],mid+1,r,vl,vr,v);
    pushup(rt);
}
inline ll query(int rt,int l,int r,int vl,int vr) //rt start with 1, query [vl,vr] 区间, [l,r] -- 总 search space
{
    if(!rt) return 0;//这个节点没有开 直接pass
    if(r<vl || l>vr) return 0;
    if(vl<=l && r<=vr) return tree[rt];
    int mid=(l+r)>>1;
    pushdown(rt,l,r);
    return query(lc[rt],l,mid,vl,vr)+query(rc[rt],mid+1,r,vl,vr);
}

public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        for (const auto& v : updates) {
            update(root, 0, length-1, v[0], v[1], v[2]);
        }
        vector<int> res;
        for (int i = 0; i < length; i++) {
            res.push_back(query(1, 0, length-1, i, i));
        }
        return res;
    }
};