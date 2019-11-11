# ifndef testbench_H
# define testbench_H

# include <systemc.h>
# include <iostream>


class testbench : public sc_module
{
	public:

		sc_in_clk clk;
		sc_in<sc_uint<11> > data_in;
		sc_out<sc_uint<11> > data_out;
		sc_out<sc_uint<2> > op_out;
		sc_out<sc_uint<3> > dir_out;

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
