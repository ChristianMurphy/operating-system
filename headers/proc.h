#ifndef _PROC__H_
#    define _PROC__H_

#    include "types.h"

typedef struct process *proc;

struct process {
	u16 _process_identity;

	u32 _vas;		// Virtual Adddress Size
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

	u16 _pti;		// Page Table Index
	u16 _sbt[1024];		// Swap Block Table
} process;

typedef struct blocked {
	proc _head;
} blocked;

typedef struct ready {
	proc _head;
	proc _tail;
} ready;

void blocked_enq( proc p, u64 estimated_time );
void blocked_deq(  );

void ready_enq( proc p );
proc ready_deq( u8 priority );

u64 time_get(  );
void time_advance( u64 time_delta );
u16 get_finished(  );

void init_queues(  );
int init_process( u8 p, u32 csize, u32 dsize, u64 t );
u8 empty_queues(  );

u32 new_code_address( u32 address, u32 limit );
u64 new_code_time(  );
u32 new_data_address( u32 address, u32 base, u32 limit );
u64 new_data_time(  );

#endif
