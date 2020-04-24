#include "stdio.h"
#include "stdlib.h"
#define NameSpace 500
typedef int SerialNum;
typedef char SpotName;
typedef char SpotDetail;
typedef struct
{
    SerialNum No;/*�������*/
    SpotName name[NameSpace];/*��������*/
    SpotDetail detail[NameSpace];/*������ϸ��Ϣ������*/
}Spot;/*�������ϸ�ṹ��*/
typedef Spot SpotMenu;
typedef struct
{
    SpotMenu place[NameSpace];
    int capacity;/*��������*/
}SpotList;/*����һ���洢��������Ա�*/
void readFile(SpotList *sp)
{
    FILE *rf;
    if((rf=fopen("info.txt","r"))==NULL)
        printf("NONE");/*��ȡ�ļ�ʧ���ˣ�����*/
    else
    {

        fscanf(rf,"%d",&sp->capacity);/*���ȶ�ȡ���Ĵ�С*/
        int i=0;
//        for(i=0;i<sp.capacity;i++)
//            sp.place[i]=(SpotMenu)malloc(sizeof(Spot));

        while(i<sp->capacity)/*������������Ĵ�С*/
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

void DisplayInfo(SpotList *sp,int v)/*���Ǹ�������������ڼ���ȡ�Ƿ�ɹ�*/
{
    if(v<sp->capacity&&v>=0)
        printf("No:%d\nName:%sNote:%s",sp->place[v].No,sp->place[v].name,sp->place[v].detail);
    else printf("ERROR");
}
