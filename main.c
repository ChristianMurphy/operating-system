#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

#define	SWAP_SIZE	 ((1 << 6))
#define	SWAP_SIZE_MASK (SWAP_SIZE - 1)
#define	PAGE_COUNT 65536
#define	PAGE_MASK	(PAGE_COUNT - 1)
#define	virtual_address_space_vector_SIZE (1 << 6)
#define	virtual_address_space_vector_SIZE_MASK (virtual_address_space_vector_SIZE - 1)

struct {
	u64 _start_time;
	u32 _run_time;
	u32 _code_size;
	u32 _data_size;
	u32 _priority;
} process_initialize[100] =
{
	{
	( u64 ) 10, 5100000, 20000000, 30000000, 1},
	{
	( u64 ) 10000000001, 6200000, 40000000, 20000000, 2},
	{
	( u64 ) 10000000200, 7300000, 60000000, 10000000, 3},
	{
	( u64 ) 80000000013, 8400000, 80000000, 90000000, 1},
	{
	( u64 ) 80000000014, 9500000, 10000000, 80000000, 2},
	{
	( u64 ) 80000000015, 5600000, 20000000, 70000000, 3},
	{
	( u64 ) 200000000016, 6700000, 30000000, 60000000, 1},
	{
	( u64 ) 200000000107, 7800000, 40000000, 50000000, 2},
	{
	( u64 ) 200000000801, 8900000, 50000000, 40000000, 3},
	{
	( u64 ) 200000009001, 9600000, 60000000, 30000000, 1},
	{
	( u64 ) 800000000000, 5500000, 70000000, 20000000, 2},
	{
	( u64 ) 800000000001, 6400000, 80000000, 10000000, 3},
	{
	( u64 ) 800000000002, 7300000, 90000000, 50000000, 1},
	{
	( u64 ) 800000000003, 8200000, 10000000, 40000000, 2},
	{
	( u64 ) 800000000004, 9000000, 20000000, 30000000, 3},
	{
	( u64 ) 1200000000025, 5400000, 30000000, 20000000, 1},
	{
	( u64 ) 1200000000026, 6000000, 40000000, 10000000, 2},
	{
	( u64 ) 1200000000027, 7666660, 50000000, 60000000, 3},
	{
	( u64 ) 1200000000028, 8400000, 60000000, 30000000, 1},
	{
	( u64 ) 1200000000029, 9200000, 70000000, 10000000, 2},
	{
	( u64 ) 1200000000010, 5000000, 20000000, 30000000, 1},
	{
	( u64 ) 2000000000011, 6100000, 40000000, 20000000, 2},
	{
	( u64 ) 2000000000102, 7200000, 60000000, 10000000, 3},
	{
	( u64 ) 2000000000301, 8300000, 80000000, 90000000, 1},
	{
	( u64 ) 2000000000401, 9400000, 10000000, 80000000, 2},
	{
	( u64 ) 2000000050001, 5500000, 20000000, 70000000, 3},
	{
	( u64 ) 2000000060001, 6600000, 30000000, 60000000, 1},
	{
	( u64 ) 2000000070001, 7700000, 40000000, 50000000, 2},
	{
	( u64 ) 3000000000018, 8800000, 50000000, 40000000, 3},
	{
	( u64 ) 3000000000019, 9900000, 60000000, 30000000, 1},
	{
	( u64 ) 3000000000020, 5000000, 70000000, 20000000, 2},
	{
	( u64 ) 3000000000021, 6900000, 80000000, 10000000, 3},
	{
	( u64 ) 3000000000022, 7800000, 90000000, 50000000, 1},
	{
	( u64 ) 3000000000023, 8700000, 10000000, 40000000, 2},
	{
	( u64 ) 3000000000024, 9600000, 20000000, 30000000, 3},
	{
	( u64 ) 3000000000025, 5500000, 30000000, 20000000, 1},
	{
	( u64 ) 5000000001026, 6400000, 40000000, 10000000, 2},
	{
	( u64 ) 5000000002027, 7300000, 50000000, 60000000, 3},
	{
	( u64 ) 5000000003028, 8200000, 60000000, 30000000, 1},
	{
	( u64 ) 5000000004029, 9100000, 70000000, 10000000, 2},
	{
	( u64 ) 5000000005010, 5000000, 20000000, 30000000, 1},
	{
	( u64 ) 5000000006011, 6600000, 40000000, 20000000, 2},
	{
	( u64 ) 5000000007012, 7500000, 60000000, 10000000, 3},
	{
	( u64 ) 5000000008013, 8400000, 80000000, 90000000, 1},
	{
	( u64 ) 5000000009014, 9300000, 10000000, 80000000, 2},
	{
	( u64 ) 7000000000005, 5200000, 20000000, 70000000, 3},
	{
	( u64 ) 7000000000016, 6100000, 30000000, 60000000, 1},
	{
	( u64 ) 7000000000118, 8000000, 50000000, 40000000, 3},
	{
	( u64 ) 7000000001019, 9600000, 60000000, 30000000, 1},
	{
	( u64 ) 7000000010020, 5500000, 70000000, 20000000, 2},
	{
	( u64 ) 7000000020021, 6400000, 80000000, 10000000, 3},
	{
	( u64 ) 7000000030022, 7300000, 90000000, 50000000, 1},
	{
	( u64 ) 7000000040023, 8200000, 10000000, 40000000, 2},
	{
	( u64 ) 7000000050017, 7100000, 40000000, 50000000, 2},
	{
	( u64 ) 7000000060024, 9000000, 20000000, 30000000, 3},
	{
	( u64 ) 9000000000025, 5600000, 30000000, 20000000, 1},
	{
	( u64 ) 9000000000026, 6500000, 40000000, 10000000, 2},
	{
	( u64 ) 9000000000027, 7400000, 50000000, 60000000, 3},
	{
	( u64 ) 9000000000028, 8300000, 60000000, 30000000, 1},
	{
	( u64 ) 9000000000029, 9200000, 70000000, 10000000, 2},
	{
	( u64 ) 9000000000110, 5100000, 20000000, 30000000, 1},
	{
	( u64 ) 9000000000111, 6000000, 40000000, 20000000, 2},
	{
	( u64 ) 9000000000112, 7600000, 60000000, 10000000, 3},
	{
	( u64 ) 9000000000113, 8500000, 80000000, 90000000, 1},
	{
	( u64 ) 9000000000114, 9400000, 10000000, 80000000, 2},
	{
	( u64 ) 9000000000115, 5300000, 20000000, 70000000, 3},
	{
	( u64 ) 11000000001016, 6200000, 30000000, 60000000, 1},
	{
	( u64 ) 11000000002017, 7100000, 40000000, 50000000, 2},
	{
	( u64 ) 11000000003018, 8000000, 50000000, 40000000, 3},
	{
	( u64 ) 11000000010019, 9300000, 60000000, 30000000, 1},
	{
	( u64 ) 11000000020020, 5000000, 70000000, 20000000, 2},
	{
	( u64 ) 11000000030021, 6600000, 80000000, 10000000, 3},
	{
	( u64 ) 11000000040022, 7200000, 90000000, 50000000, 1},
	{
	( u64 ) 11000000050023, 8400000, 10000000, 40000000, 2},
	{
	( u64 ) 11000000060024, 9100000, 20000000, 30000000, 3},
	{
	( u64 ) 11000000070025, 5000000, 30000000, 20000000, 1},
	{
	( u64 ) 11000000080026, 6000000, 40000000, 10000000, 2},
	{
	( u64 ) 11000000090027, 7000000, 50000000, 60000000, 3},
	{
	( u64 ) 14000000003028, 8000000, 60000000, 30000000, 1},
	{
	( u64 ) 14000000004029, 9900000, 70000000, 10000000, 2},
	{
	( u64 ) 14000000005010, 5800000, 20000000, 30000000, 1},
	{
	( u64 ) 14000000006011, 6600000, 40000000, 20000000, 2},
	{
	( u64 ) 14000000010012, 7300000, 60000000, 10000000, 3},
	{
	( u64 ) 14000000020013, 8000000, 80000000, 90000000, 1},
	{
	( u64 ) 14000000030014, 9000000, 10000000, 80000000, 2},
	{
	( u64 ) 14000000040015, 5000000, 20000000, 70000000, 3},
	{
	( u64 ) 14000000050016, 6000000, 30000000, 60000000, 1},
	{
	( u64 ) 14000000060017, 7600000, 40000000, 50000000, 2},
	{
	( u64 ) 14000000070018, 8300000, 50000000, 40000000, 3},
	{
	( u64 ) 14000000080019, 9300000, 60000000, 30000000, 1},
	{
	( u64 ) 14000000090020, 5600000, 70000000, 20000000, 2},
	{
	( u64 ) 15000000010021, 6300000, 80000000, 10000000, 3},
	{
	( u64 ) 15000000020022, 7000000, 90000000, 50000000, 1},
	{
	( u64 ) 15000000030023, 8000000, 10000000, 40000000, 2},
	{
	( u64 ) 15000000040024, 9000000, 20000000, 30000000, 3},
	{
	( u64 ) 15000000050025, 5100000, 30000000, 20000000, 1},
	{
	( u64 ) 15000000060026, 6300000, 40000000, 10000000, 2},
	{
	( u64 ) 15000000070027, 7500000, 50000000, 60000000, 3},
	{
	( u64 ) 15000000080028, 8300000, 60000000, 30000000, 1},
	{
	( u64 ) 15000000090029, 9400000, 70000000, 10000000, 2}
};

