#define METHOD_BIT
//#define METHOD_SEGMENT_TREE
//#define METHOD_BST
//#define METHOD_SPLAY_POINTER
//#define METHOD_SPLAY_INDEX
//#define METHOD_AVL
//#define METHOD_TREAP
//#define METHOD_PARTITION_TREE
//#define METHOD_SBT
//#define METHOD_PERSISTENT_SEGMENT_TREE

#ifdef METHOD_BIT
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;
const int MAXM = 50000 + 10;

int n, m;
int bit[MAXN];

inline int lowbit(int x)
{
    return x & (-x);
}

void build()
{
    memset(bit, 0, sizeof(bit));
}

void update(int x, int value)
{
    while (x <= n)
    {
        bit[x] += value;
        x += lowbit(x);
    }
}

int query(int x)
{
    int ret = 0;
    while (x > 0)
    {
        ret += bit[x];
        x -= lowbit(x);
    }
    return ret;
}

struct Node
{
    int value;
    int index;
    bool operator <(const Node &node) const
    {
        return value < node.value;
    }
} node[MAXN];
int pos[MAXN];
struct Query
{
    int l, r, k;
    int index;
    inline void input()
    {
        scanf("%d%d%d", &l, &r, &k);
    }
    bool operator <(const Query &query) const
    {
        return r < query.r;
    }
} queries[MAXM];
int ans[MAXN];

int find(int k, int n)
{
    int l = 1, r = n;
    while (true)
    {
        int mid = (l + r) >> 1;
        int val1 = query(mid - 1) + 1;
        int val2 = query(mid);
        if (k > val2)
        {
            l = mid + 1;
        }
        else if (k < val1)
        {
            r = mid - 1;
        }
        else
        {
            return node[mid].value;
        }
    }
}

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &node[i].value);
            node[i].index = i;
        }
        for (int i = 0; i < m; ++i)
        {
            queries[i].input();
            queries[i].index = i;
        }
        sort(node + 1, node + n + 1);
        int k = 1;
        for (int i = 1; i <= n; ++i)
        {
            if (i > 1)
            {
                if (node[i].value != node[i - 1].value)
                {
                    ++k;
                }
            }
            pos[node[i].index] = k;
            node[k] = node[i];
        }
        build();
        sort(queries, queries + m);
        int l = 1, r = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = l; j < queries[i].l && j <= r; ++j)
            {
                update(pos[j], -1);
            }
            for (int j = max(queries[i].l, r + 1); j <= queries[i].r; ++j)
            {
                update(pos[j], 1);
            }
            l = queries[i].l;
            r = queries[i].r;
            ans[queries[i].index] = find(queries[i].k, k);
        }
        for (int i = 0; i < m; ++i)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
#endif // METHOD_BIT

#ifdef METHOD_SEGMENT_TREE
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;
const int MAXM = 50000 + 10;

struct TreeNode
{
    int l, r;
    int sum;
} tree[MAXN * 3];

void build(int x, int l, int r)
{
    tree[x].l = l;
    tree[x].r = r;
    tree[x].sum = 0;
    if (l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build((x << 1) + 1, mid + 1, r);
}

void update(int x, int pos, int value)
{
    tree[x].sum += value;
    if (tree[x].l == tree[x].r)
    {
        return;
    }
    int mid = (tree[x].l + tree[x].r) >> 1;
    if (pos <= mid)
    {
        update(x << 1, pos, value);
    }
    else
    {
        update((x << 1) + 1, pos, value);
    }
}

int query(int x, int l, int r)
{
    if (l > r)
    {
        return 0;
    }
    if (tree[x].l == l && tree[x].r == r)
    {
        return tree[x].sum;
    }
    int mid = (tree[x].l + tree[x].r) >> 1;
    if (r <= mid)
    {
        return query(x << 1, l, r);
    }
    else if (l > mid)
    {
        return query((x << 1) + 1, l, r);
    }
    return query(x << 1, l, mid) + query((x << 1) + 1, mid + 1, r);
}

int n, m;
struct Node
{
    int value;
    int index;
    bool operator <(const Node &node) const
    {
        return value < node.value;
    }
} node[MAXN];
int pos[MAXN];
struct Query
{
    int l, r, k;
    int index;
    inline void input()
    {
        scanf("%d%d%d", &l, &r, &k);
    }
    bool operator <(const Query &query) const
    {
        return r < query.r;
    }
} queries[MAXM];
int ans[MAXN];

int find(int k, int n)
{
    int l = 1, r = n;
    while (true)
    {
        int mid = (l + r) >> 1;
        int val1 = query(1, 1, mid - 1) + 1;
        int val2 = query(1, 1, mid);
        if (k > val2)
        {
            l = mid + 1;
        }
        else if (k < val1)
        {
            r = mid - 1;
        }
        else
        {
            return node[mid].value;
        }
    }
}

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &node[i].value);
            node[i].index = i;
        }
        for (int i = 0; i < m; ++i)
        {
            queries[i].input();
            queries[i].index = i;
        }
        sort(node + 1, node + n + 1);
        int k = 1;
        for (int i = 1; i <= n; ++i)
        {
            if (i > 1)
            {
                if (node[i].value != node[i - 1].value)
                {
                    ++k;
                }
            }
            pos[node[i].index] = k;
            node[k] = node[i];
        }
        build(1, 1, k);
        sort(queries, queries + m);
        int l = 1, r = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = l; j < queries[i].l && j <= r; ++j)
            {
                update(1, pos[j], -1);
            }
            for (int j = max(queries[i].l, r + 1); j <= queries[i].r; ++j)
            {
                update(1, pos[j], 1);
            }
            l = queries[i].l;
            r = queries[i].r;
            ans[queries[i].index] = find(queries[i].k, k);
        }
        for (int i = 0; i < m; ++i)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
