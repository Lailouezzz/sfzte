/* *****************************************************************************
 * addr_modes.c -- All address mode fonction for 6502
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
#define OP_LO_BYTE_ADDR (ctx->pc+1)
#define OP_HI_BYTE_ADDR (ctx->pc+2)
#define OP_LO_BYTE (READ8(OP_LO_BYTE_ADDR))
#define OP_HI_BYTE (READ8(OP_HI_BYTE_ADDR))


// REGPC is positionned at the opcode so first byte is at REGPC+1

IMPL_AM(nnn)
{
    UNUSED(ctx);
    return 1;
}
IMPL_DAM(nnn)
{
    UNUSED(ctx);
    if(maxlen >= 1)
    {
        dst[0] = '\0';
        return 0;
    }
    else
    {
        return -1;
    }
}

IMPL_AM(acc)
{
    return AM(nnn)(ctx);
}
IMPL_DAM(acc)
{
    UNUSED(ctx);
    return snprintf(dst, maxlen, "A");
}

IMPL_AM(abs)
{
    EA = (sfzte_addr) CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE);
    return 3;
}
IMPL_DAM(abs)
{
    return snprintf(dst, maxlen, "$%04x", CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE));
}

IMPL_AM(abx)
{
    EA = (sfzte_addr) CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE) + REGX;
    return 3;
}
IMPL_DAM(abx)
{
    return snprintf(dst, maxlen, "$%04x, X", 
            CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE));
}

IMPL_AM(aby)
{
    EA = (sfzte_addr) CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE) + REGY;
    return 3;
}
IMPL_DAM(aby)
{
    return snprintf(dst, maxlen, "$%04x, Y", 
            CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE));
}

IMPL_AM(imm)
{
    EA = (sfzte_addr) OP_LO_BYTE_ADDR;
    return 2;
}
IMPL_DAM(imm)
{
    return snprintf(dst, maxlen, "#%02x", OP_LO_BYTE);
}

IMPL_AM(imp)
{
    return AM(nnn)(ctx);
}
IMPL_DAM(imp)
{
    return DAM(nnn)(dst, maxlen, ctx);
}

IMPL_AM(ind)
{
    EA = CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE);
    EA = (sfzte_addr) CREATE_WORD(READ8(EA), READ8(EA+1));
    return 3;
}
IMPL_DAM(ind)
{
    return snprintf(dst, maxlen, "($%04x)", 
            CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE));
}

IMPL_AM(xin)
{
    EA = (OP_LO_BYTE + REGX) & 0x00FF;
    EA = (sfzte_addr) CREATE_WORD(READ8(EA), READ8(EA+1));
    return 2;
}
IMPL_DAM(xin)
{
    return snprintf(dst, maxlen, "($%02x, X)", OP_LO_BYTE);
}

IMPL_AM(iny)
{
    EA = OP_LO_BYTE & 0x00FF;
    EA = (sfzte_addr) CREATE_WORD(READ8(EA), READ8(EA+1)) + REGY;
    return 2;
}
IMPL_DAM(iny)
{
    return snprintf(dst, maxlen, "($%02x), Y", OP_LO_BYTE);
}

IMPL_AM(rel)
{
    EA = (sfzte_addr) ((REGPC+2) + (int8_t) OP_LO_BYTE);
    return 2;
}
IMPL_DAM(rel)
{
    return snprintf(dst, maxlen, "$%04x", (REGPC+2) + (int8_t) OP_LO_BYTE);
}

IMPL_AM(zpg)
{
    EA = (sfzte_addr) (OP_LO_BYTE & 0x00FF);
    return 2;
}
IMPL_DAM(zpg)
{
    return snprintf(dst, maxlen, "$00%02x", OP_LO_BYTE);
}

IMPL_AM(zpx)
{
    EA = (sfzte_addr) ((OP_LO_BYTE & 0x00FF) + REGX) & 0x00FF;
    return 2;
}
IMPL_DAM(zpx)
{
    return snprintf(dst, maxlen, "$%04x, X", OP_LO_BYTE);
}

IMPL_AM(zpy)
{
    EA = (sfzte_addr) ((OP_LO_BYTE & 0x00FF) + REGY) & 0x00FF;
    return 2;
}
IMPL_DAM(zpy)
{
    return snprintf(dst, maxlen, "$%04x, Y", OP_LO_BYTE);
}
