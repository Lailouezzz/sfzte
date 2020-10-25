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
#include "opcode.h"
#include <stdio.h>

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
    printf("adc");
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
    printf("and");
    REGA &= READ8_EA;
    CALC_ZERO(REGA);
    CALC_NEGATIVE(REGA);
    return;
}
IMP_OPCODE(asl)
{
    printf("asl");
    WORD result = READ8_EA << 1;
    CALC_CARRY(result);
    CALC_ZERO(result);
    CALC_NEGATIVE(result);
    WRITE8_EA((BYTE)result);
    return;
}
IMP_OPCODE(asla)
{
    printf("asla");
    WORD result = READ8_EA << 1;
    CALC_CARRY(result);
    CALC_ZERO(result);
    CALC_NEGATIVE(result);
    REGA = (BYTE)result;
    return;
}
IMP_OPCODE(bcc)
{
    printf("bcc");
    if(!IS_CARRY(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bcs)
{
    printf("bcs");
    if(IS_CARRY(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(beq)
{
    printf("beq");
    if(IS_ZERO(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bit)
{
    printf("bit");
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
    printf("bmi");
    if(IS_NEGATIVE(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bne)
{
    printf("bne");
    if(!IS_ZERO(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bpl)
{
    printf("bpl");
    if(!IS_NEGATIVE(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(brk)
{
    printf("brk");
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
    printf("bvc");
    if(!IS_OVERFLOW(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(bvs)
{
    printf("bvs");
    if(IS_OVERFLOW(*ctx))
    {
        REGPC = ea;
    }
    return;
}
IMP_OPCODE(clc)
{
    printf("clc");
    UNUSED(ea);
    CLEAR_CARRY(*ctx);
    return;
}
IMP_OPCODE(cld)
{
    printf("cld");
    UNUSED(ea);
    CLEAR_DECIMAL(*ctx);
    return;
}
IMP_OPCODE(cli)
{
    printf("cli");
    UNUSED(ea);
    CLEAR_INTERRUPT(*ctx);
    return;
}
IMP_OPCODE(clv)
{
    printf("clv");
    UNUSED(ea);
    CLEAR_OVERFLOW(*ctx);
    return;
}
IMP_OPCODE(cmp)
{
    printf("cmp");
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
    printf("cpx");
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
    printf("cpy");
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
    printf("dec");
    BYTE value = READ8_EA;
    value--;
    CALC_NEGATIVE(value);
    CALC_ZERO(value);
    WRITE8_EA(value);
    return;
}
IMP_OPCODE(dex)
{
    printf("dex");
    UNUSED(ea);
    REGX--;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(dey)
{
    printf("dey");
    UNUSED(ea);
    REGY--;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    return;
}
IMP_OPCODE(eor)
{
    printf("eor");
    REGA ^= READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
}
IMP_OPCODE(inc)
{
    printf("inc");
    BYTE value = READ8_EA;
    value++;
    CALC_NEGATIVE(value);
    CALC_ZERO(value);
    WRITE8_EA(value);
    return;
}
IMP_OPCODE(inx)
{
    printf("inx");
    UNUSED(ea);
    REGX++;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(iny)
{
    printf("iny");
    UNUSED(ea);
    REGY++;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    return;
}
IMP_OPCODE(jmp)
{
    printf("jmp");
    REGPC = ea;
    return;
}
IMP_OPCODE(jsr)
{
    printf("jsr");
    push_word(REGPC-1, ctx);
    REGPC = ea;
    return;
}
IMP_OPCODE(lda)
{
    printf("lda");
    REGA = READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    return;
}
IMP_OPCODE(ldx)
{
    printf("ldx");
    REGX = READ8_EA;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(ldy)
{
    printf("ldy");
    REGY = READ8_EA;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    return;
}
IMP_OPCODE(lsr)
{
    printf("lsr");
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
    printf("lsra");
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
    printf("nop");
    UNUSED(ctx);
    UNUSED(ea);
    return;
}
IMP_OPCODE(ora)
{
    printf("ora");
    REGA |= READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    return;
}
IMP_OPCODE(pha)
{
    printf("pha");
    UNUSED(ea);
    push_byte(REGA, ctx);
    return;
}
IMP_OPCODE(php)
{
    printf("php");
    UNUSED(ea);
    push_byte(REGSR, ctx);
    return;
}
IMP_OPCODE(pla)
{
    printf("pla");
    UNUSED(ea);
    REGA = pull_byte(ctx);
    return;
}
IMP_OPCODE(plp)
{
    printf("plp");
    UNUSED(ea);
    REGSR = pull_byte(ctx);
    return;
}
IMP_OPCODE(rol)
{
    printf("rol");
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
    printf("rola");
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
    printf("ror");
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
    printf("rora");
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
    printf("rti");
    UNUSED(ea);
    REGSR = pull_byte(ctx);
    REGPC = pull_word(ctx);
    return;
}
IMP_OPCODE(rts)
{
    printf("rts");
    UNUSED(ea);
    REGPC = pull_word(ctx) + 1;
    return;
}
IMP_OPCODE(sbc)
{
    printf("sbc");
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
    printf("sec");
    UNUSED(ea);
    SET_CARRY(*ctx);
    return;
}
IMP_OPCODE(sed)
{
    printf("sed");
    UNUSED(ea);
    SET_DECIMAL(*ctx);
    return;
}
IMP_OPCODE(sei)
{
    printf("sei");
    UNUSED(ea);
    SET_INTERRUPT(*ctx);
    return;
}
IMP_OPCODE(sta)
{
    printf("sta");
    WRITE8_EA(REGA);
    return;
}
IMP_OPCODE(stx)
{
    printf("stx");
    WRITE8_EA(REGX);
    return;
}
IMP_OPCODE(sty)
{
    printf("sty");
    WRITE8_EA(REGY);
    return;
}
IMP_OPCODE(tax)
{
    printf("tax");
    UNUSED(ea);
    REGX = REGA;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(tay)
{
    printf("tay");
    UNUSED(ea);
    REGY = REGA;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    return;
}
IMP_OPCODE(tsx)
{
    printf("tsx");
    UNUSED(ea);
    REGX = REGSP;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    return;
}
IMP_OPCODE(txa)
{
    printf("txa");
    UNUSED(ea);
    REGA = REGX;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    return;
}
IMP_OPCODE(txs)
{
    printf("txs");
    UNUSED(ea);
    REGSP = REGX;
    return;
}
IMP_OPCODE(tya)
{
    printf("tya");
    UNUSED(ea);
    REGA = REGY;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    return;
}
