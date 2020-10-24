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
#include "addr_modes.h"
#define CTX_READ(addr) (ctx->read(addr))
#define OP_LO_BYTE_ADDR (ctx->pc)
#define OP_HI_BYTE_ADDR (ctx->pc+1)
#define OP_LO_BYTE (CTX_READ(OP_LO_BYTE_ADDR))
#define OP_HI_BYTE (CTX_READ(OP_HI_BYTE_ADDR))
#define REGPC (ctx->pc)
#define REGX (ctx->x)
#define REGY (ctx->y)
#define CREATE_WORD(LL, HH) (LL + (HH << 8))


DECL_AM(abs)
{
    return (sfzt_addr) CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE);
}
DECL_AM(absx)
{
    return addr_abs(ctx) + REGX;
}
DECL_AM(absy)
{
    return addr_abs(ctx) + REGY;
}
DECL_AM(imm)
{
    return (sfzt_addr) OP_LO_BYTE;
}
DECL_AM(ind)
{
    sfzt_addr addr = addr_abs(ctx);
    return (sfzt_addr) CREATE_WORD(CTX_READ(addr), CTX_READ(addr+1));
}
DECL_AM(xind)
{
    sfzt_addr addr = (OP_LO_BYTE + REGX) & 0x00FF;
    return (sfzt_addr) CREATE_WORD(CTX_READ(addr), CTX_READ(addr+1));
}
DECL_AM(indy)
{
    sfzt_addr addr = ctx->read(ctx->pc);
    return (sfzt_addr) CREATE_WORD(CTX_READ(addr), CTX_READ(addr+1)) + REGY;
}
DECL_AM(rel)
{
    return (sfzt_addr) (REGPC + (int8_t) OP_LO_BYTE);
}
DECL_AM(zpg)
{
    return (sfzt_addr) (OP_LO_BYTE & 0x00FF);
}
DECL_AM(zpgx)
{
    return (sfzt_addr) ((addr_zpg(ctx) + REGX) & 0x00FF);
}
DECL_AM(zpgy)
{
    return (sfzt_addr) ((addr_zpg(ctx) + REGY) & 0x00FF);
}
