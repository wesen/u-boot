/*
 * (C) Copyright 2007-2008
 * Stelian Pop <stelian.pop@leadtechdesign.com>
 * Lead Tech Design <www.leadtechdesign.com>
 *
 * Configuation settings for the AT91SAM9260EK board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/* ARM asynchronous clock */
#define AT91_MAIN_CLOCK		198656000	/* from 18.432 MHz crystal */
#define AT91_MASTER_CLOCK	99328000	/* peripheral = main / 2 */
#define CFG_HZ			1000000		/* 1us resolution */

#define AT91_SLOW_CLOCK		32768	/* slow clock */

#define CONFIG_ARM926EJS	1	/* This is an ARM926EJS Core	*/
#define CONFIG_AT91SAM9260	1	/* It's an Atmel AT91SAM9260 SoC*/
#define CONFIG_AT91SAM9260EK	1	/* on an AT91SAM9260EK Board	*/
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff	*/

#define CONFIG_CMDLINE_TAG	1	/* enable passing of ATAGs	*/
#define CONFIG_SETUP_MEMORY_TAGS 1
#define CONFIG_INITRD_TAG	1

#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SKIP_RELOCATE_UBOOT

/*
 * Hardware drivers
 */
#define CONFIG_ATMEL_USART	1
#undef CONFIG_USART0
#undef CONFIG_USART1
#undef CONFIG_USART2
#define CONFIG_USART3		1	/* USART 3 is DBGU */
/*
 * shlee 081124
 */

//#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTDELAY	1 /* 1 = 100ms */


/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE	1
#define CONFIG_BOOTP_BOOTPATH		1
#define CONFIG_BOOTP_GATEWAY		1
#define CONFIG_BOOTP_HOSTNAME		1

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>
#undef CONFIG_CMD_BDI
#undef CONFIG_CMD_IMI
#undef CONFIG_CMD_AUTOSCRIPT
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_IMLS
#undef CONFIG_CMD_MII

#define CONFIG_CMD_PING		1
#undef CONFIG_CMD_DHCP	
#define CONFIG_CMD_NAND		
#undef CONFIG_CMD_USB		
#define CONFIG_DRIVER_ETHER 1


/* SDRAM */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			0x20000000
/*
 * shlee_define for SDRAM 32Mbyte
 */

//#define PHYS_SDRAM_SIZE			0x04000000	/* 64 megs */
#define PHYS_SDRAM_SIZE			0x02000000	/* 32 megs */


/* DataFlash */
#define CONFIG_HAS_DATAFLASH		1
#define CFG_SPI_WRITE_TOUT		(5*CFG_HZ)
#define CFG_MAX_DATAFLASH_BANKS		2
#define CFG_DATAFLASH_LOGIC_ADDR_CS0	0xC0000000	/* CS0 */
#define CFG_DATAFLASH_LOGIC_ADDR_CS1	0xD0000000	/* CS1 */
#define AT91_SPI_CLK			15000000
#define DATAFLASH_TCSS			(0x1a << 16)
#define DATAFLASH_TCHS			(0x1 << 24)

#undef CONFIG_DISPLAY_DATAFLASHINFO 

/* NAND flash */
#define NAND_MAX_CHIPS			1
#define CFG_MAX_NAND_DEVICE		1
#define CFG_NAND_BASE			0x40000000
#define CFG_NAND_DBW_8			1

/* NOR flash - no real flash on this board */
#define CFG_NO_FLASH			1

/* console device */
#define CFG_CONSOLE_INFO_QUIET 1

/* Ethernet */
#define CONFIG_MACB			1
#undef CONFIG_RMII		
#define CONFIG_NET_MULTI	1		
#define CONFIG_NET_RETRY_COUNT		20
#define CONFIG_RESET_PHY_R		1

#define CFG_LOAD_ADDR			0x22000000	/* load address */

#define CFG_MEMTEST_START		PHYS_SDRAM
#define CFG_MEMTEST_END			0x23e00000

#undef CFG_USE_DATAFLASH_CS0
#define CFG_USE_DATAFLASH_CS1		1
#undef CFG_USE_NANDFLASH

#ifdef CFG_USE_DATAFLASH_CS0

/* bootstrap + u-boot + env + linux in dataflash on CS0 */
#define CONFIG_ENV_IS_IN_DATAFLASH	1
#define CFG_MONITOR_BASE	(CFG_DATAFLASH_LOGIC_ADDR_CS0 + 0x8400)
#define CONFIG_ENV_OFFSET		0x4200
#define CONFIG_ENV_ADDR		(CFG_DATAFLASH_LOGIC_ADDR_CS0 + CONFIG_ENV_OFFSET)
#define CONFIG_ENV_SIZE		0x4200
#define CONFIG_BOOTCOMMAND	"cp.b 0xC0042000 0x22000000 0x210000; bootm"
#define CONFIG_BOOTARGS		"console=ttyS0,115200 "			\
				"root=/dev/mtdblock0 "			\
				"mtdparts=at91_nand:-(root) "		\
				"rw rootfstype=jffs2"

