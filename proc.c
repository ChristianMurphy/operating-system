#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "headers/types.h"
#include "headers/mem_man.h"
#include "headers/proc.h"

static blocked _blocked;
static ready _high;
static ready _medium;
static ready _low;

static int counter = 0;
static u64 time = 0;
static u64 time_blocked = 0;
static u16 number_of_processes = 1;
static u16 completed_processes = 0;

void blocked_enqueue( proc current_process, u64 estimated_time )
{
	printf( "process %d is blocked\n", current_process->_process_identity );

	current_process->_blocked_timer = estimated_time;
	if ( _blocked._head == NULL )
	{
		_blocked._head = current_process;
	} else
	{
		current_process->_next = _blocked._head;
		_blocked._head = current_process;
	}
}

void blocked_dequeue(  )
{
	if ( _blocked._head == NULL )
	{
		return;
	}

	proc current_process = _blocked._head;
	proc previous_process = _blocked._head;

	if ( _blocked._head != NULL && _blocked._head->_next == NULL )
	{
		if ( current_process->_blocked_timer <= time_get(  ) )
		{
			printf( "process %d unblocked\n",
				_blocked._head->_process_identity );
			ready_enqueue( _blocked._head );
			_blocked._head = NULL;
		}
	}

	else if ( ( _blocked._head != NULL )
		  && ( _blocked._head->_next != NULL ) )
	{
		do
		{
			if ( current_process->_blocked_timer <= time_get(  ) )
			{
				if ( _blocked._head == current_process )
				{
					_blocked._head = current_process->_next;
					current_process->_next = NULL;
					printf
					    ( "process %d unblocked\n",
					      current_process->
					      _process_identity );
					ready_enqueue( current_process );
					current_process = _blocked._head;
					previous_process = current_process;
				} else
				{
					previous_process->_next =
					    current_process->_next;
					current_process->_next = NULL;
					printf
					    ( "process %d unblocked\n",
					      current_process->
					      _process_identity );
					ready_enqueue( current_process );
					current_process =
					    previous_process->_next;
				}
			}

			else
			{
				if ( current_process == previous_process )
				{
					current_process =
					    current_process->_next;
				} else
				{
					current_process =
					    current_process->_next;
					previous_process =
					    previous_process->_next;
				}
			}
		}
		while ( current_process != NULL );
	}
}

void ready_enqueue( proc current_process )
{
	if ( current_process->_priority )
	{
		if ( current_process->_priority == 1 )
		{
			if ( _high._head == NULL && _high._tail == NULL )
			{
				_high._head = current_process;
				_high._tail = current_process;
			}

			else
			{
				_high._tail->_next = current_process;
				_high._tail = current_process;
			}
			printf
			    ( "process %d is ready [high priority]\n",
			      current_process->_process_identity );
		}

		if ( current_process->_priority == 2 )
		{
			if ( _medium._head == NULL && _medium._tail == NULL )
			{
				_medium._head = current_process;
				_medium._tail = current_process;
			}

			else
			{
				_medium._tail->_next = current_process;
				_medium._tail = current_process;
			}
			printf
			    ( "process %d is ready [medium priority]\n",
			      current_process->_process_identity );
		}

		if ( current_process->_priority == 3 )
		{
			if ( _low._head == NULL && _low._tail == NULL )
			{
				_low._head = current_process;
				_low._tail = current_process;
			}

			else
			{
				_low._tail->_next = current_process;
				_low._tail = current_process;
			}
			printf
			    ( "process %d is ready [low priority]\n",
			      current_process->_process_identity );
		}
	}
}

