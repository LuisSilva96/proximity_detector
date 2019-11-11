# ifndef TESTBENCH_H
# define TESTBENCH_H

# include <systemc.h>
# include <iostream>

class Testbench : public sc_module
{

  private:

    void test();
    void print();

  public:

    sc_in_clk clk_in;
    sc_out<bool> enable_out;
    sc_out<sc_uint<4> > pc_out;
    sc_in<sc_uint<11> > result_in;

    SC_CTOR(Testbench)
    {
			SC_THREAD(test);
				sensitive << clk_in.neg();
				dont_initialize();
    }

};

# endif
