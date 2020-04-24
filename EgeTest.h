#include <stdio.h>
int readnumber(char f[])
{
    int i=0;
    int x=0;
    while(f[i]>='0'&&f[i]<='9')
    {
        x=x*10+f[i]-'0';
        i++;
    }
    return x;
}
int StTop(int st[])//ÇóÕ»³¤
{
    int i=0;
    while(st[i]!='\0')
        i++;
    return i-1;
}
int LongNum(char a[],int iti[])
{
    int i=0,j=0;
    while(a[i]!='\0')
    {

        if(a[i]>'9'||a[i]<'0')
        {
            i++;
        }
        else
        {
            iti[j++]=readnumber(a+i);
            while(a[i]<='9'&&a[i]>='0')
                i++;
        }
    }
    return j-1;
}
