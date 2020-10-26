/* *****************************************************************************
 * opcode.h -- All op code function for 6502
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
#ifndef H_OPCODE
#define H_OPCODE
#include "sfzt_context.h"
#include "util.h"
#define DECL_OPCODE(OPCODE, CYCLE) void opcode_##OPCODE(sfzt_ctx_s *ctx, \
                                                        BYTE opsize)
                        /*  static uint8_t opcode_cycle_##OPCODE = CYCLE */
#define IMPL_OPCODE(OPCODE)void opcode_##OPCODE(sfzt_ctx_s *ctx, BYTE opsize)
#define OP(OPCODE) opcode_##OPCODE
// Stringify OPCODE
#define SO(OPCODE) #OPCODE


void push_byte(BYTE b, sfzt_ctx_s *ctx);
void push_word(WORD w, sfzt_ctx_s *ctx);

BYTE pull_byte(sfzt_ctx_s *ctx);
WORD pull_word(sfzt_ctx_s *ctx);

typedef void (*opcode)(sfzt_ctx_s *ctx, BYTE opsize);
// TODO : implement cycle counter
DECL_OPCODE(adc, 0); // Add Memory to Accumulator with Carry
DECL_OPCODE(and, 0); // AND Memory with Accumulator
DECL_OPCODE(asl, 0); // Shift Left One Bit (Memory)
DECL_OPCODE(asla,0); // Shift Left One Bit (Accumulator)
DECL_OPCODE(bcc, 0); // Branch on Carry Clear
DECL_OPCODE(bcs, 0); // Branch on Carry Set
DECL_OPCODE(beq, 0); // Branch on Result Zero
DECL_OPCODE(bit, 0); // Test Bits in Memory with Accumulator
DECL_OPCODE(bmi, 0); // Branch on Result Minus
DECL_OPCODE(bne, 0); // Branch on Result not Zero
DECL_OPCODE(bpl, 0); // Branch on Result Plus
DECL_OPCODE(brk, 0); // Force Break
DECL_OPCODE(bvc, 0); // Branch on Overflow Clear
DECL_OPCODE(bvs, 0); // Branch on Overflow Set
DECL_OPCODE(clc, 0); // Clear Carry Flag
DECL_OPCODE(cld, 0); // Clear Decimal Mode
DECL_OPCODE(cli, 0); // Clear Interrupt Disable Bit
DECL_OPCODE(clv, 0); // Clear Overflow Flag
DECL_OPCODE(cmp, 0); // Compare Memory with Accumulator
DECL_OPCODE(cpx, 0); // Compare Memory and Index X
DECL_OPCODE(cpy, 0); // Compare Memory and Index Y
DECL_OPCODE(dec, 0); // Decrement Memory by One
DECL_OPCODE(dex, 0); // Decrement Index X by One
DECL_OPCODE(dey, 0); // Decrement Index Y by One
DECL_OPCODE(eor, 0); // Exclusive-OR Memory with Accumulator
DECL_OPCODE(inc, 0); // Increment Memory by One
DECL_OPCODE(inx, 0); // Increment Index X by One
DECL_OPCODE(iny, 0); // Increment Index Y by One
DECL_OPCODE(jmp, 0); // Jump to New Location
DECL_OPCODE(jsr, 0); // Jump to New Location Saving Return Address
DECL_OPCODE(lda, 0); // Load Accumulator with Memory
DECL_OPCODE(ldx, 0); // Load Index X with Memory
DECL_OPCODE(ldy, 0); // Load Index Y with Memory
DECL_OPCODE(lsr, 0); // Shift One Bit Right (Memory)
DECL_OPCODE(lsra,0); // Shift One Bit Right (Accumulator)
DECL_OPCODE(nop, 0); // No Operation
DECL_OPCODE(ora, 0); // OR Memory with Accumulator
DECL_OPCODE(pha, 0); // Push Accumulator on Stack
DECL_OPCODE(php, 0); // Push Processor Status on Stack
DECL_OPCODE(pla, 0); // Pull Accumulator from Stack
DECL_OPCODE(plp, 0); // Pull Processor Status from Stack
DECL_OPCODE(rol, 0); // Rotate One Bit Left (Memory)
DECL_OPCODE(rola,0); // Rotate One Bit Left (Accumulator)
DECL_OPCODE(ror, 0); // Rotate One Bit Right (Memory)
DECL_OPCODE(rora,0); // Rotate One Bit Right (Accumulator)
DECL_OPCODE(rti, 0); // Return from Interrupt
DECL_OPCODE(rts, 0); // Return from Subroutine
DECL_OPCODE(sbc, 0); // Subtract Memory from Accumulator with Borrow
DECL_OPCODE(sec, 0); // Set Carry Flag
DECL_OPCODE(sed, 0); // Set Decimal Flag
DECL_OPCODE(sei, 0); // Set Interrupt Disable Status
DECL_OPCODE(sta, 0); // Store Accumulator in Memory
DECL_OPCODE(stx, 0); // Store Index X in Memory
DECL_OPCODE(sty, 0); // Store Index Y in Memory
DECL_OPCODE(tax, 0); // Transfer Accumulator to Index X
DECL_OPCODE(tay, 0); // Transfer Accumulator to Index Y
DECL_OPCODE(tsx, 0); // Transfer Stack Pointer to Index X
DECL_OPCODE(txa, 0); // Transfer Index X to Accumulator
DECL_OPCODE(txs, 0); // Transfer Index X to Stack Register
DECL_OPCODE(tya, 0); // Transfer Index Y to Accumulator

