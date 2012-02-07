
/*
 * Copyright (C) systembase 
 *
 * made by John Lee
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef AT91_WATCHDOD_H
#define AT91_WATCHDOG_H

/* -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register --------  */
#define AT91C_WDTC_WDCR			(AT91_WDT + 0x00)				/* (WDTC) Watchdog Control Register */
#define AT91C_WDTC_WDRSTT		((unsigned int) 0x1 <<  0)		/* (WDTC) Watchdog Restart */
#define AT91C_WDTC_KEY			((unsigned int) 0xA5 << 24)		/* (WDTC) Watchdog KEY Password */

/* -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register --------  */
#define AT91C_WDTC_WDSR			(AT91_WDT + 0x08)				/* (WDTC) Watchdog Status Register */
#define AT91C_WDTC_WDV			((unsigned int) 0xFFF <<  0)	/* (WDTC) Watchdog Timer Restart */
#define AT91C_WDTC_WDFIEN		((unsigned int) 0x1 << 12)		/* (WDTC) Watchdog Fault Interrupt Enable */
#define AT91C_WDTC_WDRSTEN		((unsigned int) 0x1 << 13)		/* (WDTC) Watchdog Reset Enable */
#define AT91C_WDTC_WDRPROC		((unsigned int) 0x1 << 14)		/* (WDTC) Watchdog Timer Restart */
#define AT91C_WDTC_WDDIS		((unsigned int) 0x1 << 15)		/* (WDTC) Watchdog Disable */
#define AT91C_WDTC_WDD			((unsigned int) 0xFFF << 16)	/* (WDTC) Watchdog Delta Value */
#define AT91C_WDTC_WDDBGHLT		((unsigned int) 0x1 << 28)		/* (WDTC) Watchdog Debug Halt */
#define AT91C_WDTC_WDIDLEHLT	((unsigned int) 0x1 << 29)		/* (WDTC) Watchdog Idle Halt */

/* -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register --------  */
#define AT91C_WDTC_WDMR 		(AT91_WDT + 0x04)				/* (WDTC) Watchdog Mode Register */
#define AT91C_WDTC_WDUNF		((unsigned int) 0x1 <<  0)		/* (WDTC) Watchdog Underflow */
#define AT91C_WDTC_WDERR		((unsigned int) 0x1 <<  1)		/* (WDTC) Watchdog Error */

#endif 