#endif // METHOD_SEGMENT_TREE

#ifdef METHOD_BST
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;
const int MAXM = 50000 + 10;

class BST
{
public:
    BST()
    {
    }
    void clear()
    {
        root = -1;
        nodeNum = 0;
    }
    void insert(int value)
    {
        if (-1 == root)
        {
            initNode(value);
            root = nodeNum++;
            return;
        }
        int index = root;
        while (true)
        {
            int dir = value >= node[index].value;
            if (-1 == node[index].child[dir])
            {
                node[index].child[dir] = nodeNum;
                break;
            }
            else
            {
                index = node[index].child[dir];
            }
        }
        initNode(value);
        node[nodeNum++].parent = index;
        while (-1 != index)
        {
            pushUp(index);
            index = node[index].parent;
        }
    }
    void remove(int value)
    {
        int index = root;
        while (node[index].value != value)
        {
            int dir = value >= node[index].value;
            index = node[index].child[dir];
        }
        int parent = node[index].parent;
        int left = node[index].child[LEFT];
        int right = node[index].child[RIGHT];
        if (-1 == left)
        {
            if (-1 == parent)
            {
                node[right].parent = -1;
                root = right;
            }
            else
            {
                int dir = node[parent].child[RIGHT] == index;
                node[parent].child[dir] = right;
                node[right].parent = parent;
            }
            index = parent;
        }
        else if (-1 == right)
        {
            if (-1 == parent)
            {
                node[left].parent = -1;
                root = left;
            }
            else
            {
                int dir = node[parent].child[RIGHT] == index;
                node[parent].child[dir] = left;
                node[left].parent = parent;
            }
            index = parent;
        }
        else if (-1 == node[left].child[RIGHT])
        {
            if (-1 == parent)
            {
                root = left;
            }
            else
            {
                int dir = node[parent].child[RIGHT] == index;
                node[parent].child[dir] = left;
            }
            node[left].parent = parent;
            node[left].child[RIGHT] = right;
            node[right].parent = left;
            index = left;
        }
        else
        {
            int leaf = left;
            while (-1 != node[leaf].child[RIGHT])
            {
                leaf = node[leaf].child[RIGHT];
            }
            int child = node[leaf].parent;
            node[child].child[RIGHT] = node[leaf].child[LEFT];
            if (-1 != node[leaf].child[LEFT])
            {
                node[node[leaf].child[LEFT]].parent = child;
            }
            if (-1 == parent)
            {
                root = leaf;
            }
            else
            {
                int dir = node[parent].child[RIGHT] == index;
                node[parent].child[dir] = leaf;
            }
            node[leaf].parent = parent;
            node[leaf].child[LEFT] = left;
            node[left].parent = leaf;
            node[leaf].child[RIGHT] = right;
            node[right].parent = leaf;
            index = child;
        }
        while (-1 != index)
        {
            pushUp(index);
            index = node[index].parent;
        }
    }
    int query(int k)
    {
        int index = root;
        while (k != getChildNum(index, LEFT) + 1)
        {
            if (k <= getChildNum(index, LEFT))
            {
                index = node[index].child[LEFT];
            }
            else
            {
                k -= getChildNum(index, LEFT) + 1;
                index = node[index].child[RIGHT];
            }
        }
        return node[index].value;
    }
private:
    enum Dir
    {
        LEFT = 0,
        RIGHT = 1
    };
    struct Node
    {
        int parent;
        int child[2];
        int value;
        int size;
    } node[MAXN];
    int nodeNum, root;
    inline void initNode(int value)
    {
        node[nodeNum].parent = -1;
        node[nodeNum].child[LEFT] = -1;
        node[nodeNum].child[RIGHT] = -1;
        node[nodeNum].value = value;
        node[nodeNum].size = 1;
    }
    inline int getChildNum(int index, int dir)
    {
        int child = node[index].child[dir];
        if (-1 == child)
        {
            return 0;
        }
        return node[child].size;
    }
    inline void pushUp(int index)
    {
        node[index].size = 1;
        node[index].size += getChildNum(index, LEFT);
        node[index].size += getChildNum(index, RIGHT);
    }
} bst;

int n, m;
int a[MAXN];
struct Query
{
    int left;
    int right;
    int k;
    int index;
    bool operator <(const Query &query) const
    {
        return right < query.right;
    }
} query[MAXM];
int ans[MAXM];

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; ++i)
        {
            query[i].index = i;
            scanf("%d%d%d", &query[i].left, &query[i].right, &query[i].k);
        }
        sort(query, query + m);
        int left = 1, right = 0;
        bst.clear();
        for (int i = 0; i < m; ++i)
        {
            for (int j = left; j <= right && j < query[i].left; ++j)
            {
                bst.remove(a[j]);
            }
            left = query[i].left;
            for (int j = max(right + 1, query[i].left); j <= query[i].right; ++j)
            {
                bst.insert(a[j]);
            }
            right = query[i].right;
            ans[query[i].index] = bst.query(query[i].k);
        }
        for (int i = 0; i < m; ++i)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
#endif // METHOD_BST

#ifdef METHOD_SPLAY_POINTER
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
const int MAXM = 50005;
const int INF = 0x7FFFFFFF;

class SplayTree
{
public:
    SplayTree()
    {
        nil = &_nil;
        _nil.value = 0;
        _nil.size = 0;
        _nil.parent = nil;
        _nil.child[LEFT] = nil;
        _nil.child[RIGHT] = nil;
    }

