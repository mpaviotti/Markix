#include <ata.h>

void ata_read(int sector, unsigned char *buffer){
  int i=0;
  short word=0;
  char status;
  outb(0x00, HD_DRV_HEAD);
  outb(0x01, HD_SECT_CNT);
  outb((unsigned char)sector, HD_LBA_LOW);
  outb((unsigned char)(sector >> 8), HD_LBA_MID);
  outb((unsigned char)(sector >> 16), HD_LBA_HIGH);
  outb(0x20, HD_COMMAND); /* Read Command */

  /* Poll finchè il drive è pronto */
  do{
    status = inb(HD_STATUS); 
    sleep(100);
  } while(!(!(status & BSY) && (status & DRQ)));

  for(i = 0;i < 256; i++){
    word = inw(HD_DATA);
    buffer[i*2] = (unsigned char)word;
    buffer[i*2 + 1] = (unsigned char)(word >> 8);
  }
}

void ata_write(int sector, unsigned char *buffer){
  int i=0;
  short word=0;
  char status;

  outb(0x00, HD_FEATURES);
  outb(0x01, HD_SECT_CNT);
  outb(sector, HD_LBA_LOW);
  outb((sector >> 8), HD_LBA_MID);
  outb((sector >> 16), HD_LBA_HIGH);
  outb(0x00, HD_DRV_HEAD);
  outb(0x30, HD_COMMAND); /* Write Command */
	
  /* Poll finchè il drive è pronto */
  do{
    status = inb(HD_STATUS); 
    sleep(100);
  } while(!(!(status & BSY) && (status & DRQ)));

  for(i = 0;i < 512; i++){
    word = buffer[i*2] | (buffer[i*2+1] << 8);
    outw(word, HD_DATA);
  }

}

