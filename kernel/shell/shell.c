#include"shell.h"
// #include<stdio.h>
#include"util.h"
#include"satio/printf.h"
#include"satio/serial.h"

char input_buff[SHELL_BUFFER_SIZE];

void show_help()
{
    puts("\thelp: show help\n");
    puts("\texit: exit the shell\n");
    puts("\tclock: show clock counter info\n");
    puts("\t\t-s : reset and start clock counter\n");
    puts("\t\t-p : show present clock counts\n");
    puts("\t\t-f : modify the speed level\n");
    puts("\tmem: show memory info\n");
    puts("\tcpu: show cpu info\n");
    puts("\param: show boot params\n");
    puts("\tclear: clear the screen\n");
    puts("\techo: echo the input\n");
    puts("\treboot: reboot the system\n");
    puts("\tshutdown: shutdown the system\n");
    puts("\tversion: show the version of SatoriOS\n");
    puts("\tinfo: show the information of SatoriOS\n");
    puts("\tdate: show the date\n");
    puts("\ttime: show the time\n");
    puts("\tls: list the files in the current directory\n");
    puts("\tcd: change the current directory\n");
    puts("\tpwd: show the current directory\n");
    puts("\tmkdir: make a directory\n");
    puts("\trmdir: remove a directory\n");
    puts("\trm: remove a file\n");
    puts("\tcat: show the content of a file\n");
    puts("\ttouch: create a file\n");
    puts("\tcp: copy a file\n");
    puts("\tmv: move a file\n");
    puts("\tfind: find a file\n");
    puts("\twhoami: show the current user\n");
    puts("\tsu: switch the current user\n");
    puts("\tuseradd: add a user\n");
    puts("\tuserdel: delete a user\n");
    puts("\tpasswd: change the password of a user\n");
    puts("\tgroupadd: add a group\n");
    puts("\tgroupdel: delete a group\n");
    puts("\tusermod: modify the user\n");
    puts("\tgroupmod: modify the group\n");
    puts("\tchown: change the owner of a file\n");
    puts("\tchgrp: change the group of a file\n");
    puts("\tchmod: change the permission of a file\n");
    puts("\tumask: set the default permission of a file\n");
    puts("\tmount: mount a device\n");
    puts("\tumount: unmount a device\n");
    puts("\tdf: show the disk usage\n");
    puts("\tdu: show the disk usage of a file\n");
    puts("\tfree: show the free memory\n");
    puts("\ttop: show the process information\n");
    puts("\tps: show the process information\n");
    puts("\tkill: kill a process\n");
}

void entry_shell(){
    char input[256];
    for (int i = 0; i < 256; i++)
        input[i] = 0;
    while (1)
    {
        puts("SatoriOS $ ");
        printf("SatoriOS $ %d",1);
        break;
        // gets(input);
        if (strcmp(input, "help") == 0)
            show_help();
        if (strcmp(input, "exit") == 0)
            break;
    }
    
}