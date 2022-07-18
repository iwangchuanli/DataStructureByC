#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬����,��OK�� */
typedef char TElemType;
typedef enum {Link,Thread} PointerTag;/* Link = 0 :ָ��������Һ��� Thread = 1 �� ָ�����ǰ�����ߺ�̽�� */

typedef struct BiThrNode /* ���������������ݽṹ */ 
{
	TElemType data;/* ������� */ 
	struct BiThrNode *lchild, *rchild;/* ���Һ���ָ�� */
	PointerTag LTag;
	PointerTag RTag;		/* ���ұ�־ */
} BiThrNode , *BiThrTree;

TElemType Nil = '#'; /* �ַ����Կո��Ϊ�� */

Status visit(TElemType e)
{
	printf("%c ",e);
	return OK;
}

/* ������������� */
Status CreateBiThrTree(BiThrTree *T){
	TElemType h;
	scanf("%c",&h);
	
	if(h==Nil)
		*T = NULL; 
	else{
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if(!*T) exit(OVERFLOW);
		(*T)->data = h;/* ���ɸ��ڵ�(ǰ��) */
		CreateBiThrTree(&(*T)->lchild); /* �ݹ鹹�������� */
		if((*T)->lchild) /* ������ */
			(*T)->LTag=Link;
		CreateBiThrTree(&(*T)->rchild); /* �ݹ鹹�������� */
		if((*T)->rchild) /* ���Һ��� */
			(*T)->RTag=Link; 
	}
	return OK; 
}

BiThrTree pre; /* ȫ�ֱ���,ʼ��ָ��ոշ��ʹ��Ľ�� */

/* ��������������������� */
void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);/* �ݹ������仯 */
		if(!p->lchild)/* û�����ӽ�� */
		{
			p->LTag = Thread; /* ���Ϊ���� */
			p->lchild = pre; /* ����ָ��ָ��ǰ�� */	
		} 
		if(!pre->rchild)/*  ǰ��û���Һ���  */
		{
			pre->RTag = Thread; /* ���Ϊ���� */
			pre->rchild=p; /* ǰ���Һ���ָ��ָ����(��ǰ���p) */ 
		}
		pre = p;/* ����preΪָ��p��ǰ�� */ 
		InThreading(p->rchild);/* �ݹ������仯 */	
	}
}

/* �������������T,����������������,Thrtָ��ͷ��� */
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{ 
	*Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt)
		exit(OVERFLOW);
	(*Thrt)->LTag=Link; /* ��ͷ��� */
	(*Thrt)->RTag=Thread;
	(*Thrt)->rchild=(*Thrt); /* ��ָ���ָ */
	if(!T) /* ����������,����ָ���ָ */
		(*Thrt)->lchild=*Thrt;
	else
	{
		(*Thrt)->lchild=T;
		pre=(*Thrt);
		InThreading(T); /* ��������������������� */
		pre->rchild=*Thrt;
		pre->RTag=Thread; /* ���һ����������� */
		(*Thrt)->rchild=pre;
	}
	return OK;
}

/* �����������������T(ͷ���)�ķǵݹ��㷨 */
Status InOrderTraverse_Thr(BiThrTree T)
{ 
	BiThrTree p;
	p=T->lchild; /* pָ������ */
	while(p!=T)
	{ /* �������������ʱ,p==T */
		while(p->LTag==Link)
			p=p->lchild;
		if(!visit(p->data)) /* ������������Ϊ�յĽ�� */
			return ERROR;
		while(p->RTag==Thread&&p->rchild!=T)
		{
			p=p->rchild;
			visit(p->data); /* ���ʺ�̽�� */
		}
		p=p->rchild;
	}
	return OK;
}

int main()
{
	BiThrTree H,T;
	printf("�밴ǰ�����������(��:'ABDH##I##EJ###CF##G##')\n");
 	CreateBiThrTree(&T); /* ��ǰ����������� */
	InOrderThreading(&H,T); /* �������,������������������ */
	printf("�������(���)����������:\n");
	InOrderTraverse_Thr(H); /* �������(���)���������� */
	printf("\n");
	
	return 0;
}

















 
