#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status; /* 存储状态码 */

/* 二叉树结构 */
typedef struct BiTNode{
	int data; /* 结点数据 */
	struct BiTNode *lchild, *rchild; /* 左右孩子指针 */
} BiTNode,*BiTree;

/* 
递归查找二叉排序树T中是否存在key 
指针f指向T的双亲，其初始调用值为NULL 
若查找成功，指针p指向该数据元素结点，并返回TRUE 
若查找失败, 指针p指向查找路径上访问的最后一个结点并返回FALSE	
*/ 
Status SearchBST(BiTree T,int key,BiTree f,BiTree *p){
	/* 查找失败 */
	if(!T)
	{
		*p = f; 
		return FALSE;
	}
	else if(key == T->data)/* 查找失败 */
	{
		*p = T;
		return TRUE; 
	}
	else if(key<T->data)
		return	SearchBST(T->lchild,key,T,p);/* 在左子树中继续查找 */
	else 
		return SearchBST(T->rchild,key,T,p);/* 在右子树中继续查找 */ 
} 

/*  当二叉排序树T中不存在关键字等于key的数据元素时， */
/*  插入key并返回TRUE，否则返回FALSE */
Status InsertBST(BiTree *T,int key){
	BiTree p,s;
	/* 从根节点开始查找 */ 
	/* 查找不成功 */
	if(!SearchBST(*T,key,NULL,&p)){
		s = (BiTree)malloc(sizeof(BiTNode));	
		s->data = key;
		s->lchild = s->rchild = NULL;  
		if (!p) 
			*T = s;			/*  插入s为新的根结点 */
		else if (key<p->data) 
			p->lchild = s;	/*  插入s为左孩子 */
		else 
			p->rchild = s;  /*  插入s为右孩子 */
		return TRUE; 
	}else{
		return FALSE;
	}
}

Status Delete(BiTree *p){
	
	BiTree q,s;
	if((*p)->rchild == NULL)/* 右子树空则只需重接它的左子树（待删结点是叶子也走此分支) */
	{
		q=*p; *p=(*p)->lchild; free(q);
	}else if((*p)->lchild == NULL)	/* 只需重接它的右子树 */
	{
		q=*p; *p=(*p)->rchild; free(q);
	}
	/* 左右子树均不为空 */
	else{
		/* 转左，然后向右到尽头（找待删结点的前驱） */
		q=*p;s=(*p)->lchild;
		while(s->rchild){
			q = s;
			s = s->rchild; 
		} 
		(*p)->data=s->data; /*  s指向被删结点的直接前驱（将被删结点前驱的值取代被删结点的值） */
		if(q!=*p)
			q->rchild=s->lchild; /*  重接q的右子树 */ 
		else
			q->lchild=s->lchild; /*  重接q的左子树 */
	}
	return TRUE;
} 

/* 删除实现：
①要删除的结点没有子节点：直接删除 
②要删除的结点只有左子树或右子树：删除结点并将他的子树移动到它的位置 
③要删除的结点右左子树与右子树：找到需要删除的结点p的前驱（后继）结点代替结点p 

从二叉排序树中删除结点p，并重接它的左或右子树。 */
Status DeleteBST(BiTree *T, int key){
	
	/* 不存在关键字等于key的数据元素 */
	if(!*T)
		return FALSE;
	else{
		/* 找到关键字等于key的数据元素 */ 
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

