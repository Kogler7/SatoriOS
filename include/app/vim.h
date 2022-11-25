#include "fs/fs.h"

#define WIN_X 79
#define WIN_Y 24

void clear_screen();

void print2screen();

void update_file();

void create_copy();

void vim_input_handle(char c, int state, int kbd_n);

int vim_entry(struct file_folder *relative_path, char *file_name);
