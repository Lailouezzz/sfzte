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
#define DECL_OPCODE(OPCODE, CYCLE) void opcode_##OPCODE(sfzt_ctx_s *ctx); \
                            uint8_t opcode_cycle_##OPCODE = CYCLE
#define IMP_OPCODE(OPCODE) void opcode_##OPCODE(sfzt_ctx_s *ctx)


typedef void (*opcode)(sfzt_ctx_s *);

DECL_OPCODE(adc, 0); // Add Memory to Accumulator with Carry
DECL_OPCODE(and, 0); // AND Memory with Accumulator
DECL_OPCODE(asl, 0); // Shift Left One Bit (Memory or Accumulator)
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
DECL_OPCODE(lsr, 0); // Shift One Bit Right (Memory or Accumulator)
DECL_OPCODE(nop, 0); // No Operation
DECL_OPCODE(ora, 0); // OR Memory with Accumulator
DECL_OPCODE(pha, 0); // Push Accumulator on Stack
DECL_OPCODE(php, 0); // Push Processor Status on Stack
DECL_OPCODE(pla, 0); // Pull Accumulator from Stack
DECL_OPCODE(plp, 0); // Pull Processor Status from Stack
DECL_OPCODE(rol, 0); // Rotate One Bit Left (Memory or Accumulator)
DECL_OPCODE(ror, 0); // Rotate One Bit Right (Memory or Accumulator)
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


#endif /// #ifndef H_OPCODE
