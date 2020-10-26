#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sfzte.h"


static BYTE sfzte_data[0x10000];

BYTE sfzte_data_read(sfzt_addr addr);
void sfzte_data_write(BYTE v, sfzt_addr addr);
void sfzte_debug(BYTE opsize, sfzt_ctx_s *ctx);
BYTE sfzte_cb(BYTE opsize, sfzt_ctx_s *ctx);

int main(int argc, char *argv[])
{
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
    sfzt_run(INT_FAST64_MAX, &ctx, sfzte_cb);
    printf("Final : 0x%04x\n", ctx.pc);

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

void sfzte_debug(BYTE opsize, sfzt_ctx_s *ctx)
{
    // Print data at PC
    printf("0x%04x : ", REGPC);
    for(BYTE i = 0; i < opsize; i++)
    {
        printf("0x%02x ", READ8(REGPC+i));
    }
    for(BYTE i = opsize; i < 3; i++)
    {
        printf("     ");
    }
    printf(":    ");

    // Print decoded op
    char buf[256];
    if ((*am__disasm_table[CURRENT_OP])(buf, sizeof(buf), ctx) < 0)
    {
        // TODO :  handle error
    }
    printf("%-4s %-12s|  ", opcode_name_table[CURRENT_OP], 
                      buf);

    // Print reg info
    printf("EA : 0x%04x  |  ", EA);
    printf("(EA)  : 0x%02x  |  ", READ8(EA));
    printf("A  : 0x%02x  |  ", REGA);
    printf("X  : 0x%02x  |  ", REGX);
    printf("Y  : 0x%02x  |  ", REGY);
    printf("SP : 0x%02x  |  ", REGSP);
    printf("(SP-1) : 0x%02x  |  ", READ8(REGSP-1));
    printf("SR : ");
    for(BYTE i = 0x80; i != 0; i >>= 1)
    {
        printf((REGSR & i) ? "1" : "0");
    }
    printf("\n");
    return;
}

BYTE sfzte_cb(BYTE opsize, sfzt_ctx_s *ctx)
{
    UNUSED(opsize);
    // Check if we are in a trap
    static sfzt_addr lastpc = 0;
    if(lastpc == REGPC)
    {
        printf("TRAP : 0x%04x", REGPC);
        getchar();
        return 0;
    }
    lastpc = REGPC;

    // If we achieved the test
    if(REGPC == 0x3469)
    {
        printf("SUCCESS");
        getchar();
        return 0;
    }
    return 1;
}
