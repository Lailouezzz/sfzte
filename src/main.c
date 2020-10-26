#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sfzte.h"


static BYTE sfzte_data[0x10000];

BYTE sfzte_data_read(sfzt_addr addr);
void sfzte_data_write(BYTE v, sfzt_addr addr);
void sfzte_cb(BYTE opsize, sfzt_ctx_s *ctx);

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
    ctx.pc = 0x400;
    sfzt_run(50000, &ctx, sfzte_cb);

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
void sfzte_cb(BYTE opsize, sfzt_ctx_s *ctx)
{
    static sfzt_addr lastpc = 0;
    printf("0x%04x : ", REGPC);

    // Check if we are in a trap
    if(lastpc == REGPC)
    {
        getchar();
    }
    lastpc = REGPC;

    // Print data at PC
    for(BYTE i = 0; i < opsize; i++)
    {
        printf("0x%02x ", READ8(REGPC+i));
    }
    for(BYTE i = opsize; i < 3; i++)
    {
        printf("     ");
    }

    // Reg info
    printf("A  : 0x%02x | ", REGA);
    printf("X  : 0x%02x | ", REGX);
    printf("Y  : 0x%02x | ", REGY);
    printf("SP : 0x%02x | ", REGSP);
    printf("SR : ");
    for(BYTE i = 0x80; i != 0; i >>= 1)
    {
        printf("%d", (REGSR & i) ? 1 : 0);
    }
    printf(" | ");
    printf("EA : 0x%04x\n", EA);
    return;
}