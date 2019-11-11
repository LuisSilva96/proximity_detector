# ifndef TESTBENCH_MODULE
# define TESTBENCH_MODULE

# include <systemc.h>

class Testbench : public sc_module
{
public:
  sc_in<bool> clk_in;
  sc_in<sc_uint<11> > e_in;
  sc_out<sc_uint<11> > a_out, b_out, c_out, d_out;
  sc_out<sc_uint<2> > control_out; 

  SC_CTOR(Testbench);
  ~Testbench();

private:
  void test();
  void print();
};

# endif
