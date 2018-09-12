#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<unistd.h>

#define input stdin
#define output stdout
#define SKIP { \
				while((ch=fgetc(fp))=='\n');\
    				if(feof(fp))\
      					break;\
    			fseek(fp,-1,SEEK_CUR); \
    		 }

				
			  

typedef struct dt
{
 char ch;
 char **meaning;
 int num;
 int count;
 struct dt *(*element);
}DT;


void init(DT *(*));
void acceptWord(char *(*));
void readfile(DT *(*),char *);
void insert(DT *(*),char *,int,int,char *(*));
void enterMeaning(DT *(*),int,char *(*));
void printMeaning(DT *(*));
void getMeaning(DT *(*),char *,int);
void display(DT *(*));
void delete(DT *(*root),char *word,int n);
void enterMeaning2(DT *(*));


void init(DT *(*root1))
{
  *root1=(DT*)malloc(sizeof(DT));
  (*root1)->count=0;
  (*root1)->element=(DT**)malloc(sizeof(DT*)*0);
  (*root1)->num=0;
}


void acceptWord(char *(*word))
{
  fprintf(output,"\nEnter Word:");
  fscanf(input,"%s",*word);
}

void readfile(DT *(*root),char *fname)
{
  FILE *fp;
  
  char *word,*num,**meanings,*mean,ch;
  int no,i;
  
  word=(char*)malloc(sizeof(char)*80);
  num=(char*)malloc(sizeof(char)*80);
  mean=(char*)malloc(sizeof(char)*255);
  
  fp=fopen(fname,"r");
  while(1)
  {
    SKIP
    fgets(word,80,fp);
    strtok(word,"\n");
    SKIP
    fgets(num,80,fp);
    no=atoi(num);
    meanings=(char**)malloc(sizeof(char*)*no);
    
    for(i=0;i<no;i++)
    {
      SKIP
      fgets(mean,255,fp);
      meanings[i]=(char*)malloc(sizeof(char)*strlen(mean));
      strcpy(meanings[i],mean);
    }
    
   //printf("\nWord:%s",word);
   //printf("\nNo:%d",no);
   for(i=0;i<no;i++)
      //printf("\nMeaning %d:%s",i,meanings[i]);
      insert(root,word,0,no,meanings);
  }
}


void insert(DT *(*root),char *word,int n,int no,char **meanings)
{
  DT *new;
  int i;
  //printf("\nIn insert:%d",word[n]);
  for(i=0;i<(*root)->count;i++)
  {
    if((*root)->element[i]->ch==word[n])
    { 
      new=(*root)->element[i];
      if(word[n+1]!='\0')
      {
        n++;
        insert(&new,word,n,no,meanings);
      }
     else
     { 
       if(new->meaning!=NULL)
          fprintf(output,"\nWord Exists");
        else
          enterMeaning(&new,no,meanings);
          
     }
      break;
   }
  }
  if(i==(*root)->count)
  {
    new=(DT*)malloc(sizeof(DT));
    new->ch=word[n];
    new->count=0;
    new->element=(DT**)malloc(sizeof(DT*)*0);
    (*root)->count++;
    (*root)->element=(DT**)realloc((*root)->element,sizeof(DT*)*((*root)->count));
    (*root)->element[((*root)->count)-1]=new;
    if(word[n+1]!='\0')
    {
      n++;
      insert(&new,word,n,no,meanings);
    }
    else
    {
      enterMeaning(&new,no,meanings);
    }
  }

}



void insert2(DT *(*root),char *word,int n)
{
  DT *new;
  int i;
  for(i=0;i<(*root)->count;i++)
  {
    if((*root)->element[i]->ch==word[n])
    { 
      new=(*root)->element[i];
      if(word[n+1]!='\0')
      {
        n++;
        insert2(&new,word,n);
      }
     else
     { 
       if(new->meaning!=NULL)
          fprintf(output,"\nWord Exists");
        else
          enterMeaning2(&new);
          
     }
      break;
   }
  }
  if(i==(*root)->count)
  {
    new=(DT*)malloc(sizeof(DT));
    new->ch=word[n];
    new->count=0;
    new->element=(DT**)malloc(sizeof(DT*)*0);
    (*root)->count++;
    (*root)->element=(DT**)realloc((*root)->element,sizeof(DT*)*((*root)->count));
    (*root)->element[((*root)->count)-1]=new;
    if(word[n+1]!='\0')
    {
      n++;
      insert2(&new,word,n);
    }
    else
    {
      enterMeaning2(&new);
    }
  }

}





