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
#define READ8_EA (ctx->read(ea))
#define WRITE8_EA(b) (ctx->write((b), ea))
#define REGA (ctx->a)

#define CALC_CARRY(r)       if((r & 0xFF00) != 0) SET_CARRY(*ctx); \
                                             else CLEAR_CARRY(*ctx);
#define CALC_ZERO(r)        if((r & 0x00FF) == 0) SET_ZERO(*ctx); \
                                             else CLEAR_ZERO(*ctx);
#define CALC_OVERFLOW(r, m, n)    if((((r ^ n) & (r ^ m)) \
                                    & 0x80) != 0) SET_OVERFLOW(*ctx); \
                                             else CLEAR_OVERFLOW(*ctx);
#define CALC_NEGATIVE(r)    if((r & 0x0080) != 0) SET_NEGATIVE(*ctx); \
                                             else CLEAR_NEGATIVE(*ctx);


IMP_OPCODE(adc)
{
    BYTE value = READ8_EA;
    WORD result = (WORD) (REGA + value + (IS_CARRY(*ctx) ? 1 : 0));
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

}
IMP_OPCODE(bcs)
{

}
IMP_OPCODE(beq)
{

}
IMP_OPCODE(bit)
{

}
IMP_OPCODE(bmi)
{

}
IMP_OPCODE(bne)
{

}
IMP_OPCODE(bpl)
{

}
IMP_OPCODE(brk)
{

}
IMP_OPCODE(bvc)
{

}
IMP_OPCODE(bvs)
{

}
IMP_OPCODE(clc)
{

}
IMP_OPCODE(cld)
{

}
IMP_OPCODE(cli)
{

}
IMP_OPCODE(clv)
{

}
IMP_OPCODE(cmp)
{

}
IMP_OPCODE(cpx)
{

}
IMP_OPCODE(cpy)
{

}
IMP_OPCODE(dec)
{

}
IMP_OPCODE(dex)
{

}
IMP_OPCODE(dey)
{

}
IMP_OPCODE(eor)
{

}
IMP_OPCODE(inc)
{

}
IMP_OPCODE(inx)
{

}
IMP_OPCODE(iny)
{

}
IMP_OPCODE(jmp)
{

}
IMP_OPCODE(jsr)
{

}
IMP_OPCODE(lda)
{

}
IMP_OPCODE(ldx)
{

}
IMP_OPCODE(ldy)
{

}
IMP_OPCODE(lsr)
{

}
IMP_OPCODE(nop)
{

}
IMP_OPCODE(ora)
{

}
IMP_OPCODE(pha)
{

}
IMP_OPCODE(php)
{

}
IMP_OPCODE(pla)
{

}
IMP_OPCODE(plp)
{

}
IMP_OPCODE(rol)
{

}
IMP_OPCODE(ror)
{

}
IMP_OPCODE(rti)
{

}
IMP_OPCODE(rts)
{

}
IMP_OPCODE(sbc)
{

}
IMP_OPCODE(sec)
{

}
IMP_OPCODE(sed)
{

}
IMP_OPCODE(sei)
{

}
IMP_OPCODE(sta)
{

}
IMP_OPCODE(stx)
{

}
IMP_OPCODE(sty)
{

}
IMP_OPCODE(tax)
{

}
IMP_OPCODE(tay)
{

}
IMP_OPCODE(tsx)
{

}
IMP_OPCODE(txa)
{

}
IMP_OPCODE(txs)
{

}
IMP_OPCODE(tya)
{

}