    inline void clear()
    {
        nodeNumber = 0;
        root = nil;
        insert(-INF);
        insert(INF);
    }

    inline void insert(const int value)
    {
        if(root == nil)
        {
            root = newNode(nil, value);
            return;
        }
        Node *x = root;
        while(true)
        {
            int dir = x->value < value;
            if(x->child[dir] == nil)
            {
                x->child[dir] = newNode(x, value);
                update(x);
                splay(x->child[dir], nil);
                return;
            }
            else
            {
                x = x->child[dir];
            }
        }
    }

    inline void remove(const int value)
    {
        int k = find(value);
        find(k - 1, nil);
        find(k + 1, root);
        root->child[RIGHT]->child[LEFT] = nil;
        update(root->child[RIGHT]);
        update(root);
    }

    inline int getKth(const int k)
    {
        find(k + 1, nil);
        return root->value;
    }

    inline void print()
    {
        printf("Splay Tree: \n");
        print(root);
        printf("\n");
    }
private:
    static const int LEFT = 0;
    static const int RIGHT = 1;
    struct Node
    {
        int value, size;
        Node *parent, *child[2];
    } _nil, node[MAXN];
    int nodeNumber;
    Node *root, *nil;

    inline Node *newNode(Node *parent, const int value)
    {
        node[nodeNumber].value = value;
        node[nodeNumber].size = 1;
        node[nodeNumber].parent = parent;
        node[nodeNumber].child[LEFT] = nil;
        node[nodeNumber].child[RIGHT] = nil;
        return &node[nodeNumber++];
    }

    inline void update(Node *x)
    {
        if(x == nil)
        {
            return;
        }
        x->size = x->child[LEFT]->size + x->child[RIGHT]->size + 1;
    }

    inline void rotate(Node *x, const int dir)
    {
        Node *p = x->parent;
        p->child[!dir] = x->child[dir];
        p->child[!dir]->parent = p;
        x->child[dir] = p;
        x->parent = p->parent;
        if(p->parent->child[LEFT] == p)
        {
            p->parent->child[LEFT] = x;
        }
        else
        {
            p->parent->child[RIGHT] = x;
        }
        p->parent = x;
        update(p);
        update(x);
        if(root == p)
        {
            root = x;
        }
    }

    inline void splay(Node *x, Node *y)
    {
        while(x->parent != y)
        {
            if(x->parent->parent == y)
            {
                if(x->parent->child[LEFT] == x)
                {
                    rotate(x, RIGHT);
                }
                else
                {
                    rotate(x, LEFT);
                }
            }
            else if(x->parent->parent->child[LEFT] == x->parent)
            {
                if(x->parent->child[LEFT] == x)
                {
                    rotate(x->parent, RIGHT);
                    rotate(x, RIGHT);
                }
                else
                {
                    rotate(x, LEFT);
                    rotate(x, RIGHT);
                }
            }
            else
            {
                if(x->parent->child[RIGHT] == x)
                {
                    rotate(x->parent, LEFT);
                    rotate(x, LEFT);
                }
                else
                {
                    rotate(x, RIGHT);
                    rotate(x, LEFT);
                }
            }
            update(x);
        }
    }

    inline void find(int k, Node *y)
    {
        Node *x = root;
        while(k != x->child[LEFT]->size + 1)
        {
            if(k <= x->child[LEFT]->size)
            {
                x = x->child[LEFT];
            }
            else
            {
                k -= x->child[LEFT]->size + 1;
                x = x->child[RIGHT];
            }
        }
        splay(x, y);
    }

    inline int find(const int value)
    {
        Node *x = root;
        int count = 0;
        while(true)
        {
            if(x->value == value)
            {
                return count + x->size - x->child[RIGHT]->size;
            }
            else if(x->value > value)
            {
                x = x->child[LEFT];
            }
            else
            {
                count += x->size - x->child[RIGHT]->size;
                x = x->child[RIGHT];
            }
        }
    }

    inline void print(Node *x)
    {
        if(x == nil)
        {
            return;
        }
        printf("%d: %d %d %d\n", x->value, x->child[LEFT]->value, x->child[RIGHT]->value, x->size);
        print(x->child[LEFT]);
        print(x->child[RIGHT]);
    }
} splay;

struct Interval
{
    int a, b, k, index;
    bool operator < (const Interval &interval) const
    {
        return b < interval.b;
    }
} interval[MAXM];
int pretty[MAXN];
int ans[MAXM];

int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d", &pretty[i]);
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d", &interval[i].a, &interval[i].b, &interval[i].k);
            interval[i].index = i;
        }
        sort(interval, interval + m);
        splay.clear();
        int a = 1, b = 0;
        for(int i=0;i<m;++i)
        {
            for(int j=a;j<interval[i].a && j<=b;++j)
            {
                splay.remove(pretty[j]);
            }
            for(int j=max(interval[i].a, b+1);j<=interval[i].b;++j)
            {
                splay.insert(pretty[j]);
            }
            a = interval[i].a;
            b = interval[i].b;
            ans[interval[i].index] = splay.getKth(interval[i].k);
        }
        for(int i=0;i<m;++i)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
#endif // METHOD_SPLAY_POINTER

#ifdef METHOD_SPLAY_INDEX
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100001 + 10;
const int MAXM = 50001 + 10;
const int INF = 0x7fffffff;

