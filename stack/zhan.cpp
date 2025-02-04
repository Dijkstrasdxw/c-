#include<stdio.h>
typedef struct Sqstack{
    int data[100];
    int top;
}Sqstack;
bool Push(Sqstack &s, int x) {  // ✅ 引用传递
    if (s.top == 100 - 1) 
        return false; // 栈满

    s.top++;          
    s.data[s.top] = x; // 修改的是原来的 `s`
    return true;
}

int main() {
    Sqstack s = {{0}, -1}; // 初始化栈
    Push(s, 5);   // `s` 通过引用传递进去，内部修改会影响外部
    printf("%d\n", s.top);  // 变成 0，说明 `Push` 成功修改了 `s`
    return 0;
}
