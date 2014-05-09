#ifndef	_MEM_MAN__H_
#    define	_MEM_MAN__H_

#    include "types.h"
#    include "proc.h"

typedef struct {
	u64 _used:1;		// Page is being used
	u64 _dirty:1;		// Data has been changed
	u64 _pinned:1;		// Can not be swapped out
	 u64:13;		// Padding
	u64 _level_one_i:10;		// Level 1 addressess
	 u64:6;			// Padding
	u64 _level_twoi:10;		// Level 2 addressess
	 u64:6;			// Padding
	u64 _proc:16;		// Process id?????!?
} memory_manage_structure;

void read_page( u16 page_number );
void write_page( u16 page_number );
page get_page( u32 address );

void set_used_bit( u16 page_number );
void set_pinned_bit( u16 page_number );
void unset_pinned_bit( u16 page_number );

void address_set( u16 page_number, int index, u16 address );
u16 address_get( u16 page_number, int index );

u16 page_allocation(  );
void page_free( u16 x );
void page_free_all(  );

int vas_alloc( u16 v[], u32 size );
void vas_free( u16 v[], u32 size );

u32 virtual_to_physical( u32 address, proc current_process );
void page_fault( u32 address, proc current_process );

u16 walk_page_ring(  );

#endif
