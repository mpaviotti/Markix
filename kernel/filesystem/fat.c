#include <string.h>
#include <fat.h>
#include <type.h>

word fat[FAT_SIZE];
boot_sector boot;
fat_entry root_dir;

/* Legge un cluster */
void read_cluster(int cluster, byte *buffer){
  int start = ((cluster-1) * CLUSTER_SIZE)+1;
  int end = start+CLUSTER_SIZE;
  int i;

  for(i=start; i < end; i++){ 
    ata_read(i, buffer+(i-start)*SECTOR_SIZE);
  }
  return;
}

/* Scrive un cluster */
void write_cluster(int cluster, byte *buffer){
  int start = ((cluster-1) * CLUSTER_SIZE)+1;
  int end = start+CLUSTER_SIZE;
  int i;

  for(i = start; i < end; i++){
    ata_write(i, buffer+(i-start)*SECTOR_SIZE);
  }
  return;
}

/* Aggiorna la FAT sul disco */
void fat_flush(){
  int i;
  int sect_to_cpy = (FAT_SIZE * sizeof(word))/SECTOR_SIZE+1;

  for(i = 0; i < sect_to_cpy; i++){
    ata_write(i+2, ((char *)fat)+(i * SECTOR_SIZE));
  }
}

/* Controlla che ci sia un filesystem FAT12 */
int check_fat(){
  byte buffer[SECTOR_SIZE];
  byte cluster[CLUSTER_DIM];
  int i;
  fat_entry *entry = cluster;

  ata_read(1, buffer);
  memcpy(&boot, buffer, sizeof(boot_sector));
  
  /* Controllo alcuni campi del BootSector */
  if(!(boot.num_sect) && !(boot.num_sect2)){
    return -1;
  }

  /* Filesystem già presente, recupero i dati che mi servono:
    - FAT
    - Cluster della Root
  */
  for(i = 0; i < sizeof(fat)/SECTOR_SIZE; i++){
    ata_read(i+2, buffer);
    memcpy(((char *)fat)+i*SECTOR_SIZE, buffer, SECTOR_SIZE);
  }

  memset(cluster, 0, sizeof(cluster));
  read_cluster(ROOT_DIR_CLUSTER, cluster);
  memcpy(&root_dir, cluster, sizeof(fat_entry));

  return 0;
}

/* Se non è presente un bootsector valido
   ne inizializza uno e lo scrive nel disco 
   (Formatta il disco)*/
void init_fat(){
  int i;
  int sect_to_cpy;
  char buffer[CLUSTER_DIM];   

  memset(buffer, 0, sizeof(buffer));

  boot.sect_size = SECTOR_SIZE;  //SECTOR_SIZE Byte per Settore
  boot.clust_size = CLUSTER_SIZE;   //4 Settori per Cluster
  boot.fats = 1;         //Numero di tabelle FAT
  boot.dir_entries = 1;  //Numero di root directory 1
  boot.num_sect = TOT_SECTORS; //Numero di settori in totale
  boot.media = 0xF8;
  boot.sect_fat = TOT_SECTORS; //Numero di settori per tabella FAT
  boot.sect_track = 17;  //Numero di settori per Traccia
  boot.heads = 6;        //Numero di testine
  boot.hidden_sect = 0; 
  boot.num_sect2 = 0;
  
  /* Extended */
  boot.drive_num = 0x80;
  boot.signature = 0x28;
  
  //Crea la FAT
  fat[0] = CLUST_RESERVED;
  fat[1] = CLUST_RESERVED;

  for(i = 2; i < FAT_SIZE; i++){
    fat[i] = CLUST_FREE;
  }
  
  memcpy(buffer, &boot, sizeof(boot_sector));

  ata_write(1, buffer);

  memset(buffer, 0, CLUSTER_DIM);

  //Crea la root directory
  strcpy(root_dir.name, "/");
  strcpy(root_dir.ext, "");
  root_dir.attr = FILE_DIR;
  root_dir.start= ROOT_DIR_CLUSTER+1;
  root_dir.size = 0;

  memcpy(buffer, &root_dir, sizeof(fat_entry));
  write_cluster(ROOT_DIR_CLUSTER, buffer);

  fat[ROOT_DIR_CLUSTER] = CLUST_RESERVED;
  fat[root_dir.start] = CLUST_LAST;

  memset(buffer, '\0', CLUSTER_DIM);
  write_cluster(root_dir.start, buffer);

  fat_flush();

}

/* Trova un cluster libero */
int find_free_cluster(){
  int i = -1;
  for(i = ROOT_DIR_CLUSTER+1; i < CLUST_LAST_USABLE; i++){
    if(fat[i] == CLUST_FREE){
      return i;
    }
  }
  return -1;
}

