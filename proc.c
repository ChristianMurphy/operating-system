#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "headers/types.h"
#include "headers/mem_man.h"
#include "headers/proc.h"

// Create all of the queues
static blocked _blocked;
static ready _high;
static ready _medium;
static ready _low;

static int counter = 0;
static u64 time = 0;
static u64 time_blocked = 0;
static u16 num_proc = 1;
static u16 finished = 0;

// initial addressess, process time, time prediction, priority, and something else

void blocked_enq( proc p, u64 estimated_time )
{
	printf( "Placing process %d in the blocked queue\n", p->_process_identity );

	p->_blocked_timer = estimated_time;
	if ( _blocked._head == NULL )
	{
		_blocked._head = p;
	} else
	{
		p->_next = _blocked._head;
		_blocked._head = p;
	}
}

void blocked_deq(  )
{
	if ( _blocked._head == NULL )
	{
		return;
	}

	proc cp = _blocked._head;
	proc pp = _blocked._head;

	if ( _blocked._head != NULL && _blocked._head->_next == NULL )
	{
		if ( cp->_blocked_timer <= time_get(  ) )
		{
			printf( "Removing process %d from the blocked queue\n",
				_blocked._head->_process_identity );
			ready_enq( _blocked._head );
			_blocked._head = NULL;
		}
	}

	else if ( ( _blocked._head != NULL )
		  && ( _blocked._head->_next != NULL ) )
	{
		do
		{
			if ( cp->_blocked_timer <= time_get(  ) )
			{
				if ( _blocked._head == cp )
				{
					_blocked._head = cp->_next;
					cp->_next = NULL;
					printf
					    ( "Removing process %d from the blocked queue\n",
					      cp->_process_identity );
					ready_enq( cp );
					cp = _blocked._head;
					pp = cp;
				} else
				{
					pp->_next = cp->_next;
					cp->_next = NULL;
					printf
					    ( "Removing process %d from the blocked queue\n",
					      cp->_process_identity );
					ready_enq( cp );
					cp = pp->_next;
				}
			}

			else
			{
				if ( cp == pp )
				{
					cp = cp->_next;
				} else
				{
					cp = cp->_next;
					pp = pp->_next;
				}
			}
		}
		while ( cp != NULL );
	}
}

void ready_enq( proc p )
{
	if ( p->_priority )
	{
		if ( p->_priority == 1 )
		{
			if ( _high._head == NULL && _high._tail == NULL )
			{
				_high._head = p;
				_high._tail = p;
			}

			else
			{
				_high._tail->_next = p;
				_high._tail = p;
			}
			printf
			    ( "Placing process %d in the high priority queue\n",
			      p->_process_identity );
		}

		if ( p->_priority == 2 )
		{
			if ( _medium._head == NULL && _medium._tail == NULL )
			{
				_medium._head = p;
				_medium._tail = p;
			}

			else
			{
				_medium._tail->_next = p;
				_medium._tail = p;
			}
			printf
			    ( "Placing process %d in the medium priority queue\n",
			      p->_process_identity );
		}

		if ( p->_priority == 3 )
		{
			if ( _low._head == NULL && _low._tail == NULL )
			{
				_low._head = p;
				_low._tail = p;
			}

			else
			{
				_low._tail->_next = p;
				_low._tail = p;
			}
			printf
			    ( "Placing process %d in the low priority queue\n",
			      p->_process_identity );
		}
	}
}

proc ready_deq( u8 priority )
{
	proc p;

	switch ( priority )
	{
	case 1:

		if ( _high._head == NULL )
		{
			return NULL;
		} else if ( _high._head == _high._tail && _high._head != NULL )
		{
			p = _high._head;
			_high._head = NULL;
			_high._tail = NULL;
		} else
		{
			p = _high._head;
			_high._head = p->_next;
			p->_next = NULL;
		}
		printf( "Removing process %d from the high priority queue\n",
			p->_process_identity );
		break;

	case 2:

		if ( _medium._head == NULL )
		{
			return NULL;
		} else if ( _medium._head == _medium._tail
			    && _medium._head != NULL )
		{
			p = _medium._head;
			_medium._head = NULL;
			_medium._tail = NULL;
		} else
		{

			p = _medium._head;
			_medium._head = p->_next;
			p->_next = NULL;
		}

		printf( "Removing process %d from the medium priority queue\n",
			p->_process_identity );
		break;

	case 3:

		if ( _low._head == NULL )
		{
			return NULL;
		} else if ( _low._head == _low._tail && _low._head != NULL )
		{
			p = _low._head;
			_low._head = NULL;
			_low._tail = NULL;
		} else
		{
			p = _low._head;
			_low._head = p->_next;
			p->_next = NULL;
		}
		printf( "Removing process %d from the low priority queue\n",
			p->_process_identity );
		break;
	}
	return p;
}

//
u32 new_code_address( u32 address, u32 limit )
{
	static u32 x[32] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 8, 16
	};

	u32 r = rand(  );
	address = ( r & 64 ) ? address + x[r & 31] : address - x[r & 31];
	return ( address > limit ) ? address = r % limit : address;
}

//
u64 new_code_time(  )
{
	return 50 + ( rand(  ) & 0xfff );
}

