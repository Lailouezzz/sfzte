/* *****************************************************************************
 * exec.c -- All necessary for run 6502 emulation
 *
 * Copyright (C) 2020 Lailouezzz <alanlebouder@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ************************************************************************** */
#include "exec.h"


void sfzt_reset(sfzt_ctx_s *ctx)
{
    REGPC = 0x400;//CREATE_WORD(READ8(0xFFFE), READ8(0xFFFF));
    REGA = 0;
    REGX = 0;
    REGY = 0;
    REGSP = 0xFD;
    SET_CONSTANT(*ctx);
}

void sfzt_run(sfzt_ctx_s *ctx)
{
    //while(1)
    {
        printf("0x%04x : ", REGPC);
        BYTE op = READ8(REGPC++);
        printf("0x%02x 0x%02x 0x%02x : ", op, READ8(REGPC), READ8(REGPC + 1));
        SET_CONSTANT(*ctx);

        sfzt_addr ea = (*am_table[op])(ctx);
        (*opcode_table[op])(ctx, ea);
        printf(" = ");
        printf("ACC : 0x%02x | X : 0x%02x | Y : 0x%02x | PC : 0x%04x | SP : 0x%02x | EA : 0x%04x | (EA) : 0x%02x\n", REGA, REGX, REGY, REGPC, REGSP, ea, READ8(ea));
        printf("\n");

    }
}
