#ifndef _MM_BITMAP_H_
#define _MM_BITMAP_H_

#include "types.h"

void set_bit(byte *bitmap, int index, const byte value);

int alloc_bits(byte *bitmap, int map_size, int size, int *last);
int alloc_aligned_bits(byte *bitmap, int map_size, int size, int *last);

void free_bits(byte *bitmap, int index, int size);
void free_aligned_bits(byte *bitmap, int index, int size);

void print_bitmap(byte *bitmap, int size);

#endif /* !_MM_BITMAP_H_ */