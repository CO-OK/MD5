#include<stdio.h>
#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))
int main()
{
        printf("%d\n%d\n",ELF32_ST_BIND(4),ELF32_ST_TYPE(4));
}
