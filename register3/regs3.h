# ifndef REGS3_H
# define REGS3_H

# include <systemc.h>
# include <iostream>

class Regs3 : public sc_module
{
	public:

		sc_in<bool> clk_in, enable_in;
		sc_in<sc_uint<3> > data_in;
		sc_out <sc_uint<3> > data_out;

		sc_uint<3> data;

		SC_CTOR(Regs3)
		{
			data = 0;

			SC_METHOD(reading_data);
				sensitive << clk_in.neg();

			SC_METHOD(writing_data);
				sensitive << clk_in.pos();
		}

	private:

		void reading_data()
		{
			if(enable_in.read() == true)
				data = data_in.read();
		}

		void writing_data()
		{
			data_out.write(data);
		}
};

# endif
