#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>
#include    "headers/types.h"
#include    "headers/mem_man.h"
#include    "headers/proc.h"

/**
 * Christian Murphy
 */

static u64 time = 0;
static process *ready_list = 0;
static blocked_list blocked;
static ready_queue ready_low_queue;
static ready_queue ready_medium_queue;
static ready_queue ready_high_queue;
static u16 priority_index = 0;
static process temporary_process;

static int schedule_counter = 0;

typedef struct {
    u64 _t;         // time to which process is allowed to run
    u32 *_code_addr;
    u32 *_code_time;
    u32 *_data_addr;
    u32 *_data_time;
} run_time;

void initiate_queues(  )
{
    blocked._head = NULL;

    ready_high_queue.head = NULL;
    ready_high_queue.tail = NULL;

    ready_medium_queue.head = NULL;
    ready_medium_queue.tail = NULL;

    ready_low_queue.head = NULL;
    ready_low_queue.tail = NULL;
}

void initiate_process( u8 priority, u32 code_size, u32 data_size, u64 time )
{
    process new_process = malloc(sizeof(*process));
    new_process._virtual_address_space = code_size + data_size;
    new_process._priority = priority;
    new_process._time = time;
    new_process._code_address = 0;
    new_process._data_address = 0;
    new_process._code_time = 0;
    new_process._data_time = 0;
    ready_enq( new_process );
}

void blocked_enq( process * p, u64 time_process )
{
    // adding a process to the blocked list
    p->_next = blocked._head;
    blocked._head = p;
    p->_time = time_process + time;
}

process *blocked_deq(  )
{
    process *current_process = blocked._head;
    process *previous_process = blocked._head;

    if ( current_process->_next != NULL
         && current_process->_next->_next == NULL )
    {
        ready_enq( current_process->_next,
               current_process->_next->_priority );
        current_process->_next = NULL;
        return current_process;
    }

    while ( current_process->_next != NULL )
    {
        if ( current_process->_time >= time )
        {
            ready_enq( current_process,
                   current_process->_priority );
            previous_process->_next = current_process->_next;
            current_process->_next = NULL;
            current_process = previous_process->_next;
        } else
        {
            previous_process->_next = current_process;
            current_process = current_process->_next;
        }
    }

    return current_process;
}

void ready_enq( process * p, s32 priority_delta )
{
    //get the current queue
    ready_queue current_priority_queue;
    switch ( p->_priority )
    {
    case 1:
        current_priority_queue = ready_high_queue;
        break;
    case 2:
        current_priority_queue = ready_medium_queue;
        break;
    case 3:
        current_priority_queue = ready_low_queue;
        break;
    }

    // if it is empty add stuff
    if ( current_priority_queue.head == NULL
         && current_priority_queue.tail == NULL )
    {
        current_priority_queue.head = p;
        current_priority_queue.tail = p;
    }
    // otherwise append to the end
    else
    {
        current_priority_queue.tail->_next = p;
        current_priority_queue.tail = p;
    }

    // store back to the correct queue
    switch ( p->_priority )
    {
    case 1:
        ready_high_queue = current_priority_queue;
        break;
    case 2:
        ready_medium_queue = current_priority_queue;
        break;
    case 3:
        ready_low_queue = current_priority_queue;
        break;
    }
}

process *ready_deq( u8 priority )
{
    // get correct queue
    ready_queue current_priority_queue;
    switch ( priority )
    {
    case 1:
        current_priority_queue = ready_high_queue;
        break;
    case 2:
        current_priority_queue = ready_medium_queue;
        break;
    case 3:
        current_priority_queue = ready_low_queue;
        break;
    }

    // pull off a process
    temporary_process = *current_priority_queue.head;
    current_priority_queue.head = temporary_process._next;
    temporary_process._next = NULL;

    // store back to the currect queue
    switch ( priority )
    {
    case 1:
        ready_high_queue = current_priority_queue;
        break;
    case 2:
        ready_medium_queue = current_priority_queue;
        break;
    case 3:
        ready_low_queue = current_priority_queue;
        break;
    }

    return &temporary_process;
}

u32 new_code_addr( u32 addr, u32 limit )
{
    static u32 x[32] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 8, 16
    };

    u32 r = rand(  );
    addr = ( r & 64 ) ? addr + x[r & 31] : addr - x[r & 31];
    return ( addr > limit ) ? addr = r % limit : addr;
}

u64 new_code_time(  )
{
    return 50 + ( rand(  ) & 0xfff );
}

u32 new_data_addr( u32 addr, u32 base, u32 limit )
{
    static u32 x[32] = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,
        5, 5, 6, 6, 7, 7, 8, 8, 9, 10, 11, 12, 16, 20, 28, 40
    };

    u32 r = rand(  );
    addr = ( r & 64 ) ? addr + x[r & 31] : addr - x[r & 31];
    return ( ( base < addr )
         || ( addr > limit ) ) ? addr =
        base + ( r % ( limit - base ) ) : addr;
}

u64 new_data_time(  )
{
    return 100 + ( rand(  ) & 0x1fff );
}

u64 process_exec( process * current_process, u32 code_limit, u32 data_limit,
          u32 t )
{
    u64 time = time_get(  );
    u32 i;

    u32 code_trans = virtual_address_to_physical_address( NULL, current_process->_code_address );
    u32 data_trans = virtual_address_to_physical_address( NULL, current_process->_data_address );

    if ( !code_trans )
    {
        //page_fault code
    }

    if ( !data_trans )
    {
        //page_fault code
    }

    while ( 1 )
    {
        u32 time_till_timer = t - time_get(  );
        if ( current_process->_code_time < current_process->_data_time )
        {
            if ( current_process->_code_time > time_till_timer )
            {
                current_process->_code_time -= time_till_timer;
                current_process->_data_time -= time_till_timer;
                return t;
            }
            time_adv( current_process->_code_time );
            current_process->_data_time -=
                current_process->_code_time;
            current_process->_code_address =
                new_code_addr( current_process->_code_address,
                       code_limit );
            current_process->_code_time = new_code_time(  );
            code_trans =
                virt_to_phys_read( current_process->_code_address );
            if ( !code_trans )
            {
                //page_fault code
                return time_get(  );
            }
        } else if ( current_process->_data_time > time_till_timer )
        {
            current_process->_code_time -= time_till_timer;
            current_process->_data_time -= time_till_timer;
            return t;
        } else
        {
            time_adv( current_process->_data_time );
            current_process->_code_time -=
                current_process->_data_time;
            current_process->_data_address =
                new_data_addr( current_process->_data_address,
                       code_limit, data_limit );
            current_process->_data_time = new_data_time(  );
            data_trans =
                virt_to_phys_write( current_process->
                        _data_address );
            if ( !data_trans )
            {
                //page_fault code
                return time_get(  );
            }
        }
    }
}

u64 time_get(  )
{
    return time;
};

void time_adv( u32 delta )
{
    time += delta;
};

void scheduler(  )
{
    if ( schedule_counter < 4 )
    {
        ready_deq( 1 );
        schedule_counter++;
    } else if ( schedule_counter < 7 )
    {
        ready_deq( 2 );
        schedule_counter++;
    } else
    {
        ready_deq( 3 );
        schedule_counter = 0;
    }
}
