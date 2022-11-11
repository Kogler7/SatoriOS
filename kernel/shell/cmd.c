#include "shell.h"

shell_cmd shell_cmds[SHELL_CMD_MAX] = {
    {
        .cmd = "help",
        .desc = "show help",
        .params = {},
        .func = show_help
    },
    {
        .cmd = "echo",
        .desc = "echo the input",
        .params = {},
        .func = 0
    },
    {
        .cmd = "exit",
        .desc = "exit the shell",
        .params = {},
        .func = 0
    },
    {
        .cmd = "clock",
        .desc = "show clock counter info",
        .params = {
            {
                .sign = 's',
                .name = "reset",
                .desc = "reset and start clock counter",
            },
            {
                .sign = 'p',
                .name = "present",
                .desc = "show present clock counts",
            },
            {
                .sign = 'f',
                .name = "speed",
                .desc = "modify the speed level",
            }
        },
        .func = 0
    },
    {
        .cmd = "about",
        .desc = "show info about Satori OS",
        .params = {
            {
                .sign = 'v',
                .name = "version",
                .desc = "show version info",
            },
            {
                .sign = 'a',
                .name = "author",
                .desc = "show author info",
            },
            {
                .sign = 'c',
                .name = "copyright",
                .desc = "show copyright info",
            },
            {
                .sign = 'l',
                .name = "label",
                .desc = "show Satori label",
            },
            {
                .sign = 'o',
                .name = "origin",
                .desc = "show Satori origin",
            }
        },
        .func = 0
    },
    {
        .cmd = "info",
        .desc = "show the information of SatoriOS",
        .params = {
            {
                .sign = 'a',
                .name = "all",
                .desc = "show all information",
            },
            {
                .sign = 'c',
                .name = "cpu",
                .desc = "show cpu information",
            },
            {
                .sign = 'm',
                .name = "memory",
                .desc = "show memory information",
            },
            {
                .sign = 'b',
                .name = "boot",
                .desc = "show boot information",
            }
        },
        },
        .func = 0
    },
    {
        .cmd = "time",
        .desc = "show the time",
        .params = {},
        .func = 0
    },
    {
        .cmd = "ls",
        .desc = "list the files in the current directory",
        .params = {
            {
                .sign = 'l',
                .name = "long",
                .desc = "use a long listing format",
            },
            {
                .sign = 'a',
                .name = "all",
                .desc = "do not ignore entries starting with",
            },
            {
                .sign = 'h',
                .name = "human",
                .desc = "with -l, print sizes in human readable format (e.g., 1K 234M 2G)",
            },
            {
                .sign = 'r',
                .name = "reverse",
                .desc = "reverse order while sorting",
            }
        },
        .func = 0
    },
    {
        .cmd = "cd",
        .desc = "change the working directory",
        .params = {},
        .func = 0
    },
    {
        .cmd = "pwd",
        .desc = "print the working directory",
        .params = {},
        .func = 0
    },
    {
        .cmd = "mkdir",
        .desc = "make directories",
        .params = {},
        .func = 0
    },
    {
        .cmd = "rmdir",
        .desc = "remove empty directories",
        .params = {},
        .func = 0
    },
    {
        .cmd = "rm",
        .desc = "remove files or directories",
        .params = {},
        .func = 0
    },
    {
        .cmd = "cat",
        .desc = "concatenate files and print on the standard output",
        .params = {},
        .func = 0
    },
    {
        .cmd = "cp",
        .desc = "copy files and directories",
        .params = {},
        .func = 0
    },
    {
        .cmd = "mv",
        .desc = "move (rename) files",
        .params = {},
        .func = 0
    },
    {
        .cmd = "touch",
        .desc = "change file timestamps",
        .params = {},
        .func = 0
    },
    {
        .cmd = "ps",
        .desc = "report a snapshot of the current processes",
        .params = {},
        .func = 0
    },
    {
        .cmd = "kill",
        .desc = "send a signal to a process",
        .params = {},
        .func = 0
    },
    {
        .cmd = "free",
        .desc = "display amount of free and used memory in the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "df",
        .desc = "report file system disk space usage",
        .params = {},
        .func = 0
    },
    {
        .cmd = "du",
        .desc = "estimate file space usage",
        .params = {},
        .func = 0
    },
    {
        .cmd = "mount",
        .desc = "mount a filesystem",
        .params = {},
        .func = 0
    },
    {
        .cmd = "umount",
        .desc = "unmount a filesystem",
        .params = {},
        .func = 0
    },
    {
        .cmd = "ping",
        .desc = "send ICMP ECHO_REQUEST to network hosts",
        .params = {},
        .func = 0
    },
    {
        .cmd = "whoami",
        .desc = "print effective userid",
        .params = {},
        .func = 0
    }
};