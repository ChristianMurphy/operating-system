#include <stdio.h>
#include "headers/types.h"
#include "headers/memory_manage.h"
#include "headers/signatures.h"

/*!
 * memory consists of 2^12 (4,096) bits
 * seperated into 2^5 (32) bit chucks
 * meaning there are 2^7 (128) chunks in the page table
 */

int main () {
    printf("Hello World!\n");
    return 0;
}
