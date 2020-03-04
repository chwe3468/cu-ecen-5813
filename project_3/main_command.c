#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifdef BUTTON
#define PRESS printf("press ENTER to continue");getchar()
#else
#define PRESS
#endif
/*
typedef union {
  *char32_t (*allocate_bytes)(uint32_t n);
  bool (*free_allocated)(*char32_t addr);
  bool (*verify_memory)(*char32_t addr);
  *char32_t (*display_memory)(*char32_t addr, uint32_t n);
  void (*write_memory)(*char32_t addr, uint32_t m, uint32_t n, uint32_t v);
  void (*invert_block)(*char32_t addr, uint32_t m, uint32_t n);
  *char32_t (*write_pattern)(*char32_t addr, uint32_t n, uint32_t s);
  bool (*compare_pattern)(*char32_t addr, uint32_t n, uint32_t s);
} cmd_func;
*/
int main(void)
{
    size_t bufsize = 32;
    //size_t len;
    char *line = (char *)malloc(bufsize * sizeof(char));
    // Initialize Input Line String pointer
    //char * line = (char*)malloc( 65 * sizeof(char) );
    char *command = (char*)malloc( 5 * sizeof(char) );
    char *arg1 = (char*)malloc( 5 * sizeof(char) );
    char *arg2 = (char*)malloc( 5 * sizeof(char) );
    char *arg3 = (char*)malloc( 50 * sizeof(char) );
    char *args[4]={command, arg1, arg2, arg3};
    while ((gets(line)) != NULL) {
        //printf("%d|%s",len,line);
        int comma_count=0;
        int i=0;
        while(line[i]){
            if (line[i]==',' || line[i]=='\n' || line[i]=='\0'){
                strncpy(args[comma_count], line,i);
                comma_count=(comma_count+1)%4;
                if (line[i]!='\n' || line[i]!='\0'){
                    line=line+i+1;
                    i=0;
                }
            }
            i++;
        }        printf("\n--%s,%s,%s,%s--\n",args[0],args[1],args[2],args[3]);
        //cmd_func cmd;        printf("args[0] is %s",args[1]);
        switch (args[0][0])
        {
            case 'a':
            case 'A': // code to be executed if n = 1;
                //cmd.allocate_bytes=&my_allocate_bytes;
                printf("press ENTER to continue\n");
                getchar(); //wait for enter to continue to next line
                //xxx=*cmd.allocate_bytes(args[1]);
                break;
            case 'f':
            case 'F': // code to be executed if n = 2;
                //cmd.free_allocated=&my_free_allocated;
                PRESS;
                //*cmd.free_allocated(xxx);
                break;
            case 'm':
            case 'M': // code to be executed if n = 1;
                //cmd.verify_memory=&my_verify_memory;
                PRESS;
                //*cmd.verify_memory(xxx);
                break;
            case 'd':
            case 'D': // code to be executed if n = 2;
                //cmd.display_memory=&my_display_memory;
                PRESS;
                //*cmd.display_memory(xxx,args[1]);
                break;
            case 'w':
            case 'W': // code to be executed if n = 1;
                //cmd.write_memory=&my_write_memory;
                PRESS;
                uint8_t *hex;
                sscanf(args[3], "%x", hex);
                //*cmd.write_memory(xxx,args[1],args[2], hex);
                break;
            case 'i':
            case 'I': // code to be executed if n = 2;
                //cmd.invert_block=&my_invert_block;
                PRESS;
                //*cmd.invert_block(xxx,args[1],args[2]);
                break;
            case 'p':
            case 'P': // code to be executed if n = 2;
                //cmd.write_pattern=&my_write_pattern;
                printf("press ENTER to continue\n");
                getchar(); //wait for enter to continue to next line
                //*cmd.write_pattern(xxx,args[1],args[2]);
                break;
            case 'c':
            case 'C': // code to be executed if n = 2;
                //cmd.compare_pattern=&my_compare_pattern;
                PRESS;
                //*cmd.compare_pattern(xxx,args[1],args[2]);
                break;
            default: // code to be executed if n doesn't match any cases
                printf("invalid command\n");
        }
        memset(command,'\0',5);
        memset(arg1,'\0',5);
        memset(arg2,'\0',5);
        memset(arg3,'\0',50);
    }
    if (line)
        free(line);
    if (command)
        free(command);
    if (arg1)
        free(arg1);
    if (arg2)
        free(arg2);
    if (arg3)
        free(arg3);
    exit(0);
}