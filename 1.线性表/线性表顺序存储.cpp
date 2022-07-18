
#include "stdio.h"    

#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;          /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;        /* ElemType���͸���ʵ������������������Ϊint */

Status visit(ElemType c){
 	printf("%d ",c);
	return OK;
} 

/* ���Ա����ݽṹ */
typedef struct{
	ElemType data[MAXSIZE]; /* ���飬�洢����Ԫ�� */ 
	int length;/* ���Ա�ǰ���� */ 
} SqList;

 
/* ��ʼ��˳�����Ա� (��Ҫ����Ԫ�ز���Ҫ����ָ���ַ) */
Status InitList(SqList *L){
	L->length = 0;
	return OK; 
}

/* �ж����Ա��Ƿ�ΪNULL */
Status ListEmpty(SqList L){
	if(L.length == 0)
		return TRUE;
	else 
		return FALSE; 
}

/* ������Ա� */
Status ClearList(SqList *L){
	L->length = 0;
	return OK; 
}

/* �������Ա�ĳ��� */
int ListLength(SqList L){
	return L.length;
}

/* ��e����L�е�i������Ԫ�ص�ֵ,ע��i��ָλ�ã���1��λ�õ������Ǵ�0��ʼ*/
Status GetElem(SqList L,int i,ElemType *e){
	if(L.length == 0 || i<1 || i>L.length)//�ж�λ���Ƿ��׼ 
		return ERROR;
	 *e = L.data[i-1]; 
}

/* ����L�е�1����e��ȵ�����Ԫ�ص�λ�� */
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

/* ��L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
Status ListInsert(SqList *L,int i ,ElemType e){
	int k;
	if(L->length == MAXSIZE)/*���Ա��Ѿ�����*/
		return ERROR;
	if(i<1 || i>L->length+1) /* i��λ�ò���ȷ */ 
		return ERROR;
	 /* ����������λ�ò��ڱ�β */
	if(i<=L->length){
		for(k=L->length-1;k>=i-1;k--)
			L->data[k+1] = L->data[k];
	} 
	L->data[i-1] = e;
	L->length++;
	
	return OK; 
}

/* ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status ListDelete(SqList *L,int i ,ElemType *e){
	int k;
	if(L->length == 0)/*���Ա�ΪNULL*/ 
		return ERROR;
	if(i<1 || i>L->length)/* λ��i����ȷ */
		return ERROR;
	*e = L->data[i-1];
	/* ���ɾ���������λ�� ��ɾ��λ�ú��Ԫ��ǰ�� */
	if(i<L->length){
		for(k = i; k<L->length;k++)
			L->data[k-1] = L->data[k];
	} 
	L->length--;
	return OK;
}

/* ���ζ�L��ÿ������Ԫ����� */
Status ListTraverse(SqList L){
	int i;
	for(i=0 ; i<L.length ;i++)
		visit(L.data[i]);
	printf("\n");
	return OK;
}

