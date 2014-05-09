#include <stdio.h>
#include "headers/types.h"
#include "headers/proc.h"
#include "headers/mem_man.h"
#include "headers/util.h"

#define	PAGE_COUNT 65536
#define	PAGE_MASK	(PAGE_COUNT - 1)
#define	VAS_VEC_SIZE (1 << 6)
#define	VAS_VEC_SIZE_MASK (VAS_VEC_SIZE - 1)

// all of the pages
static page mem[PAGE_COUNT];

// first available page
static u16 page_availible = 1;

// meta data for the memory
static memory_manage_structure memory_manager[PAGE_COUNT] = { 0 };

static u16 mem_offset = 1;

// this is a 2^6 by 2^6 memory space that represents a page table
static u64 vas_vec[VAS_VEC_SIZE] = { 0 };

static u32 virtual_address_space_offset = 0;
static u32 virtual_address_space_count = 4096;

void read_page( u16 page_number )
{
	printf( "Page %d read\n", page_number );
}

void write_page( u16 page_number )
{
	printf( "Page %d write\n", page_number );
}

page get_page( u32 address )
{
	return mem[address];
}

void set_used_bit( u16 page_number )
{
	memory_manager[page_number]._used = 1;
}

void set_pinned_bit( u16 page_number )
{
	memory_manager[page_number]._pinned = 1;
}

void unset_pinned_bit( u16 page_number )
{
	memory_manager[page_number]._pinned = 0;
}

void address_set( u16 page_number, int index, u16 address )
{
	mem[page_number]._u32[index] = address;
	printf( "Page %d index %d is storing address\n", page_number, index, address );
}

u16 address_get( u16 page_number, int index )
{
	u32 a = mem[page_number]._u32[index];
	u16 b = a & 0xFFFF;
	return b;
}

// Creates page at page_availible, if page_availible is not 0.
// page_availible is set to the allocated pages _u16.
// Return the addressess of the newly allocated page.
u16 page_allocation(  )
{
	u16 t = page_availible;
	if ( page_availible )
	{
		page_availible = mem[page_availible]._u16[0];
	}
	int index;
	for ( index = 0; index < 512; index++ )
	{
		mem[t]._u64[index] = 0;
	}
	return t;
}

// Frees page
// Page x's _u16 is set to the current page_availible.
// page_availible is then set to the addressess of the new page.
void page_free( u16 page_index )
{
	if ( memory_manager[page_index]._dirty )
	{
		printf( "Page %d is dirty\n", page_index );
        write_page(page_index);
	}

	mem[page_index]._u16[0] = page_availible;
	page_availible = page_index;
}

void page_free_all(  )
{
	u16 index;
	for ( index = 1; index < PAGE_COUNT - 1; index++ )
	{
		mem[index]._u16[0] = index + 1;
	}
}

//
u32 virtual_to_physical( u32 address, proc current_process )
{
	u32 level_one_index = address >> 22;
	u32 level_two_index = ( ( address >> 12 ) & 0x3FF );

	u16 level_one_address = current_process->_pti;
	page level_one = mem[level_one_address];
	u32 level_two_address = level_one._u32[level_one_index];

	if ( !level_two_address )
	{
		return 0;
	}

	page level_two = mem[level_two_address];
	u32 physical_address = level_two._u32[level_two_index];

	if ( !physical_address )
	{
		return 0;
	}
	return physical_address;
}

//
void page_fault( u32 address, proc current_process )
{
	printf( "Process %d faulted on addressess %d\n", current_process->_process_identity, address );

	u16 allocation = page_allocation(  );

	if ( !allocation )
	{
		u16 swap_page = walk_page_ring(  );
		page_free( swap_page );
		allocation = page_allocation(  );

		printf( "must swap\n" );
	}
	printf( "Page %d found\n", allocation );

	u32 level_one_index = address >> 22;
	u32 level_two_index = ( ( address >> 12 ) & 0x3FF );
	u16 level_one_address = current_process->_pti;
	page level_one = mem[level_one_address];
	u32 level_two_address = level_one._u32[level_one_index];

	u64 d_time = disk_read( address, allocation );
	address_set( level_two_address, level_two_index, allocation );
	blocked_enqueue( current_process, d_time );
}

// Array is the sbt from proc(index believe), size is the number of chunks a process wants.
int vas_alloc( u16 v[], u32 size )
{
	int result = 0;

	if ( size <= virtual_address_space_count )
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
			virtual_address_space_count--;
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

		virtual_address_space_count++;
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
