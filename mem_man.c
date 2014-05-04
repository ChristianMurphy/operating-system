#include    <stdio.h>
#include    "headers/types.h"
#include    "headers/proc.h"
#include    "headers/mem_man.h"
#include    "headers/util.h"

#define PAGE_COUNT          65536
#define PAGE_MASK           (PAGE_COUNT - 1)
#define VAS_VEC_SIZE        (1 << 6)
#define VAS_VEC_SIZE_MASK   (VAS_VEC_SIZE - 1)

/**
 * Christian Murphy
 */

static page mem[PAGE_COUNT];
// point to next availible page
static u16 page_avail = 0;
static mem_manage mem_man[PAGE_COUNT] = { 0 };

static u16 mem_offset = 1;
static u64 vas_vec[VAS_VEC_SIZE] = { 0 };

static u32 vas_offset = 0;
static u32 vas_count = VAS_VEC_SIZE;

void read_page( page * x, u16 y )
{
    u32 i;
    for ( i = 0; i < 512; ++i )
        x->_u64[i] = mem[y]._u64[i];
}

// may need to set dirty bit
void write_page( page * x, u16 y )
{
    u32 i;
    for ( i = 0; i < 512; ++i )
        mem[y]._u64[i] = x->_u64[i];
}

u16 page_alloc(  )
{
    // store current free page to temp, pop next avail page
    u16 t = page_avail;
    if ( page_avail )
        page_avail = mem[page_avail]._u16[0];
    return t;
}

void page_free( u16 x )
{
    mem[x]._u16[0] = page_avail;
    page_avail = x;
}

int vas_alloc( u16 v[], u32 size )
{
    //for all the memory you are asking for
    for ( u32 counter = size; counter > 0; counter-- )
    {
        //find first open position
        u32 position = lsb64( vas_vec[vas_offset] );
        //allocate that position
        vas_vec[vas_offset] = vas_vec[vas_offset] || ( 1 << position );
        //if there is no more room in the block move to next block
        if ( position > 62 )
        {
            vas_offset++;
        }
    }
}

void vas_free( u16 v[], u32 size )
{
    for ( int index = 0; index < size; index++ )
    {
        u16 current_address = v[index];
        //getting row
        u16 bit_position = current_address & 0x00FF;
        //offset starts here
        u16 vas_offset_temporary = current_address >> 0;

        //creating mask to free a position
        u64 flipped_bit = ~( 1 << bit_position );
        //free up the page
        vas_vec[vas_offset_temporary] =
            vas_vec[vas_offset_temporary] & flipped_bit;
        //there is more free space
        vas_count++;
    }
}

u16 walk_page_ring(  )
{
    for ( u16 counter = 0; counter < PAGE_COUNT; counter++ )
    {
        mem_man[counter]._used = 0;
    }
}
