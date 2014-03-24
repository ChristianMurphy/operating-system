#pragma once
#include "types.h"

typedef
    struct {
        u64 _used : 1;
        u64 _dirty : 1;
        u64 _pinned : 1;
        u64 : 13;
        u64 _l1 : 10;
        u64 : 6;
        u64 _l2 : 10;
        u64 : 6;
        u64 _proc : 16;
    }
mem_manage;
