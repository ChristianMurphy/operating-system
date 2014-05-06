#pragma once
#include "types.h"

/**
 * Christian Murphy
 */

typedef
    struct process {
    u16 _process_id;
    u32 _virtual_address_space; // Virtual Adddress Size
    u32 _code_size;
    u32 _data_size;
    u32 _code_address;
    u32 _data_address;
    u32 _code_time;
    u32 _data_time;
    u64 _time;
    u64 _blocked_timer;
    u32 _priority;
    struct process *_next;
    u16 _page_table_index;  // Page Table Index
    u16 _swap_block_table[1024];    // Swap Block Table
} process;

typedef struct {
    process *_head;
} blocked_list;

typedef struct {
    process *head;
    process *tail;
} ready_queue;

void blocked_enq( process * p, u64 time );
process *blocked_deq(  );
void ready_enq( process * p, s32 priority_delta );
process *ready_deq( u8 priority );
u64 time_get(  );
void time_adv( u32 delta );
