#include"info.h"
#include"satio/serial.h"

const char *LABEL = "SatoriOS 0.0.1\n";

const char *LOGO =
    "   _____       __             _    ____  _____\n"
    "  / ___/____ _/ /_____  _____(_)  / __ \\/ ___/\n"
    "  \\__ \\/ __ `/ __/ __ \\/ ___/ /  / / / /\\__ \\ \n"
    " ___/ / /_/ / /_/ /_/ / /  / /  / /_/ /___/ / \n"
    "/____/\\__,_/\\__/\\____/_/  /_/   \\____//____/  \n";

const char *BIRTHDAY = "2022-10-01";

const char *COPYRIGHT = "Copyright (C) 2022 Kogler. All Rights Resevered.\n";

const char *ORIGIN = "The Story Originated on October 1, 2022.\n";

const char *THANKS = "Thanks to the Support of Beijing Jiaotong University.\n";

void print_info()
{
    puts(LOGO);
    newline();
    puts(LABEL);
    newline();
    puts(ORIGIN);
    puts(COPYRIGHT);
    puts(THANKS);
    newline();
}