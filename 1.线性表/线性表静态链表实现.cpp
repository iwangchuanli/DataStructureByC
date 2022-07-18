#include "string.h"
#include "ctype.h"      

#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000 /* �洢�ռ��ʼ������ */

typedef int Status;           /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char ElemType;        /* ElemType���͸���ʵ������������������Ϊchar */

œ
Status visit(ElemType c)
{
    printf("%c ",c);
    return OK;
}

/* ���Ա��ľ�̬�����洢�ṹ */
typedef struct 
{
    ElemType data;
    int cur;  /* �α�(Cursor) ��Ϊ0ʱ��ʾ��ָ�� */
} Component,StaticLinkList[MAXSIZE];


/* ��һά����space�и���������һ������������space[0].curΪͷָ�룬"0"��ʾ��ָ�� */
Status InitList(StaticLinkList space) 
{
	int i;
	for (i=0; i<MAXSIZE-1; i++)  
		space[i].cur = i+1;
	space[MAXSIZE-1].cur = 0; /* Ŀǰ��̬����Ϊ�գ����һ��Ԫ�ص�curΪ0 */
	return OK;
}


/* �����ÿռ������ǿգ��򷵻ط���Ľ���±꣬���򷵻�0 */
int Malloc_SSL(StaticLinkList space) 
{ 
	int i = space[0].cur;           		/* ��ǰ�����һ��Ԫ�ص�cur���ֵ */
	                                		/* ����Ҫ���صĵ�һ�����ÿ��е��±� */
	if (space[0]. cur)         
	    space[0]. cur = space[i].cur;       /* ����Ҫ�ó�һ��������ʹ���ˣ� */
	                                        /* �������Ǿ͵ð�������һ�� */
	                                        /* �������������� */
	return i;
}


/*  ���±�Ϊk�Ŀ��н����յ��������� */
void Free_SSL(StaticLinkList space, int k) 
{  
    space[k].cur = space[0].cur;    /* �ѵ�һ��Ԫ�ص�curֵ����Ҫɾ���ķ���cur */
    space[0].cur = k;               /* ��Ҫɾ���ķ����±긳ֵ����һ��Ԫ�ص�cur */
}

/* ��ʼ��������̬����L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
        i=L[i].cur;
        j++;
    }
    return j;
}

/*  ��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e   */
Status ListInsert(StaticLinkList L, int i, ElemType e)   
{  
    int j, k, l;   
    k = MAXSIZE - 1;   /* ע��k���������һ��Ԫ�ص��±� */
    if (i < 1 || i > ListLength(L) + 1)   
        return ERROR;   
    j = Malloc_SSL(L);   /* ��ÿ��з������±� */
    if (j)   
    {   
		L[j].data = e;   /* �����ݸ�ֵ���˷�����data */
		for(l = 1; l <= i - 1; l++)   /* �ҵ���i��Ԫ��֮ǰ��λ��k(����ʹ��ѭ��ʵ�� ��ΪcurΪ��һ���ڵ�) */
		   k = L[k].cur;           
		L[j].cur = L[k].cur;    /* �ѵ�i��Ԫ��֮ǰ��cur��ֵ����Ԫ�ص�cur */
		L[k].cur = j;           /* ����Ԫ�ص��±긳ֵ����i��Ԫ��֮ǰԪ�ص�ur */
		return OK;   
    } 
    return ERROR;   
}

/*  ɾ����L�е�i������Ԫ��   */
Status ListDelete(StaticLinkList L, int i)   
{ 
    int j, k;   
    if (i < 1 || i > ListLength(L))   
        return ERROR;   
    k = MAXSIZE - 1;   
    for (j = 1; j <= i - 1; j++)   
        k = L[k].cur;   
    j = L[k].cur;   
    L[k].cur = L[j].cur;   
    Free_SSL(L, j);   
    return OK;   
} 

Status ListTraverse(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
            visit(L[i].data);
            i=L[i].cur;
            j++;
    }
    return j;
    printf("\n");
    return OK;
}


int main()
{
    StaticLinkList L;
    Status i;
    i=InitList(L);
    printf("��ʼ��L��L.length=%d\n",ListLength(L));

    i=ListInsert(L,1,'F');
    i=ListInsert(L,1,'E');
    i=ListInsert(L,1,'D');
    i=ListInsert(L,1,'B');
    i=ListInsert(L,1,'A');

    printf("\n��L�ı�ͷ���β���FEDBA��\nL.data=");
    ListTraverse(L); 

    i=ListInsert(L,3,'C');
    printf("\n��L�ġ�B���롰D��֮����롰C����\nL.data=");
    ListTraverse(L); 

    i=ListDelete(L,1);
    printf("\n��L��ɾ����A����\nL.data=");
    ListTraverse(L); 

    printf("\n");

    return 0;
}


