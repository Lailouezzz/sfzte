/* *****************************************************************************
 * exec.h -- All necessary for run 6502 emulation
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
#ifndef H_EXEC
#define H_EXEC
#include <stdlib.h>
#include <stdio.h>
#include "addr_mode.h"
#include "opcode.h"
#include "sfzte_context.h"
#include "util.h"


#define SFZTE_CB_OK 0
#define SFZTE_CB_STOP 1
#define SFZTE_CB_SKIP 2


// exec_cb can be used for manage some device 
typedef BYTE (*exec_cb)(BYTE opsize, sfzte_ctx_s *ctx);

void sfzte_reset(sfzte_ctx_s *ctx);

void sfzte_run(size_t n, sfzte_ctx_s *ctx, exec_cb cb);


#endif /// #ifndef H_EXEC
