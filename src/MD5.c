#include "../include/MD5.h"
/*
四个初始向量
*/
/*
DWORD A=0x01234567;
DWORD B=0x89abcdef;
DWORD C=0xfedcba98;
DWORD D=0x76543210;
*/

DWORD A=0x67452301;
DWORD B=0xEFCDAB89;
DWORD C=0x98BADCFE;
DWORD D=0x10325476;

const DWORD A0=0x67452301;
const DWORD B0=0xEFCDAB89;
const DWORD C0=0x98BADCFE;
const DWORD D0=0x10325476;

void md5_block_encode( byte* block)
{
    DWORD a = A, b = B, c = C, d = D;
    DWORD*x=malloc(16*4);
    Decode(block, x, block_size);
    /*
        第一轮
    */
    //printf("first round\n");
    FF (a, b, c, d, x[0], 7, T(1)); 
    FF (d, a, b, c, x[1],12, T(2));
    FF (c, d, a, b, x[2],17, T(3));
    FF (b, c, d, a, x[3],22, T(4));

    FF (a, b, c, d, x[4], 7, T(5));
    FF (d, a, b, c, x[5],12, T(6));
    FF (c, d, a, b, x[6],17, T(7));
    FF (b, c, d, a, x[7],22, T(8));

    FF (a, b, c, d, x[8], 7, T(9));
    FF (d, a, b, c, x[9],12, T(10));
    FF (c, d, a, b, x[10],17, T(11));
    FF (b, c, d, a, x[11],22, T(12));

    FF (a, b, c, d, x[12], 7, T(13));
    FF (d, a, b, c, x[13],12, T(14));
    FF (c, d, a, b, x[14],17, T(15));
    FF (b, c, d, a, x[15],22, T(16));

    /*
        第二轮
    */
    GG (a, b, c, d, x[1], 5, T(17));
    GG (d, a, b, c, x[6], 9, T(18));
    GG (c, d, a, b, x[11], 14, T(19));
    GG (b, c, d, a, x[0], 20, T(20));

    GG (a, b, c, d, x[5], 5, T(21));
    GG (d, a, b, c, x[10], 9, T(22));
    GG (c, d, a, b, x[15], 14, T(23));
    GG (b, c, d, a, x[4], 20, T(24));

    GG (a, b, c, d, x[9], 5, T(25));
    GG (d, a, b, c, x[14], 9, T(26));
    GG (c, d, a, b, x[3], 14, T(27));
    GG (b, c, d, a, x[8], 20, T(28));

    GG (a, b, c, d, x[13], 5, T(29));
    GG (d, a, b, c, x[2], 9, T(30));
    GG (c, d, a, b, x[7], 14, T(31));
    GG (b, c, d, a, x[12], 20, T(32));

    /*
        第三轮
    */
    HH (a, b, c, d, x[5], 4, T(33));
    HH (d, a, b, c, x[8],11, T(34));
    HH (c, d, a, b, x[11], 16, T(35));
    HH (b, c, d, a, x[14], 23, T(36));

    HH (a, b, c, d, x[1], 4, T(37));
    HH (d, a, b, c, x[4],11, T(38));
    HH (c, d, a, b, x[7], 16, T(39));
    HH (b, c, d, a, x[10], 23, T(40));

    HH (a, b, c, d, x[13], 4, T(41));
    HH (d, a, b, c, x[0],11, T(42));
    HH (c, d, a, b, x[3], 16, T(43));
    HH (b, c, d, a, x[6], 23, T(44));

    HH (a, b, c, d, x[9], 4, T(45));
    HH (d, a, b, c, x[12],11, T(46));
    HH (c, d, a, b, x[15], 16, T(47));
    HH (b, c, d, a, x[2], 23, T(48));

    /*
        第四轮
    */
    II (a, b, c, d, x[0], 6, T(49));
    II (d, a, b, c, x[7], 10, T(50));
    II (c, d, a, b, x[14], 15, T(51));
    II (b, c, d, a, x[5], 21, T(52));

    II (a, b, c, d, x[12], 6, T(53));
    II (d, a, b, c, x[3], 10, T(54));
    II (c, d, a, b, x[10], 15, T(55));
    II (b, c, d, a, x[1], 21, T(56));

    II (a, b, c, d, x[8], 6, T(57));
    II (d, a, b, c, x[15], 10, T(58));
    II (c, d, a, b, x[6], 15, T(59));
    II (b, c, d, a, x[13], 21, T(60));

    II (a, b, c, d, x[4], 6, T(61));
    II (d, a, b, c, x[11], 10, T(62));
    II (c, d, a, b, x[2], 15, T(63));
    II (b, c, d, a, x[9], 21, T(64));
    free(x);
    //printf("final\n");   
    A+=a;
    B+=b;
    C+=c;
    D+=d;
    
}

void Decode( byte *input, DWORD *output, size_t length)
{
    for(int i=0 , j=0 ;i<length;i+=4,j++)
    {
        output[j]=input[i]|(((DWORD)input[i+1])<<8)|\
        (((DWORD)input[i+2])<<16)|(((DWORD)input[i+3])<<24);
    }
    
}

double ABS(double value)
{
    if(value<0)
        return -1*value;
    return value;
}

unsigned int T(int i)
{
    ////计算4294967296Íabs(sin(i))的整数部分
    return (unsigned int)(pow_32*ABS(sin((double)i)));
}

byte* padding(byte*source,byte*pad,int length,int total_len, int *res_len)
{
    /*
        source为读取到的字节数组
        length为source的长度
        total_len 是要加密的整个数据的长度
    */
    int current_length=length;
    //printf("length=%d\n",length);
    if(length%64!=56||length<64)
    {
        //首先计算出需要填充的字节数
        int count=0;
        while((length+count)%64!=56)
            count++;
        //printf("count=%d\n",count);
        *res_len=length+count+8;
        //printf("malloc\n");
        pad=malloc(count+length+8);
        //首先复制数组sourcec
        for(int i=0;i<length;i++)
            pad[i]=source[i];
        pad[length]=0b10000000;//填充1位1
        //其余位填充0
        for(int i=1;i<=count-1;i++)
            pad[length+i]=0;
        //然后在这个结果后面加上一个以 64 位二进制表示的填充前的消息长度,必须是完整的！！！
        //printf("%X\n",length&0xff);
        unsigned long t=total_len*8;
        for(int i=0;i<8;i++)
        {
            //printf("%X\n",((t)>>(0))&0xff);
            pad[i+length+count]=(t>>(i*8))&0xff;
            //res[7-i+length+count]=(((unsigned long)length)>>i*8)&&0xff;
            //printf("%d\n",i+length+count);
            //printf("%X\n",res[i+length+count]);
        }
        return pad;
    }
    else
    {
        return source;
    }
}

DWORD change_end(DWORD N)
{
    byte str[4];
    DWORD res=0;
    for(int i=0;i<4;i++)
    {
        str[i]=(N>>(i*8));
        res|=((DWORD)str[i])<<((3-i)*8);
        //printf("%02X\n",str[i]);
    }
    return res;
    
}