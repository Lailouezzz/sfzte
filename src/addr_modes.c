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


// REGPC is positionned after the opcode so first byte is at REGPC

DECL_AM(abs)
{
    sfzt_addr ea = (sfzt_addr) CREATE_WORD(OP_LO_BYTE, OP_HI_BYTE);
    ctx->pc += 2;
    return ea;
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
    sfzt_addr ea = (sfzt_addr) OP_LO_BYTE;
    ctx->pc += 1;
    return ea;
}
DECL_AM(ind)
{
    sfzt_addr ea = addr_abs(ctx);
    ea = (sfzt_addr) CREATE_WORD(CTX_READ(ea), CTX_READ(ea+1));
    return ea;
}
DECL_AM(xind)
{
    sfzt_addr ea = (OP_LO_BYTE + REGX) & 0x00FF;
    ea = (sfzt_addr) CREATE_WORD(CTX_READ(ea), CTX_READ(ea+1));
    ctx->pc += 1;
    return ea;
}
DECL_AM(indy)
{
    sfzt_addr ea = CTX_READ(ctx->pc);
    ea = (sfzt_addr) CREATE_WORD(CTX_READ(ea), CTX_READ(ea+1)) + REGY;
    ctx->pc += 1;
    return ea;
}
DECL_AM(rel)
{
    sfzt_addr ea = (sfzt_addr) ((REGPC+1) + (int8_t) OP_LO_BYTE);
    ctx->pc += 1;
    return ea;
}
DECL_AM(zpg)
{
    sfzt_addr ea = (sfzt_addr) (OP_LO_BYTE & 0x00FF);
    ctx->pc += 1;
    return ea;
}
DECL_AM(zpgx)
{
    sfzt_addr ea = (sfzt_addr) ((addr_zpg(ctx) + REGX) & 0x00FF);
    return ea;
}
DECL_AM(zpgy)
{
    sfzt_addr ea = (sfzt_addr) ((addr_zpg(ctx) + REGY) & 0x00FF);
    return ea;
}
