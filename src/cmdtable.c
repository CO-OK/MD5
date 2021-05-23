#include"../include/cmdtable.h"
#include"../include/MD5.h"
#include<fcntl.h>
#include<unistd.h>
extern DWORD A;
extern DWORD B;
extern DWORD C;
extern DWORD D;

extern const DWORD A0;
extern const DWORD B0;
extern const DWORD C0;
extern const DWORD D0;

struct CMD_TABLE cmd_table [] = {
  { "-h", "--help information",cmd_h },
  { "-t", "--test MD5 application",cmd_t },
  { "-c", "[file path of the file computed] \n\t\t--compute \
  MD5 of the given file",cmd_c},
  { "-v", "[file path of the file validated] \n\t\t--validate\
  the integrality of a given file by manual input MD5 value",cmd_v},
  { "-f", "[file path of the file validated] [file path of the\
   .md5 file] \n\t\t--validate the integrality of a given file by read MD5 value from .md5 file",cmd_f},
};

static int cmd_h(char *arg1,char*arg2)
{
    printf("USAGE:\n");
    for(int i=0;i<NR_CMD;i++)
    {
        printf("\t%s %s\n",cmd_table[i].name,cmd_table[i].description);
    }
    return 0;
}


static int cmd_t(char*arg1,char*arg2)
{
    char res[33];//结果数组
    char *a[]={
        "",
        "a",
        "abc",
        "message digest",
        "abcdefghijklmnopqrstuvwxyz",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
    };
    byte*pad=NULL;
    int len;
    for(int i=0;i<7;i++)
    {
        pad=padding(a[i],pad,strlen(a[i]),strlen(a[i]),&len);
        for(int j=0;j<len/64;j++)
        {
            md5_block_encode(pad+j*64);
        }
        sprintf(res,"%08X%08X%08X%08X",change_end(A),change_end(B),change_end(C),change_end(D));
        printf("\tMD5(\"%s\")=%s\n",a[i],res);
        free(pad);
        A=A0;//A0保存了A最初的值，其他的也一样        
        B=B0;
        C=C0;
        D=D0;
    }
    return 0;
}

static int cmd_c(char*arg1,char*arg2)
{
    if(arg1==NULL)
    {
        printf("USAGE:\n");
        printf("\t%s %s\n",cmd_table[2].name,cmd_table[2].description);
        return 1;
    }
    int fd;//文件描述符
    if((fd=open(arg1,O_RDONLY))==-1)
    {
        printf("open file \"%s\" failed.\n",arg1);
        return 1;
    }
    char res[33];
    cal_file_md5(fd,res);
    printf("The MD5 value of file %s is %s\n",arg1,res);
    return 0;
}

static int cmd_v(char*arg1,char*arg2)
{
    if(arg1==NULL)
    {
        printf("USAGE:\n");
        printf("\t%s %s\n",cmd_table[2].name,cmd_table[2].description);
        return 1;
    }
    int fd;//文件描述符
    if((fd=open(arg1,O_RDONLY))==-1)
    {
        printf("open file \"%s\" failed.\n",arg1);
        return 1;
    }
    //读取输入的md5字符串
    byte read_arr[33];
    read_arr[32]='\0';
    printf("input MD5 value of file (\"%s\"):\n",arg1);
    while(read(0,read_arr,32)!=32)
    {
        printf("You must input correct MD5 format string.\n");
        printf("input MD5 value of file (\"%s\"):\n",arg1);
    }
    char res[33];
    res[32]='\0';
    cal_file_md5(fd,res);
    for(int i=0;i<32;i++)
    {
        if(res[i]!=read_arr[i])
        {
            printf("Match error! The file has been modified!\n");
            printf("input MD5:\t\t%s\n",read_arr);
            printf("calculated file MD5:\t%s\n",res);
            return 1;
        }
    }
    printf("The file \"%s\" is integrated\n",arg1);
    return 0;

}

static int cmd_f(char*arg1,char*arg2)
{
    if(arg1==NULL||arg2==NULL)
    {
        printf("USAGE:\n");
        printf("\t%s %s\n",cmd_table[4].name,cmd_table[4].description);
        return 1;
    }
    int fd_test;//被测文件
    int fd_MD5;//MD5文件
    if((fd_test=open(arg1,O_RDONLY))==-1)
    {
        printf("open file \"%s\" failed.\n",arg1);
        return 1;
    }
    if((fd_MD5=open(arg2,O_RDONLY))==-1)
    {
        printf("open file \"%s\" failed.\n",arg1);
        return 1;
    }
    //对测试文件计算md5
    char res_test[33];
    res_test[32]='\0';
    cal_file_md5(fd_test,res_test);
    //读取md5 file中的值
    char res_md5[33];
    res_test[32]='\0';
    if(read(fd_MD5,res_md5,32)!=32)
    {
        printf("read file \"%s\" failed\n",arg2);
        return 1;
    }
    for (int i = 0; i < 32; i++)
    {
        if(res_md5[i]!=res_test[i])
        {
            printf("Match error! The file has been modified!\n");
            printf("MD5 file value:\t\t%s\n",res_md5);
            printf("calculated file MD5:\t%s\n",res_test);
            return 1;
        }
    }
    printf("The file \"%s\" is integrated\n",arg1);
    return 0; 
}

void cal_file_md5(int fd,char*res)
{
    byte buf[64];
    int count ;
    //char res[32];
    byte*pad=NULL;
    int len;
    int total_count=0;
    while((count = read(fd,buf,block_size))!=0)
    {
        total_count+=count;
        if(count==block_size)
        {
            md5_block_encode(buf);
        }
        else
        {
            //最后要补的长度是整个数据的长度
            pad=padding(buf,pad,count-1,total_count-1,&len);     
            md5_block_encode(pad);
            free(pad);
        }    
    }
    sprintf(res,"%08X%08X%08X%08X",change_end(A),change_end(B),change_end(C),change_end(D));
}