operating system [![Build Status](https://travis-ci.org/ChristianMurphy/operating-system.svg?branch=master)](https://travis-ci.org/ChristianMurphy/operating-system)
================

This project's goal is to create an emulated operating system


## Page Table
### levels of the page table
1. table of processes
2. process table
3. memory

### page table storage
a page is 2^12 bits in size

1. 32bit page entries
2. 32bit page entries
3. 1 bit for the nru, the rest is storage

###page structure
* 1 bit for the page use status
* 1 bit for page clean or dirty
* 1 bit for page is pinned
* 13 padding bits
* 10 bits for level one cache
* 6 padding bits
* 10 bits for level two cache
* 6 padding bits

## Program
### function signature
``` c
program(
 u32 priority,
 u32 input_output_functions,
 u32 input_output_function_standard_deviation,
 u32 size,
 u32 execution_time,
 u32 working_set_size,
 u32 working_set_size_standard_deviation,
 u32 working_set_duration,
 u32 working_set_duration_standard_deviation
)
```

### what to do when there is a page fault
1. check what process was using page
    i.
    ii. tell that process that the memory has been freed
2. check if the page is clean
    i. if the page is dirty store to disk
3. write new page into that memory
