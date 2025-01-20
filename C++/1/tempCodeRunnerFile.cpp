#include<iostream>
using namespace std;

const int N = 10;       // 定义最大路径长度
int path[N];            // 存储当前路径的数组
int n;                  // 路径长度
bool st[N];             // 标记数组，用于记录数字是否被使用

// 深度优先搜索 (DFS) 函数
void dfs(int u) {
    // 基本情况：如果路径长度等于 n，说明找到了一种排列
    if (u == n) {
        for (int i = 0; i < n; i++) cout << path[i]<<" "; // 打印当前路径
        cout << endl;
        return; // 结束当前递归调用
    }
    // 遍历所有可能的数字
    for (int i = 1; i <= n; i++) {
        // 如果数字 i 未被使用
        if (!st[i]) {
            path[u] = i;   // 将数字 i 放置在路径中的当前位
            st[i] = true; // 标记数字 i 为已使用
            dfs(u + 1);   // 递归调用，处理路径中的下一个位置
            st[i] = false; // 回溯：将数字 i 标记为未使用，以便后续的排列中可以使用
            path[u] = 0;   // 恢复路径数组中的当前位
        }
    }
}

int main() {
    cin >> n;  // 输入路径长度
    dfs(0);    // 从路径的第一个位置开始进行深度优先搜索
}