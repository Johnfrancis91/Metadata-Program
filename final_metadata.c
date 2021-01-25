#include<stdio.h>
#include<time.h>
#include<string.h>
void main(int argc,char** argv)
{
char  s[80];
FILE *fmeta,*fdata,*ftemp;
int i,j,k,c,n,length,count,d;
char ch;
i=0;
if(argc!=3)
{
	printf("usage is ./a.out metadata data......etc \n");
	return;
}
fdata=fopen(argv[2],"a+");
fmeta=fopen(argv[1],"r+");
if(fmeta==0)
	goto label;
count=0;
while((ch=fgetc(fmeta))!=-1)
{
	if (ch==':')
		count++;
	if(count==8)
	{
	   fscanf(fmeta,"%d",&n);
		break;
	}
}
fclose(fmeta);
d=0;
if(n<=9)
{
	c=0;
	ftemp=fopen("temp","w");
	while((ch=fgetc(fdata))!=-1)
		fputc(ch,ftemp);
	printf("enter the few lines of the text\n");
	gets(s);
	length=strlen(s);
	while(length>0&&n+c<10)
	{
		fputs(s,ftemp);
		fputs("\n",ftemp);
		c++;
		gets(s);
		length=strlen(s);
	}
	
	goto h1;
}

else if(n>9)
{
	ftemp=fopen("temp","w");
	printf("enter the few lines of the text\n");
	gets(s);
	length=strlen(s);
	c=0;
	while(length>0&&c<10)
	{
		fputs(s,ftemp);
		fputs("\n",ftemp);
		c++;
		gets(s);
		length=strlen(s);
	}
	if(c==10)
		goto h1;
	if(c<10)
	{
		while(d<c)
		{
			ch=fgetc(fdata);
			if(ch=='\n')
				d++;
		}
	}
	while((ch=fgetc(fdata))!=-1)
		fputc(ch,ftemp);

	h1:
	rewind(ftemp);
	rewind(fdata);
	fclose(fdata);
	fclose(ftemp);
	remove(argv[2]);
	rename("temp",argv[2]);
	
	goto here;
}


label:
printf("enter the fewlines of the text\n");
gets(s);
length=strlen(s);
c=0;
while(length>0&&c<10)
{ 
	fputs(s,fdata);
	fputs("\n",fdata);
	c++;
	gets(s);
	length=strlen(s);
}
rewind(fdata);
here:
	
fmeta=fopen(argv[1],"w+");
fputs("Storage version  :1.0\n",fmeta);
fputs("Record max size  :150\n",fmeta);
fputs("Max Record count :10\n",fmeta);
fputs("Time Stamp       :",fmeta);
time_t t;
time(&t);
fputs(ctime(&t),fmeta);

fdata=fopen(argv[2],"r+");
c=0;
while((ch=fgetc(fdata))!=-1)
	c++;

fputs("Total bytes in data file :",fmeta);
fprintf(fmeta,"%d\n",c);
rewind(fdata);

c=0;
while((ch=fgetc(fdata))!=-1)
	if(ch=='\n')
		c++;
fputs("Total record count in data file :",fmeta);
fprintf(fmeta,"%d\n",c);

printf("Set read record refference (1 to 10)\n"); //taking read record refference from user and writing to metadata
scanf("%d",&i);
fputs("Read Record Reference:",fmeta);
fprintf(fmeta,"%d\n",i);
fseek(fmeta,-1,SEEK_CUR);
fscanf(fmeta,"%d",&i);

rewind(fdata);

c=0;
while((ch=fgetc(fdata))!=-1) //making the fdata pointer to read record refference
{
	
	if(i==1)
	{
		fseek(fdata,-1,SEEK_CUR);
		break;
	}
	if(ch=='\n')
		c++;
	if(c==i-1)
		break;
}
//printing the data file on the screen
printf("The data in the data file from record %d onwards\n",i);
while((ch=fgetc(fdata))!=-1)
	printf("%c",ch);

fclose(fdata);
fclose(fmeta);

}



