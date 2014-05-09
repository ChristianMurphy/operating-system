#include	<stdio.h>
#include	"headers/types.h"

u32 least_significant_bit8( u8 x )
{
	u32 pos = 0;

	if ( !( ~x & 15 ) )
	{
		pos += 4;
		x >>= 4;
	}
	if ( !( ~x & 3 ) )
	{
		pos += 2;
		x >>= 2;
	}
	if ( !( ~x & 1 ) )
	{
		pos += 1;
		x >>= 1;
	}

/*
	u32	index;

	for (index = 4; index > 0; index >>= 1) {
		if (!(~x & ((1 << index) - 1))) {
			pos  += index;
			x	>>= index;
		}
	}
*/

	return pos;
}

u32 least_significant_bit16( u16 x )
{
	u32 pos = 0;

	if ( !( ~x & 255 ) )
	{
		pos += 8;
		x >>= 8;
	}
	if ( !( ~x & 15 ) )
	{
		pos += 4;
		x >>= 4;
	}
	if ( !( ~x & 3 ) )
	{
		pos += 2;
		x >>= 2;
	}
	if ( !( ~x & 1 ) )
	{
		pos += 1;
		x >>= 1;
	}

/*
	u32	index;

	for (index = 5; index > 0; index >>= 1) {
		if (!(~x & ((1 << index) - 1))) {
			pos  += index;
			x	>>= index;
		}
	}
*/

	return pos;
}

u32 least_significant_bit32( u32 x )
{
	u32 pos = 0;

	if ( !( ~x & 0xFFFF ) )
	{
		pos += 16;
		x >>= 16;
	}
	if ( !( ~x & 0x00FF ) )
	{
		pos += 8;
		x >>= 8;
	}
	if ( !( ~x & 0x000F ) )
	{
		pos += 4;
		x >>= 4;
	}
	if ( !( ~x & 0x0003 ) )
	{
		pos += 2;
		x >>= 2;
	}
	if ( !( ~x & 0x0001 ) )
	{
		pos += 1;
		x >>= 1;
	}

/*
	u32	index;

	for (index = 6; index > 0; index >>= 1) {
		if (!(~x & ((1 << index) - 1))) {
			pos  += index;
			x	>>= index;
		}
	}
*/

	return pos;
}

u32 least_significant_bit64( u64 x )
{
	u32 pos = 0;

	if ( !( ~x & 0xFFFFFFFF ) )
	{
		pos += 32;
		x >>= 32;
	}
	if ( !( ~x & 0x0000FFFF ) )
	{
		pos += 16;
		x >>= 16;
	}
	if ( !( ~x & 0x000000FF ) )
	{
		pos += 8;
		x >>= 8;
	}
	if ( !( ~x & 0x0000000F ) )
	{
		pos += 4;
		x >>= 4;
	}
	if ( !( ~x & 0x00000003 ) )
	{
		pos += 2;
		x >>= 2;
	}
	if ( !( ~x & 0x00000001 ) )
	{
		pos += 1;
		x >>= 1;
	}

/*
	u32	index;

	for (index = 7; index > 0; index >>= 1) {
		if (!(~x & ((1l << index) - 1))) {
			pos  += index;
			x	>>= index;
		}
	}
*/

	return pos;
}

#ifdef	_UTL_TEST_

int main(  )
{
	int index;
	int x;
	int page_number;
	int z;

	for ( index = 0; index < 256; ++index )
	{
		x = least_significant_bit8( index );
		printf( "least_significant_bit8(index) = %02x\n", x );
	}

}

#endif