proc ready_dequeue( u8 priority )
{
	proc current_process;

	if ( priority == 1 )
	{
		if ( _high._head == NULL )
		{
			return NULL;
		} else if ( _high._head == _high._tail && _high._head != NULL )
		{
			current_process = _high._head;
			_high._head = NULL;
			_high._tail = NULL;
		} else
		{
			current_process = _high._head;
			_high._head = current_process->_next;
			current_process->_next = NULL;
		}
		printf( "process %d dequeued from ready [high priority]\n",
			current_process->_process_identity );
	} else if ( priority == 2 )
	{
		if ( _medium._head == NULL )
		{
			return NULL;
		} else if ( _medium._head == _medium._tail
			    && _medium._head != NULL )
		{
			current_process = _medium._head;
			_medium._head = NULL;
			_medium._tail = NULL;
		} else
		{

			current_process = _medium._head;
			_medium._head = current_process->_next;
			current_process->_next = NULL;
		}

		printf( "process %d dequeued from ready [medium priority]\n",
			current_process->_process_identity );
	}

	else if ( priority == 3 )
	{

		if ( _low._head == NULL )
		{
			return NULL;
		} else if ( _low._head == _low._tail && _low._head != NULL )
		{
			current_process = _low._head;
			_low._head = NULL;
			_low._tail = NULL;
		} else
		{
			current_process = _low._head;
			_low._head = current_process->_next;
			current_process->_next = NULL;
		}
		printf( "process %d dequeued from ready [medium priority]\n",
			current_process->_process_identity );
	}
	return current_process;
}

u32 new_code_address( u32 address, u32 limit )
{
	static u32 x[32] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 8, 16
	};

	u32 r = rand(  );
	address = ( r & 64 ) ? address + x[r & 31] : address - x[r & 31];
	return ( address > limit ) ? address = r % limit : address;
}

u64 new_code_time(  )
{
	return 50 + ( rand(  ) & 0xfff );
}

u32 new_data_address( u32 address, u32 base, u32 limit )
{
	static u32 x[32] = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,
		5, 5, 6, 6, 7, 7, 8, 8, 9, 10, 11, 12, 16, 20, 28, 40
	};

	u32 r = rand(  );
	address = ( r & 64 ) ? address + x[r & 31] : address - x[r & 31];
	return ( ( base < address )
		 || ( address > limit ) ) ? address =
	    base + ( r % ( limit - base ) ) : address;
}

u64 new_data_time(  )
{
	return 100 + ( rand(  ) & 0x1fff );
}

u64 time_get(  )
{
	return time;
}

void time_advance( u64 time_delta )
{
	time = time += time_delta;
}

u16 get_finished(  )
{
	return completed_processes;
}

void process_execute( proc current_process )
{

	if ( current_process->_run_counter < 1 )
	{
		vas_free( current_process->_sbt, current_process->_vas );

		int index;
		for ( index = 0; index < current_process->_vas; index++ )
		{
			u16 level_two =
			    address_get( current_process->_pti, index );
			unset_pinned_bit( level_two );
		}
		unset_pinned_bit( current_process->_pti );
		printf( "process %d has completed\n",
			current_process->_process_identity );
		completed_processes++;
		printf( "%d total processes have completed\n",
			get_finished(  ) );
		return;
	}

	printf( "process %d executing\n", current_process->_process_identity );

	u32 code_translation =
	    virtual_to_physical( current_process->_code_address,
				 current_process );
	u32 data_translation =
	    virtual_to_physical( current_process->_data_address,
				 current_process );

	u64 timer = current_process->_time;

	if ( !code_translation )
	{
		printf( "page fault for code page\n" );
		page_fault( current_process->_code_address, current_process );
		return;
	}

	set_used_bit( code_translation );

	if ( !data_translation )
	{
		printf( "page fault for data page\n" );
		page_fault( current_process->_data_address, current_process );
		return;
	}

	set_used_bit( data_translation );

	while ( timer )
	{
		if ( current_process->_code_time < current_process->_data_time )
		{
			if ( current_process->_code_time > timer )
			{
				printf( "process %d timed out\n",
					current_process->_process_identity );

				current_process->_code_time -= timer;
				time_advance( timer );
				timer -= timer;
				ready_enqueue( current_process );
				current_process->_run_counter--;
				return;
			}

			else
			{
				time_advance( current_process->_code_time );
				timer -= current_process->_code_time;

				current_process->_code_address =
				    new_code_address( current_process->
						      _code_address,
						      current_process->
						      _code_size );
				current_process->_code_time = new_code_time(  );
				code_translation =
				    virtual_to_physical( current_process->
							 _code_address,
							 current_process );
				current_process->_run_counter--;
			}

			if ( !code_translation )
			{
				printf( "fault on code\n" );
				page_fault( current_process->_code_address,
					    current_process );
				return;
			}

			set_used_bit( code_translation );
		}

		else
		{
			if ( current_process->_data_time > timer )
			{
				printf( "process %d timed out\n",
					current_process->_process_identity );

				current_process->_data_time -= timer;
				time_advance( timer );
				timer -= timer;
				ready_enqueue( current_process );
				current_process->_run_counter--;
				return;
			}

			else
			{
				time_advance( current_process->_data_time );
				timer -= current_process->_data_time;

				current_process->_data_address =
				    new_data_address( current_process->
						      _data_address,
						      current_process->
						      _code_size,
						      ( current_process->
							_code_size +
							current_process->
							_data_size ) );
				current_process->_data_time = new_data_time(  );
				data_translation =
				    virtual_to_physical( current_process->
							 _data_address,
							 current_process );
				current_process->_run_counter--;
			}

			if ( !code_translation )
			{
				printf( "page fault for code page\n" );
				page_fault( current_process->_data_address,
					    current_process );
				return;
			}

			set_used_bit( data_translation );
		}
	}
}

