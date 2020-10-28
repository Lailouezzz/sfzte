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
#include "sfzte.h"


void sfzt_reset(sfzt_ctx_s *ctx)
{
    REGPC = CREATE_WORD(READ8(RSTVECTOR), READ8(RSTVECTOR+1));
    REGA = 0x00;
    REGX = 0x00;
    REGY = 0x00;
    REGSP = 0xFD;
    REGSR = 0x00;
    SET_CONSTANT(*ctx);
    SET_INTERRUPT(*ctx);
}

void sfzt_run(size_t n, sfzt_ctx_s *ctx, exec_cb cb)
{
    for(size_t i = 0; i < n; i++)
    {
        // Fetch
        BYTE op = CURRENT_OP;
        SET_CONSTANT(*ctx);

        // Resolve ea
        BYTE opsize = (*am_table[op])(ctx);

        // FIX me : cb can irq nmi etc ?
        // Call callback before execute opcode
        if(cb != NULL)
            if(cb(opsize, ctx) != 1)
                break;

        // FIX me : when REGPC is updated ?
        // Execute opcode
        (*opcode_table[op])(ctx, opsize);
    }
}

void sfzt_irq(sfzt_ctx_s *ctx)
{
    if(!IS_INTERRUPT(*ctx)) // If irq are not disabled
    {
        CLEAR_BREAK(*ctx);
        push_word(REGPC, ctx);
        push_byte(REGSR, ctx);
        SET_INTERRUPT(*ctx);
        REGPC = CREATE_WORD(READ8(IRQVECTOR), READ8(IRQVECTOR+1));
    }
}

void sfzt_nmi(sfzt_ctx_s *ctx)
{
    CLEAR_BREAK(*ctx);
    push_word(REGPC, ctx);
    push_byte(REGSR, ctx);
    SET_INTERRUPT(*ctx);
    REGPC = CREATE_WORD(READ8(NMIVECTOR), READ8(NMIVECTOR+1));
}
