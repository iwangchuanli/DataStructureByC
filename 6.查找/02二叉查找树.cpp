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

typedef int Status; /* �洢״̬�� */

/* �������ṹ */
typedef struct BiTNode{
	int data; /* ������� */
	struct BiTNode *lchild, *rchild; /* ���Һ���ָ�� */
} BiTNode,*BiTree;

/* 
�ݹ���Ҷ���������T���Ƿ����key 
ָ��fָ��T��˫�ף����ʼ����ֵΪNULL 
�����ҳɹ���ָ��pָ�������Ԫ�ؽ�㣬������TRUE 
������ʧ��, ָ��pָ�����·���Ϸ��ʵ����һ����㲢����FALSE	
*/ 
Status SearchBST(BiTree T,int key,BiTree f,BiTree *p){
	/* ����ʧ�� */
	if(!T)
	{
		*p = f; 
		return FALSE;
	}
	else if(key == T->data)/* ����ʧ�� */
	{
		*p = T;
		return TRUE; 
	}
	else if(key<T->data)
		return	SearchBST(T->lchild,key,T,p);/* ���������м������� */
	else 
		return SearchBST(T->rchild,key,T,p);/* ���������м������� */ 
} 

/*  ������������T�в����ڹؼ��ֵ���key������Ԫ��ʱ�� */
/*  ����key������TRUE�����򷵻�FALSE */
Status InsertBST(BiTree *T,int key){
	BiTree p,s;
	/* �Ӹ��ڵ㿪ʼ���� */ 
	/* ���Ҳ��ɹ� */
	if(!SearchBST(*T,key,NULL,&p)){
		s = (BiTree)malloc(sizeof(BiTNode));	
		s->data = key;
		s->lchild = s->rchild = NULL;  
		if (!p) 
			*T = s;			/*  ����sΪ�µĸ���� */
		else if (key<p->data) 
			p->lchild = s;	/*  ����sΪ���� */
		else 
			p->rchild = s;  /*  ����sΪ�Һ��� */
		return TRUE; 
	}else{
		return FALSE;
	}
}

Status Delete(BiTree *p){
	
	BiTree q,s;
	if((*p)->rchild == NULL)/* ����������ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧) */
	{
		q=*p; *p=(*p)->lchild; free(q);
	}else if((*p)->lchild == NULL)	/* ֻ���ؽ����������� */
	{
		q=*p; *p=(*p)->rchild; free(q);
	}
	/* ������������Ϊ�� */
	else{
		/* ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ���� */
		q=*p;s=(*p)->lchild;
		while(s->rchild){
			q = s;
			s = s->rchild; 
		} 
		(*p)->data=s->data; /*  sָ��ɾ����ֱ��ǰ��������ɾ���ǰ����ֵȡ����ɾ����ֵ�� */
		if(q!=*p)
			q->rchild=s->lchild; /*  �ؽ�q�������� */ 
		else
			q->lchild=s->lchild; /*  �ؽ�q�������� */
	}
	return TRUE;
} 

/* ɾ��ʵ�֣�
��Ҫɾ���Ľ��û���ӽڵ㣺ֱ��ɾ�� 
��Ҫɾ���Ľ��ֻ������������������ɾ����㲢�����������ƶ�������λ�� 
��Ҫɾ���Ľ���������������������ҵ���Ҫɾ���Ľ��p��ǰ������̣���������p 

�Ӷ�����������ɾ�����p�����ؽ���������������� */
Status DeleteBST(BiTree *T, int key){
	
	/* �����ڹؼ��ֵ���key������Ԫ�� */
	if(!*T)
		return FALSE;
	else{
		/* �ҵ��ؼ��ֵ���key������Ԫ�� */ 
		if(key == (*T)->data)
			return  Delete(T);
		else if(key<(*T)->data)
			return DeleteBST(&(*T)->lchild,key);
		else 
			return DeleteBST(&(*T)->rchild,key);
	} 
}

int main(){
	int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	BiTree T=NULL;
	
		for(i=0;i<10;i++)
	{
		InsertBST(&T, a[i]);
	}	
	
	DeleteBST(&T,93);
	DeleteBST(&T,47);
	return 0;
} 

