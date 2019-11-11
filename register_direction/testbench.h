# ifndef TESTBENCH_H
# define TESTBENCH_H

# include <systemc.h>

class Testbench : public sc_module
{
  public:

    sc_in<bool> clk_in;
    sc_out<sc_uint<2> > write_eneable_out;
		sc_out<sc_uint<11> > data_out;
		sc_in<sc_uint<3> > data_in;

    SC_CTOR(Testbench)
    {
			SC_THREAD(test);
				sensitive << clk_in.neg();
				dont_initialize();
    }

  private:

    void test();
    void print();
};

#endif
