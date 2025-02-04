#include <iostream>
#include <algorithm>
#include<cstring>
using namespace std;

const int N = 6010;
int n;
int e[N], ne[N],h[N],idx;
int happy[N];
int f[N][2];//第一维表示结点编号，第二维表示选了没选根节点
bool has_fa[N];
void dfs(int u) {
    f[u][1] = happy[u];
    for (int i = h[u]; i != -1; i = ne[i]) {//遍历当前结点的所有儿子
        int j = e[i];//取出儿子的编号
        dfs(j);//先递归算出所有子树的f值，再利用其求出根节点的f值
        f[u][0] += max(f[j][0],f[j][1]);//若根节点没选，则取选了儿子和没选儿子的以儿子为根节点的子树的f值
        f[u][1] += f[j][0];//若选了根节点，则不能再选儿子
    }
}
void add(int a, int b) {
    e[idx] = b;  ne[idx] = h[a];  h[a] = idx++;
}
int main() {
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) cin >> happy[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a>> b;
        add(b, a);
        has_fa[a] = true;
    }
    int root = 1;
    while (has_fa[root]) root++;//找出根节点的编号
    dfs(root);//深搜求f[root][0], f[root][1]
    int res = max(f[root][0], f[root][1]);
    cout << res;
    return 0;
}
