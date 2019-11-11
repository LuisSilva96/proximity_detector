#include<direction_memory.h>
#include<testbench.h>

int sc_main(int argv, char* argc[])
{
	sc_time PERIOD(10,SC_NS);
	sc_time DELAY(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	sc_signal<sc_uint<3> > dir_sg;
	sc_signal<sc_uint<2> > op_sg;
	sc_signal<sc_uint<11> > data_in_sg;
	sc_signal<sc_uint<11> > data_out_sg;
	Direction_Memory direction_memory("instruction_memory");
	testbench tb("tb");

	direction_memory.dir_in(dir_sg);
	direction_memory.op_in(op_sg);
	direction_memory.data_in(data_in_sg);
	direction_memory.data_out(data_out_sg);

	tb.dir_out(dir_sg);
	tb.op_out(op_sg);
	tb.data_in(data_out_sg);
	tb.data_out(data_in_sg);
	tb.clk(clock);

	sc_start();

	return 0;
}