class Splay
{
public:
    Splay()
    {
        clear();
    }
    void clear()
    {
        root = -1;
        nodeNum = 0;
        insert(-INF, root);
        insert(INF, root);
    }
    void insert(int value)
    {
        insert(value, root);
    }
    void remove(int value)
    {
        int k = getK(value, root);
        int indexL = query(k - 1, root);
        splay(indexL, -1);
        int indexR = query(k + 1, root);
        splay(indexR, indexL);
        node[indexR].left = -1;
        update(indexR);
        update(indexL);
    }
    int query(int k)
    {
        int index = query(k + 1, root);
        return node[index].value;
    }
private:
    struct TreeNode
    {
        int parent;
        int left, right;
        int value;
        int size;
    } node[MAXN];
    int nodeNum, root;
    void initNode(int value)
    {
        node[nodeNum].parent = -1;
        node[nodeNum].left = -1;
        node[nodeNum].right = -1;
        node[nodeNum].value = value;
        node[nodeNum].size = 1;
    }
    int getLeftNum(int index)
    {
        if (-1 == node[index].left)
        {
            return 0;
        }
        return node[node[index].left].size;
    }
    int getRightNum(int index)
    {
        if (-1 == node[index].right)
        {
            return 0;
        }
        return node[node[index].right].size;
    }
    void update(int index)
    {
        node[index].size = 1;
        node[index].size += getLeftNum(index);
        node[index].size += getRightNum(index);
    }
    void insert(int value, int index)
    {
        if (-1 == root)
        {
            root = nodeNum;
            initNode(value);
            ++nodeNum;
            return;
        }
        while (true)
        {
            if (value < node[index].value)
            {
                if (-1 == node[index].left)
                {
                    node[index].left = nodeNum;
                    break;
                }
                else
                {
                    index = node[index].left;
                }
            }
            else
            {
                if (-1 == node[index].right)
                {
                    node[index].right = nodeNum;
                    break;
                }
                else
                {
                    index = node[index].right;
                }
            }
        }
        initNode(value);
        node[nodeNum].parent = index;
        splay(nodeNum, root);
        ++nodeNum;
    }
    int query(int k, int index)
    {
        while (k != getLeftNum(index) + 1)
        {
            if (k <= getLeftNum(index))
            {
                index = node[index].left;
            }
            else
            {
                k -= getLeftNum(index) + 1;
                index = node[index].right;
            }
        }
        return index;
    }
    int getK(int value, int index, int sum = 1)
    {
        while (value != node[index].value)
        {
            if (value < node[index].value)
            {
                index = node[index].left;
            }
            else
            {
                sum += getLeftNum(index) + 1;
                index = node[index].right;
            }
        }
        return sum + getLeftNum(index);
    }
    void rotateLeft(int index)
    {
        int left = node[index].left;
        int parent = node[index].parent;
        int ancestor = node[parent].parent;
        if (-1 == ancestor)
        {
            root = index;
        }
        else
        {
            if (node[ancestor].left == parent)
            {
                node[ancestor].left = index;
            }
            else
            {
                node[ancestor].right = index;
            }
        }
        node[index].parent = ancestor;
        node[index].left = parent;
        node[parent].parent = index;
        node[parent].right = left;
        if (-1 != left)
        {
            node[left].parent = parent;
        }
        update(parent);
        update(index);
    }
    void rotateRight(int index)
    {
        int right = node[index].right;
        int parent = node[index].parent;
        int ancestor = node[parent].parent;
        if (-1 == ancestor)
        {
            root = index;
        }
        else
        {
            if (node[ancestor].left == parent)
            {
                node[ancestor].left = index;
            }
            else
            {
                node[ancestor].right = index;
            }
        }
        node[index].parent = ancestor;
        node[index].right = parent;
        node[parent].parent = index;
        node[parent].left = right;
        if (-1 != right)
        {
            node[right].parent = parent;
        }
        update(parent);
        update(index);
    }
    void splay(int index, int pos)
    {
        while (node[index].parent != pos)
        {
            int parent = node[index].parent;
            int ancestor = node[parent].parent;
            if (ancestor == pos)
            {
                if (node[parent].left == index)
                {
                    rotateRight(index);
                }
                else
                {
                    rotateLeft(index);
                }
            }
            else
            {
                if (node[ancestor].left == parent)
                {
                    if (node[parent].left == index)
                    {
                        rotateRight(parent);
                        rotateRight(index);
                    }
                    else
                    {
                        rotateLeft(index);
                        rotateRight(index);
                    }
                }
                else
                {
                    if (node[parent].right == index)
                    {
                        rotateLeft(parent);
                        rotateLeft(index);
                    }
                    else
                    {
                        rotateRight(index);
                        rotateLeft(index);
                    }
                }
            }
        }
    }
};

int n, m;
int a[MAXN];
struct Query
{
    int left;
    int right;
    int k;
    int index;
    bool operator <(const Query &query) const
    {
        return right < query.right;
    }
} query[MAXM];
int ans[MAXM];
Splay splay;

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; ++i)
        {
            query[i].index = i;
            scanf("%d%d%d", &query[i].left, &query[i].right, &query[i].k);
        }
        sort(query, query + m);
        int left = 1, right = 0;
        splay.clear();
        for (int i = 0; i < m; ++i)
        {
            for (int j = left; j <= right && j < query[i].left; ++j)
            {
                splay.remove(a[j]);
            }
            left = query[i].left;
            for (int j = max(right + 1, query[i].left); j <= query[i].right; ++j)
            {
                splay.insert(a[j]);
            }
            right = query[i].right;
            ans[query[i].index] = splay.query(query[i].k);
        }
        for (int i = 0; i < m; ++i)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
#endif // METHOD_SPLAY_INDEX

#ifdef METHOD_AVL
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;
const int MAXM = 50000 + 10;

