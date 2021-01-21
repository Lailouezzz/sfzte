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
#include "sfzte_context.h"
#include "util.h"
#define DECL_AM(am) BYTE addrmode_##am(sfzte_ctx_s *ctx); \
                    int addrmode_disasm_##am(char *dst, size_t maxlen, \
                                                sfzte_ctx_s *ctx)

#define IMPL_AM(am) BYTE addrmode_##am(sfzte_ctx_s *ctx)
#define IMPL_DAM(am) int addrmode_disasm_##am(char *dst, size_t maxlen, \
                                                 sfzte_ctx_s *ctx)

#define AM(am) (addrmode_##am)
#define DAM(am) (addrmode_disasm_##am)


typedef BYTE (*addrmode)(sfzte_ctx_s *);
typedef int (*addrmode_disasm)(char *dst, size_t maxlen, sfzte_ctx_s *);

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

static const addrmode am_table[256] = {
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
/* B */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(zpy),AM(nnn),AM(imp),AM(aby),AM(imp),AM(nnn),AM(abx),AM(abx),AM(aby),AM(nnn),
/* C */     AM(imm),AM(xin),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(imp),AM(nnn),AM(abs),AM(abs),AM(abs),AM(nnn),
/* D */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(nnn),AM(imp),AM(aby),AM(nnn),AM(nnn),AM(nnn),AM(abx),AM(abx),AM(nnn),
/* E */     AM(imm),AM(xin),AM(nnn),AM(nnn),AM(zpg),AM(zpg),AM(zpg),AM(nnn),AM(imp),AM(imm),AM(imp),AM(nnn),AM(abs),AM(abs),AM(abs),AM(nnn),
/* F */     AM(rel),AM(iny),AM(nnn),AM(nnn),AM(nnn),AM(zpx),AM(zpx),AM(nnn),AM(imp),AM(aby),AM(nnn),AM(nnn),AM(nnn),AM(abx),AM(abx),AM(nnn),
};

static const addrmode_disasm am__disasm_table[256] = {
/*              0       1       2       3       4       5       6       7       8       9       A       B       C       D       E       F */
/* 0 */     DAM(imp),DAM(xin),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpg),DAM(zpg),DAM(nnn),DAM(imp),DAM(imm),DAM(acc),DAM(nnn),DAM(nnn),DAM(abs),DAM(abs),DAM(nnn),
/* 1 */     DAM(rel),DAM(iny),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpx),DAM(zpx),DAM(nnn),DAM(imp),DAM(aby),DAM(nnn),DAM(nnn),DAM(nnn),DAM(abx),DAM(abx),DAM(nnn),
/* 2 */     DAM(abs),DAM(xin),DAM(nnn),DAM(nnn),DAM(zpg),DAM(zpg),DAM(zpg),DAM(nnn),DAM(imp),DAM(imm),DAM(acc),DAM(nnn),DAM(abs),DAM(abs),DAM(abs),DAM(nnn),
/* 3 */     DAM(rel),DAM(iny),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpx),DAM(zpx),DAM(nnn),DAM(imp),DAM(aby),DAM(nnn),DAM(nnn),DAM(nnn),DAM(abx),DAM(abx),DAM(nnn),
/* 4 */     DAM(imp),DAM(xin),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpg),DAM(zpg),DAM(nnn),DAM(imp),DAM(imm),DAM(acc),DAM(nnn),DAM(abs),DAM(abs),DAM(abs),DAM(nnn),
/* 5 */     DAM(rel),DAM(iny),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpx),DAM(zpx),DAM(nnn),DAM(imp),DAM(aby),DAM(nnn),DAM(nnn),DAM(nnn),DAM(abx),DAM(abx),DAM(nnn),
/* 6 */     DAM(imp),DAM(xin),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpg),DAM(zpg),DAM(nnn),DAM(imp),DAM(imm),DAM(acc),DAM(nnn),DAM(ind),DAM(abs),DAM(abs),DAM(nnn),
/* 7 */     DAM(rel),DAM(iny),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpx),DAM(zpx),DAM(nnn),DAM(imp),DAM(aby),DAM(nnn),DAM(nnn),DAM(nnn),DAM(abx),DAM(abx),DAM(nnn),
/* 8 */     DAM(nnn),DAM(xin),DAM(nnn),DAM(nnn),DAM(zpg),DAM(zpg),DAM(zpg),DAM(nnn),DAM(imp),DAM(nnn),DAM(imp),DAM(nnn),DAM(abs),DAM(abs),DAM(abs),DAM(nnn),
/* 9 */     DAM(rel),DAM(iny),DAM(nnn),DAM(nnn),DAM(zpx),DAM(zpx),DAM(zpy),DAM(nnn),DAM(imp),DAM(aby),DAM(imp),DAM(nnn),DAM(nnn),DAM(abx),DAM(nnn),DAM(nnn),
/* A */     DAM(imm),DAM(xin),DAM(imm),DAM(nnn),DAM(zpg),DAM(zpg),DAM(zpg),DAM(nnn),DAM(imp),DAM(imm),DAM(imp),DAM(nnn),DAM(abs),DAM(abs),DAM(abs),DAM(nnn),
/* B */     DAM(rel),DAM(iny),DAM(nnn),DAM(nnn),DAM(zpx),DAM(zpx),DAM(zpy),DAM(nnn),DAM(imp),DAM(aby),DAM(imp),DAM(nnn),DAM(abx),DAM(aby),DAM(abx),DAM(nnn),
/* C */     DAM(imm),DAM(xin),DAM(nnn),DAM(nnn),DAM(zpg),DAM(zpg),DAM(zpg),DAM(nnn),DAM(imp),DAM(imm),DAM(imp),DAM(nnn),DAM(abs),DAM(abs),DAM(abs),DAM(nnn),
/* D */     DAM(rel),DAM(iny),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpx),DAM(zpx),DAM(nnn),DAM(imp),DAM(aby),DAM(nnn),DAM(nnn),DAM(nnn),DAM(abx),DAM(abx),DAM(nnn),
/* E */     DAM(imm),DAM(xin),DAM(nnn),DAM(nnn),DAM(zpg),DAM(zpg),DAM(zpg),DAM(nnn),DAM(imp),DAM(imm),DAM(imp),DAM(nnn),DAM(abs),DAM(abs),DAM(abs),DAM(nnn),
/* F */     DAM(rel),DAM(iny),DAM(nnn),DAM(nnn),DAM(nnn),DAM(zpx),DAM(zpx),DAM(nnn),DAM(imp),DAM(aby),DAM(nnn),DAM(nnn),DAM(nnn),DAM(abx),DAM(abx),DAM(nnn),
};


#endif /// #ifndef H_ADDR_MODE
