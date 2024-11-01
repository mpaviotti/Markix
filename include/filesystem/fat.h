#ifndef __FAT_H
#define __FAT_H

#define EOF 0x1A

#define TOT_SECTORS 62730
#define FAT_SIZE 4096
#define SECTOR_SIZE 512
#define CLUSTER_SIZE 8
#define CLUSTER_DIM (CLUSTER_SIZE*SECTOR_SIZE)
#define ROOT_DIR_CLUSTER (((SECTOR_SIZE + FAT_SIZE*2)/SECTOR_SIZE)/CLUSTER_SIZE+2)

#define CLUST_FREE         0x000       //Cluster libero
#define CLUST_RESERVED     0x001       //Riservato
#define CLUST_FIRST_USABLE 0x002       //Primo cluster usabile
#define CLUST_LAST_USABLE  0xFEF       //Ultimo cluster usabile
#define CLUST_BAD          0xFF7       //Cluster non usabile
#define CLUST_LAST         0xFFF       //Ultimo cluster del file

#define FILE_RO      1		/* Sola lettura */
#define FILE_HIDDEN  2		/* Nascosto */
#define FILE_DIR     4		/* Directory */

#include <type.h>

/* Bootsector della FAT12 */
typedef struct fat_boot_sector {

  /* Primi 36 bytes, usata da tutte le FAT */
  char ignored[3];	
  char oem_id[8];	/* Versione di DOS */
  word sect_size;	/* Bytes per logical sector */
  byte clust_size;	/* Sectors/Cluster */
  word reserved_sect;	/* Reserved sectors */
  byte fats;		/* Numero di tabelle FAT */
  word dir_entries;	/* Numero di dir radice */
  word num_sect;	/* Numero di settori */
  byte media;		/* Media Descriptor Type */
  word sect_fat;	/* Sectors/FAT */
  word sect_track;	/* Settori per traccia */
  word heads;	        /* Headsx */
  dword hidden_sect;	/* Settori nascosti */
  dword num_sect2;	/* Numero totale di settori se > 65535*/

  /* Extended BIOS Parameter Block */
  byte drive_num;       /* 0x00 per il floppy, 0x80 per gliharddisks*/
  byte reserved1;       /* Riservato*/
  byte signature;       /* Firma (0x28 or 0x29)*/
  dword vol_id;      /* Volume ID*/
  byte label[11];       /* Etichetta del volume */
  dword fattype;     /* System identifier string*/
} boot_sector;

typedef struct fat_dir_entry {
  char name[8], ext[3];  /* Nome e estensione */
  byte attr;             /* Attributi */
  byte lcase;	         /* Not Used */
  byte ctime_ms;         /* Tempo di creazione (millisecondi)*/
  word ctime;            /* Tempo di creazione (sec, min, hour) */
  word cdate;            /* Data  di creazione */
  word adate;	         /* Data dell'ultimo accesso */
  word starthi;	         /* Not Used */
  word time_last_mod;    /* Ultima modifica */
  word date_last_mod;    /* Data ultima modifica */
  word start;            /* Primo cluster*/
  dword size;		 /* Dimensione in byte */
} fat_entry;

#endif
