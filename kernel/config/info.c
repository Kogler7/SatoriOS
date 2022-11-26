#include "config/info.h"
#include "io/stdio.h"

const char *LABEL = "SatoriOS";

const char *AUTHOR = "Kogler";

const char *VERSION = "SatoriOS 0.0.1";

const char *LOGO =
    "   _____       __             _    ____  _____\n\r"
    "  / ___/____ _/ /_____  _____(_)  / __ \\/ ___/\n\r"
    "  \\__ \\/ __ `/ __/ __ \\/ ___/ /  / / / /\\__ \\ \n\r"
    " ___/ / /_/ / /_/ /_/ / /  / /  / /_/ /___/ / \n\r"
    "/____/\\__,_/\\__/\\____/_/  /_/   \\____//____/  \n\r";

const char *BIRTHDAY = "2022-10-01";

const char *COPYRIGHT = "Copyright (C) 2022 Kogler. All Rights Resevered.";

const char *ORIGIN = "The Story Originated on October 1, 2022.";

const char *THANKS = "Thanks to the Support of Beijing Jiaotong University.";

void print_info()
{
    puts(LOGO);
    newline();
    puts(LABEL);
    newline();
    puts(ORIGIN);
    puts(COPYRIGHT);
    puts(THANKS);
}