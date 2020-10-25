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


void reset(sfzt_ctx_s *ctx)
{
    REGPC = CREATE_WORD(READ8(0xFFFE), READ8(0xFFFF));
    REGA = 0;
    REGX = 0;
    REGY = 0;
    REGSP = 0xFD;
    SET_CONSTANT(*ctx);
}

void run(sfzt_ctx_s *ctx)
{
    while(1)
    {
        BYTE op = READ8(REGPC++);
        SET_CONSTANT(*ctx);

        (*opcode_table[op])(ctx, (*am_table[op])(ctx));
    }
}
