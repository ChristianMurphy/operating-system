#pragma once
#include "types.h"

void    readPage                    (page* page, u16 pageNumber);
void    writePage                   (page* page, u16 pageNumber);
void    buildMemoryAvailible        (void);
u16     pageAllocate                (void);
void    pageFree                    (u16 pageNumber);
int     virtualAddressSpaceAllocate (u16 virtualSpace[], u32 size);
void    virtualAddressSpaceFree     (u16 virtualSpace[], u32 size);
u16     virtualSpaceToPhysicalPage  (process* process, u32 address);
int     memoryRead                  (process* process, u32 address);
int     memoryWrite                 (process* process, u32 address);
