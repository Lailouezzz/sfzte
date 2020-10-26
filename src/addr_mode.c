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
IMPL_AM(acc)
{
    return AM(nnn)(ctx);
}
IMPL_AM(abs)
{
    EA = (sfzt_addr) CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE);
    return 3;
}
IMPL_AM(abx)
{
    EA = (sfzt_addr) CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE) + REGX;
    return 3;
}
IMPL_AM(aby)
{
    EA = (sfzt_addr) CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE) + REGY;
    return 3;
}
IMPL_AM(imm)
{
    EA = (sfzt_addr) OP_LO_BYTE_ADDR;
    return 2;
}
IMPL_AM(imp)
{
    return AM(nnn)(ctx);
}
IMPL_AM(ind)
{
    EA = CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE);
    EA = (sfzt_addr) CREATE_WORD(READ8(EA), READ8(EA+1));
    return 3;
}
IMPL_AM(xin)
{
    EA = (OP_LO_BYTE + REGX) & 0x00FF;
    EA = (sfzt_addr) CREATE_WORD(READ8(EA), READ8(EA+1));
    return 2;
}
IMPL_AM(iny)
{
    EA = READ8(ctx->pc);
    EA = (sfzt_addr) CREATE_WORD(READ8(EA), READ8(EA+1)) + REGY;
    return 2;
}
IMPL_AM(rel)
{
    EA = (sfzt_addr) ((REGPC+2) + (int8_t) OP_LO_BYTE);
    return 2;
}
IMPL_AM(zpg)
{
    EA = (sfzt_addr) (OP_LO_BYTE & 0x00FF);
    return 2;
}
IMPL_AM(zpx)
{
    EA = (sfzt_addr) ((OP_LO_BYTE & 0x00FF) + REGX) & 0x00FF;
    return 2;
}
IMPL_AM(zpy)
{
    EA = (sfzt_addr) ((OP_LO_BYTE & 0x00FF) + REGY) & 0x00FF;
    return 2;
}
