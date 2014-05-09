#include <stdio.h>
#include "headers/types.h"
#include "headers/proc.h"
#include "headers/mem_man.h"
#include "headers/util.h"

#define	PAGE_COUNT 65536
#define	PAGE_MASK	(PAGE_COUNT - 1)
#define	VAS_VEC_SIZE (1 << 6)
#define	VAS_VEC_SIZE_MASK (VAS_VEC_SIZE - 1)

// Array of pages
static page mem[PAGE_COUNT];

// first available page
static u16 page_avail = 1;

// Status control of memory
static memory_manage_structure memory_manager[PAGE_COUNT] = { 0 };

static u16 mem_offset = 1;

// Bitmap. 64 levels of 64 bits. each bit is a chunk of 4mb that represents a page table.
static u64 vas_vec[VAS_VEC_SIZE] = { 0 };

static u32 virtual_address_space_offset = 0;
static u32 vas_count = 4096;

void read_page( u16 page_number )
{
	printf( "Reading the contents of page %d\n", page_number );
}

void write_page( u16 page_number )
{
	printf( "Writing into page %d\n", page_number );
}

page get_page( u32 address )
{
	return mem[address];
}

void set_used( u16 page_number )
{
	memory_manager[page_number]._used = 1;
}

void set_pinned( u16 page_number )
{
	memory_manager[page_number]._pinned = 1;
}

void clear_pinned( u16 page_number )
{
	memory_manager[page_number]._pinned = 0;
}

void insert_addressess( u16 page_number, int index, u16 address )
{
	mem[page_number]._u32[index] = address;
	printf( "Placing addressess %d in index %d of page %d\n", address, index, page_number );
}

u16 get_addressess( u16 page_number, int index )
{
	u32 a = mem[page_number]._u32[index];
	u16 b = a & 0xFFFF;
	return b;
}

// Creates page at page_avail, if page_avail is not 0.
// Page_avail is set to the allocated pages _u16.
// Return the addressess of the newly allocated page.
u16 page_alloc(  )
{
	u16 t = page_avail;
	if ( page_avail )
	{
		page_avail = mem[page_avail]._u16[0];
	}
	int index;
	for ( index = 0; index < 512; index++ )
	{
		mem[t]._u64[index] = 0;
	}
	return t;
}

// Frees page x.
// Page x's _u16 is set to the current page_avail.
// page_avail is then set to the addressess of the new page.
void page_free( u16 x )
{
	if ( memory_manager[x]._dirty )
	{
		printf( "Page %d is dirty and will be written to disk\n", x );
	}

	mem[x]._u16[0] = page_avail;
	page_avail = x;
}

void emancipation_proclamation(  )
{
	u16 index;
	for ( index = 1; index < PAGE_COUNT - 1; index++ )
	{
		mem[index]._u16[0] = index + 1;
	}
}

//
u32 virt_to_phys( u32 address, proc p )
{
	u32 l1_index = address >> 22;
	u32 l2_index = ( ( address >> 12 ) & 0x3FF );

	u16 l1_address = p->_pti;
	page l1 = mem[l1_address];
	u32 l2_address = l1._u32[l1_index];

	if ( !l2_address )
	{
		return 0;
	}

	page l2 = mem[l2_address];
	u32 phys_address = l2._u32[l2_index];

	if ( !phys_address )
	{
		return 0;
	}
	return phys_address;
}

//
void page_fault( u32 address, proc p )
{
	printf( "Process %d faulted on addressess %d\n", p->_process_identity, address );

	u16 alloc = page_alloc(  );

	if ( !alloc )
	{
		u16 swap_page = walk_page_ring(  );
		page_free( swap_page );
		alloc = page_alloc(  );

		printf( "must swap\n" );
	}
	printf( "Page %d found\n", alloc );

	u32 l1_index = address >> 22;
	u32 l2_index = ( ( address >> 12 ) & 0x3FF );
	u16 l1_address = p->_pti;
	page l1 = mem[l1_address];
	u32 l2_address = l1._u32[l1_index];

	u64 d_time = disk_read( address, alloc );
	insert_addressess( l2_address, l2_index, alloc );
	blocked_enq( p, d_time );
}

// Array is the sbt from proc(index believe), size is the number of chunks a process wants.
int vas_alloc( u16 v[], u32 size )
{
	int result = 0;

	if ( size <= vas_count )
	{
		int index;
		for ( index = 0; index < size; index++ )
		{
			while ( vas_vec[virtual_address_space_offset] == 0xFFFFFFFFFFFFFFFF )
			{
				virtual_address_space_offset++;
				if ( virtual_address_space_offset > 63 )
				{
					virtual_address_space_offset = 0;
				}
			}

			// Find a free chunk and record its position
			u16 bit_pos = ( u16 ) least_significant_bit64( vas_vec[virtual_address_space_offset] );
			// Create an addressess of the chunk level index and position
			u16 chunk_addressess = ( virtual_address_space_offset << 8 ) | ( bit_pos );
			// Store addressess in the passed in array
			v[index] = chunk_addressess;

			u64 flipped_bit = 1;
			flipped_bit = flipped_bit << bit_pos;

			// Flip the bit at virtual_address_space_offset and bit_post to indicate allocated memory
			vas_vec[virtual_address_space_offset] =
			    vas_vec[virtual_address_space_offset] | ( flipped_bit );

			// If the row is completely allocated
			vas_count--;
		}

		result = 1;
	}
	// result: 0 is failure, 1 is success
	return result;
}

// Array is the sbt from proc(index believe), size is the number of chunks a process wants.
void vas_free( u16 v[], u32 size )
{
	int index;
	for ( index = 0; index < size; index++ )
	{
		// Get an addressess of a chunk to be free
		u16 chunk_addressess = v[index];
		u16 bit_pos = chunk_addressess & 0x00FF;
		u16 virtual_address_space_offset_temparary = chunk_addressess >> 8;

		u64 flipped_bit = 1;
		flipped_bit = flipped_bit << bit_pos;
		vas_vec[virtual_address_space_offset_temparary] =
		    vas_vec[virtual_address_space_offset_temparary] & ~( flipped_bit );

		vas_count++;
	}
}

// Iterate through memory and do stuff:
// Set used to 0 for each page.
u16 walk_page_ring(  )
{
	u16 temparary = 0;
	int index;
	for ( index = 0; index < PAGE_COUNT; index++ )
	{
		if ( !( memory_manager[index]._used ) && !( memory_manager[index]._pinned ) )
		{
			temparary = index;
			break;
		}
		memory_manager[index]._used = 0;
	}
	return temparary;
}