void initialize_queues(  )
{
	_blocked._head = NULL;

	_low._head = NULL;
	_low._tail = NULL;

	_medium._head = NULL;
	_medium._tail = NULL;

	_high._head = NULL;
	_high._tail = NULL;
}

int initialize_process( u8 priority, u32 csize, u32 dsize, u64 t )
{
	proc np = malloc( sizeof( *np ) );

	np->_vas = ( ( ( ( csize + dsize ) / 1000 ) / 1000 ) / 4 );

	int enough_space =
	    virtual_address_space_allocation( np->_sbt, np->_vas );

	if ( enough_space )
	{
		np->_process_identity = number_of_processes;
		number_of_processes++;

		np->_priority = priority;
		np->_time = t;

		np->_code_address = 0;
		np->_code_time = new_code_time(  );
		np->_code_size = csize;

		np->_data_address = csize + 1;
		np->_data_time = new_data_time(  );
		np->_data_size = dsize;

		np->_run_counter = 5;
		np->_next = NULL;

		u16 allocation = page_allocation(  );

		if ( !allocation )
		{
			u16 swap_page = walk_page_ring(  );
			page_free( swap_page );

			allocation = page_allocation(  );
		}

		np->_pti = allocation;
		set_pinned_bit( allocation );

		int index;
		for ( index = 0; index < np->_vas; index++ )
		{
			u16 allocation = page_allocation(  );

			if ( !allocation )
			{
				u16 swap_page = walk_page_ring(  );
				page_free( swap_page );
				allocation = page_allocation(  );
			}

			address_set( np->_pti, index, allocation );
			set_pinned_bit( allocation );
		}

		printf( "Creating new process, id: %d\n",
			np->_process_identity );
		ready_enqueue( np );
		return 1;
	} else
	{
		free( np );
		return 0;
	}
}

u8 empty_queues(  )
{
	u8 b = ( _blocked._head == NULL );
	u8 h = ( _high._head == NULL );
	u8 m = ( _medium._head == NULL );
	u8 l = ( _low._head == NULL );
	u8 x = ( b && h && m && l );
	return x;
}

void scheduler(  )
{
	proc global_process;
	time_advance( 10000 );
	blocked_dequeue(  );

	if ( counter < 4 )
	{
		global_process = ready_dequeue( 1 );
	} else if ( counter < 7 )
	{
		global_process = ready_dequeue( 2 );
	} else
	{
		global_process = ready_dequeue( 3 );
	}

	if ( global_process != NULL )
	{
		counter = counter++ % 7;
		process_execute( global_process );
	}
}