//
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

//
u64 new_data_time(  )
{
	return 100 + ( rand(  ) & 0x1fff );
}

//
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
	return finished;
}

//
void process_exec( proc p )
{

	if ( p->_run_counter < 1 )
	{
		vas_free( p->_sbt, p->_vas );

		int i;
		for ( i = 0; i < p->_vas; i++ )
		{
			u16 l2 = get_addressess( p->_pti, i );
			clear_pinned( l2 );
		}
		clear_pinned( p->_pti );
		printf( "Process %d has finished executing\n", p->_process_identity );
		finished++;
		printf( "%d processes have finished executing\n",
			get_finished(  ) );
		return;
	}

	printf( "Executing process %d\n", p->_process_identity );

	u32 code_trans = virt_to_phys( p->_code_address, p );
	u32 data_trans = virt_to_phys( p->_data_address, p );

	u64 timer = p->_time;

	if ( !code_trans )
	{
		printf( "fault on code\n" );
		page_fault( p->_code_address, p );
		return;
	}

	set_used( code_trans );

	if ( !data_trans )
	{
		printf( "fault on data\n" );
		page_fault( p->_data_address, p );
		return;
	}

	set_used( data_trans );

	while ( timer )
	{
		if ( p->_code_time < p->_data_time )
		{
			if ( p->_code_time > timer )
			{
				printf( "Process %d ran out of time\n",
					p->_process_identity );

				p->_code_time -= timer;
				time_advance( timer );
				timer -= timer;
				ready_enq( p );
				p->_run_counter--;
				return;
			}

			else
			{
				time_advance( p->_code_time );
				timer -= p->_code_time;

				p->_code_address =
				    new_code_address( p->_code_address,
						   p->_code_size );
				p->_code_time = new_code_time(  );
				code_trans = virt_to_phys( p->_code_address, p );
				p->_run_counter--;
			}

			if ( !code_trans )
			{
				printf( "fault on code\n" );
				page_fault( p->_code_address, p );
				return;
			}

			set_used( code_trans );
		}

		else
		{
			if ( p->_data_time > timer )
			{
				printf( "Process %d ran out of time\n",
					p->_process_identity );

				p->_data_time -= timer;
				time_advance( timer );
				timer -= timer;
				ready_enq( p );
				p->_run_counter--;
				return;
			}

			else
			{
				time_advance( p->_data_time );
				timer -= p->_data_time;

				p->_data_address =
				    new_data_address( p->_data_address, p->_code_size,
						   ( p->_code_size +
						     p->_data_size ) );
				p->_data_time = new_data_time(  );
				data_trans = virt_to_phys( p->_data_address, p );
				p->_run_counter--;
			}

			if ( !data_trans )
			{
				printf( "fault on data\n" );
				page_fault( p->_data_address, p );
				return;
			}

			set_used( data_trans );
		}
	}
}

// Initialize values in the queues
void init_queues(  )
{
	_blocked._head = NULL;

	_high._head = NULL;
	_high._tail = NULL;

	_medium._head = NULL;
	_medium._tail = NULL;

	_low._head = NULL;
	_low._tail = NULL;
}

// Initializes a process
int init_process( u8 priority, u32 csize, u32 dsize, u64 t )
{
	proc np = malloc( sizeof( *np ) );

	np->_vas = ( ( ( ( csize + dsize ) / 1000 ) / 1000 ) / 4 );

	int enough_space = vas_alloc( np->_sbt, np->_vas );

	if ( enough_space )
	{
		np->_process_identity = num_proc;
		num_proc++;

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

		u16 alloc = page_alloc(  );

		if ( !alloc )
		{
			u16 swap_page = walk_page_ring(  );
			page_free( swap_page );

			alloc = page_alloc(  );
		}

		np->_pti = alloc;
		set_pinned( alloc );

		int i;
		for ( i = 0; i < np->_vas; i++ )
		{
			u16 alloc = page_alloc(  );

			if ( !alloc )
			{
				u16 swap_page = walk_page_ring(  );
				page_free( swap_page );
				alloc = page_alloc(  );
			}

			insert_addressess( np->_pti, i, alloc );
			set_pinned( alloc );
		}

		printf( "Creating new process, id: %d\n", np->_process_identity );
		ready_enq( np );
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

// Checks ready queues first, 4 from high, 2 from medium, 1 from low
// Then looks through blocked to see if anything is finished
void scheduler(  )
{
	proc gp;
	time_advance( 10000 );
	blocked_deq(  );

	switch ( counter )
	{
	case 0:
	case 1:
	case 2:
	case 3:
		if ( ( gp = ready_deq( 1 ) ) != NULL )
		{
			break;
		}

	case 4:
	case 5:
	case 6:
		if ( ( gp = ready_deq( 2 ) ) != NULL )
		{
			break;
		}

	case 7:
		if ( ( gp = ready_deq( 3 ) ) != NULL )
		{
			break;
		}
	default:
		if ( gp == NULL && counter > 3 )
		{
			gp = ready_deq( 1 );
		}
		break;
	}

	if ( gp != NULL )
	{
		counter = counter++ % 7;
		process_exec( gp );
	}
}
