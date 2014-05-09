#pragma once

#define	CASE	break; case

typedef char s8;
typedef unsigned char u8;

typedef short s16;
typedef unsigned short u16;

typedef int s32;
typedef unsigned int u32;

typedef long s64;
typedef unsigned long u64;

typedef union {
    u8 _u8[4096];
    s8 _s8[4096];

    u16 _u16[2048];
    s16 _s16[2048];

    u32 _u32[1024];
    s32 _s32[1024];

    u64 _u64[512];
    s64 _s64[512];
} page;

u64 disk_read( u32 block, u16 address );
u64 disk_write( u32 block, u16 address );

typedef struct process *proc;

struct process {
	u16 _process_identity;

	u32 _virtual_address_space;
	u8 _priority;
	u64 _time;

	int _run_counter;

	u64 _blocked_timer;

	u32 *_code_address;
	u64 _code_time;
	u32 _code_size;

	u32 *_data_address;
	u64 _data_time;
	u32 _data_size;

	proc _next;

	u16 _page_table_index;
	u16 _sbt[1024];
} process;

typedef struct blocked {
	proc _head;
} blocked;

typedef struct ready {
	proc _head;
	proc _tail;
} ready;

void blocked_enqueue( proc current_process, u64 estimated_time );
void blocked_dequeue(  );

void ready_enqueue( proc current_process );
proc ready_dequeue( u8 priority );

u64 time_get(  );
void time_advance( u64 time_delta );
u16 get_finished(  );

void initialize_queues(  );
int initialize_process( u8 current_process, u32 code_size, u32 data_size,
			u64 t );
u8 remaining_processes(  );

u32 new_code_address( u32 address, u32 limit );
u64 new_code_time(  );
u32 new_data_address( u32 address, u32 base, u32 limit );
u64 new_data_time(  );


u64 disk_read( u32 block, u16 address );
u64 disk_write( u32 block, u16 address );

typedef enum {
	Code,
	Data,
	File,
	Network,
	Keyboard,
	Timer
} dev_type;

u32 least_significant_bit8( u8 x );
u32 least_significant_bit16( u16 x );
u32 least_significant_bit32( u32 x );
u32 least_significant_bit64( u64 x );

typedef struct {
	u64 _used:1;
	u64 _dirty:1;
	u64 _pinned:1;
	 u64:13;
	u64 _level_one_i:10;
	 u64:6;
	u64 _level_twoi:10;
	 u64:6;
	u64 _proc:16;
} memory_manage_structure;

void read_page( u16 page_number );
void write_page( u16 page_number );
page get_page( u32 address );

void set_used_bit( u16 page_number );
void set_pinned_bit( u16 page_number );
void unset_pinned_bit( u16 page_number );

void address_set( u16 page_number, int index, u16 address );
u16 address_get( u16 page_number, int index );

u16 page_allocation(  );
void page_free( u16 x );
void page_free_all(  );

int virtual_address_space_allocation( u16 virtual_space[], u32 size );
void vas_free( u16 virtual_space[], u32 size );

u32 virtual_to_physical( u32 address, proc current_process );
void page_fault( u32 address, proc current_process );

u16 walk_page_ring(  );