void enterMeaning(DT *(*new),int n,char **meanings)
{
  int i;
  //printf("\nIn Enter Meaning:%s,%d",meanings[1],n);
  (*new)->num=n;
  (*new)->meaning=(char**)malloc(sizeof(char*)*n);
  for(i=0;i<n;i++)
  {
    (*new)->meaning[i]=(char*)malloc(sizeof(char)*strlen(meanings[i]));
    strcpy((*new)->meaning[i],meanings[i]);
  }
}



void enterMeaning2(DT *(*new))
{
  int i,n;
  char *mean,c;
  mean=(char*)malloc(sizeof(char)*255);
  fprintf(output,"\nEnter number of meanings:");
  fscanf(input,"%d",&n);
  (*new)->num=n;
  (*new)->meaning=(char**)malloc(sizeof(char*)*n);
  for(i=0;i<=n;i++)
  {
    			fprintf(output,"\nEnter Meaning:");
   				fgets(mean,255,input); 
   				(*new)->meaning[i-1]=(char*)malloc(sizeof(char)*strlen(mean));
   				strcpy((*new)->meaning[i-1],mean);
   				printf("\nMeaning:%s",(*new)->meaning[i-1]);
  }
}

void printMeaning(DT *(*root))
{
 int i;
 //printf("\nIn print Meaning");
 for(i=0;i<(*root)->num;i++)
   fprintf(output,"\nMeaning %d:%s",i+1,(*root)->meaning[i]);
}

void getMeaning(DT *(*root),char *word,int n)
{
  int i;
  DT *temp;
   //printf("\nget meaning");
   for(i=0;i<(*root)->count;i++)
  { 
    if((*root)->element[i]->ch==word[n])
    {
      temp=(*root)->element[i];
      if(word[n+1]!='\0')
      {
       n++;
       getMeaning(&temp,word,n);
      } 
      else
      {
        if(temp->num==0)
          fprintf(output,"\nNo word");
        else
          { //printf("\nOkay");
          printMeaning(&temp);
          }  
      }
      break;   
     } 
   
  }
  if(i==(*root)->count)
    { 
      fprintf(output,"\nWord doesn't exists");
	}
}

void display(DT *(*root))
{
 int i;
 DT *temp;
 //fprintf(output,"%c",(*root)->ch);

 //if(strlen((*root)->meaning)!=0)
   //  fprintf(output,"\t Meaning:%s\n\n",(*root)->meaning);

 if((*root)->count!=0)
 {
  for(i=0;i<(*root)->count;i++)
  {
   temp=(*root)->element[i];
   display(&temp);
  }
 }
 
}

void delete(DT *(*root),char *word,int n)
{
 int i,j;
 DT *temp;
 for(i=0;i<(*root)->count;i++)
 {
  if((*root)->element[i]->ch==word[n])
  {
    temp=(*root)->element[i];
    if(word[n+1]!='\0')
    {
      n++;
      delete(&temp,word,n);
    }
    else
    {
        
      if(temp->count==0)
      {
       for(j=i;j<((*root)->count-1);j++)
       {
        (*root)->element[j]=(*root)->element[j+1];
       }
        (*root)->count--;i--;
        (*root)->element=(DT**)realloc((*root)->element,sizeof(DT*)*((*root)->count));
      }
      else
      {
        temp->num=0;
        temp->meaning=(char**)malloc(sizeof(char*)*0);
      }
    }
    break;
  }  
 }
 
 if(i==(*root)->count)
    { 
      fprintf(output,"\nWord doesn't exists");
	}
}




int main(int num,char *arg[])
{
  DT *root1;
  int option;
  char *word;
  word=(char*)malloc(sizeof(char)*255);

  
  init(&root1);
  if(num<2)
  {
   fprintf(stdout,"\nError");
   return 0;
  } 
  else
   readfile(&root1,arg[1]);
   display(&root1);
  do
 {
  fprintf(output,"\n\n1.Insert\n2.Display\n3.Delete\nEnter option:");
  fscanf(input,"%d",&option);
  switch(option)
  {
   case 1:acceptWord(&word);
   		  insert2(&root1,word,0);
   		  break;
   case 2:acceptWord(&word);
   		  getMeaning(&root1,word,0);
   		  break;
   case 3:acceptWord(&word);
   		  delete(&root1,word,0);
   		  break;		   	  		  
  }
 }while(option<4);
  
return 0;   
}
