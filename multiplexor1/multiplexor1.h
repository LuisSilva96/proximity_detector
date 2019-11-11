# ifndef MULTIPLEXOR1_H
# define MULTIPLEXOR1_H

# include <systemc.h>

class Multiplexor1 : public sc_module
{
  public:
    sc_in<sc_uint<3> > rn_in, rd_in;
    sc_in<sc_uint<2> > ctrl_in;
    sc_out<sc_uint<3> > slct_out;

    SC_CTOR(Multiplexor1)
    {
      SC_METHOD(operation);
        sensitive << rn_in << rd_in;
    }

  private:
    void operation()
    {
      if(ctrl_in.read() == 3)
        slct_out.write(rn_in.read());
      else
        slct_out.write(rd_in.read());
    }

};

# endif
