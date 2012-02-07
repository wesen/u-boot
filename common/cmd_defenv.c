/*
 * (C) Copyright 2000
 * Wolfgang Denk,	DENX Software Engineering, wd@denx.de.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Boot support
 */
#include <config.h>
#include <common.h>
#include <command.h>
#include <linux/ctype.h>
#ifdef	CONFIG_NEW_DF_PARTITION
#include <dataflash.h>
#endif
#if	1
int do_defenv (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	char env[256];
  /*	int	i;*/
  /*	DECLARE_GLOBAL_DATA_PTR;*/
	

#define XMK_STR(x)	#x
#define MK_STR(x)	XMK_STR(x)

	setenv("ipaddr",	MK_STR(CONFIG_IPADDR));
	setenv("serverip",	MK_STR(CONFIG_SERVERIP));

	setenv("gatewayip",	MK_STR(CONFIG_GATEWAYIP));
	setenv("netmask",	MK_STR(CONFIG_NETMASK));

	setenv("Bootstrap_FLASH",		MK_STR(CONFIG_BOOTSTSTART));  /* Config it ! */
	setenv("Bootloader_FLASH",  MK_STR(CONFIG_BOOTLDSTART));
	setenv("OS_FLASH",					MK_STR(CONFIG_OSSTART));
	setenv("FileSystem_FLASH",	MK_STR(CONFIG_FSSTART));
	setenv("Config_FLASH",			MK_STR(CONFIG_CONFSTART));

	setenv("Bootstrap_END",		MK_STR(CONFIG_BOOTSTEND));  /* Config it ! */
	setenv("Bootloader_END",  MK_STR(CONFIG_BOOTLDEND));
	setenv("OS_END",					MK_STR(CONFIG_OSEND));
	setenv("FileSystem_END",	MK_STR(CONFIG_FSEND));
	setenv("Config_END",			MK_STR(CONFIG_CONFEND));

	setenv("Download_SDRAM",    MK_STR(CONFIG_DOWNLOADADDR));
	setenv("OS_SDRAM",					MK_STR(CONFIG_OS_SDRAM));
	setenv("FileSystem_SDRAM",	MK_STR(CONFIG_FS_SDRAM));
	
	setenv("bootdelay",		MK_STR(CONFIG_BOOTDELAY));
	
	setenv("OS_Size",		MK_STR(CONFIG_MAX_OS_SIZE));
	setenv("FileSystem_Size",		MK_STR(CONFIG_MAX_FS_SIZE));
	
//	sprintf(env, "cp.b ${OS_FLASH} ${OS_SDRAM} 0x240000; cp.b ${FileSystem_FLASH} ${FileSystem_SDRAM} 0x480000; bootm ${OS_SDRAM} ${FileSystem_SDRAM}");
	sprintf(env, "cp.b ${OS_FLASH} ${OS_SDRAM} ${OS_Size}; cp.b ${FileSystem_FLASH} ${FileSystem_SDRAM} ${FileSystem_Size}; bootm ${OS_SDRAM} ${FileSystem_SDRAM}");
	setenv("bootcmd",	env);
	setenv("console",	"ttyS0,115200");
	setenv("bootargs",	"root=/dev/ram rw console=ttyS0,115200,mem=32M");

	return (saveenv() ? 1 : 0);
}



U_BOOT_CMD(
	defenv,	1,	1,	do_defenv,
	"defenv\t- Create a default environment\n",
	"\n"
);


