#include "headers/types.h"

struct {
	u64 _start_time;
	u32 _run_time;
	u32 _code_size;
	u32 _data_size;
	u32 _priority;
} proc_init[100] =
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

int main(  )
{
	int counter = 0;
	init_queues(  );
	set_time( time_get(  ) + 20 );
	emancipation_proclamation(  );

	do
	{
		u8 time_test =
		    ( time_get(  ) > proc_init[counter]._start_time );
		if ( time_test && counter < 100 )
		{

			int success =
			    init_process( proc_init[counter]._priority,
					  proc_init[counter]._code_size,
					  proc_init[counter]._data_size,
					  proc_init[counter]._run_time );

			if ( success )
			{
				counter++;
			}
		}
		scheduler(  );
	}
	while ( ( counter < 100 ) || ( empty_queues(  ) == 0 ) );
	printf( "All processes finished\n" );
}
