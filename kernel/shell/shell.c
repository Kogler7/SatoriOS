#include"shell.h"
// #include<stdio.h>
#include"util.h"
#include"satio/printf.h"
#include"satio/serial.h"

void show_help()
{
    puts("help: show help\n");
    puts("clear: clear the screen\n");
    puts("echo: echo the input\n");
    puts("reboot: reboot the system\n");
    puts("shutdown: shutdown the system\n");
    puts("version: show the version of SatoriOS\n");
    puts("info: show the information of SatoriOS\n");
    puts("date: show the date\n");
    puts("time: show the time\n");
    puts("ls: list the files in the current directory\n");
    puts("cd: change the current directory\n");
    puts("pwd: show the current directory\n");
    puts("mkdir: make a directory\n");
    puts("rmdir: remove a directory\n");
    puts("rm: remove a file\n");
    puts("cat: show the content of a file\n");
    puts("touch: create a file\n");
    puts("cp: copy a file\n");
    puts("mv: move a file\n");
    puts("find: find a file\n");
    puts("whoami: show the current user\n");
    puts("su: switch the current user\n");
    puts("useradd: add a user\n");
    puts("userdel: delete a user\n");
    puts("passwd: change the password of a user\n");
    puts("groupadd: add a group\n");
    puts("groupdel: delete a group\n");
    puts("usermod: modify the user\n");
    puts("groupmod: modify the group\n");
    puts("chown: change the owner of a file\n");
    puts("chgrp: change the group of a file\n");
    puts("chmod: change the permission of a file\n");
    puts("umask: set the default permission of a file\n");
    puts("mount: mount a device\n");
    puts("umount: unmount a device\n");
    puts("df: show the disk usage\n");
    puts("du: show the disk usage of a file\n");
    puts("free: show the free memory\n");
    puts("top: show the process information\n");
    puts("ps: show the process information\n");
    puts("kill: kill a process\n");
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