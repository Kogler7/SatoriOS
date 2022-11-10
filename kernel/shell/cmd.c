#include "shell.h"

void show_help()
{
    for (int i = 0; i < SHELL_CMD_MAX; i++)
    {
        if (shell_cmds[i].cmd[0] == 0)
            break;
        printf("\t%s\t%s\n", shell_cmds[i].cmd, shell_cmds[i].desc);
        if (shell_cmds[i].params[0].sign != 0)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shell_cmds[i].params[j].sign == 0)
                    break;
                printf("\t\t%s\t%s\n", shell_cmds[i].params[j].name, shell_cmds[i].params[j].desc);
            }
        }
    }
}

shell_cmd shell_cmds[SHELL_CMD_MAX] = {
    {
        .cmd = "help",
        .desc = "show help",
        .params = {},
        .func = show_help
    },
    {
        .cmd = "clear",
        .desc = "clear screen",
        .params = {},
        .func = 0
    },
    {
        .cmd = "echo",
        .desc = "echo the input",
        .params = {
            {
                .sign = 'n',
                .name = "-n",
                .desc = "do not output the trailing newline",
                .func = 0
            }
        },
        .func = 0
    },
    {
        .cmd = "reboot",
        .desc = "reboot the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "shutdown",
        .desc = "shutdown the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "version",
        .desc = "show the version of SatoriOS",
        .params = {},
        .func = 0
    },
    {
        .cmd = "info",
        .desc = "show the information of SatoriOS",
        .params = {},
        .func = 0
    },
    {
        .cmd = "date",
        .desc = "show the date",
        .params = {},
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
                .name = "-l",
                .desc = "use a long listing format",
                .func = 0
            },
            {
                .sign = 'a',
                .name = "-a",
                .desc = "do not ignore entries starting with .",
                .func = 0
            },
            {
                .sign = 'h',
                .name = "-h",
                .desc = "with -l, print sizes in human readable format (e.g., 1K 234M 2G)",
                .func = 0
            },
            {
                .sign = 'r',
                .name = "-r",
                .desc = "reverse order while sorting",
                .func = 0
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
        .cmd = "nano",
        .desc = "a small and friendly text editor",
        .params = {},
        .func = 0
    },
    {
        .cmd = "vim",
        .desc = "a highly configurable text editor built to enable efficient text editing",
        .params = {},
        .func = 0
    },
    {
        .cmd = "emacs",
        .desc = "the extensible, customizable, self-documenting real-time display editor",
        .params = {},
        .func = 0
    },
    {
        .cmd = "top",
        .desc = "display Linux processes",
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
        .cmd = "reboot",
        .desc = "reboot the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "shutdown",
        .desc = "shutdown the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "ifconfig",
        .desc = "configure a network interface",
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
        .cmd = "traceroute",
        .desc = "trace the route to a network host",
        .params = {},
        .func = 0
    },
    {
        .cmd = "route",
        .desc = "show / manipulate the IP routing table",
        .params = {},
        .func = 0
    },
    {
        .cmd = "arp",
        .desc = "show / manipulate the system ARP cache",
        .params = {},
        .func = 0
    },
    {
        .cmd = "netstat",
        .desc = "print network connections, routing tables, interface statistics, masquerade connections, and multicast memberships",
        .params = {},
        .func = 0
    },
    {
        .cmd = "ss",
        .desc = "print socket statistics",
        .params = {},
        .func = 0
    },
    {
        .cmd = "wget",
        .desc = "non-interactive network downloader",
        .params = {},
        .func = 0
    },
    {
        .cmd = "curl",
        .desc = "transfer a URL",
        .params = {},
        .func = 0
    },
    {
        .cmd = "whoami",
        .desc = "print effective userid",
        .params = {},
        .func = 0
    },
    {
        .cmd = "who",
        .desc = "show who is logged on",
        .params = {},
        .func = 0
    },
    {
        .cmd = "w",
        .desc = "show who is logged on and what they are doing",
        .params = {},
        .func = 0
    },
    {
        .cmd = "last",
        .desc = "show last logged in users",
        .params = {},
        .func = 0
    },
    {
        .cmd = "id",
        .desc = "print real and effective user and group IDs",
        .params = {},
        .func = 0
    },
    {
        .cmd = "groups",
        .desc = "print the groups a user is in",
        .params = {},
        .func = 0
    },
    {
        .cmd = "passwd",
        .desc = "change user password",
        .params = {},
        .func = 0
    },
    {
        .cmd = "su",
        .desc = "run a command with substitute user and group ID",
        .params = {},
        .func = 0
    },
    {
        .cmd = "sudo",
        .desc = "execute a command as another user",
        .params = {},
        .func = 0
    },
    {
        .cmd = "adduser",
        .desc = "add a new user to the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "deluser",
        .desc = "remove a user or remove a user from a group",
        .params = {},
        .func = 0
    },
    {
        .cmd = "addgroup",
        .desc = "add a new group to the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "delgroup",
        .desc = "remove a group from the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "usermod",
        .desc = "modify a user account",
        .params = {},
        .func = 0
    },
    {
        .cmd = "groupmod",
        .desc = "modify a group account",
        .params = {},
        .func = 0
    },
    {
        .cmd = "userdel",
        .desc = "remove a user account and related files",
        .params = {},
        .func = 0
    },
    {
        .cmd = "groupdel",
        .desc = "remove a group from the system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "chown",
        .desc = "change file owner and group",
        .params = {},
        .func = 0
    },
    {
        .cmd = "chgrp",
        .desc = "change group ownership",
        .params = {},
        .func = 0
    },
    {
        .cmd = "chmod",
        .desc = "change file mode bits",
        .params = {},
        .func = 0
    },
    {
        .cmd = "chattr",
        .desc = "change file attributes on a Linux file system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "lsattr",
        .desc = "list file attributes on a Linux file system",
        .params = {},
        .func = 0
    },
    {
        .cmd = "chroot",
        .desc = "run command or interactive shell with special root directory",
        .params = {},
        .func = 0
    },
    {
        .cmd = "date",
        .desc = "print or set the system date and time",
        .params = {},
        .func = 0
    },
    {
        .cmd = "cal",
        .desc = "print a calendar",
        .params = {},
        .func = 0
    },
    {
        .cmd = "bc",
        .desc = "an arbitrary precision calculator language",
        .params = {},
        .func = 0
    },
    {
        .cmd = "dc",
        .desc = "a reverse polish notation calculator",
        .params = {},
        .func = 0
    },
    {
        .cmd = "expr",
        .desc = "evaluate expressions",
        .params = {},
        .func = 0
    },
    {
        .cmd = "factor",
        .desc = "print prime factors",
        .params = {},
        .func = 0
    },
    {
        .cmd = "fmt",
        .desc = "reformat paragraph text",
        .params = {},
        .func = 0
    },
    {
        .cmd = "fold",
        .desc = "wrap each input line to fit in specified width",
        .params = {},
        .func = 0
    },
    {
        .cmd = "head",
        .desc = "output the first part of files",
        .params = {},
        .func = 0
    },
    {
        .cmd = "join",
        .desc = "join lines of two files on a common field",
        .params = {},
        .func = 0
    },
    {
        .cmd = "nl",
        .desc = "number lines of files",
        .params = {},
        .func = 0
    },
    {
        .cmd = "od",
        .desc = "dump files in octal and other formats",
        .params = {},
        .func = 0
    },
    {
        .cmd = "paste",
        .desc = "merge lines of files",
        .params = {},
        .func = 0
    },
    {
        .cmd = "pr",
        .desc = "paginate and columnate files for printing",
        .params = {},
        .func = 0
    },
    {
        .cmd = "ptx",
        .desc = "pretty-print text files",
        .params = {},
        .func = 0
    },
    {
        .cmd = "sort",
        .desc = "sort lines of text files",
        .params = {},
        .func = 0
    },
    {
        .cmd = "split",
        .desc = "split a file into pieces",
        .params = {},
        .func = 0
    },
    {
        .cmd = "sum",
        .desc = "checksum and count the blocks in a file",
        .params = {},
        .func = 0
    },
};