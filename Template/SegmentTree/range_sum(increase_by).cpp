using ll = long long;
vector<ll> arr;
vector<ll> sum;
vector<ll> lazy;
int N;
inline ll leftson(ll fa)
{
    return fa << 1;
}

inline ll rightson(ll fa)
{
    return fa << 1 | 1;
}

void build(ll left, ll right, ll pos = 1)
{
    if (left == right)
    {   
        sum[pos] = arr[left];
        return;
    }
    build(left, (left + right) >> 1, leftson(pos));
    build(((left + right) >> 1) + 1, right, rightson(pos));
    sum[pos] = sum[leftson(pos)] + sum[rightson(pos)];
}

//更新下一层的值并下传lazy标志
void down(ll pos, ll current_left, ll current_right)
{
    //若该位置没有lazy标志或处于叶节点，直接返回
    if (!lazy[pos] || current_left == current_right) return;

    //更新两个子节点的值：加上lazy的值*区间长度
    ll ls = leftson(pos), rs = rightson(pos);
    ll mid = (current_left + current_right) >> 1;
    sum[ls] += lazy[pos] * (mid - current_left + 1);
    sum[rs] += lazy[pos] * (current_right - mid);

    //下传lazy标志并清空该位置的lazy标志
    lazy[ls] += lazy[pos];
    lazy[rs] += lazy[pos];
    lazy[pos] = 0;
}

// [left, right] -- query range, [current_left, current_right] -- search range
void update(ll left, ll right, ll current_left, ll current_right, ll val, ll pos = 1)
{
    //若当前搜索区间包含于修改区间，同步修改sum和lazy的值并返回
    if (left <= current_left && right >= current_right)
    {
        sum[pos] += val * (current_right - current_left + 1);//val*区间长度
        //注：由于本题中lazy标志是可以叠加的，因此使用+=而不是=
        lazy[pos] += val;
        return;
    }

    //否则，当前节点可能已有lazy标志，将标志下传
    down(pos, current_left, current_right);
    ll mid = (current_left + current_right) >> 1;
    if (right <= mid)
        update(left, right, current_left, mid, val, leftson(pos));
    else if (left > mid)
        update(left, right, mid + 1, current_right, val, rightson(pos));
    else
    {
        update(left, right, current_left, mid, val, leftson(pos));
        update(left, right, mid + 1, current_right, val, rightson(pos));
    }

    //回溯（同时加上lazy标志*区间长度的值）
    sum[pos] = sum[leftson(pos)] + sum[rightson(pos)];
}

// [left, right] -- query range, [current_left, current_right] -- search range
ll query(ll left, ll right, ll current_left, ll current_right, ll pos = 1)
{
	if (left <= current_left && right >= current_right)
	{
		return sum[pos];
	}
 
	//若不能直接返回区间值，则需下传lazy标志
	down(pos, current_left, current_right);
 
	ll mid = (current_left + current_right) >> 1;
	if (right <= mid)
		return query(left, right, current_left, mid, leftson(pos));
	else if (left > mid)
		return query(left, right, mid + 1, current_right, rightson(pos));
	else
		return query(left, right, current_left, mid, leftson(pos)) + query(left, right, mid + 1, current_right, rightson(pos));
}

int main() {
    arr.resize(N, 0); // query range(0, N);
    sum.resize((N<<2)+2, 0);
    lazy.resize((N<<2)+2, 0);
}