#pragma once
#include "fatfs/diskio.h"
// Returns the size of sector, which is the minimum Read/Write unit of the FAT area
U32 flash_fs_sector_size();

// Returns the total number of sectors.
LBA_t flash_fs_sector_count();

// To sync the temporary state of data with the permanent state of the data
DRESULT flash_fs_flushdata();

// Write an amount of data to flash.
DRESULT flash_fs_updatesects( LBA_t startsector, const BYTE* buf, UINT cnt );

// Read an amount of data from flash.
DRESULT flash_fs_readsects(LBA_t startsector,BYTE* buf,UINT cnt);
// Initialize
DRESULT flash_fs_init();

// Get BLOCKDEV*
BLOCKDEV* flash_fs_getdev();

