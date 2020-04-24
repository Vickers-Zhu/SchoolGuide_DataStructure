#include "stdio.h"
#include "math.h"
#define Maxi 1000
//int visited[M];
//int dfs_array[M];
//int dfs_clock=0;/*上面这些全局变量没用上*/

int visit[M];
int dfs_seq[M];
int low_anc[M];
int parent[M];


int counter = 0;
int anti_cnt = 0;/*关节点计数器*/
int anti_array[M];/*这些全局变量用于保存关节点的*/
void choiseSort(int a[])
 { ////对数组进行排序（选择排序）--升序
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
 { //将重复元素都用（最小值-1）代替，作为重复数的标记
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
void dfs_sqc(ALGraph *g,int u)/*第二个参数选择遍历起点*/
{
    int v;
    //记录dfs遍历次序


    //记录节点u的子树数
    int children = 0;
    ArcNode *p = g->adjlist[u].firstarc;
    visit[u] = 1;

    //初始化dfn与low
    dfs_seq[u]=low_anc[u] = counter++;
    for(; p != NULL; p = p->nextarc)
    {
        v = p->adjvex;

        //节点v未被访问，则(u,v)为树边
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

        //节点v已访问，则(u,v)为回边
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
void pathl(Mgraph *g,int i,int j,int k)  /*确定路径上第k+1个顶点的序号*/
{
	int s;
	if(v[cnt][k]==j)/*找到一条路径*/
	{
	    cnt++;
//		printf("              第%d条:",cnt);
		for(s=0;s<k;s++)/*输出一条路径*/
		{
	        v[cnt][s]=g->vexs[v[cnt-1][s]].adjvex;
		}
//		printf("%d\n",g->vexs[v[s]].adjvex);
		v[cnt][s]=g->vexs[v[cnt-1][s]].adjvex;
		/*路径的条数值加1*/
	}
	s=0;
	while(s<g->n)
    {
		if(s!=i)/*保证找到的是简单路径*/
		{
			if(g->edges[v[cnt][k]][s]!=FINITY&&visiting[s]==0)    /*当vk与vs之间有边存在且vs未被访问过*/
			{
				visiting[s]=1;/*置访问标志位为1,即已访问的*/
				v[cnt][k+1]=s;/*将顶点s加入到v数组中*/
//				printf("999\n");
				pathl(g,i,j,k+1);/*递归调用之*/
//				printf("222\n");
				visiting[s]=0;/*重置访问标志位为0，即未访问的，以便该顶点能被重新使用*/
		    }
		}
        s++;
     }
}
void SearchAllpath(Mgraph g,int i,int j)/*查询两个景点间的所有路径*/
{
	int k;
    v[0][0]=i;
	cnt=0;/*初始化路径的条数*/
    for(k=0;k<g.n;k++)
    {
	   visiting[k]=0;/*初始化各顶点的访问标志位，即都为未访问过的*/
    }
    pathl(&g,i,j,0);/*通过调用path函数，找到从vi到vj的所有路径并输出*//*用来输出两个景点间的所有路径*/
}
