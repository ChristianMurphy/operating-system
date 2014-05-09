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

//allocates the swap space
int swap_allocation( u16 v[], u32 size )
{
	u32 index;
	u32 t;

	if ( count < size )
	{
		return 0;
	}

	for ( index = 0; index < size; ++index )
	{
		if ( ~( avail[offset] ) )
		{
			t = least_significant_bit64( avail[offset] );
			avail[offset] |= 1ul << t;
			v[index] = ( offset << 6 ) | t;
		} else
			offset = ( offset + 1 ) & SWAP_SIZE_MASK;
	}
	count -= size;
	return 1;
}

//frees swap space
void swap_free( u16 v[], u32 size )
{
	u32 index;

	for ( index = 0; index < size; ++index )
		avail[v[index] >> 6] &= ~( 1ul << ( v[index] & 63 ) );
	count += size;
}

//reads from disk to memory
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
		//Create some garbage page that represents data from disk
		write_page( address );
	}

	return disk_time;
}

//reads from memory writes to disk
u64 disk_write( u32 block, u16 address )
{
	u32 delta = rand(  );

	if ( time_get(  ) > disk_time )
		disk_time = time_get(  );

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
