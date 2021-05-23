
struct CMD_TABLE{
  char *name;
  char *description;
  int (*handler) (char *,char*);
} ;

#define NR_CMD 5

#ifndef oops
#define oops(msg){perror(msg);exit(1);}            //打印出错信息
#endif
static int cmd_h(char*arg1,char*arg2);
static int cmd_t(char*arg1,char*arg2);
static int cmd_c(char*arg1,char*arg2);
static int cmd_v(char*arg1,char*arg2);
static int cmd_f(char*arg1,char*arg2);
void cal_file_md5(int fd,char*buf);//计算文件的MD5