static page page_memory[PAGE_COUNT];

static u16 page_availible = 1;

static memory_manage_structure memory_manager[PAGE_COUNT] = { 0 };

static u16 memory_offset = 1;

static u64 virtual_address_space_vector[virtual_address_space_vector_SIZE] =
    { 0 };

static u32 virtual_address_space_offset = 0;
static u32 virtual_address_space_count = 4096;

static u64 avail[SWAP_SIZE] = { 1, 0 };

static u32 offset = 0;
static u32 count = SWAP_SIZE << 6;

static u32 read_latency = 8 << 20;
static u32 write_latency = 8 << 20;
static u64 disk_time = 0;

static blocked _blocked;
static ready _high;
static ready _medium;
static ready _low;

static int counter = 0;
static u64 time = 0;
static u64 time_blocked = 0;
static u16 number_of_processes = 1;
static u16 completed_processes = 0;

int swap_allocation( u16 virtual_space[], u32 size )
{
	if ( count < size )
	{
		return 0;
	}

	u32 t;
	for ( u32 index = 0; index < size; ++index )
	{
		if ( ~( avail[offset] ) )
		{
			t = least_significant_bit64( avail[offset] );
			avail[offset] |= 1ul << t;
			virtual_space[index] = ( offset << 6 ) | t;
		} else
		{
			offset = ( offset + 1 ) & SWAP_SIZE_MASK;
		}
	}
	count -= size;
	return 1;
}

