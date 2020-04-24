#include "stdio.h"
#include "stdlib.h"
#define NameSpace 500
typedef int SerialNum;
typedef char SpotName;
typedef char SpotDetail;
typedef struct
{
    SerialNum No;/*景点序号*/
    SpotName name[NameSpace];/*景点名称*/
    SpotDetail detail[NameSpace];/*景点详细信息，介绍*/
}Spot;/*景点的详细结构体*/
typedef Spot SpotMenu;
typedef struct
{
    SpotMenu place[NameSpace];
    int capacity;/*景点数量*/
}SpotList;/*这是一个存储景点的线性表*/
void readFile(SpotList *sp)
{
    FILE *rf;
    if((rf=fopen("info.txt","r"))==NULL)
        printf("NONE");/*读取文件失败了！！！*/
    else
    {

        fscanf(rf,"%d",&sp->capacity);/*首先读取它的大小*/
        int i=0;
//        for(i=0;i<sp.capacity;i++)
//            sp.place[i]=(SpotMenu)malloc(sizeof(Spot));

        while(i<sp->capacity)/*根据上面读到的大小*/
        {
            fscanf(rf,"%d\n",&sp->place[i].No);
            fgets(sp->place[i].name,NameSpace,rf);
            fgets(sp->place[i].detail,NameSpace,rf);
            i++;
        }
//        for(i=0;i<sp->capacity;i++)
//        {
//            printf("No:%d\nName:%sNote:%s",sp->place[i].No,sp->place[i].name,sp->place[i].detail);
//        }
        fclose(rf);
    }
}

void DisplayInfo(SpotList *sp,int v)/*这是个输出函数，用于检测读取是否成功*/
{
    if(v<sp->capacity&&v>=0)
        printf("No:%d\nName:%sNote:%s",sp->place[v].No,sp->place[v].name,sp->place[v].detail);
    else printf("ERROR");
}
