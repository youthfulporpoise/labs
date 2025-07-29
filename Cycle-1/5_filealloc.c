#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define     DIRSIZE     32

typedef     enum { SEQN, INDX, LINK }       alloc_type;

typedef struct {
    char name[64];
    alloc_type type;
    size_t blocks[32],
           blkc;
} file;

file directory[DIRSIZE];
bool mem[DIRSIZE];

void print_file(file f)
{
    printf("%s\t", f.name);
    switch (f.type) {
        case SEQN:
            for (size_t i = 0; i < f.blkc; ++i)
                printf("%3zu ", f.blocks[i]);
            puts("");
            break;

        case INDX:
            printf("%3zu\t[ ", f.blocks[0]);
            for (size_t i = 1; i < f.blkc; ++i)
                printf("%3zu ", f.blocks[i]);
            puts(" ]");
            break;

        case LINK:
            printf("%3zu ", f.blocks[0]);
            for (size_t i = 1; i < f.blkc; ++i)
                printf(" --> %3zu ", f.blocks[i]);
            puts("");
            break;
    }
}

void clrbuff()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char **argv)
{
    size_t filec;
    printf("The number of files for allocation\n> ");
    scanf("%zu", &filec);

    char type;
    size_t start,               /*  The start of an allocation          */
           length,              /*  The allocation length in SEQN       */
           blkc,                /*  The block count                     */
           blk;                 /*  The current block holder            */

    for (size_t i = 0; i < DIRSIZE; ++i)
        mem[i] = false;

    for (size_t i = 0; i < filec; ++i) {
        puts(""); clrbuff();

        printf("Filename\n> ");
        scanf(" %s", directory[i].name);
        printf("Allocation type (S, I, L)\n> ");
        scanf(" %c", &type);

        switch (type) {
            case 'S':
                directory[i].type = SEQN;

                printf("Start   Length\n> ");
                scanf("%zu %zu", &start, &length);

                for (size_t j = 0; j < length; ++j) {
                    blk = start + j;
                    if (mem[blk]) goto error;
                    else mem[blk] = true;
                    directory[i].blocks[j] = blk;
                } directory[i].blkc = length;
                break;

            case 'I':
                directory[i].type = INDX;

                printf("Index block     Number of blocks\n> ");
                scanf("%zu %zu", &blk, &blkc);
                if (mem[blk]) goto error;
                else mem[blk] = true;
                directory[i].blocks[0] = blk;

                printf("Blocks (%zu)\n> ", blkc);
                for (size_t j = 1; j < blkc; ++j) {
                    scanf("%zu", &blk);
                    if (mem[blk]) goto error;
                    else mem[blk] = true;
                    directory[i].blocks[j] = blk;
                }
                directory[i].blkc = blkc;
                break;

            case 'L':
                directory[i].type = LINK;

                printf("Number of blocks\n> ");
                scanf("%zu", &blkc);

                printf("Blocks\n> ");
                for (size_t j = 0; j < blkc; ++j) {
                    scanf("%zu", &blk);
                    if (mem[j]) goto error;
                    else mem[j] = true;
                    directory[i].blocks[j] = blk;
                }
                directory[i].blkc = blkc;
                break;

            default:
                printf("%c: unknown allocation type\nSkipping . . .\n", type);
                continue;
        }

        continue;
        error:
            puts("This file cannot be fully allocated.");
            continue;
    }

    puts("\nDirectory");
    for (size_t i = 0; i < filec; ++i)
        print_file(directory[i]);

    return 0;
}
