/* *****************************************************************************
 * opcode.c -- All op code function for 6502
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
#include "sfzte.h"

#define CALC_CARRY(r)       if((r & 0xFF00) != 0) SET_CARRY(*ctx); \
                                             else CLEAR_CARRY(*ctx);
#define CALC_ZERO(r)        if((r & 0x00FF) == 0) SET_ZERO(*ctx); \
                                             else CLEAR_ZERO(*ctx);
#define CALC_OVERFLOW(r, m, n)    if((((r ^ n) & (r ^ m)) \
                                    & 0x80) != 0) SET_OVERFLOW(*ctx); \
                                             else CLEAR_OVERFLOW(*ctx);
#define CALC_NEGATIVE(r)    if((r & 0x0080) != 0) SET_NEGATIVE(*ctx); \
                                             else CLEAR_NEGATIVE(*ctx);


// REGPC point to next opcode

void push_byte(BYTE b, sfzt_ctx_s *ctx)
{
    WRITE8(b, STACK_ADDR + REGSP--);
    return;
}
void push_word(WORD w, sfzt_ctx_s *ctx)
{
    push_byte((BYTE) (w >> 8) & 0x00FF, ctx);
    push_byte((BYTE) w & 0x00FF, ctx);
    return;
}

BYTE pull_byte(sfzt_ctx_s *ctx)
{
    return READ8(STACK_ADDR + (++REGSP));
}
WORD pull_word(sfzt_ctx_s *ctx)
{
    BYTE lo = pull_byte(ctx);
    BYTE hi = pull_byte(ctx);
    return CREATE_WORD(lo, hi);
}

IMP_OPCODE(adc)
{
    BYTE value = READ8_EA;
    WORD result = (WORD) (REGA + value + (IS_CARRY(*ctx) ? 1u : 0u));
    CALC_CARRY(result);
    CALC_ZERO(result);
    CALC_OVERFLOW(result, value, REGA);
    CALC_NEGATIVE(result);
    REGA = (BYTE)result;
    return;
}
IMP_OPCODE(and)
{
    REGA &= READ8_EA;
    CALC_ZERO(REGA);
    CALC_NEGATIVE(REGA);
    return;
}
IMP_OPCODE(asl)
{
    WORD result = READ8_EA << 1;
    CALC_CARRY(result);
    CALC_ZERO(result);
    CALC_NEGATIVE(result);
    WRITE8_EA((BYTE)result);
    return;
}
IMP_OPCODE(asla)
{
    WORD result = READ8_EA << 1;
    CALC_CARRY(result);
    CALC_ZERO(result);
    CALC_NEGATIVE(result);
    REGA = (BYTE)result;
    return;
}
IMP_OPCODE(bcc)
{
    if(!IS_CARRY(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bcs)
{
    if(IS_CARRY(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(beq)
{
    if(IS_ZERO(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bit)
{
    BYTE value = READ8_EA;
    BYTE result = REGA & value;
    CALC_ZERO(result);
    CALC_NEGATIVE(value);

    if((value & (1 << 6)) != 0)
        SET_OVERFLOW(*ctx);
    else
        CLEAR_OVERFLOW(*ctx);

    return;
}
IMP_OPCODE(bmi)
{
    if(IS_NEGATIVE(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bne)
{
    if(!IS_ZERO(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bpl)
{
    if(!IS_NEGATIVE(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(brk)
{
    UNUSED(ea);
    REGPC++;
    push_word(REGPC, ctx);
    push_byte(REGSR | FLAG_BREAK, ctx);
    SET_INTERRUPT(*ctx);
    REGPC = CREATE_WORD(READ8(0xFFFE), READ8(0xFFFF));
    return;
}
IMP_OPCODE(bvc)
{
    if(!IS_OVERFLOW(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bvs)
{
    if(IS_OVERFLOW(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(clc)
{
    UNUSED(ea);
    CLEAR_CARRY(*ctx);
    return;
}
IMP_OPCODE(cld)
{
    UNUSED(ea);
    CLEAR_DECIMAL(*ctx);
    return;
}
IMP_OPCODE(cli)
{
    UNUSED(ea);
    CLEAR_INTERRUPT(*ctx);
    return;
}
IMP_OPCODE(clv)
{
    UNUSED(ea);
    CLEAR_OVERFLOW(*ctx);
    return;
}
IMP_OPCODE(cmp)
{
    BYTE value = READ8_EA;
    BYTE result = REGA - value;
    CALC_NEGATIVE(result);

    if(REGA == value)
        SET_ZERO(*ctx);
    else
        CLEAR_ZERO(*ctx);

    if(REGA >= value)
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    
    return;
}
IMP_OPCODE(cpx)
{
    BYTE value = READ8_EA;
    BYTE result = REGX - value;
    CALC_NEGATIVE(result);

    if(REGX == value)
        SET_ZERO(*ctx);
    else
        CLEAR_ZERO(*ctx);

    if(REGX >= value)
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    
    return;
}
IMP_OPCODE(cpy)
{
    BYTE value = READ8_EA;
    BYTE result = REGY - value;
    CALC_NEGATIVE(result);

    if(REGY == value)
        SET_ZERO(*ctx);
    else
        CLEAR_ZERO(*ctx);

    if(REGY >= value)
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    
    return;
}
IMP_OPCODE(dec)
{
    BYTE value = READ8_EA;
    value--;
    CALC_NEGATIVE(value);
    CALC_ZERO(value);
    WRITE8_EA(value);
    return;
}
IMP_OPCODE(dex)
{
    UNUSED(ea);
    REGX--;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(dey)
{
    UNUSED(ea);
    REGY--;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    return;
}
IMP_OPCODE(eor)
{
    REGA ^= READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
}
IMP_OPCODE(inc)
{
    BYTE value = READ8_EA;
    value++;
    CALC_NEGATIVE(value);
    CALC_ZERO(value);
    WRITE8_EA(value);
    return;
}
IMP_OPCODE(inx)
{
    UNUSED(ea);
    REGX++;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(iny)
{
    UNUSED(ea);
    REGY++;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    return;
}
IMP_OPCODE(jmp)
{
    REGPC = ea;
    return;
}
IMP_OPCODE(jsr)
{
    push_word(REGPC-1, ctx);
    REGPC = ea;
    return;
}
IMP_OPCODE(lda)
{
    REGA = READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    return;
}
IMP_OPCODE(ldx)
{
    REGX = READ8_EA;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(ldy)
{
    REGY = READ8_EA;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    return;
}
IMP_OPCODE(lsr)
{
    BYTE value = READ8_EA;
    BYTE result = value >> 1;
    if((value & 1))
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    CLEAR_NEGATIVE(*ctx);
    CALC_ZERO(result);
    WRITE8_EA(result);
    return;
}
IMP_OPCODE(lsra)
{
    UNUSED(ea);
    BYTE value = REGA;
    BYTE result = value >> 1;
    if((value & 1))
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    CLEAR_NEGATIVE(*ctx);
    CALC_ZERO(result);
    REGA = result;
    return;
}
IMP_OPCODE(nop)
{
    UNUSED(ctx);
    UNUSED(ea);
    return;
}
IMP_OPCODE(ora)
{
    REGA |= READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    return;
}
IMP_OPCODE(pha)
{
    UNUSED(ea);
    push_byte(REGA, ctx);
    return;
}
IMP_OPCODE(php)
{
    UNUSED(ea);
    push_byte(REGSR, ctx);
    return;
}
IMP_OPCODE(pla)
{
    UNUSED(ea);
    REGA = pull_byte(ctx);
    return;
}
IMP_OPCODE(plp)
{
    UNUSED(ea);
    REGSR = pull_byte(ctx);
    return;
}
IMP_OPCODE(rol)
{
    BYTE value = READ8_EA;
    WORD result = (WORD) ((value << 1) | (IS_CARRY(*ctx) ? 1u : 0u));

    CALC_NEGATIVE(result);
    CALC_ZERO(result);
    CALC_CARRY(result);
    WRITE8_EA((BYTE) result);
    return;
}
IMP_OPCODE(rola)
{
    UNUSED(ea);
    WORD result = (WORD) ((REGA << 1) | (IS_CARRY(*ctx) ? 1u : 0u));

    CALC_NEGATIVE(result);
    CALC_ZERO(result);
    CALC_CARRY(result);
    REGA = (BYTE) result;
    return;
}
IMP_OPCODE(ror)
{
    BYTE value = READ8_EA;
    WORD result = (WORD) ((value >> 1) | (IS_CARRY(*ctx) ? (1u << 7) : 0u));

    CALC_NEGATIVE(result);
    CALC_ZERO(result);
    if((value & 1) != 0)
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    
    WRITE8_EA((BYTE) result);
    return;
}
IMP_OPCODE(rora)
{
    UNUSED(ea);
    BYTE value = REGA;
    WORD result = (WORD) ((value >> 1) | (IS_CARRY(*ctx) ? (1u << 7) : 0u));

    CALC_NEGATIVE(result);
    CALC_ZERO(result);
    if(value & 1)
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    
    REGA = (BYTE) result;
    return;
}
IMP_OPCODE(rti)
{
    UNUSED(ea);
    REGSR = pull_byte(ctx);
    REGPC = pull_word(ctx);
    return;
}
IMP_OPCODE(rts)
{
    UNUSED(ea);
    REGPC = pull_word(ctx) + 1;
    return;
}
IMP_OPCODE(sbc)
{
    BYTE value = ~READ8_EA;
    WORD result = (WORD) (REGA + value + (IS_CARRY(*ctx) ? 1u : 0u));

    CALC_NEGATIVE(result);
    CALC_ZERO(result);
    CALC_CARRY(result);
    CALC_OVERFLOW(result, REGA, value);

    REGA = (BYTE) result;
    return;
}
IMP_OPCODE(sec)
{
    UNUSED(ea);
    SET_CARRY(*ctx);
    return;
}
IMP_OPCODE(sed)
{
    UNUSED(ea);
    SET_DECIMAL(*ctx);
    return;
}
IMP_OPCODE(sei)
{
    UNUSED(ea);
    SET_INTERRUPT(*ctx);
    return;
}
IMP_OPCODE(sta)
{
    WRITE8_EA(REGA);
    return;
}
IMP_OPCODE(stx)
{
    WRITE8_EA(REGX);
    return;
}
IMP_OPCODE(sty)
{
    WRITE8_EA(REGY);
    return;
}
IMP_OPCODE(tax)
{
    UNUSED(ea);
    REGX = REGA;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(tay)
{
    UNUSED(ea);
    REGY = REGA;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    return;
}
IMP_OPCODE(tsx)
{
    UNUSED(ea);
    REGX = REGSP;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(txa)
{
    UNUSED(ea);
    REGA = REGX;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    return;
}
IMP_OPCODE(txs)
{
    UNUSED(ea);
    REGSP = REGX;
    return;
}
IMP_OPCODE(tya)
{
    UNUSED(ea);
    REGA = REGY;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    return;
}
