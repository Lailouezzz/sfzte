/* *****************************************************************************
 * addr_mode.h -- All address mode fonction for 6502
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
#include "sfzt_context.h"
#include "util.h"
#define DECL_AM(am) sfzt_addr addr_##am(sfzt_ctx_s *ctx)
#define AM(am) addr_##am

typedef sfzt_addr (*addr_mode)(sfzt_ctx_s *);

DECL_AM(abs);
DECL_AM(absx);
DECL_AM(absy);

DECL_AM(imm);

DECL_AM(ind);
DECL_AM(xind);
DECL_AM(indy);

DECL_AM(rel);

DECL_AM(zpg);
DECL_AM(zpgx);
DECL_AM(zpgy);

static const addr_mode am_table[256] = {
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
    AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),AM(abs),
};


#endif /// #ifndef H_ADDR_MODE
