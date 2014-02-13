operating system
================

This project's goal is to create a network driver for an emulated operating system


## Page Table
###levels of the page table
1. table of processes
2. process table
3. memory

###page table storage
a page is 2^12 bits in size

1. 32bit page entries
2. 32bit page entries
3. 1 bit for the nru, the rest is storage

###page structure
* page table entry
  * 1 bit for page clean or dirty
  * 1 bit for page is valid
  * 14 unused bits
  * 16 bit address
* standard page
  * 1 Not Recently Used bit
