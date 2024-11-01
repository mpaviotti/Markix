#ifndef __ATA_H
#define __ATA_H

#define PRIMARY_MSTR   0x1F0 /* Master */
#define PRIMARY_SLV    0x3F6 /* Slave */
#define SECONDARY_MSTR 0x170 /* Master */
#define SECONDARY_SLV  0x376 /* Slave */

#define HD_BASE     PRIMARY_MSTR  /* Selezionare il controller */

#define HD_DATA     HD_BASE   /* R/W */ 
#define HD_ERROR    HD_BASE+1 /* Read-Only */ 
#define HD_FEATURES HD_BASE+1 /* Write-Only */
#define HD_SECT_CNT HD_BASE+2 /* R/W */
#define HD_LBA_LOW  HD_BASE+3 /* R/W */
#define HD_LBA_MID  HD_BASE+4 /* R/W */
#define HD_LBA_HIGH HD_BASE+5 /* R/W */
#define HD_DRV_HEAD HD_BASE+6 /* R/W */
#define HD_STATUS   HD_BASE+7 /* Read-Only */
#define HD_COMMAND  HD_BASE+7 /* Write-Only */

#define BSY  0x80 /* Busy */
#define DRDY 0x40 /* Device Ready */
#define DF   0x20 /* Device Fault */
#define DSC  0x10 /* Seek Fault */
#define DRQ  0x08 /* Data Transfer Requested */
#define CORR 0x04 /* Data Corrected */
#define IDX  0x02 /* Index Mark */
#define ERR  0x01 /* Error */

extern void ata_read(int sector, unsigned char *buffer);
extern void ata_write(int sector, unsigned char *buffer);

#endif
