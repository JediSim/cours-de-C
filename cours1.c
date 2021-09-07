#include <stdio.h>
#include <stdlib.h>

// #include <cours1.h>

int remove_letter(char c, char s[])
{
    int i = 0;
    while(s[i] != 0)
    {
        s[i] = c=s[i]
    }
}

int is_in_string(char c, char s[])
{
    int i = 0;
    while(s[i] != 0)
    {
        if(s[i] == c)return 1;
        i++;
    }
    return 0;
}

int nb_words(char t[], char sep[])
{
    int w,l,n = 0;
    while(t[n] != 0)
    {
        if(t[n] == ' ')
        {
            l = w>0?l++:l;
            w = 0;
        }
        else w++;
        n++;
    }
    l = w>0?l++:l;
    return l;
}

int size_longest_word(char t[], char sep[])
{
    int w = 0;
    int l = 0;
    int n = 0;
    while(t[n] != 0)
    {
        if(t[n] == ' ')
        {
            l = w>l?w:l;
            w = 0;
        }
        else w++;
        n++;
    }
    l = w>l?w:l;
    return l;
}

int main()
{
    char sep[] = " ,;:!?.'";
    char str[] = "c'est une phrase de test";
    int s = size_longest_word(str,sep);
    int nb = nb_words(str,sep);
    printf("mot le plus long : %i \n",s);
    printf("nb mot : %i \n",nb);
    printf("Hello world!");
    return 0;
}
