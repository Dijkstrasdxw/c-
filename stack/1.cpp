#include <iostream>
using namespace std;
//不带头节点的 
typedef struct LinkNode{
	int data;//数据域
	struct LinkNode *next;//指针域 
}stackNode,*LinkStack;
void initStack(LinkStack &s)
{
	s=NULL;//不需要头节点 
}
int stackEmpty(LinkStack s)
{
	if(s==NULL)
		return 1;
	return 0;
}
int stackLength(LinkStack s)
{
	int sum=0;
	stackNode *temp=s;
	while(temp!=NULL)
	{
		sum++;
		temp=temp->next;
	}
	return sum;
}
void push(LinkStack &s,int e)
{
	stackNode *p=new stackNode;
	p->data=e;
	p->next=NULL;
	if(s==NULL)
		s=p;
	else
	{
		p->next=s;
		s=p;
	}
}
void pop(LinkStack &s,int &e)
{
	stackNode *p=new stackNode;
	if(s==NULL)
	{
		cout<<"栈为空，无法弹出"<<endl;
	}
	else
	{
		p=s;
		e=p->data;
		s=s->next;
		delete p;
		cout<<"成功弹出栈顶元素"<<endl;
	}
}
int top(LinkStack s)
{
	if(s==NULL)
		return -1;
	return s->data;
}
 
//销毁栈 
//所有节点
void DestoryStack(LinkStack &S)
{
	stackNode *p;
	while(S)
	{
		p=S;
		S=S->next;
		delete p;
	}
	S=NULL;
	cout<<"成功销毁"<<endl;
}
 
void menu()
{
	cout<<"**************************"<<endl;
	cout<<"1.初始化"<<endl;
	cout<<"2.判断栈是否为空"<<endl;
	cout<<"3.求栈的长度"<<endl;
	cout<<"4.销毁栈"<<endl;
	cout<<"5.入栈"<<endl;
	cout<<"6.出栈"<<endl;
	cout<<"7.求栈顶元素"<<endl;
	cout<<"8.退出"<<endl;
	cout<<"**************************"<<endl;
}
int main()
{
	LinkStack s;
	int e1,e2;
	initStack(s);
    push(s,4);
    push(s,7);
    pop(s,e1);
}