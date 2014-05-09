#ifndef	_DISK_H_
#    define	_DISK_H_

#    include	"types.h"

u64 disk_read( u32 block, u16 address );
u64 disk_write( u32 block, u16 address );
int in_alloc( u16 virtual_space[], u32 size );
void in_free( u16 virtual_space[], u32 size );
int lb_alloc( u16 virtual_space[], u32 size );
void lb_free( u16 virtual_space[], u32 size );
int sb_alloc( u16 virtual_space[], u32 size );
void sb_free( u16 virtual_space[], u32 size );

#endif
