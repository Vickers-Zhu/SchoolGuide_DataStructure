#include "stdio.h"
#include "math.h"
#define Maxi 1000
//int visited[M];
//int dfs_array[M];
//int dfs_clock=0;/*������Щȫ�ֱ���û����*/

int visit[M];
int dfs_seq[M];
int low_anc[M];
int parent[M];


int counter = 0;
int anti_cnt = 0;/*�ؽڵ������*/
int anti_array[M];/*��Щȫ�ֱ������ڱ���ؽڵ��*/
void choiseSort(int a[])
 { ////�������������ѡ������--����
    int n=-1;
    while(a[++n]!='\0');
    int i,j,k,temp;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        if(a[k]>a[j]) k=j;
        if(i!=k)
        {
            temp=a[i];
            a[i]=a[k];
            a[k]=temp;
        }
     }
}
 void DealArray(int a[])
 { //���ظ�Ԫ�ض��ã���Сֵ-1�����棬��Ϊ�ظ����ı��
    int i,j;
    int f;
    f=-1;
    for(i=0;a[i]!='\0';i++)
    {
        j=i+1;
        while(a[i]==a[j])
       {
           a[j]=f;
           j++;
       }
    }
}
void DeleArray(int a[])
{
    int i=-1,j,k;
    while(a[++i]!='\0');
    for(j=0;j<i;j++)
    {
        if(a[j]==-1)
            for(k=j+1;k<i;k++)
            a[k]=a[k-1];
    }
}
void dfs_sqc(ALGraph *g,int u)/*�ڶ�������ѡ��������*/
{
    int v;
    //��¼dfs��������


    //��¼�ڵ�u��������
    int children = 0;
    ArcNode *p = g->adjlist[u].firstarc;
    visit[u] = 1;

    //��ʼ��dfn��low
    dfs_seq[u]=low_anc[u] = counter++;
    for(; p != NULL; p = p->nextarc)
    {
        v = p->adjvex;

        //�ڵ�vδ�����ʣ���(u,v)Ϊ����
        if(!visit[v])
        {
            children++;
            parent[v] = u;
            dfs_sqc(g,v);
            low_anc[u] = min(low_anc[u], low_anc[v]);
            //case (1)
            if(parent[u] == -1 && children > 1)
            {
                anti_array[anti_cnt++]=u;
            }
            //case (2)
            if(parent[u] != -1 && low_anc[v] >= dfs_seq[u])
            {
                anti_array[anti_cnt++]=u;
            }
        }

        //�ڵ�v�ѷ��ʣ���(u,v)Ϊ�ر�
        else if(v != parent[u])
        {
            low_anc[u] = min(low_anc[u], dfs_seq[v]);
        }
    }
}
void arti(ALGraph* g,int v)
{
//    int i;
    parent[0]=-1;
    dfs_sqc(g,v);
}

int v[Maxi][Maxi],visiting[Maxi];
int cnt;
void pathl(Mgraph *g,int i,int j,int k)  /*ȷ��·���ϵ�k+1����������*/
{
	int s;
	if(v[cnt][k]==j)/*�ҵ�һ��·��*/
	{
	    cnt++;
//		printf("              ��%d��:",cnt);
		for(s=0;s<k;s++)/*���һ��·��*/
		{
	        v[cnt][s]=g->vexs[v[cnt-1][s]].adjvex;
		}
//		printf("%d\n",g->vexs[v[s]].adjvex);
		v[cnt][s]=g->vexs[v[cnt-1][s]].adjvex;
		/*·��������ֵ��1*/
	}
	s=0;
	while(s<g->n)
    {
		if(s!=i)/*��֤�ҵ����Ǽ�·��*/
		{
			if(g->edges[v[cnt][k]][s]!=FINITY&&visiting[s]==0)    /*��vk��vs֮���бߴ�����vsδ�����ʹ�*/
			{
				visiting[s]=1;/*�÷��ʱ�־λΪ1,���ѷ��ʵ�*/
				v[cnt][k+1]=s;/*������s���뵽v������*/
//				printf("999\n");
				pathl(g,i,j,k+1);/*�ݹ����֮*/
//				printf("222\n");
				visiting[s]=0;/*���÷��ʱ�־λΪ0����δ���ʵģ��Ա�ö����ܱ�����ʹ��*/
		    }
		}
        s++;
     }
}
void SearchAllpath(Mgraph g,int i,int j)/*��ѯ��������������·��*/
{
	int k;
    v[0][0]=i;
	cnt=0;/*��ʼ��·��������*/
    for(k=0;k<g.n;k++)
    {
	   visiting[k]=0;/*��ʼ��������ķ��ʱ�־λ������Ϊδ���ʹ���*/
    }
    pathl(&g,i,j,0);/*ͨ������path�������ҵ���vi��vj������·�������*//*���������������������·��*/
}
