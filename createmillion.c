#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

int main(void)
{
 char *str;
 str=malloc(sizeof(char)*80);
 FILE *fp;
 fp=fopen("b.txt","w");
 int i;
 for(i=0;i<1000000;i++)
 {
   sprintf(str, "%d", i);
   fputs(str,fp);
   fputc('\n',fp);
   fputs("3\n",fp);
   fputs("That confidence was certainly evident in the way Smith handled the winning play with 14 seconds left on the clock practice.\n",fp);	
   fputs("He directed and acted in plays every season and became known for exploring Elizabethan theatre practices intend.\n",fp);
   fputs("He had an adorable personality\n\n",fp);
 }
 fclose(fp);
 return 0;
 
}