class AVL
{
public:
    AVL()
    {
    }
    void clear()
    {
        root = -1;
        nodeNum = 0;
    }
    void insert(int value)
    {
        if (-1 == root)
        {
            initNode(value);
            root = nodeNum++;
            return;
        }
        int index = root;
        while (true)
        {
            int dir = value >= node[index].value;
            if (-1 == node[index].child[dir])
            {
                node[index].child[dir] = nodeNum;
                break;
            }
            else
            {
                index = node[index].child[dir];
            }
        }
        initNode(value);
        node[nodeNum++].parent = index;
        while (-1 != index)
        {
            pushUp(index);
            balance(index);
            index = node[index].parent;
        }
    }
    void remove(int value)
    {
        int index = root;
        while (node[index].value != value)
        {
            int dir = value >= node[index].value;
            index = node[index].child[dir];
        }
        while (!isLeaf(index))
        {
            if (-1 != node[index].child[LEFT])
            {
                rotate(node[index].child[LEFT], RIGHT);
            }
            if (-1 != node[index].child[RIGHT])
            {
                rotate(node[index].child[RIGHT], LEFT);
            }
        }
        int parent = node[index].parent;
        if (-1 == parent)
        {
            root = -1;
        }
        else
        {
            int dir = node[parent].child[RIGHT] == index;
            node[parent].child[dir] = -1;
        }
        index = parent;
        while (-1 != index)
        {
            pushUp(index);
            balance(index);
            index = node[index].parent;
        }
    }
    int query(int k)
    {
        int index = root;
        while (k != getChildNum(index, LEFT) + 1)
        {
            if (k <= getChildNum(index, LEFT))
            {
                index = node[index].child[LEFT];
            }
            else
            {
                k -= getChildNum(index, LEFT) + 1;
                index = node[index].child[RIGHT];
            }
        }
        return node[index].value;
    }
private:
    enum Dir
    {
        LEFT = 0,
        RIGHT = 1
    };
    struct Node
    {
        int parent;
        int child[2];
        int value;
        int size;
        int height;
    } node[MAXN];
    int nodeNum, root;
    inline void initNode(int value)
    {
        node[nodeNum].parent = -1;
        node[nodeNum].child[LEFT] = -1;
        node[nodeNum].child[RIGHT] = -1;
        node[nodeNum].value = value;
        node[nodeNum].size = 1;
        node[nodeNum].height = 1;
    }
    inline int getChildNum(int index, int dir)
    {
        int child = node[index].child[dir];
        if (-1 == child)
        {
            return 0;
        }
        return node[child].size;
    }
    inline int getChildHeight(int index, int dir)
    {
        int child = node[index].child[dir];
        if (-1 == child)
        {
            return 0;
        }
        return node[child].height;
    }
    inline bool isLeaf(int index)
    {
        return -1 == node[index].child[LEFT] && -1 == node[index].child[RIGHT];
    }
    inline void pushUp(int index)
    {
        node[index].size = 1;
        node[index].size += getChildNum(index, LEFT);
        node[index].size += getChildNum(index, RIGHT);
        node[index].height = max(getChildHeight(index, LEFT), getChildHeight(index, RIGHT)) + 1;
    }
    inline void rotate(int index, int dir)
    {
        int child = node[index].child[dir];
        int parent = node[index].parent;
        int ancestor = node[parent].parent;
        if (-1 == ancestor)
        {
            root = index;
        }
        else
        {
            node[ancestor].child[node[ancestor].child[RIGHT] == parent] = index;
        }
        node[index].parent = ancestor;
        node[index].child[dir] = parent;
        node[parent].parent = index;
        node[parent].child[!dir] = child;
        if (-1 != child)
        {
            node[child].parent = parent;
        }
        pushUp(parent);
        pushUp(index);
    }
    void balance(int index)
    {
        int L = node[index].child[LEFT];
        int R = node[index].child[RIGHT];
        int heightL = getChildHeight(index, LEFT);
        int heightR = getChildHeight(index, RIGHT);
        if (heightL - heightR > 1)
        {
            int LR = node[L].child[RIGHT];
            int heightLL = getChildHeight(L, LEFT);
            int heightLR = getChildHeight(L, RIGHT);
            if (heightLL >= heightLR)
            {
                rotate(L, RIGHT);
            }
            else
            {
                rotate(LR, LEFT);
                rotate(LR, RIGHT);
            }
        }
        else if (heightR - heightL > 1)
        {
            int RL = node[R].child[LEFT];
            int heightRR = getChildHeight(R, RIGHT);
            int heightRL = getChildHeight(R, LEFT);
            if (heightRR >= heightRL)
            {
                rotate(R, LEFT);
            }
            else
            {
                rotate(RL, RIGHT);
                rotate(RL, LEFT);
            }
        }
    }
} avl;

int n, m;
int a[MAXN];
struct Query
{
    int left;
    int right;
    int k;
    int index;
    bool operator <(const Query &query) const
    {
        return right < query.right;
    }
} query[MAXM];
int ans[MAXM];

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; ++i)
        {
            query[i].index = i;
            scanf("%d%d%d", &query[i].left, &query[i].right, &query[i].k);
        }
        sort(query, query + m);
        int left = 1, right = 0;
        avl.clear();
        for (int i = 0; i < m; ++i)
        {
            for (int j = left; j <= right && j < query[i].left; ++j)
            {
                avl.remove(a[j]);
            }
            left = query[i].left;
            for (int j = max(right + 1, query[i].left); j <= query[i].right; ++j)
            {
                avl.insert(a[j]);
            }
            right = query[i].right;
            ans[query[i].index] = avl.query(query[i].k);
        }
        for (int i = 0; i < m; ++i)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
#endif // METHOD_AVL

#ifdef METHOD_TREAP
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;
const int MAXM = 50000 + 10;
const int INF = 0x7fffffff;

