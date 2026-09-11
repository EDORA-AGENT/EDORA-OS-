#ifndef EDORA_ATA_H
#define EDORA_ATA_H

bool ata_init();
bool ata_ready();
bool ata_read_sector(unsigned int lba, unsigned char* buffer);
void ata_status();

#endif
