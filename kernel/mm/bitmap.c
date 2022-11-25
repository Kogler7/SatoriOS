#include "mm/bitmap.h"
#include "sysio/io.h"

void set_bit(byte *bitmap, int index, const byte value)
{
    if (value == 0)
        bitmap[index / 8] &= ~(1 << (index % 8));
    else
        bitmap[index / 8] |= (1 << (index % 8));
}

int alloc_bits(byte *bitmap, int map_size, int size, int *last)
{
    int last_i = *last / 8;
    int i = last_i, j = *last % 8, k = 0;
    while (k < size)
    {
        if (j == 8)
        {
            j = 0;
            i = (i + 1) % map_size;
            if (i == last_i)
                return -1;
        }
        if ((bitmap[i] & (1 << j)) == 0)
            k++;
        else
            k = 0;
        j++;
    }
    *last = i * 8 + j;
    for (int l = 0; l < size; l++)
        set_bit(bitmap, *last - l - 1, 1);
    return *last - size;
}

// 尚未测试
int alloc_aligned_bits(byte *bitmap, int map_size, int size, int *last)
{
    int last_i = (*last + 7) / 8 % map_size;
    size = (size + 7) / 8;
    int i = last_i, k = 0;
    while (k < size)
    {
        if (bitmap[i] == 0)
            k++;
        else
            k = 0;
        i = (i + 1) % map_size;
        if (i == last_i)
            return -1;
    }
    *last = i * 8;
    for (int l = 0; l < size; l++)
        bitmap[i - l - 1] = 0xFF;
    return *last - size * 8;
}

void free_bits(byte *bitmap, int index, int size)
{
    for (int i = 0; i < size; i++)
        set_bit(bitmap, index + i, 0);
}

// 尚未测试
void free_aligned_bits(byte *bitmap, int index, int size)
{
    size = (size + 7) / 8;
    index = (index + 7) / 8;
    for (int i = 0; i < size; i++)
        bitmap[index + i] = 0;
}

void print_bitmap(byte *bitmap, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 8; j++)
            printf("%d", (bitmap[i] >> j) & 1);
        printf(" ");
        if (i % 4 == 3)
            printf("\n");
    }
}