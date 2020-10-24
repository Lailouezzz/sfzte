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


sfzt_addr addr_abs(sfzt_ctx_s *ctx)
{
    byte lo = ctx->read(ctx->pc);
    byte hi = ctx->read(ctx->pc+1);
    return (sfzt_addr) (lo + (hi << 8));
}
sfzt_addr addr_absx(sfzt_ctx_s *ctx)
{
    return addr_abs(ctx) + ctx->x;
}
sfzt_addr addr_absy(sfzt_ctx_s *ctx)
{
    return addr_abs(ctx) + ctx->y;
}
sfzt_addr addr_imm(sfzt_ctx_s *ctx)
{
    return ctx->pc;
}
sfzt_addr addr_imp(sfzt_ctx_s UNUSED *ctx)
{
    return 0;
}
sfzt_addr addr_ind(sfzt_ctx_s *ctx)
{
    sfzt_addr addr = addr_abs(ctx);
    byte lo = ctx->read(addr);
    byte hi = ctx->read(addr+1);
    return (sfzt_addr) (lo + (hi << 8));
}
sfzt_addr addr_xind(sfzt_ctx_s *ctx)
{
    sfzt_addr addr = (ctx->read(ctx->pc) + ctx->x) & 0x00FF;
    byte lo = ctx->read(addr);
    byte hi = ctx->read(addr+1);
    return (sfzt_addr) (lo + (hi << 8));
}
sfzt_addr addr_indy(sfzt_ctx_s *ctx)
{
    sfzt_addr addr = ctx->read(ctx->pc);
    byte lo = ctx->read(addr);
    byte hi = ctx->read(addr+1);
    return (sfzt_addr) (lo + (hi << 8) + ctx->y);
}
sfzt_addr addr_rel(sfzt_ctx_s *ctx)
{
    sfzt_addr addr = ctx->pc;
    int8_t bb = (int8_t) ctx->read(ctx->pc);
    return (sfzt_addr) (addr + bb);
}
sfzt_addr addr_zpg(sfzt_ctx_s *ctx)
{
    return (sfzt_addr) (ctx->read(ctx->pc) & 0x00FF);
}
sfzt_addr addr_zpgx(sfzt_ctx_s *ctx)
{
    return (sfzt_addr) ((addr_zpg(ctx) + ctx->x) & 0x00FF);
}
sfzt_addr addr_zpgy(sfzt_ctx_s *ctx)
{
    return (sfzt_addr) ((addr_zpg(ctx) + ctx->y) & 0x00FF);
}
