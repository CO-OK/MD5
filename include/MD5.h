/*
    对64字节数据块进行MD5加密
*/
#include"common.h"
#include<math.h>
#include<stdlib.h>


/*
算法四个基本函数
*/
#define F(x,y,z) (((x)&(y))|((~x)&(z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/*
循环左移
*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/*
FF,GG,HH,II
*/
#define FF(a, b, c, d, x, s, ac) {\
(a) += F ((b), (c), (d)) + (x) + ac;\
(a) = ROTATE_LEFT ((a), (s));\
(a) += (b);\
}
#define GG(a, b, c, d, x, s, ac) {\
(a) += G ((b), (c), (d)) + (x) + ac;\
(a) = ROTATE_LEFT ((a), (s));\
(a) += (b);\
}
#define HH(a, b, c, d, x, s, ac) {\
(a) += H ((b), (c), (d)) + (x) + ac;\
(a) = ROTATE_LEFT ((a), (s));\
(a) += (b);\
}
#define II(a, b, c, d, x, s, ac) {\
(a) += I ((b), (c), (d)) + (x) + ac;\
(a) = ROTATE_LEFT ((a), (s));\
(a) += (b);\
}

#define pow_32 4294967296//2的32次方

#define block_size 64
void md5_block_encode( byte* block);//对64字节block进行md5加密
void Decode( byte *input, DWORD *output, size_t length);//将字节流转化为双字流
double ABS(double value);//求sin绝对值
unsigned int T(int i);//计算4294967296Íabs(sin(i))的整数部分
byte* padding(byte*source,byte*pad,int length,int total_len,int*res_len);//填充数据
DWORD change_end(DWORD N);//改变编址



