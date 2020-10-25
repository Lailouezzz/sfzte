#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sfzte.h"


static BYTE sfzte_data[0x10000];

BYTE sfzte_data_read(sfzt_addr addr);
void sfzte_data_write(BYTE v, sfzt_addr addr);

int main(int argc, char *argv[])
{
    UNUSED(argv);
    if(argc != 2)
    {
        printf("Error please enter filename : sfzte [file]\n");
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    printf("Openning %s\n", filename);

    FILE *fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        printf("Error when openning %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if(fread(sfzte_data, 1, sizeof(sfzte_data), fp) != sizeof(sfzte_data))
    {
        printf("File size to small\n");
        exit(EXIT_FAILURE);
    }

    sfzt_ctx_s ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.read = sfzte_data_read;
    ctx.write = sfzte_data_write;

    sfzt_reset(&ctx);
    for(int i = 0; i < 25000; i++)
        sfzt_run(&ctx);

    fclose(fp);
    return EXIT_SUCCESS;
}

BYTE sfzte_data_read(sfzt_addr addr)
{
    return sfzte_data[addr];
}
void sfzte_data_write(BYTE v, sfzt_addr addr)
{
    sfzte_data[addr] = v;
}