class Treap
{
public:
    Treap()
    {
    }
    void clear()
    {
        root = -1;
        nodeNum = 0;
    }
    void insert(int value)
    {
        if (-1 == root)
        {
            initNode(value);
            root = nodeNum++;
            return;
        }
        int index = root;
        while (true)
        {
            int dir = value >= node[index].value;
            if (-1 == node[index].child[dir])
            {
                node[index].child[dir] = nodeNum;
                break;
            }
            else
            {
                index = node[index].child[dir];
            }
        }
        initNode(value);
        node[nodeNum].parent = index;
        index = nodeNum++;
        while (-1 != index)
        {
            pushUp(index);
            int parent = node[index].parent;
            if (-1 != parent)
            {
                if (node[index].rank < node[parent].rank)
                {
                    int dir = node[parent].child[LEFT] == index;
                    rotate(index, dir);
                }
                else
                {
                    index = parent;
                }
            }
            else
            {
                break;
            }
        }
    }
    void remove(int value)
    {
        int index = root;
        while (node[index].value != value)
        {
            int dir = value >= node[index].value;
            index = node[index].child[dir];
        }
        while (!isLeaf(index))
        {
            int dir = getChildRank(index, RIGHT) <= getChildRank(index, LEFT);
            rotate(node[index].child[dir], !dir);
        }
        int parent = node[index].parent;
        if (-1 == parent)
        {
            root = -1;
            return;
        }
        else
        {
            int dir = node[parent].child[RIGHT] == index;
            node[parent].child[dir] = -1;
        }
        index = parent;
        while (index != -1)
        {
            pushUp(index);
            index = node[index].parent;
        }
    }
    int query(int k)
    {
        int index = root;
        while (k != getChildNum(index, LEFT) + 1)
        {
            if (k <= getChildNum(index, LEFT))
            {
                index = node[index].child[LEFT];
            }
            else
            {
                k -= getChildNum(index, LEFT) + 1;
                index = node[index].child[RIGHT];
            }
        }
        return node[index].value;
    }
private:
    enum Dir
    {
        LEFT = 0,
        RIGHT = 1
    };
    struct Node
    {
        int parent;
        int child[2];
        int value;
        int size;
        int rank;
    } node[MAXN];
    int nodeNum, root;
    inline void initNode(int value)
    {
        node[nodeNum].parent = -1;
        node[nodeNum].child[LEFT] = -1;
        node[nodeNum].child[RIGHT] = -1;
        node[nodeNum].value = value;
        node[nodeNum].size = 1;
        node[nodeNum].rank = rand();
    }
    inline int getChildNum(int index, int dir)
    {
        int child = node[index].child[dir];
        if (-1 == child)
        {
            return 0;
        }
        return node[child].size;
    }
    inline int getChildRank(int index, int dir)
    {
        int child = node[index].child[dir];
        if (-1 == child)
        {
            return INF;
        }
        return node[child].size;
    }
    inline bool isLeaf(int index)
    {
        return -1 == node[index].child[LEFT] &&
               -1 == node[index].child[RIGHT];
    }
    inline void pushUp(int index)
    {
        node[index].size = 1;
        node[index].size += getChildNum(index, LEFT);
        node[index].size += getChildNum(index, RIGHT);
    }
    inline void rotate(int index, int dir)
    {
        int child = node[index].child[dir];
        int parent = node[index].parent;
        int ancestor = node[parent].parent;
        if (-1 == ancestor)
        {
            root = index;
        }
        else
        {
            node[ancestor].child[node[ancestor].child[RIGHT] == parent] = index;
        }
        node[index].parent = ancestor;
        node[index].child[dir] = parent;
        node[parent].parent = index;
        node[parent].child[!dir] = child;
        if (-1 != child)
        {
            node[child].parent = parent;
        }
        pushUp(parent);
        pushUp(index);
    }
} treap;

int n, m;
int a[MAXN];
struct Query
{
    int left;
    int right;
    int k;
    int index;
    bool operator <(const Query &query) const
    {
        return right < query.right;
    }
} query[MAXM];
int ans[MAXM];

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; ++i)
        {
            query[i].index = i;
            scanf("%d%d%d", &query[i].left, &query[i].right, &query[i].k);
        }
        sort(query, query + m);
        int left = 1, right = 0;
        treap.clear();
        for (int i = 0; i < m; ++i)
        {
            for (int j = left; j <= right && j < query[i].left; ++j)
            {
                treap.remove(a[j]);
            }
            left = query[i].left;
            for (int j = max(right + 1, query[i].left); j <= query[i].right; ++j)
            {
                treap.insert(a[j]);
            }
            right = query[i].right;
            ans[query[i].index] = treap.query(query[i].k);
        }
        for (int i = 0; i < m; ++i)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
#endif // METHOD_TREAP

#ifdef METHOD_PARTITION_TREE
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
static const int MAXN = 100005;

struct TreeNode
{
    int l, r;
} node[MAXN<<2];

int leftNumber[20][MAXN];
int treeValue[20][MAXN];
int sortedArray[MAXN];