int get_file(char *filename, fat_entry* entry){
  byte buffer[CLUSTER_DIM];
  fat_entry* file;
  int i;
  char res[50];

  read_cluster(root_dir.start, buffer);
  file = (fat_entry *)buffer;

  for(i = 0; i < CLUSTER_DIM/sizeof(fat_entry); i++){
    if((file+i)->name[0] == '\0'){
      continue;
    } else {
      res[0]='\0';
      strcat((file+i)->name, ".\0", res);
      strcat(res, (file+i)->ext, res);

      if (strcmp(res, filename) == 0){
	memcpy(entry, file+i, sizeof(fat_entry));      
	return 0;
      }
    }
  }
  return -1;
}

fat_entry* get_new_fat_entry(char* buffer){
  int i;
  fat_entry *entry = buffer;
  for(i = 0; i < CLUSTER_DIM/sizeof(fat_entry);i++){
    if((entry+i)->name[0] == '\0'){
      return entry+i;
    }
  }
  return NULL ;
}

/* Crea un nuovo file */
int create_file(char *file){
  char filename[100];
  int start_sect;
  int splitted;
  fat_entry e;
  fat_entry* entry;
  char buffer[CLUSTER_DIM];
  char file_init[CLUSTER_DIM];
  file_init[0] = EOF;
  strcpy(filename, file);

  if(get_file(filename, &e) >= 0){
    return -1;
  }

  read_cluster(root_dir.start, buffer);
  entry = get_new_fat_entry(buffer);
  if(entry == NULL){
    puts("No FAT entry available\n");
    return -1;
  }

  splitted = split(filename, '.');
  filename[splitted] = '\0';

  strcpy(entry->name, filename);
  strcpy(entry->ext, filename + splitted + 1);

  entry->start = find_free_cluster();
  entry->size  = 0x0;

  fat[entry->start] = CLUST_LAST;
  write_cluster(entry->start, file_init);
  write_cluster(root_dir.start, buffer);
  fat_flush();
  return 0;
}

void read_data(int cluster, char* buf, int buf_size){
  char* temp = buf;
  char* buffer[CLUSTER_DIM];
  int i;
  read_cluster(cluster, buffer);
  memcpy(temp, buffer, buf_size);
  
  buf_size -= CLUSTER_DIM;
  for(i = 0; i < CLUSTER_DIM; i++){
    if(temp[i] == EOF){
      return;
    }
  }
  if(buf_size > 0 && cluster != CLUST_LAST){
    read_data(fat[cluster], temp + CLUSTER_DIM, buf_size);
  }
}

/* Legge dal file specificato */
int read_file(char *name, char *buf, int buf_size){
  fat_entry entry;

  char n[100];
  strcpy(n, name);
  if(get_file(n, &entry) < 0){
    puts("Entry not found.\n");
    return -1;
  }

  read_data(entry.start, buf, buf_size);

  return 0;
}

/** 
 * Inserisce il buffer a partire da un cluster
 * e dall'offset
*/
void insert_data(int cluster, int offset, char* buffer, int buffer_size){
  int free_mem = CLUSTER_DIM - offset;
  char buf[CLUSTER_DIM];
  int mem_to_cpy = min(free_mem, buffer_size);

  buf[CLUSTER_DIM-1]='\0';
  read_cluster(cluster, buf);
  memcpy(buf+offset, buffer, mem_to_cpy);
 
  /* Base, buffer end.*/
  if(buffer_size-mem_to_cpy <= 0){
    *(buf+offset+mem_to_cpy) = EOF;
    fat_flush();
    write_cluster(cluster, buf);
  } else { /* Recursive case */
    write_cluster(cluster, buf);
    fat[cluster] = find_free_cluster();
    insert_data(fat[cluster], 0, (buffer + mem_to_cpy), 
		buffer_size-mem_to_cpy);
  }

  return;
}

/* Scrive in coda al file specificato il buffer */
void write_file(char *name, char *buf, int buf_size){
  fat_entry entry;
  char ch;
  int i;
  int cluster;
  char buffer[CLUSTER_DIM];


  if(get_file(name, &entry) < 0){
    create_file(name);
    if(get_file(name, &entry) < 0){
      puts("unknown error\n");
      return ;
    }
  }

  i=0;
  cluster = entry.start;
  while(1){
    read_cluster(cluster, buffer);
    do{
      ch = buffer[i];
      i++;
    } while(ch != EOF && i < CLUSTER_DIM);

    if(ch == EOF || fat[cluster] == CLUST_LAST){
      i--;
      break;
    }
    cluster = fat[cluster];    
  }
  
  insert_data(cluster, i, buf, buf_size);
  
}

/* Riempie il buffer passato con le fat_entry 
che rappresentano i file */
void list_files(fat_entry *entry_list){
  read_cluster(root_dir.start, (void *)entry_list);
}

