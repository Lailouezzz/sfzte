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

#define NEGATIVE    1 << 7
#define OVERFLOW    1 << 6
#define BREAK       1 << 4
#define DECIMAL     1 << 3
#define INTERRUPT   1 << 2
#define ZERO        1 << 1
#define CARRY       1 << 0

#define IS_CARRY(ctx) ((ctx).status && CARRY != 0)


struct sfzt_ctx
{
    bus_read read;
    bus_write write;

    sfzt_addr pc; // program counter
    byte a, x, y; // 3 registers
    // 8 N (negative) - 7 V (overflow)  - 6 ignored  - 5 B (break) 
    // 4 D (decimal)  - 3 I (interrupt) - 2 Z (zero) - 1 C (carry)
    byte status;
    byte sp;
};

typedef struct sfzt_ctx sfzt_ctx_s; 


#endif /// #ifndef H_SFZT_CONTEXT