static const opcode opcode_table[256] = {
        /*  0       1       2       3       4       5       6       7       8       9       A       B       C       D       E       F*/
/* 0 */ OP(brk),OP(ora),OP(nop),OP(nop),OP(nop),OP(ora),OP(asl),OP(nop),OP(php),OP(ora),OP(asla),OP(nop),OP(nop),OP(ora),OP(asl),OP(nop),
/* 1 */ OP(bpl),OP(ora),OP(nop),OP(nop),OP(nop),OP(ora),OP(asl),OP(nop),OP(clc),OP(ora),OP(nop),OP(nop),OP(nop),OP(ora),OP(asl),OP(nop),
/* 2 */ OP(jsr),OP(and),OP(nop),OP(nop),OP(bit),OP(and),OP(rol),OP(nop),OP(plp),OP(and),OP(rola),OP(nop),OP(bit),OP(and),OP(rol),OP(nop),
/* 3 */ OP(bmi),OP(and),OP(nop),OP(nop),OP(nop),OP(and),OP(rol),OP(nop),OP(sec),OP(and),OP(nop),OP(nop),OP(nop),OP(and),OP(rol),OP(nop),
/* 4 */ OP(rti),OP(eor),OP(nop),OP(nop),OP(nop),OP(eor),OP(lsr),OP(nop),OP(pha),OP(eor),OP(lsra),OP(nop),OP(jmp),OP(eor),OP(lsr),OP(nop),
/* 5 */ OP(bvc),OP(eor),OP(nop),OP(nop),OP(nop),OP(eor),OP(lsr),OP(nop),OP(cli),OP(eor),OP(nop),OP(nop),OP(nop),OP(eor),OP(lsr),OP(nop),
/* 6 */ OP(rts),OP(adc),OP(nop),OP(nop),OP(nop),OP(adc),OP(ror),OP(nop),OP(pla),OP(adc),OP(rora),OP(nop),OP(jmp),OP(adc),OP(ror),OP(nop),
/* 7 */ OP(bvs),OP(adc),OP(nop),OP(nop),OP(nop),OP(adc),OP(ror),OP(nop),OP(sei),OP(adc),OP(nop),OP(nop),OP(nop),OP(adc),OP(ror),OP(nop),
/* 8 */ OP(nop),OP(sta),OP(nop),OP(nop),OP(sty),OP(sta),OP(stx),OP(nop),OP(dey),OP(nop),OP(txa),OP(nop),OP(sty),OP(sta),OP(stx),OP(nop),
/* 9 */ OP(bcc),OP(sta),OP(nop),OP(nop),OP(sty),OP(sta),OP(stx),OP(nop),OP(tya),OP(sta),OP(txs),OP(nop),OP(nop),OP(sta),OP(nop),OP(nop),
/* A */ OP(ldy),OP(lda),OP(ldx),OP(nop),OP(ldy),OP(lda),OP(ldx),OP(nop),OP(tay),OP(lda),OP(tax),OP(nop),OP(ldy),OP(lda),OP(ldx),OP(nop),
/* B */ OP(bcs),OP(lda),OP(nop),OP(nop),OP(ldy),OP(lda),OP(ldx),OP(nop),OP(clv),OP(lda),OP(tsx),OP(nop),OP(ldy),OP(lda),OP(ldx),OP(nop),
/* C */ OP(cpy),OP(cmp),OP(nop),OP(nop),OP(cpy),OP(cmp),OP(dec),OP(nop),OP(iny),OP(cmp),OP(dex),OP(nop),OP(cpy),OP(cmp),OP(dec),OP(nop),
/* D */ OP(bne),OP(cmp),OP(nop),OP(nop),OP(nop),OP(cmp),OP(dec),OP(nop),OP(cld),OP(cmp),OP(nop),OP(nop),OP(nop),OP(cmp),OP(dec),OP(nop),
/* E */ OP(cpx),OP(sbc),OP(nop),OP(nop),OP(cpx),OP(sbc),OP(inc),OP(nop),OP(inx),OP(sbc),OP(nop),OP(nop),OP(cpx),OP(sbc),OP(inc),OP(nop),
/* F */ OP(beq),OP(sbc),OP(nop),OP(nop),OP(nop),OP(sbc),OP(inc),OP(nop),OP(sed),OP(sbc),OP(nop),OP(nop),OP(nop),OP(sbc),OP(inc),OP(nop),
};

