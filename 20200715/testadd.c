#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 
	@input param : dram_id from 64-255 
				  
	@output: file1_str name to open
			file2_str name to open
*/
void mem_index_convert(int dram_id, char *file1_str,char *file2_str)
{
	int tmp_col,row,col;
	char mem_name[100]="mem_I";
	if(dram_id>127) { //ipu 
		row = (dram_id-128)/16*2+1;
		printf("row addr is %0d \n",row);
		tmp_col = (dram_id-128)%16;
		printf("tmp_col is %0d \n",tmp_col);
		if(tmp_col<8)
		  col = tmp_col;
		else
		  col = 16-tmp_col+9;
		printf("col is %0d",col);
	} 
	else if(dram_id ==126) {  //cfg dram
		col =9;
		row = 0;
	} 
	else if(dram_id == 127) { //processor dram
		col =7;
		row = 0;
	} 
	else {//gpu
		 tmp_col = (dram_id-64)/2;
		 col = dram_id%2+8;
		 row = tmp_col*2+1;
	}
    sprintf(file1_str,"mem_IR%dC%d",row,col);
    sprintf(file2_str,"mem_IR%dC%d",row+1,col);
}
void main(int argc, char **argv)
{
	int i,j;
	char file1_str[100]={0};
	char file2_str[100]={0};

	for(i=64;i<255;i++){
		mem_index_convert(i,file1_str,file2_str);
		printf("file1_str %s, file2_str %s \r\n",file1_str,file2_str);
	}

}