void buildTree(int l, int r, int c, int d)
{
    node[c].l = l;
    node[c].r = r;
    if (l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    int sameNumber = mid - l + 1;
    for (int i = l; i <= r; ++i)
    {
        if (treeValue[d][i] < sortedArray[mid])
        {
            --sameNumber;
        }
    }
    int pLeft = l, pRight = mid + 1;
    for ( int i = l; i <= r; ++i)
    {
        leftNumber[d][i] = i == l ? 0 : leftNumber[d][i - 1];
        if (treeValue[d][i] < sortedArray[mid])
        {
            treeValue[d + 1][pLeft++] = treeValue[d][i];
            ++leftNumber[d][i];
        }
        else if (treeValue[d][i] > sortedArray[mid])
        {
            treeValue[d + 1][pRight++] = treeValue[d][i];
        }
        else if (sameNumber)
        {
            treeValue[d + 1][pLeft++] = treeValue[d][i];
            ++leftNumber[d][i];
            --sameNumber;
        }
        else
        {
            treeValue[d + 1][pRight++] = treeValue[d][i];
        }
    }
    buildTree(l, mid, (c<<1)+1, d + 1);
    buildTree(mid+1, r, (c<<1)+2, d + 1);
}

int query(int l, int r, int c, int d, int k)
{
    if (l == r)
    {
        return treeValue[d][l];
    }
    int lLeft = l == node[c].l ? 0 : leftNumber[d][l-1];
    int rLeft = leftNumber[d][r];
    int totalLeft = rLeft - lLeft;
    if (k <= totalLeft)
    {
        return query(node[c].l + lLeft, node[c].l + rLeft - 1, (c << 1) + 1, d + 1, k);
    }
    int mid = (node[c].l + node[c].r) >> 1;
    int lRight = l - node[c].l - lLeft;
    int totalRight = r - l + 1 - totalLeft;
    return query(mid + lRight + 1, mid + lRight + totalRight, (c << 1) + 2, d + 1, k - totalLeft);
}

int main(int argc, char *argv[])
{
    int n,m,l,r,k;
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &sortedArray[i]);
            treeValue[0][i] = sortedArray[i];
        }
        sort(sortedArray, sortedArray + n);
        buildTree(0, n - 1, 0, 0);
        while (m--)
        {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", query(l - 1, r - 1, 0, 0, k));
        }
    }
    return 0;
}
#endif // METHOD_PARTITION_TREE

#ifdef METHOD_SBT
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;
const int MAXM = 50000 + 10;

class SBT
{
public:
    SBT()
    {
    }
    void clear()
    {
        root = -1;
        nodeNum = 0;
    }
    void insert(int value)
    {
        if (-1 == root)
        {
            initNode(value);
            root = nodeNum++;
            return;
        }
        int index = root;
        while (true)
        {
            int dir = value >= node[index].value;
            if (-1 == node[index].child[dir])
            {
                node[index].child[dir] = nodeNum;
                break;
            }
            else
            {
                index = node[index].child[dir];
            }
        }
        initNode(value);
        node[nodeNum++].parent = index;
        while (-1 != index)
        {
            pushUp(index);
            maintain(index);
            index = node[index].parent;
        }
    }
    void remove(int value)
    {
        int index = root;
        while (node[index].value != value)
        {
            int dir = value >= node[index].value;
            index = node[index].child[dir];
        }
        int parent = node[index].parent;
        int left = node[index].child[LEFT];
        int right = node[index].child[RIGHT];
        if (-1 == left)
        {
            if (-1 == parent)
            {
                node[right].parent = -1;
                root = right;
            }
            else
            {
                int dir = node[parent].child[RIGHT] == index;
                node[parent].child[dir] = right;
                node[right].parent = parent;
            }
            index = parent;
        }
        else if (-1 == right)
        {
            if (-1 == parent)
            {
                node[left].parent = -1;
                root = left;
            }
            else
            {
                int dir = node[parent].child[RIGHT] == index;
                node[parent].child[dir] = left;
                node[left].parent = parent;
            }
            index = parent;
        }
        else if (-1 == node[left].child[RIGHT])
        {
            if (-1 == parent)
            {
                root = left;
            }
            else
            {
                int dir = node[parent].child[RIGHT] == index;
                node[parent].child[dir] = left;
            }
            node[left].parent = parent;
            node[left].child[RIGHT] = right;
            node[right].parent = left;
            index = left;
        }
        else
        {
            int leaf = left;
            while (-1 != node[leaf].child[RIGHT])
            {
                leaf = node[leaf].child[RIGHT];
            }
            int child = node[leaf].parent;
            node[child].child[RIGHT] = node[leaf].child[LEFT];
            if (-1 != node[leaf].child[LEFT])
            {
                node[node[leaf].child[LEFT]].parent = child;
            }
            if (-1 == parent)
            {
                root = leaf;
            }
            else
            {
                int dir = node[parent].child[RIGHT] == index;
                node[parent].child[dir] = leaf;
            }
            node[leaf].parent = parent;
            node[leaf].child[LEFT] = left;
            node[left].parent = leaf;
            node[leaf].child[RIGHT] = right;
            node[right].parent = leaf;
            index = child;
        }
        while (-1 != index)
        {
            pushUp(index);
            index = node[index].parent;
        }
    }
    int query(int k)
    {
        int index = root;
        while (k != getChildNum(index, LEFT) + 1)
        {
            if (k <= getChildNum(index, LEFT))
            {
                index = node[index].child[LEFT];
            }
            else
            {
                k -= getChildNum(index, LEFT) + 1;
                index = node[index].child[RIGHT];
            }
        }
        return node[index].value;
    }
private:
    enum Dir
    {
        LEFT = 0,
        RIGHT = 1
    };
    struct Node
    {
        int parent;
        int child[2];
        int value;
        int size;
    } node[MAXN];
    int nodeNum, root;
    inline void initNode(int value)
    {
        node[nodeNum].parent = -1;
        node[nodeNum].child[LEFT] = -1;
        node[nodeNum].child[RIGHT] = -1;
        node[nodeNum].value = value;
        node[nodeNum].size = 1;
    }
    inline int getChildNum(int index, int dir)
    {
        int child = node[index].child[dir];
        if (-1 == child)
        {
            return 0;
        }
        return node[child].size;
    }
    inline int size(int index, int dir)
    {
        return getChildNum(index, dir);
    }
    inline int size(int index, int dir1, int dir2)
    {
        int child = node[index].child[dir1];
        if (-1 == child)
        {
            return 0;
        }
        return size(child, dir2);
    }
    inline void pushUp(int index)
    {
        node[index].size = 1;
        node[index].size += getChildNum(index, LEFT);
        node[index].size += getChildNum(index, RIGHT);
    }
    inline void rotate(int index, int dir)
    {
        int child = node[index].child[dir];
        int parent = node[index].parent;
        int ancestor = node[parent].parent;
        if (-1 == ancestor)
        {
            root = index;
        }
        else
        {
            node[ancestor].child[node[ancestor].child[RIGHT] == parent] = index;
        }
        node[index].parent = ancestor;
        node[index].child[dir] = parent;
        node[parent].parent = index;
        node[parent].child[!dir] = child;
        if (-1 != child)
        {
            node[child].parent = parent;
        }
        pushUp(parent);
        pushUp(index);
    }
    void maintain(int index)
    {
        if (-1 == index)
        {
            return;
        }
        int l = node[index].child[LEFT];
        int r = node[index].child[RIGHT];
        if (size(index, RIGHT, RIGHT) > size(index, LEFT))
        {
            rotate(r, LEFT);
            maintain(l);
            maintain(index);
        }
        else if (size(index, RIGHT, LEFT) > size(index, LEFT))
        {
            int rl = node[r].child[LEFT];
            rotate(rl, RIGHT);
            rotate(rl, LEFT);
            maintain(r);
            maintain(index);
            maintain(rl);
        }
        if (size(index, LEFT, LEFT) > size(index, RIGHT))
        {
            rotate(l, RIGHT);
            maintain(r);
            maintain(index);
        }
        else if (size(index, LEFT, RIGHT) > size(index, RIGHT))
        {
            int lr = node[l].child[RIGHT];
            rotate(lr, LEFT);
            rotate(lr, RIGHT);
            maintain(l);
            maintain(index);
            maintain(lr);
        }
    }
} sbt;

