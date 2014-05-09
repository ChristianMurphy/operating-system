#include <stdio.h>
#include "headers/types.h"
#include "headers/proc.h"
#include "headers/mem_man.h"
#include "headers/util.h"

#define	PAGE_COUNT 65536
#define	PAGE_MASK	(PAGE_COUNT - 1)
#define	virtual_address_space_vector_SIZE (1 << 6)
#define	virtual_address_space_vector_SIZE_MASK (virtual_address_space_vector_SIZE - 1)

static page page_memory[PAGE_COUNT];

static u16 page_availible = 1;

static memory_manage_structure memory_manager[PAGE_COUNT] = { 0 };

static u16 memory_offset = 1;

static u64 virtual_address_space_vector[virtual_address_space_vector_SIZE] =
    { 0 };

static u32 virtual_address_space_offset = 0;
static u32 virtual_address_space_count = 4096;

void read_page( u16 page_number )
{
	printf( "page %d read\n", page_number );
}

void write_page( u16 page_number )
{
	printf( "page %d write\n", page_number );
}

page get_page( u32 address )
{
	return page_memory[address];
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
	page_memory[page_number]._u32[index] = address;
	printf( "Page %d index %d is storing address\n", page_number, index,
		address );
}

u16 address_get( u16 page_number, int index )
{
	u32 a = page_memory[page_number]._u32[index];
	u16 b = a & 0xFFFF;
	return b;
}

u16 page_allocation(  )
{
	u16 t = page_availible;
	if ( page_availible )
	{
		page_availible = page_memory[page_availible]._u16[0];
	}
	int index;
	for ( index = 0; index < 512; index++ )
	{
		page_memory[t]._u64[index] = 0;
	}
	return t;
}

void page_free( u16 page_index )
{
	if ( memory_manager[page_index]._dirty )
	{
		printf( "Page %d is dirty\n", page_index );
		write_page( page_index );
	}

	page_memory[page_index]._u16[0] = page_availible;
	page_availible = page_index;
}

void page_free_all(  )
{
	u16 index;
	for ( index = 1; index < PAGE_COUNT - 1; index++ )
	{
		page_memory[index]._u16[0] = index + 1;
	}
}

u32 virtual_to_physical( u32 address, proc current_process )
{
	u32 level_one_index = address >> 22;
	u32 level_two_index = ( ( address >> 12 ) & 0x3FF );

	u16 level_one_address = current_process->_page_table_index;
	page level_one = page_memory[level_one_address];
	u32 level_two_address = level_one._u32[level_one_index];

	if ( !level_two_address )
	{
		return 0;
	}

	page level_two = page_memory[level_two_address];
	u32 physical_address = level_two._u32[level_two_index];

	if ( !physical_address )
	{
		return 0;
	}
	return physical_address;
}

void page_fault( u32 address, proc current_process )
{
	printf( "process %d faulted on address %d\n",
		current_process->_process_identity, address );

	u16 allocation = page_allocation(  );

	if ( !allocation )
	{
		u16 swap_page = walk_page_ring(  );
		page_free( swap_page );
		allocation = page_allocation(  );

		printf( "swap page\n" );
	}
	printf( "page %d taken\n", allocation );

	u32 level_one_index = address >> 22;
	u32 level_two_index = ( ( address >> 12 ) & 0x3FF );
	u16 level_one_address = current_process->_page_table_index;
	page level_one = page_memory[level_one_address];
	u32 level_two_address = level_one._u32[level_one_index];

	u64 d_time = disk_read( address, allocation );
	address_set( level_two_address, level_two_index, allocation );
	blocked_enqueue( current_process, d_time );
}

int virtual_address_space_allocation( u16 virtual_space[], u32 size )
{
	int result = 0;

	if ( size <= virtual_address_space_count )
	{
		int index;
		for ( index = 0; index < size; index++ )
		{
			while ( virtual_address_space_vector
				[virtual_address_space_offset] ==
				0xFFFFFFFFFFFFFFFF )
			{
				virtual_address_space_offset++;
				if ( virtual_address_space_offset > 63 )
				{
					virtual_address_space_offset = 0;
				}
			}

			u16 bit_position =
			    ( u16 )
			    least_significant_bit64
			    ( virtual_address_space_vector
			      [virtual_address_space_offset] );

			u16 chunk_addressess =
			    ( virtual_address_space_offset << 8 ) |
			    ( bit_position );

			virtual_space[index] = chunk_addressess;

			u64 flipped_bit = 1;
			flipped_bit = flipped_bit << bit_position;

			virtual_address_space_vector
			    [virtual_address_space_offset] =
			    virtual_address_space_vector
			    [virtual_address_space_offset] | ( flipped_bit );

			virtual_address_space_count--;
		}

		result = 1;
	}

	return result;
}

void vas_free( u16 virtual_space[], u32 size )
{
	int index;
	for ( index = 0; index < size; index++ )
	{

		u16 chunk_addressess = virtual_space[index];
		u16 bit_position = chunk_addressess & 0x00FF;
		u16 virtual_address_space_offset_temparary =
		    chunk_addressess >> 8;

		u64 flipped_bit = 1;
		flipped_bit = flipped_bit << bit_position;
		virtual_address_space_vector
		    [virtual_address_space_offset_temparary] =
		    virtual_address_space_vector
		    [virtual_address_space_offset_temparary] & ~( flipped_bit );

		virtual_address_space_count++;
	}
}

u16 walk_page_ring(  )
{
	u16 temparary = 0;
	int index;
	for ( index = 0; index < PAGE_COUNT; index++ )
	{
		if ( !( memory_manager[index]._used )
		     && !( memory_manager[index]._pinned ) )
		{
			temparary = index;
			break;
		}
		memory_manager[index]._used = 0;
	}
	return temparary;
}
