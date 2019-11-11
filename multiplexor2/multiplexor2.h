# ifndef MULTIPLEXOR2_H
# define MULTIPLEXOR2_H

# include <systemc.h>

class Multiplexor2 : public sc_module
{
  public:
    sc_in<sc_uint<11> > datamem_in, dataalu_in;
    sc_in<sc_uint<2> > ctrl_in;
    sc_out<sc_uint<11> > slct_out;

    SC_CTOR(Multiplexor2)
    {
      SC_METHOD(operation);
        sensitive << datamem_in << dataalu_in;
    }

  private:
    void operation()
    {
      if(ctrl_in.read() == 2 || ctrl_in.read() == 3)
        slct_out.write(dataalu_in.read());
      else
        slct_out.write(datamem_in.read());
    }

};

# endif