#elif CFG_USE_DATAFLASH_CS1

#define CONFIG_ENV_IS_IN_DATAFLASH	1
#define CFG_MONITOR_BASE	(CFG_DATAFLASH_LOGIC_ADDR_CS1 + 0x3180)
#define CONFIG_ENV_OFFSET		0x2100
#define CONFIG_ENV_ADDR		(CFG_DATAFLASH_LOGIC_ADDR_CS1 + CONFIG_ENV_OFFSET)
#define CONFIG_ENV_SIZE		0x1080
#define CONFIG_BOOTCOMMAND	"cp.b ${OS_FLASH} ${OS_SDRAM} ${OS_Size}; cp.b ${FileSystem_FLASH} ${FileSystem_SDRAM} ${FileSystem_Size}; bootm ${OS_SDRAM} ${FileSystem_SDRAM}"
#define CONFIG_BOOTARGS		"root=/dev/ram rw console=ttyS0,115200,mem=32M "

#else /* CFG_USE_NANDFLASH */

/* bootstrap + u-boot + env + linux in nandflash */
#define CONFIG_ENV_IS_IN_NAND	1
#define CONFIG_ENV_OFFSET		0x60000
#define CONFIG_ENV_OFFSET_REDUND	0x80000
#define CONFIG_ENV_SIZE		0x20000		/* 1 sector = 128 kB */
#define CONFIG_BOOTCOMMAND	"nand read 0x22000000 0xA0000 0x200000; bootm"
#define CONFIG_BOOTARGS		"console=ttyS0,115200 "			\
				"root=/dev/mtdblock5 "			\
				"mtdparts=at91_nand:128k(bootstrap)ro,"	\
				"256k(uboot)ro,128k(env1)ro,"		\
				"128k(env2)ro,2M(linux),-(root) "	\
				"rw rootfstype=jffs2"

#endif

#define CONFIG_BAUDRATE		115200
#define CFG_BAUDRATE_TABLE	{115200 , 19200, 38400, 57600, 9600 }

#define CFG_PROMPT		"U-Boot> "
#define CFG_CBSIZE		256
#define CFG_MAXARGS		16
#define CFG_PBSIZE		(CFG_CBSIZE + sizeof(CFG_PROMPT) + 16)
#define CFG_LONGHELP		1
#define CONFIG_CMDLINE_EDITING	1

#define ROUND(A, B)		(((A) + (B)) & ~((B) - 1))
/*
 * Size of malloc() pool
 */
#define CFG_MALLOC_LEN		ROUND(3 * CONFIG_ENV_SIZE + 128*1024, 0x1000)
#define CFG_GBL_DATA_SIZE	128	/* 128 bytes for initial data */

#define CONFIG_STACKSIZE	(32*1024)	/* regular stack */

#ifdef CONFIG_USE_IRQ
#error CONFIG_USE_IRQ not supported
#endif

#define CONFIG_BOOTSTSTART		0xD0000000
#define CONFIG_BOOTSTEND		0xD00020FF
#define CONFIG_BOOTCFSTART      0xD0002100
#define CONFIG_BOOTCFEND		0xD000317F
#define CONFIG_BOOTLDSTART		0xD0003180
#define CONFIG_BOOTLDEND		0xD003FEFF
#define CONFIG_OSSTART          0xD003FF00
#define CONFIG_OSEND			0xD025D57F
#define CONFIG_FSSTART			0xD025D580
#define CONFIG_FSEND			0xD06A7E1F
#define CONFIG_CONFSTART		0xD06A7E20
#define CONFIG_CONFEND			0xD07FFFFF

#define CONFIG_BOOTSTFILE_HEAD	"eddy-bs-"
#define CONFIG_BOOTLDFILE_HEAD  "eddy-bl-"
#define CONFIG_OSFILE_HEAD      "eddy-os-"
#define CONFIG_FSFILE_HEAD   	"eddy-fs-"
#define CONFIG_CONFFILE_HEAD	"eddy-cf-"

#define CONFIG_BOOTSTFILE_TAIL	".bin"
#define CONFIG_BOOTLDFILE_TAIL	".bin"
#define CONFIG_OSFILE_TAIL		".bin"
#define CONFIG_FSFILE_TAIL		".bin"
#define CONFIG_CONFFILE_TAIL	".bin"

#define CONFIG_CONSOLE_ENV		"ttyS0,115200"

#define CONFIG_DOWNLOADADDR     0x20000000
#define CONFIG_OS_SDRAM			0x20000000
#define CONFIG_FS_SDRAM			0x20500000

#define CONFIG_MAX_OS_SIZE		0x21d680
#define CONFIG_MAX_FS_SIZE		0x44A8A0


#define MAC_EEPROM_ADDR   		0x54

#define CONFIG_ETHADDR      	00:05:F4:11:22:33
#define CONFIG_IPADDR       	192.168.0.223
#define CONFIG_SERVERIP     	192.168.0.220
#define CONFIG_GATEWAYIP		192.168.0.1
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_HOSTNAME		Eddy
#define CONFIG_EXTRA_ENV_SETTINGS 1
#endif
