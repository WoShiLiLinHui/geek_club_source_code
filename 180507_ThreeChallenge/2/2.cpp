//*******************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void makestring(int, int);
char str1[1024];
char str2[1024];

int main(int argc, char **argv)
{
    memset(str1, 0x00, sizeof (char) * 1024);
	memset(str2, 0x00, sizeof (char) * 1024);
    int k,n;
	n=4;
	for(k=1;k<=n;k++)
		makestring(k,n);
    puts(str1);
	system("pause");
    return 0;
}   

void makestring(int i, int n)
{  // i counts the revert order,so (i=1) deals with the tail number
	if(i==1)
        sprintf(str1, "%d", n);//add the first char to str1
	if(i>1)
	{
        strcpy(str2, str1);
        sprintf(str1,"%d%s%s",n-i+1,str2,str2);//catenate number to string
	}
}
//*******************************