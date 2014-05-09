#include	<stdio.h>
#include	"headers/types.h"

u32 least_significant_bit8( u8 number )
{
	u32 position = 0;

	if ( !( ~number & 15 ) )
	{
		position += 4;
		number >>= 4;
	}
	if ( !( ~number & 3 ) )
	{
		position += 2;
		number >>= 2;
	}
	if ( !( ~number & 1 ) )
	{
		position += 1;
		number >>= 1;
	}

	return position;
}

u32 least_significant_bit16( u16 number )
{
	u32 position = 0;

	if ( !( ~number & 255 ) )
	{
		position += 8;
		number >>= 8;
	}
	if ( !( ~number & 15 ) )
	{
		position += 4;
		number >>= 4;
	}
	if ( !( ~number & 3 ) )
	{
		position += 2;
		number >>= 2;
	}
	if ( !( ~number & 1 ) )
	{
		position += 1;
		number >>= 1;
	}

	return position;
}

u32 least_significant_bit32( u32 number )
{
	u32 position = 0;

	if ( !( ~number & 0xFFFF ) )
	{
		position += 16;
		number >>= 16;
	}
	if ( !( ~number & 0x00FF ) )
	{
		position += 8;
		number >>= 8;
	}
	if ( !( ~number & 0x000F ) )
	{
		position += 4;
		number >>= 4;
	}
	if ( !( ~number & 0x0003 ) )
	{
		position += 2;
		number >>= 2;
	}
	if ( !( ~number & 0x0001 ) )
	{
		position += 1;
		number >>= 1;
	}

	return position;
}

u32 least_significant_bit64( u64 number )
{
	u32 position = 0;

	if ( !( ~number & 0xFFFFFFFF ) )
	{
		position += 32;
		number >>= 32;
	}
	if ( !( ~number & 0x0000FFFF ) )
	{
		position += 16;
		number >>= 16;
	}
	if ( !( ~number & 0x000000FF ) )
	{
		position += 8;
		number >>= 8;
	}
	if ( !( ~number & 0x0000000F ) )
	{
		position += 4;
		number >>= 4;
	}
	if ( !( ~number & 0x00000003 ) )
	{
		position += 2;
		number >>= 2;
	}
	if ( !( ~number & 0x00000001 ) )
	{
		position += 1;
		number >>= 1;
	}

	return position;
}

#ifdef	_UTL_TEST_

int main(  )
{
	int index;
	int number;
	int page_number;
	int z;

	for ( index = 0; index < 256; ++index )
	{
		number = least_significant_bit8( index );
		printf( "least_significant_bit8(index) = %02x\n", number );
	}

}

#endif
