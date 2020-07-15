#include "sunrise.h"

fail_tag *create_head()
{
    fail_tag *head = (fail_tag *)malloc(sizeof(fail_tag));
    if (!head){
    head->next = NULL;
    return head;
	}
	return NULL;
}

void insert_list(fail_tag *head,fail_tag *newnode)//from head
{
   // printf("%s , head 0x%x \r\n",__func__,head);
    newnode->next = head->next;
    head->next = newnode;
}

fail_tag *create_fail_tag_list()
{
    fail_tag *l = malloc(sizeof(fail_tag));
     if (!l)return NULL;
    l->size = 0;
    l->pre = NULL;
    l->next = NULL;
    return l;
}

void verify_fail_tag(fail_tag *l)
{
    while(l){
		printf("l->dram_id %d \r\n",l->dram_id);
        if(l->next)l=l->next;
		else break;
    }
}

int main()
{
BYTE data;
BYTE wdata[32];
BYTE rdata[256];
BYTE reg_value;

int flag;
int fail_cnt =0;
   time_t start_t, end_t;
   double diff_t;


fail_tag  *c_tag,*c_tag_head;
c_tag_head=create_fail_tag_list();
//init the list.
    printf("DEBUG\n");
write_reg(0,8,0);
data=read_reg(1,0);

    printf("rdata is %0x \n",data);
for(int i=0; i<32;i++) {
  wdata[i]= rand();
   }
burst_write(wdata);

burst_read(rdata);
  for(int i=0;i<256;i++) {
    printf("r_data[%0d] is %0x \n",i,rdata[i]);
  }
   time(&start_t);
   printf("Run time = %f\n",start_t );
for(dram_id_t dram_id = DRAM128;dram_id<=DRAM255;dram_id++){
   for(DW row_addr=0; row_addr<2048; row_addr++){
    for(BYTE col_addr=0; col_addr<64;col_addr++){ 
    flag=  spi_prog_dram(dram_id,col_addr,row_addr,wdata);
	
    if(!flag){
    c_tag=create_fail_tag_list();
	c_tag->dram_id=dram_id;
    c_tag->row_addr= row_addr;
    c_tag->col_addr= col_addr;
	insert_list(c_tag_head,c_tag);
   // printf("PROG DRAM %0x ROW ADDR %0x, COL ADDR %0x FAIL \n",dram_id,row_addr,col_addr);
     fail_cnt++;
     //f_tag++;
     }
    }
  }
 
  printf("End of dram %0x fail_cnt is %0x \n",dram_id,fail_cnt);
   
 }
//}
// for(int i=0; i<sizeof(f_tag);i++) {

for(dram_id_t dram_id = DRAM128;dram_id<=DRAM255;dram_id+=4){
   for(DW row_addr=0; row_addr<2048; row_addr++){
    for(BYTE col_addr=0; col_addr<64;col_addr++) 
      spi_read_dram(dram_id,col_addr,row_addr,rdata);
  }
  printf("RD::End of  dram %0x \n",dram_id);
}

   time(&end_t);
   diff_t = difftime(end_t, start_t);
 
spi_read_inreg(DRAM0,0,reg_value);

   printf("Run time = %f\n", diff_t);
 printf("END OF MAIN ! \n");
#ifdef TEST_LIST
for(dram_id_t dram_id = 1;dram_id<=6;dram_id++){
    c_tag=create_fail_tag_list();
c_tag->dram_id=dram_id;
insert_byhead(c_tag_head,c_tag);
#endif
}
#if 0
verify_fail_tag(c_tag);
#endif
//}
