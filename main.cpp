#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "Scenespot.h"
#include "Ljjz.h"
#include "EgeTest.h"
#include "Arti.h"

int main()
{
    int path_dij[M];
    int dist_dij[M];
    int path_flo[M][M];
    int dist_flo[M][M];
    int stack_dij[M];
    int stack_flo[M];
    int stack_All[M];
    SpotList sp;
    readFile(&sp);

//    int i,j=0,k,l;
//    int c[M];
//    char b[M]={'1','4','a','3',' ','6',' ','9'};
//    int beta;
//    int a[M]={1,5,2,3,6,'\0'};
//    int i=0;
    Mgraph g;
    ALGraph G;
    creat(&g,0);

////
//    printf("%d\n",v[37][0]);
//    for(i=0;i<=cnt;i++)
//    {
//        for(j=0;v[i][j]!=14;j++)
//            printf("%d->",v[i][j]);
//        printf("%d",v[i][j]);
//        printf("\n");
//    }

//    printf("%d",cnt);
//    while(v[i]!='\0')
//        printf("\n%d",v[i++]);
    MatToList(&g,&G);
    dijkstra(g,0,path_dij,dist_dij);
    floyd(g,path_flo,dist_flo);

//    printf("%d\n",anti_cnt);
//    for(i=0;i<=anti_cnt;i++)
//    {
//        printf("%5d\n",anti_array[i]);
//    }
////    j=LongNum(b,c);
//    OverFloyd(g,c,j,path_flo,dist_flo,stack_All);
//    beta=StTop(stack_All);
//    printf("%5d",beta);
//    for(i=0;i<beta;i++)
//        printf("\n%5d",stack_All[i]);
//    for(i=0;i<=j;i++)
//    {
//        printf("\n%10d",c[i]);
//    }


//
//    for(i=0;i<G.n;i++) printf("%5d",dfs_array[i]);
//    DispAdj(&G);
//    outPut(&g);
//
//
//
//    for(top=0;top<=g.n;top++)
//        printf("%5d",stack_dij[top]);
//
//
//    DisplayInfo(&sp,1);

    setinitmode(0,0,0);
    initgraph(1366, 768);
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    setfont(80, 0, "黑体");
    setbkmode(TRANSPARENT);
    outtextxy(523, 150, "中北大学");
    setcolor(EGERGB(0xff, 0x0, 0xff));
    setfont(60, 0, "黑体");
    outtextxy(503, 400, "校园导游系统");
    setcolor(EGERGB(0x40, 0xe0, 0xd0));
    setfont(40, 0, "黑体");
    outtextxy(563, 680, "按任意键继续");
    getch();
    cleardevice();

    char getK;
    int x,y,i,j;
    while(getK!=key_esc)
    {

        PIMAGE NUC = newimage();
        getimage(NUC, "NUC.jpg");
        putimage(10, 10, NUC);
        setcolor(EGERGB(0xEE,0x82,0xEE));
        setfont(40, 0, "黑体");
        char str[NameSpace];
        for(i=0;i<sp.capacity/2;i++)
        {
            sprintf(str,"%d %s",sp.place[i].No,sp.place[i].name);
            outtextxy(700, 20+i*40, str);
        }
        for(;i<sp.capacity;i++)
        {
            sprintf(str,"%d %s",sp.place[i].No,sp.place[i].name);
            outtextxy(900, 20+(i-sp.capacity/2)*40, str);
        }
        setcolor(EGERGB(0x0,0xFF,0x0));
        setfont(20, 0, "宋体");
        outtextxy(1200, 720, "按Esc退出");
        i=0;
        setcolor(EGERGB(0x00, 0xFF, 0xFF));
        setfont(40, 0, "微软雅黑");
        setbkmode(TRANSPARENT);
        outtextxy(200, 500, "A: 查询景点详细信息");
        outtextxy(650, 500, "S: 查询当前位置到任意景点路径及耗时");
        outtextxy(200, 550, "D: 任意两景点路径及耗时");
        outtextxy(650, 550, "F: 定制路径及耗时");
        outtextxy(200, 600, "G: 两个景点所有路径查询");
        outtextxy(650, 600, "H: 看一看关节点");
        getK=getch();
        if(getK=='a')
        {
            setviewport(30, 650, 1300, 700, 1);
            char str[NameSpace];
            inputbox_getline("请输入", "序号", str, NameSpace);
            x=readnumber(str);
            sprintf(str,"%d  %s    %s",sp.place[x].No,sp.place[x].name,sp.place[x].detail);
            setcolor(EGERGB(0x87,0xCE,0xFA));
            setfont(30, 0, "宋体");
            outtextxy(0,0,str);
            setviewport(0, 0, getwidth(), getheight(), 1);
        }
        else if(getK=='s')
        {
            setviewport(50, 650, 1300, 750, 1);
            char str1[NameSpace];
            char str2[NameSpace];
            inputbox_getline("请输入", "序号", str1, NameSpace);
            x=readnumber(str1);
            sprintf(str1,"需要花费时间：%d",dist_dij[x]);
            setcolor(EGERGB(0x87,0xCE,0xFA));
            setfont(30, 0, "宋体");
            outtextxy(0,0,str1);

            print_gpd(g,x,path_dij,dist_dij,stack_dij);
            int counter=0,top_dij=StTop(stack_dij);
            while(top_dij>0)
            {
                sprintf(str2,"%d->",stack_dij[top_dij--]);
                outtextxy(30+(counter++)*70,30,str2);
            }
            sprintf(str2,"%d",stack_dij[top_dij--]);
            outtextxy(30+(counter++)*70,30,str2);
            setviewport(0, 0, getwidth(), getheight(), 1);
        }
        else if(getK=='d')
        {
            setviewport(50, 650, 1300, 750, 1);
            char str1[NameSpace];
            char str2[NameSpace];
            char str3[NameSpace];
            inputbox_getline("请输入", "序号1", str1, NameSpace);
            inputbox_getline("请输入", "序号2", str2, NameSpace);
            x=readnumber(str1);
            y=readnumber(str2);
            sprintf(str1,"需要花费时间：%d",dist_flo[x][y]);
            setcolor(EGERGB(0x87,0xCE,0xFA));
            setfont(30, 0, "宋体");
            outtextxy(0,0,str1);

            print_floyd(g,x,y,path_flo,dist_flo,stack_flo);
            int counter=0,top_flo=StTop(stack_flo);
            while(top_flo>0)
            {
                sprintf(str3,"%d->",stack_flo[top_flo--]);
                outtextxy(30+(counter++)*70,30,str3);
            }
            sprintf(str3,"%d",stack_flo[top_flo--]);
            outtextxy(30+(counter++)*70,30,str3);
            setviewport(0, 0, getwidth(), getheight(), 1);
        }
        else if(getK=='f')
        {
            setviewport(50, 650, 1300, 750, 1);
            char str1[NameSpace];
            char str2[NameSpace];
            int iti[NameSpace];
            int AllNum;
            int top_All;
            int counter=0;
            inputbox_getline("请输入", "空格隔开", str1, NameSpace);
            AllNum=LongNum(str1,iti);
            sprintf(str1,"需要花费时间：%d",OverFloyd(g,iti,AllNum,path_flo,dist_flo,stack_All));
            setcolor(EGERGB(0x87,0xCE,0xFA));
            setfont(30, 0, "宋体");
            outtextxy(0,0,str1);

            top_All=StTop(stack_All);
            printf("%5d",top_All);
            while(top_All>0)
            {
                sprintf(str2,"%d->",stack_All[top_All--]);
                outtextxy(30+(counter++)*70,30,str2);
            }
            sprintf(str2,"%d",stack_All[top_All]);
            outtextxy(30+(counter++)*70,30,str2);
            stack_All[0]='\0';/*全局变量初始化*/
            setviewport(0, 0, getwidth(), getheight(), 1);
        }
        else if(getK=='h')
        {
            setviewport(50, 650, 1300, 750, 1);
            char str1[NameSpace];
            char str2[NameSpace];
            int x;
            i=0;
            inputbox_getline("你选择从哪里遍历关节点", "回车确认", str2, NameSpace);
            x=readnumber(str2);
            arti(&G,x);
            setcolor(EGERGB(0x87,0xCE,0xFA));
            setfont(30, 0, "宋体");
            while(i<anti_cnt)
            {
                sprintf(str1,"%d",anti_array[i++]);
                outtextxy(30+(i)*70,30,str1);
            }
            anti_array[0]='\0';
            setviewport(0, 0, getwidth(), getheight(), 1);
        }
        else if(getK=='g')
        {
            char str1[NameSpace];
            char str2[NameSpace];
            char str3[NameSpace];
            inputbox_getline("请输入", "序号1", str1, NameSpace);
            inputbox_getline("请输入", "序号2", str2, NameSpace);
            x=readnumber(str1);
            y=readnumber(str2);
            cleardevice();
            SearchAllpath(g,x,y);
            setcolor(EGERGB(0x87,0xCE,0xFA));
            setfont(15, 0, "黑体");
            i=0;j=0;
            for(i=0;i<=cnt;i++)
            {
                for(j=0;v[i][j]!=y;j++)
                {
                    if(10+i*20<750)
                    {
                        sprintf(str3,"%d->",v[i][j]);
                        outtextxy(10+j*40,10+i*20,str3);
                    }
                    else
                    {
                        sprintf(str3,"%d->",v[i][j]);
                        outtextxy(693+j*40,i*20-730,str3);
                    }

                }
                    if(10+i*20<750)
                    {
                        sprintf(str3,"%d",v[i][j]);
                        outtextxy(10+j*40,10+i*20,str3);
                    }
                    else
                    {
                        sprintf(str3,"%d",v[i][j]);
                        outtextxy(693+j*40,i*20-730,str3);
                    }
            }
        }

    getK=getch();
    delimage(NUC);
    cleardevice();
}
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    setfont(80, 0, "黑体");
    setbkmode(TRANSPARENT);
    outtextxy(523, 150, "感谢使用");

    setcolor(EGERGB(0x0, 0xFF, 0xFF));
    setfont(50, 0, "黑体");
    outtextxy(450, 400, "组长：      朱继熠");
    outtextxy(450, 480, "组员：      梁亚亚");
    outtextxy(450, 560, "组员：      李静涵");
    outtextxy(450, 640, "组员：      涂大祥");
    getch();
    closegraph();
    return 0;
}
