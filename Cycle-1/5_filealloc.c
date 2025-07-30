#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define     DIRSIZE     64

typedef     enum { SEQN, INDX, LINK }       alloc_type;
typedef struct {
    char name[64];                  /*  Filename                */
    alloc_type type;                /*  File allocation type    */
    size_t n;                       /*  Number of blocks        */
    size_t blocks[DIRSIZE];         /*  Blocks                  */
} file;

file directory[DIRSIZE];
bool memory[DIRSIZE];

/*  Allocate the i-th block as b for a file f.  */
void allocate(file *f, size_t *blocks, size_t blockc)
{
    size_t block;
    for (size_t i = 0; i < blockc; ++i) {
        block = blocks[i];
        if (memory[block])
            printf("`%s` could not be fully allocated.\n", f->name);
        else {
            f->blocks[i] = block;
            memory[block] = true;
        }
    } f->n = blockc;
}

void print_file(file f)
{
    printf("%-16s ", f.name);
    switch (f.type) {
        case SEQN:
            for (size_t i = 0; i < f.n; ++i)
                printf("%3zu ", f.blocks[i]);
            break;
        case INDX:
            printf("%3zu\t[ ", f.blocks[0]);
            for (size_t i = 1; i < f.n; ++i)
                printf("%3zu ", f.blocks[i]);
            printf("] ");
            break;
        case LINK:
            printf("%3zu ", f.blocks[0]);
            for (size_t i = 1; i < f.n; ++i)
                printf(" --> %3zu ", f.blocks[i]);
            break;
    } puts("");
}

int main(int argc, char **argv)
{
    size_t filec, type;
    printf("The number of files for allocation\n> ");
    scanf("%zu", &filec);

    size_t blocks[DIRSIZE],         /*  The blocks for allocation               */
           blockc,                  /*  The number of blocks for allocation     */
           start;                   /*  The start or index block                */

    for (size_t i = 0; i < filec; ++i) {
        printf("\nFilename\n> ");
        scanf("%s", directory[i].name);
        printf("Allocation type\t\t0 - Seqn, 1 - Indx, 2 - Link\n> ");
        scanf("%zu", &type);

        switch (type) {
            case 0:
                directory[i].type = SEQN;
                printf("Start   Length\n> ");
                scanf("%zu %zu", &start, &blockc);
                for (size_t j = 0; j  < blockc; ++j)
                    blocks[j] = start + j;
                break;

            case 1:
                directory[i].type = INDX;
                printf("Index block         Number of blocks\n> ");
                scanf("%zu %zu", &start, &blockc);
                blocks[0] = start;
                printf("Blocks\n> ");
                for (size_t j = 1; j <= blockc; ++j)
                    scanf("%zu", &blocks[j]);
                blockc++;
                break;

            case 2:
                directory[i].type = LINK;
                printf("Number of blocks        Blocks\n> ");
                scanf("%zu", &blockc);
                for (size_t j = 0; j < blockc; ++j)
                    scanf("%zu", &blocks[j]);
                break;

            default:
                puts("The allocation method is invalid.");
                continue;
        }
        allocate(&directory[i], blocks, blockc);
    } puts("");

    for (size_t i = 0; i < filec; ++i)
        print_file(directory[i]);
    return 0;
}
