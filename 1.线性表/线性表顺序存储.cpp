
#include "stdio.h"    

#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;          /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;        /* ElemType类型根据实际情况而定，这里假设为int */

Status visit(ElemType c){
 	printf("%d ",c);
	return OK;
} 

/* 线性表数据结构 */
typedef struct{
	ElemType data[MAXSIZE]; /* 数组，存储数据元素 */ 
	int length;/* 线性表当前长度 */ 
} SqList;

 
/* 初始化顺序线性表 (需要操作元素才需要引入指针地址) */
Status InitList(SqList *L){
	L->length = 0;
	return OK; 
}

/* 判断线性表是否为NULL */
Status ListEmpty(SqList L){
	if(L.length == 0)
		return TRUE;
	else 
		return FALSE; 
}

/* 清空线性表 */
Status ClearList(SqList *L){
	L->length = 0;
	return OK; 
}

/* 返回线性表的长度 */
int ListLength(SqList L){
	return L.length;
}

/* 用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始*/
Status GetElem(SqList L,int i,ElemType *e){
	if(L.length == 0 || i<1 || i>L.length)//判断位置是否标准 
		return ERROR;
	 *e = L.data[i-1]; 
}

/* 返回L中第1个与e相等的数据元素的位序 */
int LocateElem(SqList L,ElemType e){
	int i;
	if(L.length == 0) 
		return 0;
	for(i=0 ; i<L.length ; i++){
		if(L.data[i] == e)
			break;
	}
	if(i>=L.length)
		return 0;
		
	return i+1;
} 

/* 在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(SqList *L,int i ,ElemType e){
	int k;
	if(L->length == MAXSIZE)/*线性表已经满了*/
		return ERROR;
	if(i<1 || i>L->length+1) /* i的位置不正确 */ 
		return ERROR;
	 /* 若插入数据位置不在表尾 */
	if(i<=L->length){
		for(k=L->length-1;k>=i-1;k--)
			L->data[k+1] = L->data[k];
	} 
	L->data[i-1] = e;
	L->length++;
	
	return OK; 
}

/* 删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList *L,int i ,ElemType *e){
	int k;
	if(L->length == 0)/*线性表为NULL*/ 
		return ERROR;
	if(i<1 || i>L->length)/* 位置i不正确 */
		return ERROR;
	*e = L->data[i-1];
	/* 如果删除不是最后位置 将删除位置后继元素前移 */
	if(i<L->length){
		for(k = i; k<L->length;k++)
			L->data[k-1] = L->data[k];
	} 
	L->length--;
	return OK;
}

/* 依次对L的每个数据元素输出 */
Status ListTraverse(SqList L){
	int i;
	for(i=0 ; i<L.length ;i++)
		visit(L.data[i]);
	printf("\n");
	return OK;
}

