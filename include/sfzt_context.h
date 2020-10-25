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

#define FLAG_NEGATIVE    (1 << 7)
#define FLAG_OVERFLOW    (1 << 6)
#define FLAG_BREAK       (1 << 4)
#define FLAG_DECIMAL     (1 << 3)
#define FLAG_INTERRUPT   (1 << 2)
#define FLAG_ZERO        (1 << 1)
#define FLAG_CARRY       (1 << 0)

#define IS_CARRY(ctx)       (((ctx).status & FLAG_CARRY) != 0)
#define IS_ZERO(ctx)        (((ctx).status & FLAG_ZERO) != 0)
#define IS_INTERRUPT(ctx)   (((ctx).status & FLAG_INTERRUPT) != 0)
#define IS_DECIMAL(ctx)     (((ctx).status & FLAG_DECIMAL) != 0)
#define IS_BREAK(ctx)       (((ctx).status & FLAG_BREAK) != 0)
#define IS_OVERFLOW(ctx)    (((ctx).status & FLAG_OVERFLOW) != 0)
#define IS_NEGATIVE(ctx)    (((ctx).status & FLAG_NEGATIVE) != 0)

#define SET_CARRY(ctx)      ((ctx).status |= FLAG_CARRY)
#define SET_ZERO(ctx)       ((ctx).status |= FLAG_ZERO)
#define SET_INTERRUPT(ctx)  ((ctx).status |= FLAG_INTERRUPT)
#define SET_DECIMAL(ctx)    ((ctx).status |= FLAG_DECIMAL)
#define SET_BREAK(ctx)      ((ctx).status |= FLAG_BREAK)
#define SET_OVERFLOW(ctx)   ((ctx).status |= FLAG_OVERFLOW)
#define SET_NEGATIVE(ctx)   ((ctx).status |= FLAG_NEGATIVE)

#define CLEAR_CARRY(ctx)        ((ctx).status &= (BYTE)(~FLAG_CARRY))
#define CLEAR_ZERO(ctx)         ((ctx).status &= (BYTE)(~FLAG_ZERO))
#define CLEAR_INTERRUPT(ctx)    ((ctx).status &= (BYTE)(~FLAG_INTERRUPT))
#define CLEAR_DECIMAL(ctx)      ((ctx).status &= (BYTE)(~FLAG_DECIMAL))
#define CLEAR_BREAK(ctx)        ((ctx).status &= (BYTE)(~FLAG_BREAK))
#define CLEAR_OVERFLOW(ctx)     ((ctx).status &= (BYTE)(~FLAG_OVERFLOW))
#define CLEAR_NEGATIVE(ctx)     ((ctx).status &= (BYTE)(~FLAG_NEGATIVE))


struct sfzt_ctx
{
    bus_read read;
    bus_write write;

    sfzt_addr pc; // program counter
    BYTE a, x, y; // 3 registers
    // 8 N (negative) - 7 V (overflow)  - 6 ignored  - 5 B (break) 
    // 4 D (decimal)  - 3 I (interrupt) - 2 Z (zero) - 1 C (carry)
    BYTE status;
    BYTE sp;
};

typedef struct sfzt_ctx sfzt_ctx_s; 


#endif /// #ifndef H_SFZT_CONTEXT