void swap_free( u16 virtual_space[], u32 size )
{
	for ( u32 index = 0; index < size; ++index )
	{
		avail[virtual_space[index] >> 6] &=
		    ~( 1ul << ( virtual_space[index] & 63 ) );
	}
	count += size;
}

u64 disk_read( u32 block, u16 address )
{
	printf( "Reading block %d from disk\n", block );

	u32 delta = rand(  );

	if ( time_get(  ) > disk_time )
	{
		disk_time = time_get(  );
	}

	if ( delta & 1 )
	{
		disk_time += read_latency + ( delta & 0x3FFFFF );
	}

	else
	{
		disk_time += read_latency - ( delta & 0x1FFFFF );
	}

	if ( block < SWAP_SIZE )
	{

		write_page( address );
	}

	return disk_time;
}

u64 disk_write( u32 block, u16 address )
{
	u32 delta = rand(  );

	if ( time_get(  ) > disk_time )
	{
		disk_time = time_get(  );
	}

	if ( delta & 1 )
	{
		disk_time += write_latency + ( delta & 0x3FFFFF );
	} else
	{
		disk_time += write_latency - ( delta & 0x1FFFFF );
	}

	if ( block < SWAP_SIZE )
	{
		read_page( address );
	}

	return disk_time;
}

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
			} else
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
		vas_free( current_process->_sbt,
			  current_process->_virtual_address_space );

		for ( int index = 0;
		      index < current_process->_virtual_address_space; index++ )
		{
			u16 level_two =
			    address_get( current_process->_page_table_index,
					 index );
			unset_pinned_bit( level_two );
		}
		unset_pinned_bit( current_process->_page_table_index );
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
				    new_code_address
				    ( current_process->_code_address,
				      current_process->_code_size );
				current_process->_code_time = new_code_time(  );
				code_translation =
				    virtual_to_physical
				    ( current_process->_code_address,
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
			} else
			{
				time_advance( current_process->_data_time );
				timer -= current_process->_data_time;

				current_process->_data_address =
				    new_data_address
				    ( current_process->_data_address,
				      current_process->_code_size,
				      ( current_process->_code_size +
					current_process->_data_size ) );
				current_process->_data_time = new_data_time(  );
				data_translation =
				    virtual_to_physical
				    ( current_process->_data_address,
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

int initialize_process( u8 priority, u32 code_size, u32 data_size, u64 t )
{
	proc new_process = malloc( sizeof( *new_process ) );

	new_process->_virtual_address_space =
	    ( ( ( ( code_size + data_size ) / 1000 ) / 1000 ) / 4 );

	int enough_space = virtual_address_space_allocation( new_process->_sbt,
							     new_process->_virtual_address_space );

	if ( enough_space )
	{
		new_process->_process_identity = number_of_processes;
		number_of_processes++;

		new_process->_priority = priority;
		new_process->_time = t;

		new_process->_code_address = 0;
		new_process->_code_time = new_code_time(  );
		new_process->_code_size = code_size;

		new_process->_data_address = code_size + 1;
		new_process->_data_time = new_data_time(  );
		new_process->_data_size = data_size;

		new_process->_run_counter = 5;
		new_process->_next = NULL;

		u16 allocation = page_allocation(  );

		if ( !allocation )
		{
			u16 swap_page = walk_page_ring(  );
			page_free( swap_page );

			allocation = page_allocation(  );
		}

		new_process->_page_table_index = allocation;
		set_pinned_bit( allocation );

		for ( int index = 0;
		      index < new_process->_virtual_address_space; index++ )
		{
			u16 allocation = page_allocation(  );
			if ( !allocation )
			{
				u16 swap_page = walk_page_ring(  );
				page_free( swap_page );
				allocation = page_allocation(  );
			}
			address_set( new_process->_page_table_index, index,
				     allocation );
			set_pinned_bit( allocation );
		}

		printf( "Creating new process, id: %d\n",
			new_process->_process_identity );
		ready_enqueue( new_process );
		return 1;
	} else
	{
		free( new_process );
		return 0;
	}
}

u8 remaining_processes(  )
{
	u8 blocked_empty = ( _blocked._head == NULL );
	u8 high_empty = ( _high._head == NULL );
	u8 medium_empty = ( _medium._head == NULL );
	u8 low_empty = ( _low._head == NULL );
	u8 all_empty = ( blocked_empty && high_empty && medium_empty
			 && low_empty );
	return all_empty;
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

void read_page( u16 page_number )
{
	printf( "page %d read\n", page_number );
}

void write_page( u16 page_number )
{
	printf( "page %d write\n", page_number );
}

page get_page( u32 address )
{
	return page_memory[address];
}

void set_used_bit( u16 page_number )
{
	memory_manager[page_number]._used = 1;
}

void set_pinned_bit( u16 page_number )
{
	memory_manager[page_number]._pinned = 1;
}

void unset_pinned_bit( u16 page_number )
{
	memory_manager[page_number]._pinned = 0;
}

void address_set( u16 page_number, int index, u16 address )
{
	page_memory[page_number]._u32[index] = address;
	printf( "Page %d index %d is storing address\n", page_number, index,
		address );
}

u16 address_get( u16 page_number, int index )
{
	u32 a = page_memory[page_number]._u32[index];
	u16 b = a & 0xFFFF;
	return b;
}

u16 page_allocation(  )
{
	u16 t = page_availible;
	if ( page_availible )
	{
		page_availible = page_memory[page_availible]._u16[0];
	}
	int index;
	for ( index = 0; index < 512; index++ )
	{
		page_memory[t]._u64[index] = 0;
	}
	return t;
}

void page_free( u16 page_index )
{
	if ( memory_manager[page_index]._dirty )
	{
		printf( "Page %d is dirty\n", page_index );
		write_page( page_index );
	}

	page_memory[page_index]._u16[0] = page_availible;
	page_availible = page_index;
}

void page_free_all(  )
{
	for ( u16 index = 1; index < PAGE_COUNT - 1; index++ )
	{
		page_memory[index]._u16[0] = index + 1;
	}
}

u32 virtual_to_physical( u32 address, proc current_process )
{
	u32 level_one_index = address >> 22;
	u32 level_two_index = ( ( address >> 12 ) & 0x3FF );

	u16 level_one_address = current_process->_page_table_index;
	page level_one = page_memory[level_one_address];
	u32 level_two_address = level_one._u32[level_one_index];

	if ( !level_two_address )
	{
		return 0;
	}

	page level_two = page_memory[level_two_address];
	u32 physical_address = level_two._u32[level_two_index];

	if ( !physical_address )
	{
		return 0;
	}
	return physical_address;
}

void page_fault( u32 address, proc current_process )
{
	printf( "process %d faulted on address %d\n",
		current_process->_process_identity, address );

	u16 allocation = page_allocation(  );

	if ( !allocation )
	{
		u16 swap_page = walk_page_ring(  );
		page_free( swap_page );
		allocation = page_allocation(  );

		printf( "swap page\n" );
	}
	printf( "page %d taken\n", allocation );

	u32 level_one_index = address >> 22;
	u32 level_two_index = ( ( address >> 12 ) & 0x3FF );
	u16 level_one_address = current_process->_page_table_index;
	page level_one = page_memory[level_one_address];
	u32 level_two_address = level_one._u32[level_one_index];

	u64 d_time = disk_read( address, allocation );
	address_set( level_two_address, level_two_index, allocation );
	blocked_enqueue( current_process, d_time );
}

int virtual_address_space_allocation( u16 virtual_space[], u32 size )
{
	int result = 0;

	if ( size <= virtual_address_space_count )
	{
		for ( int index = 0; index < size; index++ )
		{
			while ( virtual_address_space_vector
				[virtual_address_space_offset] ==
				0xFFFFFFFFFFFFFFFF )
			{
				virtual_address_space_offset++;
				if ( virtual_address_space_offset > 63 )
				{
					virtual_address_space_offset = 0;
				}
			}

			u16 bit_position =
			    ( u16 )
			    least_significant_bit64
			    ( virtual_address_space_vector
			      [virtual_address_space_offset] );

			u16 chunk_addressess =
			    ( virtual_address_space_offset << 8 ) |
			    ( bit_position );

			virtual_space[index] = chunk_addressess;

			u64 flipped_bit = 1;
			flipped_bit = flipped_bit << bit_position;

			virtual_address_space_vector
			    [virtual_address_space_offset] =
			    virtual_address_space_vector
			    [virtual_address_space_offset] | ( flipped_bit );

			virtual_address_space_count--;
		}

		result = 1;
	}

	return result;
}

void vas_free( u16 virtual_space[], u32 size )
{
	for ( int index = 0; index < size; index++ )
	{

		u16 chunk_addressess = virtual_space[index];
		u16 bit_position = chunk_addressess & 0x00FF;
		u16 virtual_address_space_offset_temparary =
		    chunk_addressess >> 8;

		u64 flipped_bit = 1;
		flipped_bit = flipped_bit << bit_position;
		virtual_address_space_vector
		    [virtual_address_space_offset_temparary] =
		    virtual_address_space_vector
		    [virtual_address_space_offset_temparary] & ~( flipped_bit );

		virtual_address_space_count++;
	}
}

u16 walk_page_ring(  )
{
	u16 temparary = 0;
	for ( int index = 0; index < PAGE_COUNT; index++ )
	{
		if ( !( memory_manager[index]._used )
		     && !( memory_manager[index]._pinned ) )
		{
			temparary = index;
			break;
		}
		memory_manager[index]._used = 0;
	}
	return temparary;
}

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

int main(  )
{
	int counter = 0;
	initialize_queues(  );
	time_advance( 20 );
	page_free_all(  );

	do
	{
		u8 time_test =
		    ( time_get(  ) > process_initialize[counter]._start_time );
		if ( time_test && counter < 100 )
		{

			int success =
			    initialize_process( process_initialize
						[counter]._priority,
						process_initialize
						[counter]._code_size,
						process_initialize
						[counter]._data_size,
						process_initialize
						[counter]._run_time );

			if ( success )
			{
				counter++;
			}
		}
		scheduler(  );
	}
	while ( ( counter < 100 ) || ( remaining_processes(  ) == 0 ) );
	printf( "program complete\n" );
}
