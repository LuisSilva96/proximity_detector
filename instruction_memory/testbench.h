# ifndef testbench_H
# define testbench_H

# include <systemc.h>
# include <iostream>

# define instruction_length 8

class testbench : public sc_module
{
	public:

		sc_in_clk clk;
		sc_in<sc_uint<instruction_length> > instr_in;

		sc_out<sc_uint<5> > dir_out;

		SC_CTOR(testbench)
		{
			SC_THREAD(test)
				sensitive << clk.neg();
				dont_initialize();
		}

	private:

	void test();
	void print();
};

# endif
