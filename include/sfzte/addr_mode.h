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
#define DECL_AM(am) BYTE addr_##am(sfzt_ctx_s *ctx)
#define IMPL_AM(am) BYTE addr_##am(sfzt_ctx_s *ctx)
#define AM(am) (addr_##am)

typedef BYTE (*addr_mode)(sfzt_ctx_s *);

DECL_AM(nnn);
DECL_AM(acc);

DECL_AM(abs);
DECL_AM(abx);
DECL_AM(aby);

DECL_AM(imm);

DECL_AM(imp);

DECL_AM(ind);
DECL_AM(xin);
DECL_AM(iny);

DECL_AM(rel);

DECL_AM(zpg);
DECL_AM(zpx);
DECL_AM(zpy);

static const addr_mode am_table[256] = {
/*              0       1       2       3       4       5       6       7       8       9       A       B       C       D       E       F */
/* 0 */     AM(imp),AM(xin),AM(nnn),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(acc),AM(nnn),AM(nnn),AM(abs),AM(abs),AM(nnn),
/* 1 */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(nnn),AM(imp),AM(aby),AM(nnn),AM(nnn),AM(nnn),AM(abx),AM(abx),AM(nnn),
/* 2 */     AM(abs),AM(xin),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(acc),AM(nnn),AM(abs),AM(abs),AM(abs),AM(nnn),
/* 3 */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(nnn),AM(imp),AM(aby),AM(nnn),AM(nnn),AM(nnn),AM(abx),AM(abx),AM(nnn),
/* 4 */     AM(imp),AM(xin),AM(nnn),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(acc),AM(nnn),AM(abs),AM(abs),AM(abs),AM(nnn),
/* 5 */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(nnn),AM(imp),AM(aby),AM(nnn),AM(nnn),AM(nnn),AM(abx),AM(abx),AM(nnn),
/* 6 */     AM(imp),AM(xin),AM(nnn),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(acc),AM(nnn),AM(ind),AM(abs),AM(abs),AM(nnn),
/* 7 */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(nnn),AM(imp),AM(aby),AM(nnn),AM(nnn),AM(nnn),AM(abx),AM(abx),AM(nnn),
/* 8 */     AM(nnn),AM(xin),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(nnn),AM(imp),AM(nnn),AM(abs),AM(abs),AM(abs),AM(nnn),
/* 9 */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(zpy),AM(nnn),AM(imp),AM(aby),AM(imp),AM(nnn),AM(nnn),AM(abx),AM(nnn),AM(nnn),
/* A */     AM(imm),AM(xin),AM(imm),AM(nnn),AM(zpg),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(imp),AM(nnn),AM(abs),AM(abs),AM(abs),AM(nnn),
/* B */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(zpy),AM(nnn),AM(imp),AM(aby),AM(imp),AM(nnn),AM(abx),AM(abx),AM(abx),AM(nnn),
/* C */     AM(imm),AM(xin),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(imp),AM(nnn),AM(abs),AM(abs),AM(abs),AM(nnn),
/* D */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(nnn),AM(imp),AM(aby),AM(nnn),AM(nnn),AM(nnn),AM(abx),AM(abx),AM(nnn),
/* E */     AM(imm),AM(xin),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(imp),AM(nnn),AM(abs),AM(abs),AM(abs),AM(nnn),
/* F */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(nnn),AM(imp),AM(aby),AM(nnn),AM(nnn),AM(nnn),AM(abx),AM(abx),AM(nnn),
};


#endif /// #ifndef H_ADDR_MODE
