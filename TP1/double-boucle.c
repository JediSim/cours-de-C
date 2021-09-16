#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert( char* str, int* data )
{
    for(int i=0;str[i]!=0;i++)
    {
        if (str[i]>='0' && str[i]<='9')
        {
            data[i]=str[i]-48;
        }
        else if(str[i]>='a' && str[i]<='z')
        {
            data[i]=str[i]-87;
        }
    }
    return 0;
}
void affiche_str(char str[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%c",str[i]);
    }
}
void affiche_int(int inte[],int n)
{

    for(int i=0;i<n;i++)
    {
        printf("%i",inte[i]);
    }
}
int max(int data[], int n)
{
    int res = data[0];
    for(int i=0;i<n;i++)
    {
        if (res<data[i])
        {
            res = data[i];
        }
    }
    return res;
}
int min(int data[], int n)
{
    int res = data[0];
    for(int i=0;i<n;i++)
    {
        if (res>data[i])
        {
            res = data[i];
        }
    }
    return res;
}
void affiche_histogramme( int* data, int n )
{
    int mini = min(data,n);
    for(int i=max(data,n);i>=mini;i--)
    {
        for(int j=0;j<n;j++)
        {
            if (data[j]==0)
            {
                printf(" ");
            }else if(data[j]==i)
            {
                printf("#");
            }else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    affiche_int(data,n);
}

void affiche_histogramme_style( int* data, int n )
{
    int mini = min(data,n);
    for(int i=max(data,n);i>=mini;i--)
    {
        for(int j=0;j<n-1;j++)
        {
            if(data[j]==i)
            {
                if(j>0)
                {
                    if (data[j]<data[j+1])
                    {
                        printf("/");
                    }else if(data[j-1]>data[j])
                    {
                        printf("\\");
                    }else if(data[j]==data[j+1])
                    {
                        printf("_");
                    }
                }else
                {
                    if (data[j]<data[j+1])
                    {
                        printf("/");
                    }else if(data[j]==data[j+1])
                    {
                        printf("_");
                    }
                }
            }else
            {
                printf(" ");
            }  
        }
        if(i==mini)
        {
            if(data[n-2]>data[n-1])
            {
                printf("\\");
            }else if(data[n-1]==data[n])
            {
                printf("_");
            }
        }
        
        printf("\n");
    }
    affiche_int(data,n);
}

int main( int argc, char* argv[] )
{
    char* str = argv[1];
    int len = strlen(str);
    printf("%i",len);
    int data[len];
    affiche_str(str,len);
    printf("\n");
    convert(str,data);
    printf("max : %i\n",max(data,len));
    printf("min : %i\n",min(data,len));
    printf("\n");
    affiche_histogramme_style(data,len);

    return 0;
}