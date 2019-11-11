# ifndef REGISTERFILE_H
# define REGISTERFILE_H

# include <systemc.h>

# define TAM_REG 5

class Register_file : public sc_module
{
  public:
    sc_in_clk clk_in;
    sc_in<sc_uint<2> > write_eneable_in;

    sc_in<sc_uint<3> > dirdata_in;
    sc_in<sc_uint<11> > data_in;

    sc_in<sc_uint<3> > dir_in;
    sc_out<sc_uint<11> > readn_out;
    sc_out<sc_uint<11> > reads_out;
    sc_out<sc_uint<11> > reade_out;
    sc_out<sc_uint<11> > reado_out;

    SC_CTOR(Register_file)
    {
      SC_METHOD(read);
        sensitive << clk_in.neg() << dir_in;


      SC_METHOD(write);
        sensitive << clk_in.pos() << write_eneable_in << dirdata_in << data_in;

      for(int i=0; i < TAM_REG; i++)
      {
        registers[i] = 255;
      }
    }

  private:
    sc_uint<11> registers[TAM_REG];

    void read()
    {
      readn_out.write(registers[0]);
      reads_out.write(registers[1]);
      reade_out.write(registers[2]);

      if(dir_in.read() == 3)
        reado_out.write(registers[4]);
      else
        reado_out.write(registers[3]);

      if(write_eneable_in.read() == 1)
        reado_out.write(registers[dir_in.read()]);
    }

    void write()
    {
      if(write_eneable_in.read() == 0 )
        registers[dirdata_in.read()] = data_in.read();
      else if(write_eneable_in.read() == 3)
        registers[4] = data_in.read();
    }
};

# endif
