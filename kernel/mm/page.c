// void* get_free_page()
// {
//     for (u64 i = 0; i < MAX_SPACE / 64 / PAGE_SIZE; i++)
//     {
//         if (bitmap[i] != 0xffffffffffffffff)
//         {
//             for (u64 j = 0; j < 64; j++)
//             {
//                 if ((bitmap[i] & (1UL << j)) == 0)
//                 {
//                     bitmap[i] |= (1UL << j);
//                     return (void *)(i * 64 * PAGE_SIZE + j * PAGE_SIZE);
//                 }
//             }
//         }
//     }
//     return NULL;
// }

// int free_page(void* addr)
// {
//     u64 i = (u64)addr / PAGE_SIZE;
//     bitmap[i / 64] &= ~(1UL << (i % 64));
//     return 0;
// }