#include <stdio.h>

typedef struct {
    int a;
    int b;
} MyStruct;

void modifyStruct(MyStruct* p) {
    int u=15;

    p->a = u;  // 仅修改局部副本，不影响外部结构体
}

int main() {
    MyStruct s = {10, 20};
    modifyStruct(&s);
    printf("a = %d, b = %d\n", s.a, s.b); // 仍然是 a = 10, b = 20
    return 0;
}

