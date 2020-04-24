#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define FINITY 5000
#define M 50
typedef struct ANode
{
    int adjvex;
    struct ANode *nextarc;
    int value;
}ArcNode;
typedef int Vertex;
typedef struct Vnode
{
    Vertex data;
    ArcNode *firstarc;
}VNode;
typedef VNode AdjList[M];
typedef struct
{
    AdjList adjlist;
    int n,e;
}ALGraph;

typedef char vertextype[M];
typedef int edgetype;
typedef struct
{
    int adjvex;
    vertextype data;
}VType;
typedef struct
{
    VType vexs[M];
    edgetype edges[M][M];
    int n,e;
}Mgraph;

void creat(Mgraph *g, int c)
{
    int i,j,k,w;
    FILE *rf;
    rf=fopen("Ljjz.txt","r");
    if(rf)
    {
        fscanf(rf,"%d%d\n",&g->n,&g->e);
        for(i=0;i<g->n;i++)
        {
            fscanf(rf,"%d",&g->vexs[i].adjvex);
        }
//        for(i=0;i<g->n;i++)
//        {
//            printf("%d",g->vexs[i]);
//        }
        for(i=0;i<g->n;i++)
            for(j=0;j<g->n;j++)
            if(i==j) g->edges[i][j]=0;
            else g->edges[i][j]=FINITY;
        for(k=0;k<g->e;k++)
        {
            fscanf(rf,"%d%d%d",&i,&j,&w);
            g->edges[i][j]=w;
            if(c==0) g->edges[j][i]=w;
        }
    }
    else g->n=0;
    fclose(rf);
}
void outPut(Mgraph *g)
{
    int i,j;
    for(i=0;i<g->n;i++)
    {
        for(j=0;j<g->n;j++)
            printf("%5d",g->edges[i][j]);
        printf("\n");
    }

}

void MatToList(Mgraph *g, ALGraph *G)
{
    int i,j;
    ArcNode *p;
    for(i=0;i<g->n;i++)
        G->adjlist[i].firstarc=NULL;
    for(i=0;i<g->n;i++)
    {
        for(j=g->n-1;j>=0;j--)
        if((g->edges[i][j]!=0)&&(g->edges[i][j]!=FINITY))
           {
            p=(ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex=j;
            p->value=g->edges[i][j];
            p->nextarc=G->adjlist[i].firstarc;/*ͷ�巨*/
            G->adjlist[i].firstarc=p;
           }
        G->adjlist[i].data=i;
    }

    G->n=g->n;
    G->e=g->e;
}
void DispAdj(ALGraph *G)
{
    int i;
    ArcNode *p;
    for(i=0;i<G->n;i++)
    {
        p=G->adjlist[i].firstarc;
        printf("%3d",G->adjlist[i].data);
        while(p!=NULL)
        {
            printf("->%3d,%d",p->adjvex,p->value);
            p=p->nextarc;
        }
        printf("\n");
    }
}
typedef int path_d[M];
typedef int dist_d[M];
typedef int path_f[M][M];
typedef int dist_f[M][M];
typedef int st_d[M];
typedef int st_f[M];

void floyd(Mgraph g,path_f p,dist_f d)
{
    int i,j,k;
    for(i=0;i<g.n;i++)
        for(j=0;j<g.n;j++)
        {
            d[i][j]=g.edges[i][j];
            if(i!=j&&d[i][j]<FINITY)
                p[i][j]=i;
            else p[i][j]=-1;
        }
    for(k=0;k<g.n;k++)
    {
        for(i=0;i<g.n;i++)
            for(j=0;j<g.n;j++)
            if(d[i][j]>d[i][k]+d[k][j])
           {
               d[i][j]=d[i][k]+d[k][j];
               p[i][j]=k;
           }
    }
}
void dijkstra(Mgraph g,int v0,path_d p,dist_d d)
{
	boolean final[M];
	int i,k,v,min;
	for(v=0;v<g.n;v++)
        {
            final[v]=FALSE;
            d[v]=g.edges[v0][v];
            if(d[v]<FINITY&&d[v]!=0)
                p[v]=v0;else p[v]=-1;
        }
            final[v0]=TRUE;d[v0]=0;
            for(i=1;i<g.n;i++)
                {
                    min=FINITY;
            for(k=0;k<g.n;++k)
                if(!final[k]&&d[k]<min)
                {
                    v=k;min=d[k];
                }
                    if(min==FINITY) return;
                    final[v]=TRUE;
                    for(k=0;k<g.n;++k)
                        if(!final[k]&&(min+g.edges[v][k]<d[k]))
                        {
                            d[k]=min+g.edges[v][k];
                            p[k]=v;
                        }
                 }
}
void print_gpd(Mgraph g,int fn,path_d p,dist_d d,st_d s)
{
    int pre,top=-1;
    s[++top]=fn;
    pre=p[fn];
    while(pre!=-1)
    {
        s[++top]=pre;
        pre=p[pre];
    }
//    while(top>=0)
//        printf("%5d",s[top--]);
}
void print_floyd(Mgraph g,int bgn,int fnl,path_f p,dist_f d, st_f s)
{
    int pre,top=-1;
//    printf("%5d",d[bgn][fnl]);
    s[++top]=fnl;
    pre=p[bgn][fnl];
    while(pre!=-1)
    {
        s[++top]=pre;
        pre=p[bgn][pre];
    }
//    while(top>=0)
//        printf("%5d",s[top--]);
}
int st_All[M];
int top_all;
int print_floyd_All(Mgraph g,int bgn,int fnl,path_f p,dist_f d,int top,st_f s)
{
    int pre;
//    printf("%5d",d[bgn][fnl]);
    s[top]=fnl;
    pre=p[bgn][fnl];
    while(pre!=-1)
    {
        s[++top]=pre;
        pre=p[bgn][pre];
    }
    s[++top]=bgn;
    return top;
}

int OverFloyd(Mgraph g,int AllPath[M],int Max,path_f p,dist_f d,st_f s)
{
    int j=Max;
    int i=Max-1;
    int sum=0,top=0;
    while(i>=0)
    {
//            printf("\n%d",top);
            top=print_floyd_All(g,AllPath[i],AllPath[j],p,d,top,s);
            sum=sum+d[AllPath[i--]][AllPath[j--]];

    }
    return sum;
}
