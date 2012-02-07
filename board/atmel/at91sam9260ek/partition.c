/*
 * (C) Copyright 2008
 * Ulf Samuelsson <ulf@atmel.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */
#include <common.h>
#include <config.h>
#include <asm/hardware.h>
#include <dataflash.h>

AT91S_DATAFLASH_INFO dataflash_info[CFG_MAX_DATAFLASH_BANKS];

struct dataflash_addr cs[CFG_MAX_DATAFLASH_BANKS] = {
	{CFG_DATAFLASH_LOGIC_ADDR_CS0, 0},	/* Logical adress, CS */
	{CFG_DATAFLASH_LOGIC_ADDR_CS1, 1}
};
/*
 * shlee change 2008 11 24
 */
#if 0

/*define the area offsets*/
dataflash_protect_t area_list[NB_DATAFLASH_AREA] = {
	{0x00000000, 0x000041FF, FLAG_PROTECT_SET,   0, "Bootstrap"},
	{0x00004200, 0x000083FF, FLAG_PROTECT_CLEAR, 0, "Environment"},
	{0x00008400, 0x00041FFF, FLAG_PROTECT_SET,   0, "U-Boot"},
	{0x00042000, 0x00251FFF, FLAG_PROTECT_CLEAR, 0,	"Kernel"},
	{0x00252000, 0xFFFFFFFF, FLAG_PROTECT_CLEAR, 0,	"FS"},
};
#endif

/*define the area offsets*/
dataflash_protect_t area_list[NB_DATAFLASH_AREA] = {
	{0x00000000, 0x00001FFF, FLAG_PROTECT_CLEAR, 0, "Bootstrap"},
	{0x00002000, 0x00002FFF, FLAG_PROTECT_CLEAR, 0, "Environment"},
	{0x00003000, 0x0003FFFF, FLAG_PROTECT_CLEAR, 0, "U-Boot"},
	{0x00040000, 0x0027FFFF, FLAG_PROTECT_CLEAR, 0,	"Kernel"},
	{0x00280000, 0x006FFFFF, FLAG_PROTECT_CLEAR, 0,	"FS"},
	{0x00700000, 0x007FFFFF, FLAG_PROTECT_CLEAR, 0,	"CF"},
};
