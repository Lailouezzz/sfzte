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

#define CALC_CARRY(r)       if(r >> 8) SET_CARRY(*ctx); \
                                  else CLEAR_CARRY(*ctx);

#define CALC_NOTCARRY(r)       if(!(r >> 8)) SET_CARRY(*ctx); \
                                        else CLEAR_CARRY(*ctx);

#define CALC_ZERO(r)        if((r & 0x00FF) == 0) SET_ZERO(*ctx); \
                                             else CLEAR_ZERO(*ctx);

#define CALC_OVERFLOW(r, m, n)    if((((r ^ n) & (r ^ m)) \
                                    & 0x80) != 0) SET_OVERFLOW(*ctx); \
                                             else CLEAR_OVERFLOW(*ctx);

#define CALC_NEGATIVE(r)    if((r & 0x80) != 0) SET_NEGATIVE(*ctx); \
                                             else CLEAR_NEGATIVE(*ctx);

#define NEXTINSTR() REGPC += opsize


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

IMPL_OPCODE(adc)
{
    BYTE value = READ8_EA;
    WORD result = (WORD) (REGA + value + (IS_CARRY(*ctx) ? 1u : 0u));

    if(IS_DECIMAL(*ctx))
    {
        if((REGA & 0x0F) + (value & 0x0F) + (IS_CARRY(*ctx) ? 1u : 0u) > 0x09)
        {
            result += 0x06;
        }
        if(result > 0x99)
        {
            result += 0x60;
        }
    }
    CALC_CARRY(result);
    CALC_ZERO(result);
    CALC_OVERFLOW(result, value, REGA);
    CALC_NEGATIVE(result);

    REGA = (BYTE)result;
    NEXTINSTR();
    return;
}
IMPL_OPCODE(and)
{
    REGA &= READ8_EA;
    CALC_ZERO(REGA);
    CALC_NEGATIVE(REGA);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(asl)
{
    WORD result = READ8_EA << 1;
    CALC_CARRY(result);
    CALC_ZERO(result);
    CALC_NEGATIVE(result);
    WRITE8_EA((BYTE)result);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(asla)
{
    WORD result = READ8_EA << 1;
    CALC_CARRY(result);
    CALC_ZERO(result);
    CALC_NEGATIVE(result);
    REGA = (BYTE)result;
    NEXTINSTR();
    return;
}
IMPL_OPCODE(bcc)
{
    if(!IS_CARRY(*ctx))
    {
        REGPC = EA;
    }
    else
    {
        NEXTINSTR();
    }
    return;
}
IMPL_OPCODE(bcs)
{
    if(IS_CARRY(*ctx))
    {
        REGPC = EA;
    }
    else
    {
        NEXTINSTR();
    }
    return;
}
IMPL_OPCODE(beq)
{
    if(IS_ZERO(*ctx))
    {
        REGPC = EA;
    }
    else
    {
        NEXTINSTR();
    }
    return;
}
IMPL_OPCODE(bit)
{
    BYTE value = READ8_EA;
    BYTE result = REGA & value;
    CALC_ZERO(result);
    CALC_NEGATIVE(value);

    if((value & (1 << 6)) != 0)
        SET_OVERFLOW(*ctx);
    else
        CLEAR_OVERFLOW(*ctx);

    NEXTINSTR();
    return;
}
IMPL_OPCODE(bmi)
{
    if(IS_NEGATIVE(*ctx))
    {
        REGPC = EA;
    }
    else
    {
        NEXTINSTR();
    }
    return;
}
IMPL_OPCODE(bne)
{
    if(!IS_ZERO(*ctx))
    {
        REGPC = EA;
    }
    else
    {
        NEXTINSTR();
    }
    return;
}
IMPL_OPCODE(bpl)
{
    if(!IS_NEGATIVE(*ctx))
    {
        REGPC = EA;
    }
    else
    {
        NEXTINSTR();
    }
    return;
}
IMPL_OPCODE(brk)
{
    UNUSED(opsize);
    push_word(REGPC+2, ctx);
    push_byte(REGSR | FLAG_BREAK, ctx);
    SET_INTERRUPT(*ctx);
    REGPC = CREATE_WORD(READ8(0xFFFE), READ8(0xFFFF));
    return;
}
IMPL_OPCODE(bvc)
{
    if(!IS_OVERFLOW(*ctx))
    {
        REGPC = EA;
    }
    else
    {
        NEXTINSTR();
    }
    return;
}
IMPL_OPCODE(bvs)
{
    if(IS_OVERFLOW(*ctx))
    {
        REGPC = EA;
    }
    else
    {
        NEXTINSTR();
    }
    return;
}
IMPL_OPCODE(clc)
{
    CLEAR_CARRY(*ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(cld)
{
    CLEAR_DECIMAL(*ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(cli)
{
    CLEAR_INTERRUPT(*ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(clv)
{
    CLEAR_OVERFLOW(*ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(cmp)
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
    
    NEXTINSTR();
    return;
}
IMPL_OPCODE(cpx)
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
    
    NEXTINSTR();
    return;
}
IMPL_OPCODE(cpy)
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
    
    NEXTINSTR();
    return;
}
IMPL_OPCODE(dec)
{
    BYTE value = READ8_EA;
    value--;
    CALC_NEGATIVE(value);
    CALC_ZERO(value);
    WRITE8_EA(value);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(dex)
{
    REGX--;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(dey)
{
    REGY--;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(eor)
{
    REGA ^= READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(inc)
{
    BYTE value = READ8_EA;
    value++;
    CALC_NEGATIVE(value);
    CALC_ZERO(value);
    WRITE8_EA(value);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(inx)
{
    REGX++;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(iny)
{
    REGY++;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(jmp)
{
    UNUSED(opsize);
    REGPC = EA;
    return;
}
IMPL_OPCODE(jsr)
{
    UNUSED(opsize);
    push_word(REGPC+2, ctx);
    REGPC = EA;
    return;
}
IMPL_OPCODE(lda)
{
    REGA = READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(ldx)
{
    REGX = READ8_EA;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(ldy)
{
    REGY = READ8_EA;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(lsr)
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
    NEXTINSTR();
    return;
}
IMPL_OPCODE(lsra)
{
    BYTE value = REGA;
    BYTE result = value >> 1;
    if((value & 1))
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    CLEAR_NEGATIVE(*ctx);
    CALC_ZERO(result);
    REGA = result;
    NEXTINSTR();
    return;
}
IMPL_OPCODE(nop)
{
    UNUSED(ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(ora)
{
    REGA |= READ8_EA;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(pha)
{
    push_byte(REGA, ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(php)
{
    push_byte(REGSR | FLAG_BREAK, ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(pla)
{
    REGA = pull_byte(ctx);
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(plp)
{
    REGSR = pull_byte(ctx) | FLAG_CONSTANT;
    NEXTINSTR();
    return;
}
IMPL_OPCODE(rol)
{
    BYTE value = READ8_EA;
    WORD result = (WORD) ((value << 1) | (IS_CARRY(*ctx) ? 1u : 0u));

    CALC_NEGATIVE(result);
    CALC_ZERO(result);
    CALC_CARRY(result);
    WRITE8_EA((BYTE) result);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(rola)
{
    WORD result = (WORD) ((REGA << 1) | (IS_CARRY(*ctx) ? 1u : 0u));

    CALC_NEGATIVE(result);
    CALC_ZERO(result);
    CALC_CARRY(result);
    REGA = (BYTE) result;
    NEXTINSTR();
    return;
}
IMPL_OPCODE(ror)
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
    NEXTINSTR();
    return;
}
IMPL_OPCODE(rora)
{
    BYTE value = REGA;
    WORD result = (WORD) ((value >> 1) | (IS_CARRY(*ctx) ? (1u << 7) : 0u));

    CALC_NEGATIVE(result);
    CALC_ZERO(result);
    if(value & 1)
        SET_CARRY(*ctx);
    else
        CLEAR_CARRY(*ctx);
    
    REGA = (BYTE) result;
    NEXTINSTR();
    return;
}
IMPL_OPCODE(rti)
{
    UNUSED(opsize);
    REGSR = pull_byte(ctx);
    REGPC = pull_word(ctx);
    return;
}
IMPL_OPCODE(rts)
{
    UNUSED(opsize);
    REGPC = pull_word(ctx) + 1;
    return;
}
IMPL_OPCODE(sbc)
{
    BYTE value = READ8_EA;
    WORD result = (WORD) (REGA - value - (IS_CARRY(*ctx) ? 0u : 1u));

    if(IS_DECIMAL(*ctx))
    {
        if((REGA & 0x0F) - (value & 0x0F) - (IS_CARRY(*ctx) ? 0u : 1u) > 0x09)
        {
            result -= 0x06;
        }
        if(result > 0x99)
        {
            result -= 0x60;
        }
    }
    CALC_NOTCARRY(result);
    CALC_ZERO(result);
    CALC_OVERFLOW(REGA, value, result);
    CALC_NEGATIVE(result);

    REGA = (BYTE) result;
    NEXTINSTR();
    return;
}
IMPL_OPCODE(sec)
{
    SET_CARRY(*ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(sed)
{
    SET_DECIMAL(*ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(sei)
{
    SET_INTERRUPT(*ctx);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(sta)
{
    WRITE8_EA(REGA);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(stx)
{
    WRITE8_EA(REGX);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(sty)
{
    WRITE8_EA(REGY);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(tax)
{
    REGX = REGA;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(tay)
{
    REGY = REGA;
    CALC_NEGATIVE(REGY);
    CALC_ZERO(REGY);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(tsx)
{
    REGX = REGSP;
    CALC_NEGATIVE(REGX);
    CALC_ZERO(REGX);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(txa)
{
    REGA = REGX;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    NEXTINSTR();
    return;
}
IMPL_OPCODE(txs)
{
    REGSP = REGX;
    NEXTINSTR();
    return;
}
IMPL_OPCODE(tya)
{
    REGA = REGY;
    CALC_NEGATIVE(REGA);
    CALC_ZERO(REGA);
    NEXTINSTR();
    return;
}
