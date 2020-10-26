/* *****************************************************************************
 * sfzt_context.h -- All necessary for 6502 status
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
#ifndef H_SFZT_CONTEXT
#define H_SFZT_CONTEXT
#include <stdint.h>
#include "util.h"

#define STACK_ADDR      0x0100  

#define EA      (ctx->ea)
#define REGA    (ctx->a)
#define REGX    (ctx->x)
#define REGY    (ctx->y)
#define REGPC   (ctx->pc)
#define REGSP   (ctx->sp)
#define REGSR   (ctx->sr)

#define FLAG_NEGATIVE   (1 << 7)
#define FLAG_OVERFLOW   (1 << 6)
#define FLAG_CONSTANT   (1 << 5)
#define FLAG_BREAK      (1 << 4)
#define FLAG_DECIMAL    (1 << 3)
#define FLAG_INTERRUPT  (1 << 2)
#define FLAG_ZERO       (1 << 1)
#define FLAG_CARRY      (1 << 0)

#define IS_CARRY(ctx)       (((ctx).sr & FLAG_CARRY) != 0)
#define IS_ZERO(ctx)        (((ctx).sr & FLAG_ZERO) != 0)
#define IS_INTERRUPT(ctx)   (((ctx).sr & FLAG_INTERRUPT) != 0)
#define IS_DECIMAL(ctx)     (((ctx).sr & FLAG_DECIMAL) != 0)
#define IS_BREAK(ctx)       (((ctx).sr & FLAG_BREAK) != 0)
#define IS_CONSTANT(ctx)    (((ctx).sr & FLAG_CONSTANT) != 0)
#define IS_OVERFLOW(ctx)    (((ctx).sr & FLAG_OVERFLOW) != 0)
#define IS_NEGATIVE(ctx)    (((ctx).sr & FLAG_NEGATIVE) != 0)

#define SET_CARRY(ctx)      ((ctx).sr |= FLAG_CARRY)
#define SET_ZERO(ctx)       ((ctx).sr |= FLAG_ZERO)
#define SET_INTERRUPT(ctx)  ((ctx).sr |= FLAG_INTERRUPT)
#define SET_DECIMAL(ctx)    ((ctx).sr |= FLAG_DECIMAL)
#define SET_BREAK(ctx)      ((ctx).sr |= FLAG_BREAK)
#define SET_CONSTANT(ctx)   ((ctx).sr |= FLAG_CONSTANT)
#define SET_OVERFLOW(ctx)   ((ctx).sr |= FLAG_OVERFLOW)
#define SET_NEGATIVE(ctx)   ((ctx).sr |= FLAG_NEGATIVE)

#define CLEAR_CARRY(ctx)        ((ctx).sr &= (BYTE)(~FLAG_CARRY))
#define CLEAR_ZERO(ctx)         ((ctx).sr &= (BYTE)(~FLAG_ZERO))
#define CLEAR_INTERRUPT(ctx)    ((ctx).sr &= (BYTE)(~FLAG_INTERRUPT))
#define CLEAR_DECIMAL(ctx)      ((ctx).sr &= (BYTE)(~FLAG_DECIMAL))
#define CLEAR_BREAK(ctx)        ((ctx).sr &= (BYTE)(~FLAG_BREAK))
#define CLEAR_CONSTANT(ctx)     ((ctx).sr &= (BYTE)(~FLAG_CONSTANT))
#define CLEAR_OVERFLOW(ctx)     ((ctx).sr &= (BYTE)(~FLAG_OVERFLOW))
#define CLEAR_NEGATIVE(ctx)     ((ctx).sr &= (BYTE)(~FLAG_NEGATIVE))

#define READ8(addr) (ctx->read((addr)))
#define WRITE8(b, addr) (ctx->write((b), (addr)))
#define READ8_EA READ8(EA)
#define WRITE8_EA(b) WRITE8(b, EA)
#define CURRENT_OP READ8(REGPC)


struct sfzt_ctx
{
    bus_read read;
    bus_write write;

    sfzt_addr pc; // program counter
    sfzt_addr ea; // effective address of current op
    BYTE a, x, y; // 3 registers
    // 8 N (negative) - 7 V (overflow)  - 6 ignored  - 5 B (break) 
    // 4 D (decimal)  - 3 I (interrupt) - 2 Z (zero) - 1 C (carry)
    BYTE sr;
    BYTE sp;
};

typedef struct sfzt_ctx sfzt_ctx_s; 


#endif /// #ifndef H_SFZT_CONTEXT