static const char opcode_name_table[256][5] = {
        /*  0       1       2       3       4       5       6       7       8       9       A       B       C       D       E       F*/
/* 0 */ SO(brk),SO(ora),SO(nop),SO(nop),SO(nop),SO(ora),SO(asl),SO(nop),SO(php),SO(ora),SO(asla),SO(nop),SO(nop),SO(ora),SO(asl),SO(nop),
/* 1 */ SO(bpl),SO(ora),SO(nop),SO(nop),SO(nop),SO(ora),SO(asl),SO(nop),SO(clc),SO(ora),SO(nop),SO(nop),SO(nop),SO(ora),SO(asl),SO(nop),
/* 2 */ SO(jsr),SO(and),SO(nop),SO(nop),SO(bit),SO(and),SO(rol),SO(nop),SO(plp),SO(and),SO(rola),SO(nop),SO(bit),SO(and),SO(rol),SO(nop),
/* 3 */ SO(bmi),SO(and),SO(nop),SO(nop),SO(nop),SO(and),SO(rol),SO(nop),SO(sec),SO(and),SO(nop),SO(nop),SO(nop),SO(and),SO(rol),SO(nop),
/* 4 */ SO(rti),SO(eor),SO(nop),SO(nop),SO(nop),SO(eor),SO(lsr),SO(nop),SO(pha),SO(eor),SO(lsra),SO(nop),SO(jmp),SO(eor),SO(lsr),SO(nop),
/* 5 */ SO(bvc),SO(eor),SO(nop),SO(nop),SO(nop),SO(eor),SO(lsr),SO(nop),SO(cli),SO(eor),SO(nop),SO(nop),SO(nop),SO(eor),SO(lsr),SO(nop),
/* 6 */ SO(rts),SO(adc),SO(nop),SO(nop),SO(nop),SO(adc),SO(ror),SO(nop),SO(pla),SO(adc),SO(rora),SO(nop),SO(jmp),SO(adc),SO(ror),SO(nop),
/* 7 */ SO(bvs),SO(adc),SO(nop),SO(nop),SO(nop),SO(adc),SO(ror),SO(nop),SO(sei),SO(adc),SO(nop),SO(nop),SO(nop),SO(adc),SO(ror),SO(nop),
/* 8 */ SO(nop),SO(sta),SO(nop),SO(nop),SO(sty),SO(sta),SO(stx),SO(nop),SO(dey),SO(nop),SO(txa),SO(nop),SO(sty),SO(sta),SO(stx),SO(nop),
/* 9 */ SO(bcc),SO(sta),SO(nop),SO(nop),SO(sty),SO(sta),SO(stx),SO(nop),SO(tya),SO(sta),SO(txs),SO(nop),SO(nop),SO(sta),SO(nop),SO(nop),
/* A */ SO(ldy),SO(lda),SO(ldx),SO(nop),SO(ldy),SO(lda),SO(ldx),SO(nop),SO(tay),SO(lda),SO(tax),SO(nop),SO(ldy),SO(lda),SO(ldx),SO(nop),
/* B */ SO(bcs),SO(lda),SO(nop),SO(nop),SO(ldy),SO(lda),SO(ldx),SO(nop),SO(clv),SO(lda),SO(tsx),SO(nop),SO(ldy),SO(lda),SO(ldx),SO(nop),
/* C */ SO(cpy),SO(cmp),SO(nop),SO(nop),SO(cpy),SO(cmp),SO(dec),SO(nop),SO(iny),SO(cmp),SO(dex),SO(nop),SO(cpy),SO(cmp),SO(dec),SO(nop),
/* D */ SO(bne),SO(cmp),SO(nop),SO(nop),SO(nop),SO(cmp),SO(dec),SO(nop),SO(cld),SO(cmp),SO(nop),SO(nop),SO(nop),SO(cmp),SO(dec),SO(nop),
/* E */ SO(cpx),SO(sbc),SO(nop),SO(nop),SO(cpx),SO(sbc),SO(inc),SO(nop),SO(inx),SO(sbc),SO(nop),SO(nop),SO(cpx),SO(sbc),SO(inc),SO(nop),
/* F */ SO(beq),SO(sbc),SO(nop),SO(nop),SO(nop),SO(sbc),SO(inc),SO(nop),SO(sed),SO(sbc),SO(nop),SO(nop),SO(nop),SO(sbc),SO(inc),SO(nop),
};


#endif /// #ifndef H_OPCODE
