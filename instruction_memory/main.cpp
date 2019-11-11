#include<instruction_memory.h>
#include<testbench.h>

int sc_main(int argv, char* argc[])
{
	sc_time PERIOD(10,SC_NS);
	sc_time DELAY(10,SC_NS);	
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);
	
	sc_signal<sc_uint<5> > dir;
	sc_signal<sc_uint<instruction_length> > instruction;
	sc_signal<bool> enable;
	Instruction_Memory instruction_memory("instruction_memory");
	testbench tb("tb");
	
	instruction_memory.dir_in(dir);
	instruction_memory.instr_out(instruction);
	
	tb.dir_out(dir);
	tb.instr_in(instruction);
	tb.clk(clock);

	sc_start();
	
	return 0;
}
