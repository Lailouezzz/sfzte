/* *****************************************************************************
 * addr_modes.h -- All address mode fonction for 6502
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
#ifndef H_ADDR_MODE
#define H_ADDR_MODE
#include <stdint.h>
#include "sfzt_context.h"
#include "util.h"


typedef sfzt_addr (*addr_mode)(sfzt_ctx_s *);

sfzt_addr addr_abs(sfzt_ctx_s *ctx);
sfzt_addr addr_absx(sfzt_ctx_s *ctx);
sfzt_addr addr_absy(sfzt_ctx_s *ctx);

sfzt_addr addr_imm(sfzt_ctx_s *ctx);

sfzt_addr addr_imp(sfzt_ctx_s UNUSED *ctx);

sfzt_addr addr_ind(sfzt_ctx_s *ctx);
sfzt_addr addr_xind(sfzt_ctx_s *ctx);
sfzt_addr addr_indy(sfzt_ctx_s *ctx);

sfzt_addr addr_rel(sfzt_ctx_s *ctx);

sfzt_addr addr_zpg(sfzt_ctx_s *ctx);
sfzt_addr addr_zpgx(sfzt_ctx_s *ctx);
sfzt_addr addr_zpgy(sfzt_ctx_s *ctx);


#endif /// #ifndef H_ADDR_MODE