int do_setargs (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{

	char cmd[512];
	char *fstype;


	fstype = getenv("fstype");
	if(fstype != NULL) {
		if(fstype[0] == 'f') {
	
			sprintf(cmd,"root=%s rootfstype=%s ip=%s:%s:%s:%s console=%s,mem=%s",
				getenv("flashfs"),
				getenv("rootfstype"),
				getenv("ipaddr"),
				getenv("serverip"),
				getenv("gatewayip"),
				getenv("netmask"),
				getenv("console"),
				getenv("mem")
			);
			cmd[511] = '\0';
			printf("len=%d: %s\n",strlen(cmd),cmd);
			if(strlen(cmd) > 500) {
				printf("Error: Environment too large during 'setargs'\n");
			} else {
				setenv("bootargs",cmd);
				setenv("bootcmd",	"run load-kernel ; bootm 21000000");
			}
		} else if(cmd[0] == 'r') {
			sprintf(cmd,"root=%s %s initrd=%s ramdisk_size=%s ip=%s:%s:%s:%s console=%s,mem=%s",
				getenv("ramfs"),
				getenv("access"),
				getenv("initrd"),
				getenv("ramdisk_size"),
				getenv("ipaddr"),
				getenv("serverip"),
				getenv("gatewayip"),
				getenv("netmask"),
				getenv("console"),
				getenv("mem")
			);
			printf("len=%d: %s\n",strlen(cmd),cmd);
			cmd[511] = '\0';
			if(strlen(cmd) > 500) {
				printf("Error: Environment too large during 'setargs'\n");
			} else {
				setenv("bootargs",cmd);
				setenv("bootcmd",	"run load ; bootm 21000000");
			}
		}
	}
	return 0;
}

U_BOOT_CMD(
	setargs,	1,	1,	do_setargs,
	"setargs\t- Create a bootargs from:"
	"fstype=flash:	(${flash} ${access} ${initrd} ${ramdisk_size}) "
	"fstype=ram:	(${ram}   ${access} ${initrd} ${ramdisk_size}) "
	"${ipaddr} ${serverip} ${gatewayip} ${netmask} "
	"${console} ${mem}\n"
	,	"\n"
);

int do_os (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	char *kchip;
	char *kdate;
	char *kver;
	char cmd[512];
	kchip = getenv("hostname");
	kdate = getenv("kernel-date");
	kver = getenv("kernel-version");
	if((strlen(kdate) + strlen(kver) + 32) >  500) {
		printf("Error: Environment too large during 'os': ");
		printf("len=%d\n", strlen(kdate) + strlen(kver) + 32);
	} else if(kver != NULL) {
		if(kdate != NULL) {
			sprintf(cmd,"%s-linux-%s-%s.gz",kchip,kver,kdate);
		} else {
			sprintf(cmd,"%s-linux-%s.gz",kchip,kver);
		}
		printf("Setting kernel to %s\n",cmd);
		setenv("linux",cmd);
		return 0;
	}
	return 1;
}

U_BOOT_CMD(
	os,	1,	1,	do_os,
	"os\t- Select linux version  ${hostname}-linux-${kernel-name}-${kernel-date}\n"
	,	"\n"
);


int do_fs (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	char *ver;
	char *fsdate;
	char *hostname;
	char cmd[512];
	fsdate		= getenv("fs-date");
	hostname	= getenv("hostname");

	if(fsdate != NULL) {
		sprintf(cmd,"rootfs.arm-%s.ext2",fsdate);
		setenv("rd-1",cmd);
		sprintf(cmd,"rootfs.arm-%s.jffs2",fsdate);
		setenv("rd-2",cmd);
	}
	ver = getenv("ver");		/* Find out which version we are using*/
	if(cmd==NULL) {
		setenv("ver","1");
	}
	ver = getenv("ver");		/* Find out which version we are using*/
	sprintf(cmd,"rd-%s",ver);	/* create rd${ver}*/
	ver=getenv(cmd);
	sprintf(cmd,"%s",ver);
	printf("Setting ramdisk to %s\n",cmd);
	setenv("rd",cmd);
	return 0;
}


U_BOOT_CMD(
	fs,	1,	1,	do_fs,
	"fs\t- Select ramdisk version == rd-${ver}\n"
	,	"\n"
);

#endif	/* CONFIG_DEFENV */
