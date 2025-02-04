#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct LNode{
        int data;
        struct LNode*next;
}LNode,*LinkList;

bool InitList(LinkList &L){
    L=(LNode*)malloc(sizeof(LNode));
    if(L==NULL) return false;
    L->next=NULL;
    return true;
}
int Length(LinkList L){
    int len=0;//栈上的局部变量在函数结束的时候会被释放
    LNode*p=L;
    while(p->next!=NULL){
        p=p->next;
        len++;
    }
    return len;
}
LNode* GetElem(LinkList L,int i){
    LNode *p=L;
    int j=0;//初始下标为头结点
    while(p!=NULL&&j<i){
        p=p->next;
        j++;
    }
    //到这j=i-1,p指向第i-1个结点
    return p;
}
LNode*LocateElem(LinkList L,int e){
    LNode *p=L;
    while(p!=NULL&&p->data!=e)
        p=p->next;
    if(p==NULL) return NULL;
    return p;
}

bool ListInsert(LinkList&L,int i,int e){
    LNode*p=L;
    int j=0;
    while(p!=NULL&&j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL) return false;
    LNode*s=(LNode*)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return true;
}
bool ListDelete(LinkList &L,int i,int &e){
    LNode*p=L;
    int j=0;
    while(p->next!=NULL&&j<i-1){
        p=p->next;
        j++;
    }
    if(p->next==NULL||j>i-1)
        return false;
    LNode*q=p->next;
    e=q->data;
    p->next=q->next;
    free(q);
    return true;
}
LinkList List_HeadInsert(LinkList &L){
        LNode *s;int x;
        L=(LNode*)malloc(sizeof(LNode));
        L->next=NULL;
        cin>>x;
        while(x!=999){
            s=(LNode*)malloc(sizeof(LNode));
            s->data=x;
            s->next=L->next;
            L->next=s;
            cin>>x;
        }
        return L;
}
LinkList List_TailInsert(LinkList &L){
    int x;
    L=(LNode*)malloc(sizeof(LNode));
    L->next=NULL;
    LNode* r=L;
    LNode*s;
    cin>>x;
    while(x!=999){
        s=(LNode*)malloc(sizeof(LNode));
        s->data=x;
        s->next=NULL;
        r->next=s;
        r=s;
        cin>>x;
    }
    return L;
}
int main(){
    LinkList L;
    LNode*p;
    //尾插
    List_TailInsert(L);
    //求长度
    int length=Length(L);
    cout<<length<<endl;
    p=GetElem(L,2);//查找位序为2的结点，头结点位序是0
    cout<<"p结点的数据为:"<<p->data<<"地址为"<<p->next<<endl;
    p=LocateElem(L,9);//查找数值是9的结点
    if(p==NULL){
        cout<<"删除失败"<<endl;
    }
    else cout<<"p结点的数据为:"<<p->data<<"地址为"<<p->next<<endl;
    ListInsert(L,4,66);//在4号位插入data=66的结点
    int e=0;
    ListDelete(L,5,e);
    cout<<"删除的结点的data是:"<<e<<endl;

}