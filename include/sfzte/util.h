/* *****************************************************************************
 * util.h -- All utility typedef/function
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
#ifndef H_UTIL
#define H_UTIL
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#define UNUSED(x) (void)(x)
#define CREATE_WORD(LL, HH) (WORD) ((LL) + ((WORD)(HH) << 8))


typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint16_t sfzt_addr;
typedef BYTE (*bus_read)(sfzt_addr);
typedef void (*bus_write)(BYTE, sfzt_addr);


#endif /// #ifndef H_UTIL
