#include <stdio.h>
#include "headers/types.h"
#include "headers/util.h"

#define	SWAP_SIZE	 ((1 << 6))
#define	SWAP_SIZE_MASK (SWAP_SIZE - 1)

static u64 avail[SWAP_SIZE] = { 1, 0 };

static u32 offset = 0;
static u32 count = SWAP_SIZE << 6;

static u32 read_latency = 8 << 20;
static u32 write_latency = 8 << 20;
static u64 disk_time = 0;

int swap_allocation( u16 virtual_space[], u32 size )
{
	if ( count < size )
	{
		return 0;
	}

    u32 t;
	for ( u32 index = 0; index < size; ++index )
	{
		if ( ~( avail[offset] ) )
		{
			t = least_significant_bit64( avail[offset] );
			avail[offset] |= 1ul << t;
			virtual_space[index] = ( offset << 6 ) | t;
		}
        else
        {
			offset = ( offset + 1 ) & SWAP_SIZE_MASK;
        }
	}
	count -= size;
	return 1;
}

void swap_free( u16 virtual_space[], u32 size )
{
	for ( u32 index = 0; index < size; ++index )
    {
		avail[virtual_space[index] >> 6] &=
		    ~( 1ul << ( virtual_space[index] & 63 ) );
    }
	count += size;
}

u64 disk_read( u32 block, u16 address )
{
	printf( "Reading block %d from disk\n", block );

	u32 delta = rand(  );

	if ( time_get(  ) > disk_time )
	{
		disk_time = time_get(  );
	}

	if ( delta & 1 )
	{
		disk_time += read_latency + ( delta & 0x3FFFFF );
	}

	else
	{
		disk_time += read_latency - ( delta & 0x1FFFFF );
	}

	if ( block < SWAP_SIZE )
	{

		write_page( address );
	}

	return disk_time;
}

u64 disk_write( u32 block, u16 address )
{
	u32 delta = rand(  );

	if ( time_get(  ) > disk_time )
    {
		disk_time = time_get(  );
    }

	if ( delta & 1 )
	{
		disk_time += write_latency + ( delta & 0x3FFFFF );
	}
	else
	{
		disk_time += write_latency - ( delta & 0x1FFFFF );
	}

	if ( block < SWAP_SIZE )
	{
		read_page( address );
	}

	return disk_time;
}
