#include"../include/MD5.h"
#include"../include/common.h"
#include"../include/cmdtable.h"
extern struct CMD_TABLE cmd_table[];
int main(int ac,char*av[])
{
    if(ac==1)
    {
        cmd_table[0].handler(NULL,NULL);
        return 1;
    }
    for(int i=0;i<NR_CMD;i++)
    {
        if(strcmp(av[1],cmd_table[i].name)==0)
        {
            return cmd_table[i].handler(av[2],av[3]);
        }
    }
    cmd_table[0].handler(NULL,NULL);
    return 1;
}