#pragma once
#include "types.h"

/**
 * Christian Murphy
 */

typedef
    struct process {
    u16 _pid;
    u32 _virtual_address_space; // Virtual Adddress Size
    dev_type _wait_on;
    u32 _code_side;     // Code Size
    u32 _data_size;     // Data Size
    u32 _file_size;     // File Size
    u32 _code_address;  // Code Address
    u32 _data_address;  // Data Address
    u32 _file_address;  // File Address
    u32 _code_time;     // Code Time
    u32 _data_time;     // Data Time
    u32 _file_time;     // File Time
    u32 _net_time;      // Net Time
    u32 _kdb_time;      // kbd Time
    void ( *_cp ) ( u32 m, u32 t, u32 * l, u32 * d );   // Code Profile
    void ( *_dp ) ( u32 m, u32 t, u32 * l, u32 * d );   // Data Profile
    void ( *_fp ) ( u32 m, u32 t, u32 * l, u32 * d );   // File Profile
    void ( *_np ) ( u32 m, u32 t, u32 * l, u32 * d );   // Net Profile
    void ( *_kp ) ( u32 m, u32 t, u32 * l, u32 * d );   // kbd Profile
    u16 _file_pointer_index;    // File Pointer Index
    u64 _time;
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
