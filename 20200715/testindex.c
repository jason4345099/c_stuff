#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INT_MAX 2147483647

typedef struct dram_list {
    int linenum;
	char buf[33];
    int dram_id;
    struct dram_list *pre;
    struct dram_list *next;
} dram_list;

void insert_list(dram_list *head,dram_list *newnode)//from head
{
    newnode->next = head->next;
    head->next = newnode;
}

dram_list *create_dram_list()
{
    dram_list *l = malloc(sizeof(dram_list));
     if (!l)return NULL;
    l->pre = NULL;
    l->next = NULL;
    return l;
}

void verify_dram_list(dram_list *l,char *path)
{
	FILE *fp=NULL;
	fp=fopen(path,"wb");
    while(l){
        printf("l->dram_id %d \r\n",l->dram_id);
        printf("l->linenum %d \r\n",l->linenum);
		fwrite(l->buf, sizeof(char),strlen(l->buf), fp);
		fwrite("\n", sizeof(char),1, fp);
        if(l->next)l=l->next;
        else break;
    }
	fclose(fp);
}

void free_dram_list(dram_list *l)
{
	printf("%s \r\n",__func__);
	dram_list *tmp;
    while(l){
		tmp=l->next;
		free(l);
		l=tmp;
    }
}


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
	int linenum=0;
	char buf1[16],buf2[16];
	char file1_str[100]={0};
	char file2_str[100]={0};
	FILE *fp_dram1 = NULL;
	FILE *fp_dram2 = NULL;

	for(i=64;i<255;i++){
		mem_index_convert(i,file1_str,file2_str);
		printf("file1_str %s, file2_str %s \r\n",file1_str,file2_str);
	
		char filepath1[100]="./";
		char filepath2[100]="./";
		char filepath_new[100]="./newfile_32B_";
		char index_str[10]={'0'};
		strcat(filepath2,file2_str);
		strcat(filepath1,file1_str);
		fp_dram1 = fopen(filepath1, "rb");
		fp_dram2 = fopen(filepath2, "rb");
		if(fp_dram1==NULL || fp_dram2==NULL){
			printf("file not exits %s or %s\r\n",filepath1,filepath2);
		}
	
		dram_list *dram_list_head,*dram_list_cur;	
		dram_list_head=create_dram_list();
		for(linenum=0; fgets(buf1, sizeof(buf1)+1, fp_dram1) != NULL &&  fgets(buf2, sizeof(buf2)+1, fp_dram2) != NULL && linenum < 3;linenum++){
			if(strstr(buf1,"x")!=NULL || strstr(buf2,"x")!=NULL)continue;
			dram_list_cur=create_dram_list();
			dram_list_cur->dram_id=i;
			dram_list_cur->linenum=linenum;
			strncpy(dram_list_cur->buf,buf1,16);
			strncpy(dram_list_cur->buf+16,buf2,16);
			
		}
		
		//save the new 32B file
		//itoa(i,index_str,10);
		strcat(filepath_new,index_str);
		verify_dram_list(dram_list_cur,filepath_new);

		//release the list.
		free_dram_list(dram_list_cur);
				
		fclose(fp_dram1);
		fclose(fp_dram2);
	}
}
