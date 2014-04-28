#pragma once
#include    <stdio.h>
#include    "headers/types.h"
#include    "headers/mem_man.h"
#include    "headers/proc.h"

static  u64          time            = 0;
static  process*     ready_list      = 0;
static  blocked_list blocked;
static  ready_queue ready_low_queue;
static  ready_queue ready_medium_queue;
static  ready_queue ready_high_queue;
static  u16 priority_index = 0;

void
blocked_enq (
    process*    p,
    u64 time_process
)
{
    // adding a process to the blocked list
    p -> _next = blocked._head;
    blocked._head = p;
    p -> _time = time_process + time;
}

process*
blocked_deq (
)
{
    process* current_process  = blocked.head;
    process* previous_process = blocked.head;

    while (current_process -> _next != NULL) {
        if (current_process -> time >= time) {
            ready_enq(current_process);
            previous_process -> _next = current_process -> _next;
            current_process -> _next  = NULL;
            current_process           = previous_process -> _next;
        } else {
            previous_process -> _next = current_process;
            current_process           = current_process -> _next;
        }
    }
}

void
ready_enq (
    process*    p,
    s32         priority_delta
)
{
}

process*
ready_deq (
)
{
}

void
process_execute (
    process*    p,
    u64         x
)
{
    while (time < x) {
        time += (*profiles[1])(code_size, *code_pointer);
        if (!mem_read(p, code_pointer)) {
            blocked_enq(p);
            return;
        }

        time += (*profiles[2])(data_size, *data_pointer);
        if (!mem_read(p, data_pointer)) {
            blocked_enq(p);
            return;
        }

        time += (*profiles[1])(code_size, *data_pointer);
        if (!mem_write(p, code_pointer)) {
            blocked_enq(p);
            return;
        }

        time += (*profiles[2])(data_size, *data_pointer);
        if (!mem_read(p, data_pointer)) {
            blocked_enq(p);
            return;
        }
    }
    ready_enq2p);
        cbar.comtime += (*profiles[2])(data_size, *data_pointer);
        if (!mem_read(p, data_pointer)) {
            blocked_enq(p);
            return;
        }
}

void
scheduler (
)
{

}
