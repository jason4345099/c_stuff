#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INT_MAX 2147483647
int  fgetl_int(FILE *fp)
{
    if (feof(fp)) return 0;
    size_t size = 512;
    char *line = malloc(size * sizeof(char));
    if (!fgets(line, size, fp)) {
        free(line);
        return 0;
    }

    size_t curr = strlen(line);

    while ((line[curr - 1] != '\n') && !feof(fp)) {
        if (curr == size - 1) {
            size *= 2;
            line = realloc(line, size * sizeof(char));
            if (!line) {
                printf("%ld\n", (int long)size);
            }
        }
        size_t readsize = size - curr;
        if (readsize > INT_MAX) readsize = INT_MAX - 1;
        fgets(&line[curr], readsize, fp);
        curr = strlen(line);
    }
    if (line[curr - 1] == '\n') line[curr - 1] = '\0';
    if (line[curr - 2] == '\r') line[curr - 2] = '\0';//support wind's \r\n
    return atoi(line);
}
void itoa(int n,char *s)
{
	int sign=n;
	if(sign<0)
		n=-n;
	int i=0;
	do
	{
		s[i++]=n%10+'0';//取最后一位数转换

		n=n/10;//删除最后一位

	}while(n>0);

	if(sign<0)
		s[i++]='-';
	s[i]='\0';
//	__rev(s);
}

void itoa_tmp(int n,char *s)
{
	int sign=n;
	if(sign<0)
		n=-n;
	int i=0;
	do
	{
		s[i++]=n%10+'0';//取最后一位数转换

		n=n/10;//删除最后一位

	}while(n>0);

	if(sign<0)
		s[i++]='-';
	s[i]='\0';
	//__rev(s);
}

void main(int argc, char **argv)
{
   unsigned char str[10]={0},str1[10]={0};
   FILE *fp;
   int kkk;
    char aaa=-12;
    char bbbb=-95;
    kkk=aaa;
    printf("aaa -12 aaa = 0x%x bb -95 0x%x \n",(unsigned char)aaa,(unsigned char)bbbb);exit(1);
    kkk=bbbb;
    printf("bbb 2 kk = %d \n",kkk);
   fp=fopen("./2.txt","wb");

   sprintf(str1, "%c",str[0]);
   printf("str %s\n",str);
   fwrite(str,1,2,fp);
   printf("str1 %d\n",str1[0]);

   FILE *fp1;
   unsigned char str3[10]={0};
   fp1=fopen("./1.txt","rb");
	//while(str3[0]=(char)fgetl_int(fp1)){
   int ii=10,jj;
   while(ii--){
	   jj=fgetl_int(fp1);
	   printf("jj=%d\n",jj);
   str3[0]=(char)jj;

   printf("int to char %d\n",((char)str3[0]));
	 //  sprintf(str3, "%d", (int)str3[0]);
		itoa_tmp((char)str3[0],str3);
	   //sprintf_s(str3, sizeof(str3),"%d\n", (int)str3[0]);
	printf("char to int to string %s sizeof(str3) is %d \n",str3,sizeof(str3));
	printf("strlen(str3) %d \n",strlen(str3));
  str3[strlen(str3)]='\n';
   printf("str3 char to int %d\n",((char)str3[0]));

   fwrite(&str3[0],1,3,fp);
   }

   fclose(fp1);
   fclose(fp);
}
