#include<stdio.h>
#include<stdlib.h> 
int main()
{
	printf("rgb三原色转16进制\n");
	int a,b,c,d;
	while(d != 2){
		printf("输入1继续，输入2退出\n");
		scanf("%d",&d);
		scanf("%d%d%d",&a,&b,&c);
		printf("[%x %x %x]\n",a,b,c); //%x 可以直接把我们输入的十进制转换为 十六进制
	}
	return 0;
}
