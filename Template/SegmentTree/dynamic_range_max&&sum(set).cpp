class Solution
{
private:
    using ll = long long;
    const static int maxn = 1e5 + 7;
    //线段树维护区间和 涉及区间修改
    ll MAX[maxn << 2];     //表示对应的区间max 有时候需要 -- /*fill(MAX,MAX+(maxn<<2), 0);*/
    ll lazyMAX[maxn << 2]; //懒标记 表示当前区间的子区间还未被标记信息更新 这里是区间值的变动
    ll SUM[maxn << 2];     //表示对应的区间和 有时候需要 -- /*fill(SUM,SUM+(maxn<<2), 0);*/
    ll lazySUM[maxn << 2]; //懒标记 表示当前区间的子区间还未被标记信息更新 这里是区间值的变动
    int n, m;
    int lc[maxn << 2], rc[maxn << 2]; //动态开点
    int root = 1, cnt = 1;            // root用于传引用,cnt记录开点数目

    inline void pushupMAX(int &rt)
    {
        MAX[rt] = max(MAX[lc[rt]], MAX[rc[rt]]); //父节点与子节点的关系
    }

    inline void pushdownMAX(int rt, int l, int r)
    {
        if (lazyMAX[rt])
        {
            if (!lc[rt])
                lc[rt] = ++cnt; //动态开点就这里不一样
            if (!rc[rt])
                rc[rt] = ++cnt;
            int mid = (l + r) >> 1;
            lazyMAX[lc[rt]] = lazyMAX[rt];
            lazyMAX[rc[rt]] = lazyMAX[rt];
            MAX[lc[rt]] = lazyMAX[rt];
            MAX[rc[rt]] = lazyMAX[rt];
            lazyMAX[rt] = 0;
        }
    }
    inline void updateMAX(int &rt, int l, int r, int vl, int vr, ll v) // rt start with root(1), [vl,vr] 区间每个数加v, [l,r] -- 总 search space
    {
        if (r < vl || l > vr)
            return;
        if (!rt)
            rt = ++cnt; //动态开点 边访问边开点
        if (vl <= l && r <= vr)
        {
            MAX[rt] = v;
            lazyMAX[rt] = v;
            return;
        }
        int mid = (l + r) >> 1;
        pushdownMAX(rt, l, r);
        updateMAX(lc[rt], l, mid, vl, vr, v);
        updateMAX(rc[rt], mid + 1, r, vl, vr, v);
        pushupMAX(rt);
    }
    inline ll queryMAX(int rt, int l, int r, int vl, int vr) // rt start with 1, query [vl,vr] 区间, [l,r] -- 总 search space
    {
        if (!rt)
            return LLONG_MIN; //这个节点没有开 直接pass
        if (r < vl || l > vr)
            return LLONG_MIN;
        if (vl <= l && r <= vr)
            return MAX[rt];
        int mid = (l + r) >> 1;
        pushdownMAX(rt, l, r);
        return max(queryMAX(lc[rt], l, mid, vl, vr), queryMAX(rc[rt], mid + 1, r, vl, vr));
    }

    inline void pushupSUM(int &rt)
    {
        SUM[rt] = SUM[lc[rt]] + SUM[rc[rt]]; //父节点与子节点的关系
    }
    inline void pushdownSUM(int rt, int l, int r)
    {
        if (lazySUM[rt])
        {
            if (!lc[rt])
                lc[rt] = ++cnt; //动态开点就这里不一样
            if (!rc[rt])
                rc[rt] = ++cnt;
            int mid = (l + r) >> 1;
            lazySUM[lc[rt]] = lazySUM[rt];
            lazySUM[rc[rt]] = lazySUM[rt];
            SUM[lc[rt]] = (mid - l + 1) * lazySUM[rt];
            SUM[rc[rt]] = (r - mid) * lazySUM[rt];
            lazySUM[rt] = 0;
        }
    }
    inline void updateSUM(int &rt, int l, int r, int vl, int vr, int v) // rt start with root(1), [vl,vr] 区间每个数加v, [l,r] -- 总 search space
    {
        if (r < vl || l > vr)
            return;
        if (!rt)
            rt = ++cnt; //动态开点 边访问边开点
        if (vl <= l && r <= vr)
        {
            SUM[rt] = (r - l + 1) * v;
            lazySUM[rt] = v;
            return;
        }
        int mid = (l + r) >> 1;
        pushdownSUM(rt, l, r);
        updateSUM(lc[rt], l, mid, vl, vr, v);
        updateSUM(rc[rt], mid + 1, r, vl, vr, v);
        pushupSUM(rt);
    }
    inline ll querySUM(int rt, int l, int r, int vl, int vr) // rt start with 1, query [vl,vr] 区间, [l,r] -- 总 search space
    {
        if (!rt)
            return 0; //这个节点没有开 直接pass
        if (r < vl || l > vr)
            return 0;
        if (vl <= l && r <= vr)
            return SUM[rt];
        int mid = (l + r) >> 1;
        pushdownSUM(rt, l, r);
        return querySUM(lc[rt], l, mid, vl, vr) + querySUM(rc[rt], mid + 1, r, vl, vr);
    }
    inline void init()
    {
        fill(MAX, MAX + (maxn << 2), 0);
        fill(SUM, SUM + (maxn << 2), 0);
    }
};