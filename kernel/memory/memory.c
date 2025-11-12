#include <screen.h>
#include <memory.h>

unsigned int phys_mem_size;
char mem_bitmap[MEM_BITMAP_SIZE];

/* Calcola la dimensione della memoria fisica */
unsigned int mem_size(void){
  
  unsigned int *mem_current = (unsigned int *)START_EXT_MEM;

  /* assumiamo che la memoria sia grande 'TOTAL_MEM'*/
  #ifndef AUTO_PROBE

  mem_current = TOTAL_MEM; 

  #else AUTO_PROBE
  while(1){
    *mem_current = (unsigned int)0xAA55AA55;
    asm("": : :"memory");

    if(*mem_current == (unsigned int)0xAA55AA55){
      *mem_current= (unsigned int)~0xAA55AA55;
      asm("": : :"memory");

      if(*mem_current == (unsigned int)~0xAA55AA55){
	mem_current = mem_current + 0x400;	
      } else {
	break;
      }
    } else {
      break;
    }
    
    asm("": : :"memory");
  }
  #endif
  return (unsigned int)mem_current - START_EXT_MEM;
}

/* Inizializza la bitmap delle pagine da PAGE_SIZE bytes */
void init_memory(void){
  int i;
  unsigned char bit_value = 0x00;
  phys_mem_size = mem_size();

  for(i = 0; i < MEM_BITMAP_SIZE; i++){
    
    //imposta come occupate le pagine non valide
    if(i * 8 * PAGE_SIZE > mem_size){
      bit_value = 0xFF;
    }

    mem_bitmap[i] = bit_value ;
  }
}

/* First Fit */
void *alloc_pages(int pages){
  int i, j;
  
  unsigned char byte;

  int pages_found; //numero di pagine trovate
  int fst_bit;     //prima pagina trovata
  int fst_index;   //indice nella bitmap 
  int lst_bit;     //ultima pagina trovata
  int lst_index;   //indice nella bitmap

  unsigned int mem_location;

  i = 0;
  pages_found = 0;

  fst_bit=0;
  fst_index=0;
  lst_bit=0;  //ultima pagina trovata
  lst_index=0;

  mem_location = 0x00;

  //trova un blocco contiguo di n pagine
  do{
      byte = mem_bitmap[lst_index];

      for(lst_bit = 0; lst_bit < 8; lst_bit++){

        /* se il bit=1 la pagina è occupata
           e resetta tutto al fine di trovare
           delle pagine contigue*/
        if(byte & 0x80){
          pages_found=0;

          fst_bit = (lst_bit + 1) % 8;
          fst_index = lst_index + (fst_bit == 0)?1 : 0;
        } else {
          pages_found++;
          if(pages_found >= pages){
            break;
          }
        }
	
        byte = byte << 1;
      }
      lst_index++;
  } while(pages_found < pages && lst_index < MEM_BITMAP_SIZE);

  lst_index--;

  if(pages_found >= pages){

    //Calcola il puntatore da restituire
    mem_location = START_EXT_MEM + fst_index * 8 * PAGE_SIZE;
    mem_location += PAGE_SIZE * fst_bit;

    //Aggiorna la bitmap
    byte = 0x80 >> fst_bit;        
    while(pages > 0){
      while(byte != 0 && pages > 0){
	mem_bitmap[fst_index] = mem_bitmap[fst_index] | byte;
	byte = byte >> 1;
	pages--;
      }

      byte = 0x80;
      fst_index++;
    }
  }
 
  return (void *)mem_location;
}

/* Alloca in memoria 'bytes' bytes */
void *kmalloc(int bytes){
  int pages = bytes/PAGE_SIZE;
  char *mem;
  int i;

  if(bytes % PAGE_SIZE > 0){
    pages++;
  }

  mem = alloc_pages(pages);
  if(mem != 0x00){
    for(i = 0; i < bytes; i++){
      mem[i] = 0x00;
    }
  }
  return (void *)mem;
}
