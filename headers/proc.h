# pragma once

#    include "types.h"

typedef struct process *proc;

struct process {
	u16 _process_identity;

	u32 _vas;
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

	u16 _pti;
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
int initialize_process( u8 current_process, u32 csize, u32 dsize, u64 t );
u8 empty_queues(  );

u32 new_code_address( u32 address, u32 limit );
u64 new_code_time(  );
u32 new_data_address( u32 address, u32 base, u32 limit );
u64 new_data_time(  );
