#include <stdio.h>
#include <stdlib.h>
int float_to_int(float f)
{
    int *p = (int*)&f;
    //由于指针访问内存是按照基类型进行的，首先进行强转访问浮点数f
    int temp = *p;
    //用中间变量接受f的值
    //提取符号位
    int sign = -1;
    if((temp & 0x80000000) == 0)
    {
        sign = 1;
    }
    //条件表达式中进行了位与运算，其实就是提取指数位的值。前面已经讲过了，符号位为0，其为正值。若为1，其为负值。

    //提取指数位
    int exp;
    exp = ( (  (temp >> 23) & 0x0ff  )  ) - 127;
    //由于在存储的时候指数位加了偏置常数   现在相当于是计算指数位的逆过程 所以自然要减去

    //提取尾数位
    int tail;
    tail = ( ( temp & 0x007fffff ) | 0x00800000 );
    /*和之前提取指数位和符号位的方法是一致的，要提取哪几位，在对应的位进行与1运算就可以了
    现在我们要提取的是除符号位和指数位共计九位的其他23，即尾数为。只需要在对应的为与1即可*/
    /*还记得在存储尾数的时候，因为任意一个单精度的二进制数以科学记数法表示时，第一位都是1，
    所以存储的时间，为了能够提高精度，省略了改位。但是现在是在进行他的逆过程，所以我们要在
    要进行或1位运算*/

    int res = (tail >> (23 - exp));

    return res * sign;

}

//进行验证
int main()
{
    float a  = 12.825; //a = -12.125 a = 0.05 a = -0.05
    int b = float_to_int(a);
    short d = a*3.1456;
    printf("size of short %d \r\n",sizeof(short));
    printf("b = %d\n",b);
    printf("d = %d\n",d);
    b=(int)a;
    printf("b2 = %d\n",b);
}
//原文链接：https://blog.csdn.net/ASJBFJSB/article/details/79499233
