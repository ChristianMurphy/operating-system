#pragma once
#include "types.h"
#include "proc.h"

/**
 * Christian Murphy
 */

typedef
    struct {
    u64 _used:1;        //page is being used
    u64 _dirty:1;       //page has been edited
    u64 _pinned:1;      //page cannot be swapped
     u64:13;
    u64 _l1i:10;        //level 1 cache
     u64:6;
    u64 _l2i:10;        //level 2 cache
     u64:6;
    u64 _proc:16;       //proceedure number
} mem_manage;

void read_page( page * x, u16 y );
void write_page( page * x, u16 y );
void build_mem_avail(  );
u16 page_alloc(  );
void page_free( u16 x );
int vas_alloc( u16 v[], u32 size );
void vas_free( u16 v[], u32 size );
