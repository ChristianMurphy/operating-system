#include <stdio.h>
#include "types.h"

/*!
 * memory consists of 2^12 (4,096) bits
 * seperated into 2^5 (32) bit chucks
 * meaning there are 2^7 (128) chunks in the page table
 */
typedef struct page {
	u32[128] page;
} page;

int main () {
	printf("Hello World!\n");
	return 0;
}