int n, m;
int a[MAXN];
struct Query
{
    int left;
    int right;
    int k;
    int index;
    bool operator <(const Query &query) const
    {
        return right < query.right;
    }
} query[MAXM];
int ans[MAXM];

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; ++i)
        {
            query[i].index = i;
            scanf("%d%d%d", &query[i].left, &query[i].right, &query[i].k);
        }
        sort(query, query + m);
        int left = 1, right = 0;
        sbt.clear();
        for (int i = 0; i < m; ++i)
        {
            for (int j = left; j <= right && j < query[i].left; ++j)
            {
                sbt.remove(a[j]);
            }
            left = query[i].left;
            for (int j = max(right + 1, query[i].left); j <= query[i].right; ++j)
            {
                sbt.insert(a[j]);
            }
            right = query[i].right;
            ans[query[i].index] = sbt.query(query[i].k);
        }
        for (int i = 0; i < m; ++i)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
#endif // METHOD_SBT

#ifdef METHOD_PERSISTENT_SEGMENT_TREE
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;

struct TreeNode
{
    int l, r;
    int lc, rc;
    int sum;
} tree[MAXN * 20];
int treeNum, root[MAXN];

int build(int l, int r)
{
    int x = treeNum++;
    tree[x].l = l;
    tree[x].r = r;
    tree[x].sum = 0;
    if (l == r)
    {
        return x;
    }
    int mid = (l + r) >> 1;
    tree[x].lc = build(l, mid);
    tree[x].rc = build(mid + 1, r);
    return x;
}

int update(int o, int pos, int val)
{
    int x = treeNum++;
    tree[x] = tree[o];
    tree[x].sum += val;
    if (tree[o].l == tree[o].r)
    {
        return x;
    }
    int mid = (tree[x].l + tree[x].r) >> 1;
    if (pos <= mid)
    {
        tree[x].lc = update(tree[o].lc, pos, val);
    }
    else
    {
        tree[x].rc = update(tree[o].rc, pos, val);
    }
    return x;
}

int query(int x, int o, int k)
{
    if (tree[x].l == tree[x].r)
    {
        return tree[x].l;
    }
    int num = tree[tree[x].lc].sum - tree[tree[o].lc].sum;
    if (k <= num)
    {
        return query(tree[x].lc, tree[o].lc, k);
    }
    return query(tree[x].rc, tree[o].rc, k - num);
}

int n, m, c;
int a[MAXN];
struct Node
{
    int val, index;
    bool operator <(const Node &node) const
    {
        return val < node.val;
    }
} node[MAXN];
int pos[MAXN];

int main()
{
    int l, r, k;
    while (~scanf("%d%d", &n, &m))
    {
        treeNum = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
            node[i].val = a[i];
            node[i].index = i;
        }
        sort(node + 1, node + 1 + n);
        pos[node[1].index] = 1;
        int j = 1;
        for (int i = 2; i <= n; ++i)
        {
            if (node[i].val == node[i - 1].val)
            {
                pos[node[i].index] = j;
            }
            else
            {
                pos[node[i].index] = ++j;
                node[j] = node[i];
            }
        }
        root[0] = build(1, j);
        for (int i = 1; i <= n; ++i)
        {
            root[i] = update(root[i - 1], pos[i], 1);
        }
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", node[query(root[r], root[l - 1], k)].val);
        }
    }
    return 0;
}
#endif // METHOD_PERSISTENT_SEGMENT_TREE
