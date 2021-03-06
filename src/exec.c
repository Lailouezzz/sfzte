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


void sfzte_reset(sfzte_ctx_s *ctx)
{
    REGPC = CREATE_WORD(READ8(0xFFFC), READ8(0xFFFD));
    REGA = 0;
    REGX = 0;
    REGY = 0;
    REGSP = 0xFD;
    SET_CONSTANT(*ctx);
}

void sfzte_run(size_t n, sfzte_ctx_s *ctx, exec_cb cb)
{
    for (size_t i = 0; i < n; ++i)
    {
        // Fetch
        BYTE op = CURRENT_OP;
        SET_CONSTANT(*ctx);

        // Resolve ea
        BYTE opsize = (*am_table[op])(ctx);

        // Call callback before execute opcode
        if (cb != NULL)
        {
            BYTE ret = cb(opsize, ctx);
            if (ret == SFZTE_CB_STOP)
            {
                break;
            }
            else if (ret == SFZTE_CB_SKIP)
            {
                continue;
            }
        }

        // Execute opcode
        (*opcode_table[op])(ctx, opsize);
    }
}
